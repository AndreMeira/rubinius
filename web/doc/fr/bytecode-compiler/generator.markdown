---
layout: doc_fr
title: Generateur
previous: Transformations
previous_url: bytecode-compiler/transformations
next: Personnaliser le pipeline du Compilateur
next_url: bytecode-compiler/customization
review: true
---

Une fois que Melbourne a créé l'arbre syntaxique (AST), il passe l'AST 
à l'étape du générateur.

A l'étape du Générateur est créé une nouvelle instance de 
`Rubinius::Generator`, et on demande à la racine de l'arbre de générer son 
bytecode sur l'objet `Generator`.

Un générateur fourni une pure Ruby DSL (domain specific language) qui permet 
de générer le bytecode Rubinius. En interne, le générateur fournit des 
méthodes qui correspondent (mapping) directement aux 
[instructions Rubinius](/doc/fr/virtual-machine/instructions/)
Par exemple, pour créer l'instruction de mettre nil sur la pile, vous pouvez 
appelez la méthode `push_nil` d'une instance de `Generator`.

La classe `Generator` fournit également un certain nombre de méthodes utiles
qui vous permettent de générer des motifs (patterns) fréquents de bytecode, 
sans que vous n'ayez à entrer dans les détails de très bas niveau des 
instructions Rubinius.

Par exemple, pour faire un appel de méthode ("un envoi de message") en 
utilisant du bytecode Rubinius directement, vous aurez besoin de créer une 
representation literale du nom de la méthode, et ensuite appeler `send_call` 
pour appeler la méthode.  De plus si vous souhaitiez appeler une méthode 
privée, vous auriez dû d'abord créer du bytecode qui permet spécifiquement les 
invocations de méthodes privées.  Si vous vouliez faire un appel privée, vous 
auriez dû faire:

    # ici, g est une instance de Generator
    g.allow_private
    name = find_literal(:puts)
    g.send_stack name, 0

En utilisant la méthode d'aide, vous pouvez le faire plus simplement:

    g.send :puts, 0, true

Lorsque le bytecode est généré pour l'arbre syntaxique (AST), Rubinius
invoke la méthode `bytecode` sur chaque noeud, en passant en argument 
l'instance du générateur courant. Voici la methode bytecode pour le
le noeud 'if'.

    def bytecode(g)
      pos(g)

      done = g.new_label
      else_label = g.new_label

      @condition.bytecode(g)
      g.gif else_label

      @body.bytecode(g)
      g.goto done

      else_label.set!
      @else.bytecode(g)

      done.set!
    end

D'abord, la méthode appelle la méthode `pos`, une méthode hérité de la 
classe Node de base, qui elle même appelle `g.set_line @line`. 
Ceci est utilisé par la machine virtuelle pour fournir des informations de
déboggage pendant l'execution de code. 

Ensuite, le code utilise le "helper" (methode d'aide) de label sur 
l'instance du générateur. Le bytecode brut de Rubinius n'a aucune 
structure de contrôle, mis à part `goto` et ses dérivés 
(`goto_if_true` et `goto_if_false`). Vous pouvez utiliser les racourcis
git (goto_if_true) ou gif (goto_if_false). 

Dans notre exemple, on crée 
deux nouveaux labels, un pour la fin de la condition `if`, et l'autre
pour marquer la début du bloc `else`.

Après avoir créer les deux labels, la noeud `if` invoque la méthode 
`bytecode` de son noeud enfant `@condition`, et lui passe l'instance
du générateur courant. Cela produira le bytecode de la condition dans le
flux courant.

Ce processus devrait laisser la valeur de la condition sur la pile,
et donc si le noeud `if` emet une instruction `goto_if_false` 
cela provoquera un saut immédiat vers le label `else_label`. On utilise
ensuite le pattern que l'on a déjà vu pour appeler le noeud enfant `@body`
et émettre ainsi son bytecode dans le flux courant. On émet ensuite
un goto inconditionnel (toujours réalisé) vers la fin de la condition.

Ensuite, nous avons besoin de marquer la position du label `else_label`.
En découplant la création du label de son utilisation, on peut lui passer
une instruction `goto` avant de connaître sa réelle position, ce qui
est crucial pour beaucoup de structure de contrôle.

Nous demandons maintenant au noeud `@else` d'emettre son bytecode et de 
marquer la position du label `done`.

Ce processus s'effectue récursivement depuis la racine à travers les
branches de l'arbre syntaxique (AST). Cela a pour conséquence de remplir
l'objet `Generator` avec le bytecode produit par l'AST en commençant par la 
racine.

Vous trouverez certainement utile de regarder les classes présente 
dans le dossier `lib/compiler/ast`, qui définissent tous les noeuds
de l'AST, et leur méthode `bytecode`associée. C'est également un bon 
moyen de voir des exemples pratiques de l'utilisation de l'API du 
`Generator`.

Une fois que le `Generator` a acquis la represention en bytecode de l'arbre 
syntaxique, il invoque l'étape suivante, l'étape d'encodage.

## Fichiers référencés

* *lib/compiler/generator_methods.rb*: Un fichier généré qui contient
   une enveloppe Ruby (Ruby wrapper) des instructions Rubinius. Ces méthodes
   correspondent directement aux 
   [InstructionsRubinius](/doc/en/virtual-machine/instructions/)
* *lib/compiler/generator.rb*: La définition de l'objet `Generator`.
   Cette classe mixe des méthodes de bas niveau et de plus haut niveau,
   pour générer certains motifs de bytecode.
* *lib/compiler/ast*: Contient la définition de tous les noeuds de l'AST
   créé à l'étape du Parseur.
   
## Personnalisation

La façon la plus simple de personnaliser l'étape de génération du processus
de compilation est de crée des instruction de haut niveau en plus des 
instructions communes fournis par l'implémentation par défaut du `Generator`.

Vous pouvez aussi personnaliser quelle classe de générateur est passée.
Pour apprendre davantage sur la personnalisation des étapes de compilations,
lisez 
[Personnaliser le pipeline du compilateur](/doc/fr/bytecode-compiler/customization/).

