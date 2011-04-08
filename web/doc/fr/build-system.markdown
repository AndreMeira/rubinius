---
layout: doc_fr
title: Construction (Build System)
previous: Specs - Compilateur
previous_url: specs/compiler
next: Bootstrap
next_url: bootstrapping
review: true
---

TODO: Many details are missing.

Rubinius utilise abondamment Rake comme systeme de construction (build system) de ses propres fichiers.
Cependant rubinius utilise également plusieurs librairies externes et donc utilise des fichiers makefile.  


## Build de developpement et build d'installation

Rubinius consiste dans son executable et son support de fichiers variés tel que 
les librairies "core" et "standard". L'executable a besoin de savoir où trouver les fichiers
même s'ils sont déplacés [lors de l'installation]. Pour résoudre ce problème,
Rubinius distingue deux types de "build" : developpement et installation (development and install).
L'executable conserve le chemin complet de son dossier de base, à partir duquel il s'attend
à trouver les fichiers dont il a besoin.

L'executable de developpement conserve le chemin du dossier source dans lequel 
il a été construit ("buildé"). Vous pouvez ensuite déplacé l'executable. Tant que vous
modifiez les fichiers dans le dossier kernel, ces changements seront visibles, 
car l'executable continuera d'utiliser ces fichiers.

L'executable d'installation (install executable) conserve le chemin du dossier d'installation.
Si l'executable est déplacer il saura où trouver malgré tout les fichiers installés.

Evidemment, cela a des conséquenses. Si vous construsiez un executable de developpement et
qu'ensuite vous renommez votre dossier source, vous devrez refaire votre build. De même
si vous construisez un executable d'installation et que vous renommez le répertoire, 
l'executable *ne* fonctionnera *plus*, et cela *même si vous n'avez pas déplacé l'executable*.
L'executable teste un unique chemin codé en dur au moment du build.
Si par la suite cela se révèle trop hadicapant, nous modifieront ce comportement.

## Installer Rubinius

Avant d'installer rubinius vous devez préciser dans quel dossier l'installer.

    ./configure --prefix=/path/to/install/dir

Le processus de configuration crée un fichier 'config.rb' qui spécifie les chemins 
importants utilisés par Rubinius. Une fois configuré, executez 'rake install'
pour construire (build) et installer Rubinius.
la procédure d'installation fait un build de tous les fichiers 
y compris ceux de la librairie standard de Ruby, situés dans le dossier lib/,
et les copies ensuite dans le répertoire d'installation en utilisant le programme 'install'.
Les tâches d'installation (install tasks) sont situés dans le dossier rakelib/install.rake.