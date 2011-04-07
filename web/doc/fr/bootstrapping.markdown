---
layout: doc_fr
title: Démarrage (Bootstrapping)
previous: Construction (Build System)
previous_url: build-system
next: Machine virtuelle
next_url: virtual-machine
---

Le bootstrap est le process de construction des fonctionnalités requises par le système
avant que du code Ruby puissent être executé. Le bootstrap comporte sept étapes.

 
  1. VM: La machine virtuelle est capable de charger et d'executer du bytecode, d'envoyer
     des messages (c'est-à-dire rechercher et executer des methodes). Toutes les 
     fonctions primitives sont disponibles, bien que pas encore "branchées" en tant que 
     méthodes Ruby.

     Aussitôt après, la classe "Class" doit être manuellement configurée - 
     de telle sorte qu'elle soit sa propre classe, et qu'elle ait la classe 
     Module pour classe parente (superclass).
     En plus des classes "Class" et "Module", un certains nombre d'autres classes,
     dont Object, Tuple, LookupTable, et MethodTable, sont créées.
     
     Maintenant que ces classes ont été définies, à peu près 35 classes natives (built-in)
     reçoivent l'ordre de s'initialiser, les symboles (:object_id, :call,
     :protected, etc) pour les méthodes de haut-niveau (top level methods) sont créés,
     les expressions de base sont définies, les primitives sont enregistrées. 
     Enfin, les entrées/sorties (I/O) sont branchées. C'est également à cette étape
     que les plusieurs methodes fondamentales de Ruby sont liées aux primitives.
     
     A partir de là, les comportements sont suffisamment définis pour commencer à charger
     le reste du noyau de l'environnement d'execution (kernel runtime) qui est 
     entièrement défini en ruby. Cela doit être réalisé en plusieurs passe afin
     d'enrichir le langage progressivement.

  2. alpha: C'est ici qu'on commence à chargé le code Ruby. On peut désormais
     ouvrir des classes et modules, et définir des méthodes. Le support des méthodes suivantes
     est implémenté dans kernel/alpha.rb:
     
       attr_reader :sym
       attr_writer :sym
       attr_accessor :sym
       private :sym
       protected :sym
       module_function :sym
       include mod

     Par ailleurs, il est possible de lancer une exception et de mettre fin au processus en cours (exit). 
     Cette étape pose les fondations nécéssaires aux deux prochaines étapes.
     
     
  3. bootstrap: cette étape continue d'ajouter les fonctionnalités minimum 
     requises pour charger la plateforme. Les fonctions primitives sont ajoutées à la
     plupart des classes du noyau.

  4. platform: The FFI (foreign function interface) system is implemented and
     Ruby method interfaces to platform-specific functions are created.  Once
     this is set up, platform specific things such as pointers, file access,
     math, and POSIX commands are attached.

  5. common: The vast majority of the Ruby core library classes are
     implemented. The Ruby core classes are kept as implementation-neutral as
     possible. Also, most of the functionality for Rubinius specific classes
     is added.

  6. delta: Final versions of methods like #attr_reader, etc. are added. Also,
     implementation-specific versions of methods that override the versions
     provided in common are added.

  7. loader: The compiled version of kernel/loader.rb is run.

     The final stage sets up the life cycle of a ruby process. It starts by
     connecting the VM to the system, sets up load paths, and reads
     customization scripts from the home directory. It traps signals, and
     processes command line arguments.

     After that, it either runs the script passed to it from the command line
     or boots up the interactive ruby shell. When that finishes, it runs any
     at_exit blocks that had been registered, finalizes all objects, and
     exits.

## Load Order

The files in the kernel directories bootstrap, platform, common, and delta,
implement the respective bootstrapping stages above. The order in
which these directories are loaded is specified in runtime/index.

When an rbc file is loaded, code at the script level and in class or module
bodies is executed. For instance, when loading

    class SomeClass
      attr_accessor :value
    end

the call to #attr_accessor will be run. This requires that any code called in
script, class, or module bodies be loaded before the file that calls the code.
The kernel/alpha.rb defines most of the code that will be needed at the script
or module level. However, other load order dependencies exist between some of
the platform, common, delta, and compiler files.

These load order dependencies are addressed by the load_order.txt file located
in each of the kernel/\*\* directories. If you modify code that adds a load
order dependency, you must edit the load_order.txt files to place the depended
on file above the file that depends on it. Also, if you add a new file to one
of the kernel directories, you must add the file name to the load_order.txt
file in that directory. These files are copied to the appropriate runtime/\*\*
directories during build. During each of the bootstrap stages above, the VM
loads the files listed in load_order.txt in order.
