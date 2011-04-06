---
layout: doc_fr
title: Appendix B - Lectures conseillées
previous: Appendix A - Glossaire
previous_url: appendix-a-glossary
next: Terms Index
next_url: terms-index
review: true
---

Concevoir une machine virtuelle et implémenter un langage demande des connaissances. 
Le but de Rubinius est de repousser les frontières entre le langage et son implémentation,
en vous permettant de rester à l'intérieur de Ruby lui-même - 
et d'accéder à des ressources bas niveau. Mais avant que vous n'hackiez le 
Garbage Collector (système de nettoyage de la mémoire) vous devez comprendre
ce qui se passe sous le capot.

Cette page contient des références bibliographiques, imprimées ou en ligne, 
des adresses de blogs, et d'autres publications qui vous seront utiles 
pour travailler avec Rubinius.

NOTE : certains liens peuvent contenir des informations périmées à propos de Rubinius.

## Machine virtuelle

  * [Smalltalk-80: language and its implementation](http://tinyurl.com/3a2pdq)
    par Goldberg, Robson, Harrison (aka "The Blue Book"), les chapitres 
    sur l'implementation sont disponibles en ligne (http://tinyurl.com/6zlsd)
  * [Virtual machines](http://tinyurl.com/3ydkqg) par Iain D. Craig
  * Très bons articles d'Adam Gardiner: [introduction](http://tinyurl.com/35y2jh),
    [How send sites work](http://tinyurl.com/34c6e8)


## Collecte et nettoyage mémoire (Garbage collection)

  * [Garbage Collection: Algorithms for Automatic Dynamic Memory
    Management](http://tinyurl.com/3dygmo) par Richard Jones
  * [Garbage collection lectures](http://tinyurl.com/2mhek4)


## Primitives

  * [Ruby extensions and Smalltalk
    primitives](http://talklikeaduck.denhaven2.com/articles/2007/06/04/ruby-extensions-vs-smalltalk-primitives)
  * [Guide to Squeak
    primitives](http://www.fit.vutbr.cz/study/courses/OMP/public/software/sqcdrom2/Tutorials/SqOnlineBook_(SOB)/englisch/sqk/sqk00083.htm)


## FFI

  * [Implementing File#link using
    FFI](http://redartisan.com/2007/10/11/rubinius-coding)
  * [Rubinius' foreign function
    interface](http://blog.segment7.net/articles/2008/01/15/rubinius-foreign-function-interface)
