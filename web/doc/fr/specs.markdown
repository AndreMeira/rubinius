---
layout: doc_fr
title: Specs
previous: Ruby - Les variables globales
previous_url: ruby/global-variables
next: RubySpec
next_url: specs/rubyspec
---

Le projet Rubinius suit en général le type de spécifications logicielles TDD-BDD 
(develeoppement conduit par test, developpement conduit par le comportement) 
pour conduire les développement. Le dossier spec de Rubinius est conceptuellement
divisé en deux parties. 

  1. Tous les fichiers dans './spec/ruby' décrivent le comportement de 'MatzRuby'
  2. Tous les fichiers dans './spec' décrivent le comportement de Rubinius. 
  

Les specs présentes dans ./spec/ruby sont une copie des RubySpec à une révision donnée.
Elles sont régulièrement importées depuis le projet RubySpec. Les specs qui échouent
sont taggées et ainsi le processus de CI execute en permanence un large ensemble de specs.
Ceci permet de s'assurer en partie que des changements du code de Rubinius 
ne provoquera pas de régressions.

La documentation à propos de l'organisation des specs et des conventions pour 
écrire des specs peuvent être trouvées ici: [RubySpec project](http://rubyspec.org/).

Utilisez le workflow suivant lorsque vous ajoutez des specs et du code à Rubinius.

  1. Ecrivez des specs qui définissent un aspect du comportement de Ruby.
     Commitez les specs (dans un commit à part) dans le dossier aproprié dans ./spec/ruby
  2. Ecrivez le code qui permette de passer les specs. Une fois encore,
     commitez les modification séparément du commit des specs.  
  3. Executez la commande `rake` pour s'assurer que toutes les specs du CI passent.

Les modifications des fichiers de ./spec/ruby sont régulièrement pushé dans le projet
RubySpec. Aussi, les modification courantes apportés à RubySpec de la part des committers
d'autres implémentations de Ruby sont régulièrement mis à jour, dans le dossier
./spec/ruby. Lorsque les specs sont mis à jour depuis RubySpec, le tag CI est 
également mis à jour.