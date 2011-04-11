---
layout: doc_fr
title: Etape d'encodage
previous: Etape de génération
previous_url: bytecode-compiler/generator
next: Etape d'empaquetage
next_url: bytecode-compiler/packager
---

Une fois que le générateur a traité l'arbre syntaxique (AST), on a
besoin d'encoder le bytecode. Cette étape est très simple, et principalement
effectué en vue de sauvegarde ("recordkeeping").

L'étape d'encodage est responsable de deux choses:

* convertir en séquence d'instruction le flux des instruction créées à l'étape 
  précédente (lorsque les noeuds de l'arbre syntaxique - AST - ont été 
  convertis en bytecode)
* s'assurer que la pile n'est pas sous alimentée (underflow), qu'elle ne 
  déborde pas (overflow), ou qu'elle ne contient pas de faute sémantique.

On effectue ces étapes sur l'objet Generator principal (main Generator object),
ainsi que sur tous les générateur enfants (générateur pour les blocks,
les méthodes et autres structures rencontrés à l'intérieur du corps principal).

Une fois cette étape terminée, on passe l'objet Generator encodé à l'étape 
suivante, l'empaquetage.

## Fichiers référencés

* *lib/compiler/generator.rb*: La méthode `encode` dans le fichier effectue
  la majeur partie du travail de cette étape.

## Personnalisation

Comme cette étape est très simple, vous n'aurez pas besoin de la 
personnalisée.  Vous souhaiterez peut-être agir dessus (par exemple, pour 
profiler ou imprimer). 
Regarder 
[Personnaliser le Pipeline du Compilateur](/bytecode-compiler/customization/)
pour une vue globale sur la personnalisation.
