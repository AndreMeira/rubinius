---
layout: doc_fr
title: Comment écrire des traductions
previous: Ecrire de la Documentation
previous_url: how-to/write-documentation
next: Appendix A - Glossaire
next_url: appendix-a-glossary
---

Il y a deux tâches dans la traduction de la documentation:

1. Mettre à jour une traduction existente
2. Ajouter une langue aux traductions

Commencez par lire [Comment écrire de la
Documentation](/doc/en/how-to/write-documentation/)


### Mettre à jour une traduction existente

Pour mettre à jour une traduction existente, ouvrez le sujet à traduire
dans `web/doc/LANG` et éditez le texte ou ajouter du texte supplémentaire.


### Ajouter une langue

Pour ajouter une langue, suivez ces instructions:

1. Copiez `web/doc/en` vers `web/doc/LANG` où 'LANG' représente le code
   de la langue à ajouter selon la norme 
   [ISO-639-1](http://en.wikipedia.org/wiki/List_of_ISO_639-2_codes)
2. Editez les liens de la table des matières pour qu'ils pointent à 
   l'adresse des fichiers de votre langue. (Il semble que `page.base_dir`
   ne fonctionne pas quand ces fichiers sont traités par Jekyll. Il faudrait
   enquêter la dessus)
3. Traduisez l'anglais dans la langue cible.

