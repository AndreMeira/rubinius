---
layout: doc_fr
title: Variables Globales
previous: Variables de Classe
previous_url: ruby/class-variables
next: Specs
next_url: specs
review: true
---

Syntaxiquement, une variable globale est une variable dont le nom commence
par un `$`. Les variables globales sont sensé être disponibles depuis 
n'importe quel contexte d'un programme Ruby. Il y a en fait trois type de
globales : les "vraies" globales, les globales locales à un thread, et 
les pseudos globales, 

Les vrais globales associent une valeur à un nom global (global name) comme
`$LOAD_PATH`.

Les globales de Thread ont une syntaxe identique aux vraies globales, mais 
ont une existence séparée de tel sorte qu'il existe une version de la globale
dans chaque thread du processus. 
`$SAFE` et `$!` sont des exemples de variables globale localement au thread.
Pour vérifier que ces valeur dépendent du thread, examinez le résultat du 
code suivant:

    puts $SAFE

    Thread.new do
      $SAFE = 2
      puts $SAFE
    end

    puts $SAFE

Les pseudos globales sont un sous ensemble strict de noms qui ne se réfèrent
pas à des valeurs globales mais à des valeurs liées à la portées courantes,
de la même manière que les variables locales. Elles sont toujours considérées
comme globales car elles commencent aussi par un dollar, ce qui constitue 
une source de confusion pour les utilisateurs.

Toutes les pseudos globales sont organisées autour de la pseudo globale
`$~`. Elles procèdent toutes de `$~` et lorsque que `$~` change, elles
changent toutes également.

Ces pseudo globales sont:  `$&`, <code>$`</code> (backtick), `$'` (guillemet
simple), `$+`, et `$1`, `$2`, `$3`, etc.

L'astuce réside en cela que ces valeurs sont lié strictement à la portée 
courante mais que Ruby autorise des alias imitant des globales, comme 
cela est fait dans English.rb. 

Ces nouveaux alias ajoute de nouvelles variables locales dans toutes les 
portées, même celle qui sont en cours d'execution. Rubinius ne supporte pas
complètement ce comportement. A la place nous fournissons les alias présent
dans English.rb par défault. Par exemple $MATCH peut être utilisé à la place
de `$~` que English.rb soit inclus ou pas.
