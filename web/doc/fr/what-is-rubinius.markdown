---
layout: doc_fr
next: Pour commencer
next_url: getting-started
---

## Qu'est-ce que Rubinius ?

Rubinius est une implémentation du langage de programmation 
[Ruby](http://ruby-lang.org).

Rubinius comprend une machine virtuelle à bytecode, un parseur syntaxique,
un garbage collector générationnel, un compilateur de bytecode "just-in-time",
et les librairies "Core" et "Standard" de Ruby.

Rubinius implémente pour l'instant la version 1.8.7 de Ruby.

## Licence

Rubinius utilise la licence BSD. Reportez vous à cette licence dans le code source.

## Installation

Rubinius tourne sous Mac OS X, et beaucoup de système d'exploitation UNIX/LINUX.
Le support de Microsoft Window arrivera sous peu.

Pour installer Rubinius, suivez les étapes suivantes. Pour de plus amples 
informations, reportez vous à [Pour commencer](/doc/fr/getting-started/).


1. `git clone git://github.com/evanphx/rubinius.git`
1. `cd rubinius`
1. `./configure --prefix=/path/to/install/dir`
1. `rake install`

Une fois le processus d'installation terminé, suivez les instructions pour 
ajouter l'executable Rubinius à votre PATH.

Rubinius vient avec RubyGems nativement et possède rake ainsi que rdoc pré-installés.
Pour installer le gem nokogiri, par exemple, executez `rbx gem install
nokogiri`.