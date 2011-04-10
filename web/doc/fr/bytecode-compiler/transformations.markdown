---
layout: doc_fr
title: Transformations du compilateur
previous: Le compilateur
previous_url: bytecode-compiler/compiler
next: Le générateur
next_url: bytecode-compiler/generator
---

Le compilateur de bytecode possède un mécanisme simple pour transformer 
l'arbre syntaxique (AST). Ce mécanisme est basé sur la reconnaissance et la
substitution de certaines formes de l'arbre. La forme remplacée emet du bytecode
différent de la forme originale. Le code source pour ces substitutions se trouve
dans le fichier  lib/compiler/ast/transforms.rb.

TODO: document the compiler plugin architecture.



### La substitution sécurisée des formes Mathématiques

Comme les librairies du coeur de Ruby sont construit comme n'importe quel
autre code Ruby, et comme Ruby est un langage dynamique avec la possibilité de
rouvrir des classes et de fixer des liens "au dernier moment" (late binding)
il est possible de modifier des classes fondamentales comme Fixnum, d'une façon
qui viole la sémantique des classes qui en dépendent. Par exemple, imaginez
que nous ayons écrit ceci :

  class Fixnum
    def +(other)
      (self + other) % 5
    end
  end

[NdT cet exemple ne fonctionne pas tout à fait car il est récursif (stack level too deep)]

Comme il est possible de redéfinir l'addition comme une opération modulo 5,
les classes comme Array ne seront plus capable de calculer leur taille.
La nature très dynamique de Ruby est ce qui le rend attrayant, mais c'est un
avantage à double tranchant.

Dans la librairie standard, la librairie 'mathn' redéfinit Fixnum#/ (la division)
d'une manière "unsafe". La librairie fait un alias de Fixnum#/ vers Fixnum#quo,
et change le type de retour (de Float vers Rational).

A cause de cela, il y a un plugin spécial du compilateur qui emet 
des noms de méthodes différent quand il rencontre la méthode '#/'. 
Le compilateur emet un "#divide" au lieu d'un "#/". Les classes de nombres
définissent toutes cette méthode.

La manière sûre de procéder au transformation mathématique est d'activer le
plugin lors de la compilation des librairies faisant partie du "Core". 
Durant la compilation de code normal, le plugin n'est pas activé? 
Cela nous permet de supporter la librairie 'mathn' sans casser les
librairie du 'Core' ou de nous forcer à des pratiques génantes dans la compilation.

