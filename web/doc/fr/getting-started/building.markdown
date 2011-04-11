---
layout: doc_fr
title: Construire Rubinius (build)
previous:  Pré-requis
previous_url: getting-started/requirements
next: Executez Rubinius 
next_url getting-started/running-rubinius
---

Vous pouvez construire (build) et executez Rubinius depuis le dossier des 
sources. Vous n'aurez pas besoin d'installer Rubinius pour l'executer. 
Les instructions ci-dessous détailleront à la fois l'installation et 
l'execution de Rubinius depuis le dossier des sources.

Rubinius utilise LLVM comme compilateur JIT. Rubinius dépend d'une version
particulière de LLVM et LLVM doit être construit (build) avec C++ RTTI 
(runtime type information) d'activé.
Le script `configure` vérifiera automatiquement ce pré-requis quand il 
cherchera une version installée de LLVM. Si vous avez LLVM d'installé et que
Rubinius échoue à se lier à LLVM - pour quelques raisons que ce soit, 
ajoutez l'option  `--skip-system` à `configure`.


### Récupérer les sources

Le code source de Rubinius est disponible sous la forme d'un tarball et comme
projet sur GitHub. Vous pouvez 
[télécharger le tarball ici](http://rubini.us/download/latest).

Pour utiliser Git

  1. Placez vous dans votre répertoire de developpement.  
  2. executez `git clone git://github.com/evanphx/rubinius.git`


### Installez Rubinius

Si vous avez prévu de faire tourner votre application sous Rubinius, c'est 
une bonne option. Cependant, vous pouvez aussi executez Rubinius directement
depuis le dossier des sources. Voyez la section suivante pour plus 
d'information.


Nous recommendons d'installer Rubinius à un endroit qui ne nécessitera pas 
de sudo ou de privilège super utilisateur.


  1. executez `./configure --prefix=/path/to/install/dir`
  2. executez `rake install`
  3. Suivez les instructions pour ajouter répertoire bin de Rubinius 
     à votre variable PATH 

### Executez Rubinius depuis le dossier des sources

Si vous avez prévue de travailler sur Rubinius lui-même, vous devriez 
suivre ces instructions.


  1. `./configure`
  2. `rake`


Si vous souhaitez seulement essayer Rubinius, suivez les instruction pour
ajouter le dossier _bin_ Rubinius à votre PATH. parce que le build de Rubinius 
ira chercher `ruby` et `rake` pour les lier à l'executable Rubinius. 
Rubinius a besoin d'un ruby séparé pour le démarrage (bootstrap) pendant
le processus de construction (build) 


