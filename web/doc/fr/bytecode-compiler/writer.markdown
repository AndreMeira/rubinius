---
layout: doc_fr
title: Etape d'écriture
previous: Etape d'empaquetage
previous_url: bytecode-compiler/packager
next: Transformations
next_url: bytecode-compiler/transformations
---

Une fois que le packager a créé la CompiledMethod, Rubinius écrira
la méthode dans un fichier pour une future consommation. Par exemple,
après qu'un fichier ait été inclus une première fois, les inclusions
ultérieures chargeront le fichier à partir du disque, plutôt que de charger 
le code Ruby, de le parser à nouveau et le compiler.

Cette étape est extrèmement simple. Elle prend le nom du fichier original,
lui ajoute un `c` à la fin, et appelle Rubinius::CompiledFile.dump avec
la CompiledMethod reçu de l'étape précédente et le nom du fichier à écrire.

Une fois l'écriture terminée, l'entrée est retournée (la CompiledMethod) 
et devient la valeur de retour du tout le processus de compilation.

## Fichiers référencés

* *lib/compiler/compiled_file.rb*: L'implémentation de CompiledFile.
  `CompiledFile.dump` est appelé dans le but de "dumper" la  CompiledMethod 
  courante.
  
## Personnalisation

Cette étape est en fait optionnelle, et n'est utilisée que lorsque des
fichiers sont compilés. Quand une chaine est compilée, comme avec un 
appel à `eval` cette étape est sautée. Dans ce cas, le compilateur 
s'arrête à l'étape d'empaquetage (Packaging) et retourne la CompiledMethod 
de cette étape comme valeur de retour du compilateur.

Grâce à l'architecture du compilateur Rubinius, il est facile d'ajouter
des étapes supplémentaires à la fin du processus, et tant que ces étapes
retourne la CompiledMethod qu'elles ont reçu en entrée (ou une autre
CompiledMethod), tout fonctionnera comme prévu.

Pour plus d'information, voyez [personnaliser le pipeline du compilateur]
(/bytecode-compiler/customization/).
