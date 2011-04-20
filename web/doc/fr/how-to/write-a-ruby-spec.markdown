---
layout: doc_fr
title: How-To - Ecrire une RubySpec
previous: Ecrire un ticket
previous_url: how-to/write-a-ticket
next:  Corriger une spec
next_url: how-to/fix-a-failing-spec
---
Assurez-vous d'avoir lu:

  *  [Pour commencer](/doc/fr/getting-started/)
  *  [Specs](/doc/fr/specs/)

Puis, suivez ces étapes pour écrire une spec sur une méthode Ruby

  1. Editez un fichier dans le répertoire `spec/ruby/...`
  2. Executez `bin/mspec -tr spec/ruby/some/spec_file.rb`
  3. Répétez tant que la spec passe dans l'implémentation MatzRuby
  4. Commitez vos modifications
  5. Utilisez `git format-patch`
  6. Créer un gist avec votre patch et liez le au ticket dans le tracker à
      <http://github.com/evanphx/rubinius/issues>. 

