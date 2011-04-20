---
layout: doc_fr
title: Analyse de la mémoire
previous: Profileur
previous_url: tools/profiler
next: How-To
next_url: how-to
review: true
---

Rubinius fournit une interface pour dumper l'état courant du tas (heap) dans
un fichier, pour une analyse ultérieure. Plusieurs projets autour de Rubinius
analyse ce fichier et facilité la mise à jour des fuites mémoire (memory leak),
des collections trop grandes, et des problèmes relatif à la mémoire et à 
l'environnement d'execution.

## Un exemple

Le code suivant (sans vérification d'erreurs) servira de fondation à notre analyse 
des fuites mémoire en Ruby, et des fuites dans le code, en utilisant le sous 
système FFIb

Le code de cet exemple est un peu artificiel, mais illustre de multiples 
problèmes, que vous pourriez rencontrez dans la réalité. 
Admettons que ce code soit dans le fichier leak.rb.

    require 'rubygems'
    require 'ffi-rzmq' 
    
    if ARGV.length < 3
      puts "usage: ruby leak.rb <connect-to> <message-size> <roundtrip-count>"
      exit
    end
    
    link = ARGV[0]
    message_size = ARGV[1].to_i
    roundtrip_count = ARGV[2].to_i
    
    ctx = ZMQ::Context.new
    request_socket = ctx.socket ZMQ::REQ
    reply_socket = ctx.socket ZMQ::REP
    
    request_socket.connect link
    reply_socket.bind link
    
    poller = ZMQ::Poller.new
    poller.register_readable request_socket
    poller.register_readable reply_socket
    
    start_time = Time.now
    
    message = ZMQ::Message.new("a" * message_size)
    request_socket.send message, ZMQ::NOBLOCK
    i = roundtrip_count
    messages = []
    
    until i.zero?
      i -= 1
    
      poller.poll_nonblock
    
      poller.readables.each do |socket|
        message = ZMQ::Message.new
        socket.recv message, ZMQ::NOBLOCK
        messages << message
        socket.send ZMQ::Message.new(message.copy_out_string), ZMQ::NOBLOCK
      end
    end
    
    elapsed_usecs = (Time.now.to_f - start_time.to_f) * 1_000_000
    latency = elapsed_usecs / roundtrip_count / 2
    
    puts "mean latency: %.3f [us]" % latency
    puts "received #{messages.size} messages in #{elapsed_usecs / 1_000_000} seconds"

Ouhou! ce programme fuit comme une passoire. Essayons de mieux comprendre 
pourquoi.

## Sauvegarder l'état du tas (Saving A Heap Dump)

Rubinius fournit un accès à la machine virtuelle via une interface "agent".
L'agent ouvre une socket réseau et répond au commandes émises par le 
programme de la console. L'agent doit être démarré avec le programme.

    rbx -Xagent.start <script name>

Pour notre exemple, executer le programme avec l'agent activé:

    rbx -Xagent.start leak.rb

Connectez-vous à l'agent en utilisant la console rbx. Ce programme ouvre une
session interactive avec l'agent executé dans la machine virtuelle. Les 
commandes sont émises vers l'agent. En ce qui nous concerne, nous sommes entrain
de sauvegarder l'état du tas pour une analyse hors-ligne (offline analysis).

Au démarrage, l'agent écrit dans un fichier $TMPDIR/rubinius-agent.\<pid\> 
qui contient quelques détails important pour la console rbx. En quittant la
programme, l'agent nettoie ce fichier et le supprime. Dans certaines conditions
de crash, le fichier ne sera pas supprimé, et vous devrez le supprimer vous 
même.

    $ rbx console
    VM: rbx -Xagent.start leak.rb tcp://127.0.0.1:5549 1024 100000000
    Connecting to VM on port 60544
    Connected to localhost:60544, host type: x86_64-apple-darwin10.5.0
    console> set system.memory.dump heap.dump
    console> exit

La commande est `set system.memory.dump <filename>`. Le dump du tas est écrit
dans le dossier de travail courant pour le programme qui execute l'agent.

## Analyser le dump du tas

Le fichier résultant du dump du tas est écrit dans un format bien documenté.
Il existe deux outils capables de lire et  d'interpréter ce format. Ce sont
deux projets distincts du projet Rubinius.

Retrouverez l'outil heap\_dump [ici](https://github.com/evanphx/heap_dump).

Cet outil lit le fichier du dump et donne en sortie des informations utiles 
en trois colonnes, qui correspondent au nombre d'objet visible dans le tas,
à la classe de ces objets, et le nombre total d'octets occupés par les toutes
instances de ces objets.

Executez l'outil sur le dump du tas extrait du programme `leak.rb` ; il nous
donne une indication de l'endroit où la fuite se situe. 

    $ rbx -I /path/to/heap_dump/lib /path/to/heap_dump/bin/histo.rb heap.dump 
        169350   Rubinius::CompactLookupTable 21676800
        168983             FFI::MemoryPointer 6759320
        168978                   ZMQ::Message 8110944
        168978                    LibZMQ::Msg 6759120
         27901                Rubinius::Tuple 6361528
         15615                         String 1124280
         13527            Rubinius::ByteArray 882560
          3010                          Array 168560
           825                    Hash::Entry 46200
           787       Rubinius::AccessVariable 62960
            87                           Time 4872
            41                           Hash 3280
            12                   FFI::Pointer 480
             2                    ZMQ::Socket 96


Rien de ce qui est listé ci-dessus ne semble exagéré. Cependant, on remarque
les détails suivants:


1. L'empreinte la plus volumineuse est causée par `Rubinius::CompactLookupTable`,
qui est une classe jamais instanciée explicitement dans le code et qui occupe 
ici 20MB. On en conclut que certaines structures internes à Rubinius sont 
reportées dans le dump du tas. C'est intéressant, mais peu instructif pour 
notre fuite de mémoire. 

2. La classe `ZMQ::Message` présente à la troisième ligne est la première 
classe du rapport qui est explicitement instanciée dans le code de l'exemple.
Il y a près de 170ko occupés par des instances de cette classe. Il semble que
ce soit l'origine de la fuite. 

Parfois, un simple cliché (snapshot) n'est pas suffisant pour identifier 
l'origine de la fuite. Dans cette situation, nous devrions prendre plusieurs
clichés du tas à différents moment et laisser l'outil d'analyse faire une 
analyse de *diff*. Le *diff* nous montre ce qui a changé dans le tas *avant*
et *après*.  

    $ rbx -I /path/to/heap_dump/lib /path/to/heap_dump/bin/histo.rb heap.dump heap2.dump
    203110   Rubinius::CompactLookupTable 25998080
    203110                   ZMQ::Message 9749280
    203110                    LibZMQ::Msg 8124400
    203110             FFI::MemoryPointer 8124400

Le diff nous montre clairement que la source de la croissance de la mémoire 
utilisée. Le code a 200k de plus d'instances de `ZMQ::Message` entre le premier
et le second dump du tas. C'est donc de là que vient la fuite de mémoire.

Un examen du code nous montre les deux lignes coupables.

    messages << message
    ...
    puts "received #{messages.size} messages in #{elapsed_usecs / 1_000_000} seconds"

Il n'est probablement pas nécessaire de conserver tous les messages pour 
calculer le total à la fin. Nous pourrions simplement utiliser une variable
à incrémenter. Nous éviterions ainsi la fuite. 


## Outils avancés - OSX uniquement

Après avoir modifié le code afin d'utiliser un simple compteur et laisser le
garbage collector (collecte des déchets de la mémoire) traiter les instances
de `ZMQ::Message`, le programme continue d'occuper la mémoire de manière 
irrationnelle. En prenant deux clichés et en les analysant, nous n'avons pas
beaucoup d'indication quant à la source du problème. 

    $ rbx -I /path/to/heap_dump/lib /path/to/heap_dump/bin/histo.rb heap3.dump heap4.dump
      -4                          Array -224
     -90                 Digest::SHA256 -4320
     -90          Rubinius::MethodTable -4320
     -90                   Digest::SHA2 -3600
     -90          Rubinius::LookupTable -4320
     -90                          Class -10080
    -184                Rubinius::Tuple -29192


Ce diff montre qu'en effet certaines structure ont diminué entre les clichés.
Apparemment la fuite ne se trouve plus dans le code Ruby: la machine virtuelle
est incapable de nous dire ce qui consomme la mémoire.

Par chance, il existe un outil puissant sur Mac OS X appelé `leaks` qui peut
nous aider à déterminet l'origine du problème. La page de manuel
de malloc (`man malloc`) contient des informations sur une variable 
d'environnement qui fournit des détails supplémentaires au programme `leaks`,
comme la pile d'appel (stack trace) de chaque fuite.


    $ MallocStackLogging=1 rbx leak.rb tcp://127.0.0.1:5549 1024 10000000 &
    $ leaks 36700 > leak.out
    $ vi leak.out
    leaks Report Version:  2.0
    Process:         rbx [36700]
    Path:            /Volumes/calvin/Users/cremes/.rvm/rubies/rbx-head/bin/rbx
    Load Address:    0x100000000
    Identifier:      rbx
    Version:         ??? (???)
    Code Type:       X86-64 (Native)
    Parent Process:  bash [997]
    
    Date/Time:       2010-12-22 11:34:35.225 -0600
    OS Version:      Mac OS X 10.6.5 (10H574)
    Report Version:  6
    
    Process 36700: 274490 nodes malloced for 294357 KB
    Process 36700: 171502 leaks for 263427072 total leaked bytes.
    Leak: 0x101bb2400  size=1536  zone: DefaultMallocZone_0x100dea000
            0x01bb2428 0x00000001 0x00000400 0x00000000     ($..............
            0x00000000 0x00000000 0x00000000 0x00000000     ................
            0x00000000 0x00000000 0x61616161 0x61616161     ........aaaaaaaa
            0x61616161 0x61616161 0x61616161 0x61616161     aaaaaaaaaaaaaaaa
            0x61616161 0x61616161 0x61616161 0x61616161     aaaaaaaaaaaaaaaa
            0x61616161 0x61616161 0x61616161 0x61616161     aaaaaaaaaaaaaaaa
            0x61616161 0x61616161 0x61616161 0x61616161     aaaaaaaaaaaaaaaa
            0x61616161 0x61616161 0x61616161 0x61616161     aaaaaaaaaaaaaaaa
            ...
            Call stack: [thread 0x102f81000]: | thread_start | _pthread_start | 
            thread_routine | zmq::kqueue_t::loop() | zmq::zmq_engine_t::in_event() | 
            zmq::decoder_t::eight_byte_size_ready() | zmq_msg_init_size | malloc | 
            malloc_zone_malloc

La sortie montre qu'au moment du cliché nous avons presque 172ko d'objets 
dû à la fuite. La pile d'appel montre que la fuite de mémoire est apparue à 
l'appel de `zmq_msg_init_size`, ce qui ne signifie pas grand chose avant que 
nous creusions un peu dans l'implémentation de `ZMQ::Message`. C'est ici que 
la connaissance du système sous-jacent est essentiel ; il serait beaucoup plus 
difficile de traquer le problème sans savoir où cet appel est fait.

Il s'avère que `ZMQ::Message` alloue de la mémoire via `malloc` qui n'est pas
traquer par le garbage collector (GC) de Rubinius. Il a besoin d'être 
explicitement désalloué. 

Un appel approprié à `ZMQ::Message#close` dans notre code resoud le problème 
de mémoire.
