---
layout: doc_fr
title: Comment corriger une spec
previous: Ecrire une spec Ruby
previous_url: how-to/write-a-ruby-spec
next: Ecrire un test de performance (Benchkmark)
next_url: how-to/write-benchmarks
---

Assurez-vous d'avoir lu:


  *  [Pour commencer]({{ page.lang_dir }}getting-started/)
  *  [Specs]({{ page.lang_dir }}specs/)

Ensuite, lisez ceci pour corriger une spec:

  1.  executez `rake` pour être sûr que toutes les specs CI passent.
  2.  executez `bin/mspec spec/some/spec_file.rb` pour confirmer que la spec
      que vous voulez corriger échoue.
  3.  éditez le fichier que vous tenez pour responsable (probablement un 
      fichier dans le répertoire du Kernel).
  4.  executez `rake build` pour que vos changements soient pris en compte
  5.  executez `bin/mspec spec/some/spec_file.rb`pour voir si vos 
      modifications ont corrigé la spec, sinon :
  6.  répétez ces opérations jusqu'à ce que ce soit le cas
  7.  executez `rake` pour être sûr qu'il n'y a pas de régression
  8.  placez vous à la racine de Rubinius, si vous n'y étiez pas déjà
  9.  executez `git status, git add, git commit`, etc. Toute modification
      apportée aux fichiers de la spec et qui se trouvent dans le répertoire
      spec/ruby doit être commitée dans un commit différent que le commit
      des changements apportés aux autres fichiers sources de Rubinius.
  10. executez `git format-patch origin, ce qui extraira les commits faits
      sur la branche courante depuis le dernier pull de l'origine, ou 
      `git format-patch -N', où N représente le nombre (1, 2, etc) de commits
     que vous souhaitez inclure dans le patch
  11. créez un gist avec votre patch et lié-le à un ticket sur le tracker
      à l'adresse http://github.com/evanphx/rubinius/issues. Vous pouvez
      ajouter plusieurs patchs dans un ticket.

Quand votre patche est accepté par le projet Rubinius, vous recevrez un 
'commit bit' pour le dépôt Rubinius. Tenez Evan informer de votre nom 
d'utilisateur Github.
