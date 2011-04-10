---
layout: doc_fr
title: L'analyseur grammatical (Ruby Parser)
previous: Le compilateur de bytecode
previous_url: bytecode-compiler
next: AST
next_url: bytecode-compiler/ast
review: true
---

La première étape du pipeline de compilation est l'étape du Parseur Ruby.
Le parseur Ruby peut recevoir aussi bien une chaine de caractères qu'un
fichier. A partir de cette entrée, il construit un arbre syntaxique (AST)
à l'étape suivante, l'étape de génération.

Le parser en lui même (appelé Melbourne) possède une partie en C, qui 
correspond essentiellement au parser MRI, et une partie en Ruby. Cette 
dernière partie est responsable de la construction de l'arbre syntaxique (AST).
La partie en C communique avec la partie en Ruby en appelant une méthode
pour chaque noeud au cours de l'analyse de l'arbre.

Chacune de ces méthode a une signature qui contient toutes les informations
sur la partie de l'arbre qui est en cours d'analyse. Par exemple, 
si le code sous jacent contient un `if`, le parser C appelera la méthode
`process_if` avec le numéro de ligne, un paramètre représentant la condition,
et un paramètre qui représente le corps du `if` et la partie `else`,
s'il y en a une.

    def process_if(line, cond, body, else_body)
      AST::If.new line, cond, body, else_body
    end

Vous pourrez voir tous les appels possible aux méthode du type `process_`
dans le fichier `lib/melbourne/processor.rb` du code source de Rubinius.

Notez que dans beaucoup de cas, le parser passe le résultat d'un précédent
appel à une méthode `process_` comme argument d'une méthode `process_`. 
Dans le cas de `true if 1`, le parser appelle d'abord `process_lit(line 1)`
et `process_true(line)`. Il appelle également `process_nil(line)`, parce que 
l'arbre original contient un `nil` comme corps du `else`. Il appelle ensuite
`process_if` avec le numéro de ligne, le résultat de `process_lit`, le résultat
de `process_true`, et le resultat de `process_nil`.

Le processus construit récursivement la structure de l'arbre, que Rubinius
passera à l'étape suivante: l'étape de génération.

## Fichiers référencés

* *lib/melbourne/processor.rb*: L'interface Ruby du parser C. Ce fichier
   contient les méthodes commençant par `process_`, que le parser C appelle
   pour chaque noeud de l'arbre d'analyse brut.
* *lib/compiler/ast/\**: Les définitions de chaque noeud de l'arbre syntaxique (AST)
   utilisé par Melbourne.
  
## Personnalisation

Il y a deux façon de personnaliser cette étape de la compilation. 
La plus simple est de  [transformer l'AST](/bytecode-compilation/transformations/)., 

Vous pouvez aussi définir une sous-classe du processeur Melbourne, et définir
vos propres "handlers" pour les méthodes `process_`. Ceci est une technique avancée
qui n'est pas encore documentée.

