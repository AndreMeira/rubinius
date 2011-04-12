---
layout: doc_fr
title: Résolution des problèmes
previous: Executez Rubinius
previous_url: getting-started/running-rubinius
next: Contribuez
next_url: contributing
---

Vous trouverez ici les erreurs que vous pourriez rencontrer en construisant 
(build), en installant, ou en executant Rubinius, et des conseils pour les 
résoudre. 


Le premier réflexe est de s'assurer que vous avez la version courante, 
et propre de Rubinius. Avant d'aller plus loin, suivez les étapes suivantes:

    $ git co master
    $ git reset --hard
    $ git pull
    $ rake distclean
    $ rake


### Rubinius ne trouve pas le répertoire d'execution (`runtime directory`)

  Après avoir construit (build) ou installé Rubinius, vous tombez sur les 
  erreurs suivantes quand vous essayez d'executer Runbinius.
  
    ERROR: unable to find runtime directory 


    Rubinius was configured to find the runtime directory at:

      /Users/brian/devel/rubinius/runtime

    but that directory does not exist.

    Set the environment variable RBX_RUNTIME to the location
    of the directory with the compiled Rubinius kernel files.

    You may have configured Rubinius for a different install
    directory but you have not run 'rake install' yet.

#### Solution:

  Si vous avez configuré Rubinius avec `--prefix`, executez rake install.V

  Si vous avez configuré Rubinius avec `--prefix` et renommez le dossier
  après avoir installé Rubinius, re-configurez Rubinius, et réinstallez-le.

  Si vous avez renommé le dossier des sources après avoir construit (build)
  Rubinius, re-configurez-le et reconstruisez-le (build)

  En général, ne renommez pas le dossier de construction (build) ou 
  d'installation après avoir construit ou installé Rubinius.


### Segfaults pendant la construction (build) de Rubinius sur FreeBSD

  Sur FreeBSD, version 8.1 stable comprise, il y a un problème avec execinfo
  qui provoque une segfault (erreur de segmentation) quand Rubinius est 
  chargé.

#### Solution:

  Désactivez execinfo quand vous configurez Rubinius

    ./configure --without-execinfo
