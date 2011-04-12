---
layout: doc_fr
title: Pré-requis
previous: Pour commencer
previous_url: getting-started
next: Construction (build)
next_url: getting-started/building
---

Assurez vous d'avoir les programmes et librairies suivants d'installés.
Voyez aussi les sous-sections ci-dessous pour les pré-requis spécifiques à 
votre système d'exploitation.

Voici des suggestions pour obtenir davantage d'informations sur les programmes
et librairies requises pour construire Rubinius. Votre système d'exploitation
ou votre gestionnaire de paquets doivent avoir les paquets suivants

  * [GCC and G++ 4.x](http://gcc.gnu.org/)
  * [GNU Bison](http://www.gnu.org/software/bison/)
  * [MRI Ruby 1.8.7+](http://www.ruby-lang.org/) Si votre système n'a pas 
    Ruby 1.8.7 d'installé, utilisez [RVM](http://rvm.beginrescueend.com/)
    pour l'installer
  * [Rubygems](http://www.rubygems.org/)
  * [Git](http://git.or.cz/)
  * [ZLib](http://www.zlib.net/)
  * pthread - la librairie pthread devrait être installée.
  * [gmake](http://savannah.gnu.org/projects/make/)
  * [rake](http://rake.rubyforge.org/) `[sudo] gem install rake`


### Apple OS X

La façon la plus simple de récupérer un environemment de developppeur sur
OS X est d'installer les outils et utilitaires XCode. Une fois installé,
vous pouvez activer le mode de développement 'crash reporting' dans
/Developer/Applications/Utilities/CrashReporterPrefs.app


### Debian/Ubuntu

  * ruby-dev or ruby1.8-dev
  * libreadline5-dev
  * zlib1g-dev
  * libssl-dev
