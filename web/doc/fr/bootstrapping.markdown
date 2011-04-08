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

  4. platform: Le système FFI ("foreign function interface", interface pour les fonctions externes) 
     est implémenté et les interfaces de méthodes Ruby vers les fonctions dépendantes de la plateforme
     (le système d'exploitation) sont créées. Une fois ceci fait, on attache les spécificités
     liées à la plateforme, tel que les pointers, l'accès au fichiers, les librairies de calcul
     mathématiques, les commandes POSIX.

  5. common: La quasi totalité des classes faisant parties du coeur de Ruby sont implémentées. 
     On tente de conserver une implémentation la plus neutre possible de ces classes.
     Par ailleurs, la plupart des fonctionnalités des classes spécifiques à Rubinius sont ajoutées.
     
     
  6. delta: Les versions finales des méthodes telle que #attr_reader, etc. sont ajoutées. 
     Aussi, les implémentations spécfiques de ces méthodes - qui surchargent l'implémentation
     de base, sont ajoutées.
     
  7. loader: La version compilée de kernel/loader.rb est executé.

     La dernière étape règle les cycles de vie d'un processus Ruby. On commence par 
     connecter la machine virtuelle au système, configurer le load path 
     (chemin où sont cherché les fichiers ruby), et lire les scripts de personnalisation à la
     racine du dossier personnel de l'utilisateur (home directory). On capture les signaux systemes,
     et on traite les arguments fourni sur la ligne de command.

     Après ça, on execute le script passé sur la ligne de commande
     ou on charge le mode interactif ruby (ruby shell).
     Lorsque ceci se termine, on execute les blocks "at_exit" qui ont été enregistrés, 
     On "finalize" tous les objets, et enfin on quitte le processus.


## Ordre de chargement (load order)

Les fichiers présent dans les répertoires bootstrap, platform, common et delta,
dans le dossier kernel, implémentent respectivement les étapes du bootstrap ci dessus.
L'ordre de chargement à l'intérieur de chaque dossier est spécifié dans runtime/index.

Quant un fichier rbc est chargé, le code du script, et le code des classes et modules
est executé ([NdT] En ruby on défini une classe ou un module en executant du code). Par exemple,
si l'on charge : 

    class SomeClass
      attr_accessor :value
    end

l'appel à #attr_accessor sera executé. Ceci nécessite que n'importe quel appel au niveau du script
ou du corps d'une classe ou d'un module, soit défini avant le chargement du fichier. Le fichier
kernel/alpha.rb contient presque tous le code nécessaire pour executer un script ou définir une classe
ou un module. Cependant d'autres dépendances - lié au chargement (load order dependencies), 
existent entre les étapes platform, common, delta, et les fichiers du compilateur.  

Ces dépendances sont répertoriés dans un fichier load_order.txt présent dans chaque répertoire
du dossier kernel. Si vous modifiez du code qui ajoute une dépendance au chargement, vous devez
éditer le fichier load_order.txt et placer le nom du fichier au-dessus de celui qui en dépend.
Par ailleurs, si vous ajouter un nouveau fichier à l'un des répertoires du dossier kernel,
vous devez ajouter son nom au load_order.txt du répertoire.
Ces fichiers sont copiés dans le répertoire aproprié du dossier runtime pendant la phase de build. 
A chacune des étapes décrites précedemment, la machine virtuelle charge les fichiers lister dans 
load_order.txt dans l'ordre de leur apparation.