---
layout: doc_fr
title: Contribuer
previous: Résolution des problèmes
previous_url: getting-started/troubleshooting
next: Communication
next_url: contributing/communication
---

Le projet Rubinius reçoit avec plaisir vos contributions. Il y a beaucoup de choses
à faire pour venir en aide au projet. Si vous souhaitez contribuer, 
choisissez quelque chose qui vous intéresse. C'est le meilleur moyen pour préserver
son enthousiasm et son energy.

Si vous avez des questions à propos de Rubinius, la meilleurs façon d'obtenir des
réponses est de discuter en ligne sur le channel IRC irc.freenode.net #rubinius.

Voici plusieurs idées de contributions à Runbinius.

## Executer du code réel

Votre code est souvent plus exigeant que des specs. Executez vos projets personnels
sous Rubinius et faites part des problèmes rencontrés. 
[Comment écrire un Ticket](/doc/en/how-to/write-a-ticket).

## Demandez de l'aide

Nous ferons ce qui est en notre pouvoir pour vous aider. N'hésitez pas à chercher 
par vous même aussi. Rubinius essaie d'être un projet facile à étudier, 
à apprendre, et à étendre.

Nous apprécirons tous bug rapporté, mais nous ne pouvons prioriser que les 
tickets que nous pouvons reproduire facilement. Les tickets les plus appréciés
sont ceux qui inclus une RubySpecs qui révèle le bug, et le patch qui le corrige.

## Ecrire des specs

  1. Executez `bin/mspec tag --list incomplete <dir>` pour voir les specs 
     qui ont été marquées comme incomplètes. Ces specs ont peut-être simplement
     besoin d'être relues, ou peuvent être des specs manquantes pour certaines classes.

     NOTE: Vous pouvez spécifier un pseudo répertoire ':files' à la place \<dir\>, ce qui
     montrera les tags pour toutes les specs qui devraient être executées sur Rubinius.
     Ou vous pouvez spécifier un sous répertoire du dossier 'spec' pour lister les tags 
     des specs de cette sous-catégorie.
     

  2. Trouver des comportement non spécifiés. Voir [Comment écrire des specs Ruby]
     (/doc/en/how-to/write-a-ruby-spec).

## Corriger des specs qui échouent.

  1. Executez `bin/mspec tag --list fails <dir>` pour voir les specs en échec.

	 NOTE: Vous pouvez spécifier un pseudo répertoire ':files' à la place \<dir\>, ce qui
     montrera les tags pour toutes les specs qui devraient être executées sur Rubinius.
     Ou vous pouvez spécifier un sous répertoire du dossier 'spec' pour lister les tags 
     des specs de cette sous-catégorie.
     
  2. Choisir une spec qui a l'air intéressante et faire en sorte qu'elle réussisse.


## Ecrire de la documentation

Etudier comment Rubinius fonctionne et écrire de la documentation de haut niveau
aidera les autres à comprendre des détails de l'implémentation.


## Nettoyer du code

Cherche les tag TODO, HACK, FIXME dans le code et soumettez des patches
qui résolvent le code marqué. Voici une commande utile pour trouver ces tags

    `grep -re "@todo\|TODO\|HACK\|FIXME" .`

Relisez le [Style Guide](/doc/en/contributing/style-guide/) pour respecter les
conventions de codage.


## Trier les tickets

  * Rouvrir ou fermé les vieux tickets
  * Construire les cas d'utilisation minimum pour reproduire le bug. Et voir ensuite
    si il y a déjà une RubySpecs pour ce problème. S'il n'y en a pas, essayez d'en
    écrire une.
  