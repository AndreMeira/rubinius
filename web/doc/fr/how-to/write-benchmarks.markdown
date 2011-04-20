---
layout: doc_fr
title: How-To - Ecrire un test de performance (Benchmark)
previous: Corriger un Spec
previous_url: how-to/fix-a-failing-spec
next: Ecrire un article dans un Blog
next_url: how-to/write-a-blog-post
---

Pourquoi tester la performance ?

Les benchmarks (test de performances) sont des outils puissants pour comparer
Rubinius aux autres environnement d'execution et implémentation, c'est-à-dire
à MRI, JRuby, IronRuby. Il ne s'agit pas tant de mesurer Rubinius lui-même,
donc si vous voulez participer à l'écriture de benchmarks, suivez les étapes
suivantes :



  1.  Trouvez un benchmark existant dans rubinius/benchmarks et étudiez-le. 
  2.  Tous les benchmarks devraient mesurer un aspect spécifique de Ruby.
      Par exemple les différentes façon de supprimer des paires clé/valeur 
      d'un Hash.
  3.  Utilisez le framework benchmark.  
  4.  Faites un test simple et court. 
  5.  Les benchmarks ne sont pas censé mesurés Rubinius. Donc si vous écrivez
      un test pour une classe avec une methode destructive (généralement elle
      se termine par '!') et non destructive, vous voudrez sans doute utilisez 
      une variable dupliquer pour la méthode destructive, mais vous n'avez pas
      besoin d'une copie pour la version non destructive. 

Si vous voulez tester un benchmark vous pouvez executer le fichier qui contient
le benchmark ou même le répertoire entier:

Vous pouvez executer un benchmark particulier en executant le fichier qui le
contient ou vous pouvez executer tous les benchmarks d'un répertoire.

    bin/benchmark benchmark/core/string/bench_case.rb
    bin/benchmark benchmark/core
