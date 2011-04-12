---
layout: doc_fr
title: Convention de codave
previous: Communication
previous_url: contributing/communication
next: Ruby
next_url: ruby
---

Les conventions de codage suivante visent à garder le code Rubinius dans un 
état maintenable. Lorsque vous avez un doute sur la convention a adopté, 
demandez sur le channel IRC #rubinius sur irc.freenode.net.

## Tout code

  * Configurez votre éditeur avec des espaces pour tabulation (pas de vraie tabulation)
  * Les tabulations valent deux espaces
  * Laisser un retour à la ligne à la fin de chaque fichier.
  
  
## code C++ 

  * Ne mettez pas d'espace entre la condition et les parenthèses:
      Utilisez `if(1)` PAS `if (1)`

  * Ouvrez l'accolade sur la même ligne que la déclaration de fonction ou
    de condition.

  * Utilisez toujours les accolades, même lorsqu'elles sont optionnelles

  * Parenthèsez de préference les opérations même si la précèdences 
    des opérateurs vous permettrait d'omettre les parenthèses. 

  * les fonctions alternatives doivent être nommées de telle sorte
    que leur nom permette de comprendre en quoi elles diffèrent. Si par exemple
    il y a une fonction 'person()' et vous voulez une version qui prend le nom
    de la personne en paramètre, cette fonction devrait s'appeler   
    'person_with_name(char \*name)' ou 'person_with_details(char \*name, ...)'
    et surtout PAS 'person1(char \*name)'.

## code Ruby

  * Methodes: Faites en sorte que vos méthodes restent courtes, et qu'elles tiennes
    entière à l'écran, et essayez d'adhérer au principe DRY ("ne vous répétez pas")
    dans des limites raisonnables. Généralement, les fonctionnalités communes 
    devraient être abstractisée dans des méthodes helpers (que vous pouvez rendre privées).
    Parfois cependant, en particulier lorsque vous travailler avec "Core" la méthode
    DRY vous handicapera - par exemple, si vous devez manoeuvrez 
    entre plusieurs conditions d'erreurs differentes.        

  * Nom de méthodes : Les noms de méthodes doivent être clairs, expressifs et
    porteur de sens. Evitez d'utiliser des underscores pour "protéger" la méthode
    ('\_\_send\_\_'). Il y a bien sûr des exceptions.
    
  * Les noms de méthodes à la smalltalk sont autorisé, au sens où
    une méthode telle que `SomeClass.make_from` est destinée à être 
    appelée comme `SomeClass.make_from file` ou `SomeClass.make_from :file => name`,
    c'est-à-dire lorsque le nom du paramètre complète le nom de la méthode et rend
    la lecture du code plus naturelle.

  * Les nom de variables: les noms de variables doivent être clairs et 
    porteur de sens, (hormis les exception bien connues telles que
    l'utilisation de `i` pour un compteur). Essayer d'éviter de masquer un nom 
    de méthode par un nom de variable ; par exemple dans une classe Array, préférez
    `idx` plutôt que `index`, qui est aussi un nom de méthode.  
  
    
  * Post-conditions: utilisez les post-conditions *uniquement si* votre 
    expression tiens sur une ligne *et* votre condition ne possède pas plusieurs termes.
    
  * Blocks : Mettez des espaces entre les délimiteurs et le code, que vous utilisiez 
    do ... end` ou `{...}`. Découpez les expressions longues ou complexes en plusieurs lignes :
    
        mapped = foo.map do |elem|
          do_something_with elem
        end

  * les définitions de Module/Class dans un espace de nom (scope qualifiers):

        module Rubinius::Profiler
          class Sampler
          end
        end

## Code du Kernel

La convention première pour tout code du kernel est d'être simple et efficace.
Du code simple est souvent plus efficace et généralement plus compréhensible. 
Il ne devrait pas y avoir de metaprogrammation dans l'étape de bootstrap. 
Utilisez les méthodes #attr_xxx tout au long du code source du kernel.
Si vous faites des alias de méthodes, appelez  #alias_method à côté de la définition
de la méthode. Si vous rendez privée une méthode avec `private :sym`, faites le 
à côté de la méthode rendue privée. Souvenez vous que les versions des méthodes 
listées ci-dessus ne prennent qu'un argument de type symbol à l'étape "alpha". 

## Documentation

  * Utilisez  RDoc pour la documention du code Ruby
  
  * Utilisez Doxygen pour la documentation du code C++.

  * Utilisez Markdown pour la documentation dans le dossier /doc. Voyez [Markdown
    syntax](http://daringfireball.net/projects/markdown/syntax) Limitez 
    la largeur du texte à 78 caractères, et utilisez des sauts de lignes.
