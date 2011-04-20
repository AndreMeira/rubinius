---
layout: doc_fr
title: How-To - Ecrire de la documentation
previous: Ecrire un article de blog
previous_url: how-to/write-a-blog-post
next: Traduire la documentation
next_url: how-to/translate-documentation
---

La documentation rubinius est intégrée au site web et au blog. Jekyll est 
utilisé comme un composant comme les autres.

Pour commencer, assurez vous d'avoir les gems `kramdown` et `jekyll`
d'installer.

    rbx gem install jekyll kramdown

Les sources de la documentation se trouvent dans le répertoire `web/doc`. Il
s'y trouvent des sous-répertoires pour chaque langue qui a été traduite
(par exemple `en`, `es`, etc.).  

Il y a une table des matières pour chaque traduction (par exemple 
`/web/doc/fr/index.markdown`). Le reste de la documentation consiste en de
simples fichiers avec des attributs YAML qui spécifient comment les documents
reliés. La documentation peut être vu comme une liste doublement chainée de 
documents, chacun pointant sur le précédent et le suivant. La table des 
matières expose l'organisation complète des documents.


Les attributs YAML dans un document ressemblent à ça:

    ---
    layout: doc_en
    title: How-To - Write Documentation
    previous: Write a Blog Post
    previous_url: how-to/write-a-blog-post
    next: Translate Documentation
    next_url: how-to/translate-documentation
    ---

L'attribut _layout_ spécifie quel layout Jekyll doit utiliser quand il 
formatte le document. Le layout devrait être `doc_LANG`, où _LANG_ représente
le code ISO-639-2 de la langue.

Le _title_ spécifie le titre du document qui est affiché en haut de la page.


Les attibuts _previous_ et _previous\_url_  donnent le titre et le lien 
du document précédent. Parallèlement les attributs _next_ et _next\_url_ 
donnent le titre et l'url du document suivant. Ceci est utilisé pour améliorer
la navigation dans la documentation et pour limiter la charge de travail 
nécessaire pour réordonner une partie de la documentation.

Les sources de la documentation comme les fichiers générés par Jekyll sont 
committés dans le dépôt Rubinius. Quand le dépôt est clôné, il est possible
d'executer `rake docs` pour voir la documentation avant de builder Rubinius,
ce qui peut être utile en cas de problème dans le build.


### Editer de la documentation existante 

Une première ébauche de documentation a été créée. Il y a des topics qui ont
encore besoin d'être documentés.

Pour ajouter de la documentation à un topic existant ou pour corriger un point
de documentation, suivez les points suivants:

1. Ouvrez le fichier du topic dans `web/doc/LANG`. Ajoutez ou améliorer la 
documentation.
2. Pour voir vos modifications pendant que vous travaillez dessus, executez
   `rbx -S jekyll --server --auto` dans le répertoire `web/`.
3.Une fois finis, vous devez commiter vos changements dans les sources. 
4. Executez `rbx -S jekyll` dans le répertoire `web` pour forcer l'update de 
   tous les fichiers générés dans `web/_site`. 
5. Commitez les fichiers générés. Si les changements sont mineurs, les fichiers
   générés et les sources peuvent être commités en même temps. Si les 
   modifications sont importantes, commitez les fichiers générés dans un 
   commit différent, afin de rendre la relecture pour facile.


### Ajoutez de la documentation

Pour ajouter de la documentation sur un topic qui n'existe pas encore:

1. Créez un nouveau fichier avec l'extension .markdown dans le répertoire
   `web/doc/LANG`. 
2. Configurez les attributs qui lient le nouveau fichier aux fichiers existants
   Vous aurez besoin d'éditer les attributs _previous_ et _next_ de fichiers
   existants pour insérer le nouveau fichiers dans la navigation, et ajoutez
   une entrée dans `index.markdown`.
3. Pour voir vos modifications pendant que vous travaillez sur le fichiers,
   executez `rbx -S jekyll --server --auto`
4. Editez le nouveau fichier en utilisant la syntaxe Markdown.
5. Une fois finis, commitez vos changements dans les sources.
6. Executez `rbx -S jekyll` dans le dossier `web/` pour forcer les modifications
   à être répercutées dans les fichiers générés `web/_site`. 
7. Commitez les fichiers générés. Si les changements sont mineurs, les fichiers
  générés et les sources peuvent être commités en même temps. Si les 
  modifications sont importantes, commitez les fichiers générés dans un
  commit différent, afin de rendre la relecture pour facile. 

