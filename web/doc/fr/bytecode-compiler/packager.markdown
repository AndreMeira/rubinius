---
layout: doc_fr
title: L'étape de l'empaquetage
previous: L'étape de l'encodage
previous_url: bytecode-compiler/encoder
next: L'étape d'écriture
next_url: bytecode-compiler/writer
---

Une fois que le générateur a été proprement encodé à l'étape d'encodage,
Rubinius empaquette (package) le bytecode comme une "CompiledMethod" 
(méthode compilée) en créant une nouvelle CompiledMethod 
et en configurant un certain nombre de ses propriétés.

Ces propriétés sont disponibles sur n'importe quelle CompiledMethod.
Vous pouvez récupérer la CompiledMethod d'une méthode d'un objet Ruby
en appelant sa méthode `executable` (NdT les méthodes sont aussi des objets). 

* *iseq*: un Tuple qui contient la séquense brute des instructions
* *literals*: un Tuple qui contient les littéraux utilisés par la méthode.
  Les littéraux sont utilisés de manière interne par Rubinius pour les 
  valeurs comme les chaînes de caractères, et sont utilisés par les 
  instructions `push_literal` et `set_literal`.
* *lines*: un Tableau (Array) qui contient le pointeur sur la première 
  instruction du bytecode pour chaque ligne de code.
* *required_args*: le nombre d'arguments requis par la méthode
* *total_args*: le nombre total d'arguments, y compris les arguments 
  facultatifs mais d'argument "splat" (syntaxiquement écrit `*args`)
* *splat*: la position d'un argument "splat", s'il y en a
* *local_count*: le nombre de variables locales, dont les paramètres
* *local_names*: un Tuple qui contient la liste des noms de toutes les 
  variables locales
  Les premiers noms seront les arguments requis, optionels, splat et block 
  dans cet ordre.
* *file*: le nom du fichier qui sera utilisé dans les informations de 
  déboggage.
* *name*: le nom de la méthode.
* *primitive*: le nom de la primitive associée à cette méthode
* metadata: il est possible de conserver des structures additionnelles 
  qui contiennent des métadonnées (metadata) sur la méthode compilée. 
  La méthode compilée possède une métadonnée nommée `for_block`
  qui vaut `true` si le générateur original a été créé pour un "block".
  
L'étape d'empaquetage (Packager stage) s'assure également que tous 
les enfants générateurs (comme les générateurs pour les block et méthodes)
sont convertis en méthodes compilées. Ces méthodes compilés "enfants" 
sont inclus dans le tuple des litéraux de la méthode compilée parente.

Une fois que le générateur a finis de s'empaqueter dans une CompiledMethod,
il invoque l'étape d'écriture, en passant la CompiledMethod en entrée.

## Fichiers référencés

* *kernel/bootstrap/compiled_method.rb*: L'implémentation basique de 
   CompiledMethod, principalement composée de branchement vers les 
   primitives.
* *kernel/common/compiled_method.rb*: une implémentation plus robuste
   de CompiledMethod, une combinaison de primitives et de méthodes
   écrites en Ruby.
* *vm/builtin/compiledmethod.cpp*: l'implémentation en C++ 
  des primitives CompiledMethod.
* *lib/compiler/generator.rb*: L'implémentation de la méthode 
  `package`, qui remplit la CompiledMethod avec les informations
  de l'objet générateur.

## Personnalisatin

En général, la méthode `package` est conçu pour remplir la CompiledMethod 
avec un group de variables. Cependant, vous pouvez aussi utiliser le 
"packager" pour remplir un autre objet avec la même interface. Mais, cela ne 
sera pas forcément très utile en soi, sans d'autres personnalisations 
ultérieures.
