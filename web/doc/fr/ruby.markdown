---
layout: doc_fr
title: Ruby
previous: Style Guide
previous_url: contributing/style-guide
next: Scripts
next_url: ruby/scripts
review: true
---

Comprendre comment rubinius implémente ruby suppose que l'on comprenne
la façon dont ruby fonctionne et les concepts qu'il propose. Le but de ce 
sujet est de vous introduire aux features Rubinius à travers des concepts de Ruby -
qui devraient déjà vous être familier. La documentation de Rubinius suppose que
vous n'êtes pas étranger à Ruby, et aux concepts relatifs aux machines virtuelles
et à la compilation.

Le concept de _portée_ (scope) est au centre de tous les topics suivants. Dans la syntaxe Ruby,
la scope est généralement un concept dérivé. Ou pour dire autrement, il n'y a pas
de marqueur syntaxique qui délimite une portée. Cela peut parfois prêter à confusion.
Un exemple de cette possible confusion est donné dans l'exemple suivant :

    a = 5

    def diligent(a)
      puts a * 2
    end

Ici, la méthode `#diligent` nous donne un nom auquel se référer pour l'opération
`puts a * 2`. Mais la méthode définit également une portée lexicale pour la variable a.
La portée est fermée car la ligne `a = 5` au dessus n'exerce aucune influence. La variable
'a' de cette ligne et celle de la méthode sont complétement distinctes.

Souvent, il est dit que tout en Ruby est objet. Ce n'est pas tout à fait vrai.
Presque tout en Ruby est objet, mais certaines choses, essentielles
pour le fonctionnement de Ruby, ne sont pas nécessairement des objets que vous 
pouvez toucher du doigt. Des choses comme l'environnement d'execution sont 
des objets qui dépendent très largement de l'implémentation. La portée est 
également l'une de ces choses.

La portée est un concept qui permet de répondre au question telle que :
"Quelle est la valeur de 'self' ici ? Quelles sont les variables locales existantes ?
Quelle sera la valeur de la constante `APPLE` à cet endroit du code ?"

Les éléments Ruby suivants sont discuté à travers la manière dont Rubinius 
les comprend et les implémente, et la façon dont le concept de portée est impliqué dans
chacun.

1. [Scripts](/doc/fr/ruby/scripts/)
1. [Methodes](/doc/fr/ruby/methods/)
1. [Constantes](/doc/fr/ruby/constants/)
1. [Classes & Modules](/doc/fr/ruby/classes-and-modules/)
1. [Blocks & Procs](/doc/fr/ruby/blocks-and-procs/)
1. [Variables Locales](/doc/fr/ruby/local-variables/)
1. [Variables d'Instance](/doc/fr/ruby/instance-variables/)
1. [Variables de Class](/doc/fr/ruby/class-variables/)
1. [Variables Globales](/doc/fr/ruby/global-variables/)
