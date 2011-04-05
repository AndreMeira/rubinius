---
layout: doc_fr
title: Appendix A - Glossaire
previous: How-To - Traduire la documentation
previous_url: how-to/translate-documentation
next: Appendix B - Reading List
next_url: appendix-b-reading-list
review: true
---
Définition des termes et des expressions utilisés dans le langage de programmation Ruby
ainsi que dans cette implémentation. Regarder aussi "The Ruby Programming Language" par Flanagan et
Matsumoto [O'Reilly 2008] et "Programming Ruby: The Pragmatic Programmer's
Guide" 2nd or 3rd Edition par Thomas et al [The Pragmatic Programmers
2005-2008]


* _Où sont cherchées les méthodes ? (method lookup)_

  La règle est simple: prenez l'objet assumant le rôle de classe pour votre objet
  (ce n'est pas forcément l'objet retourné par Object#class, mais potentiellement une classe "singleton") 
  et commencer à chercher.
  
  La recherche remonte à travers la chaines de parenté des classes (superclass chain) jusqu'à ce qu'à trouver la classe nil (ou la méthode évidemment!).

  Si la recherche est sans résultat, on commence à chercher selon le même processus, la méthode nommée "method_missing".
  Si cette méthode n'est pas non plus trouvée, alors la recherche se solde enfin par un échec.


                                            +----------------+
                                            |      nil       |
                                            +----------------+
                                                    ^
                                                    | superclass
                                                    |
                                            +----------------+
                                            |     Object     |
                                            +----------------+
                                                    ^
                                                    | superclass
                                                    |
                                            +----------------+
                                            |     Module     |
                                            +----------------+
                                                    ^
                                                    | superclass
                                                    |
                                            +----------------+
                                            |     Class      |
                                            +----------------+
                                                    ^
                                                    | superclass
                                                    |
                                            +----------------+
                                            | SingletonClass |
                                            |    (Object)    |
                                            +----------------+
                                                    ^
                                                    | superclass
                                                    |
       +-------------+                      +----------------+
       |      F      |  ----------------->  | SingletonClass |
       +-------------+   singleton class    |      (F)       |
                                            +----------------+


      class Class
        def wanker
          puts 'you are'
        end
      end

      class F
        def self.bloke
          wanker
        end
      end

  1. Recherche de la méthode 'wanker' -- on recherche ainsi dans les tables de méthode de:

      1. SingletonClass(F) //classe singleton de F
      1. SingletonClass(Object) //class singleton de la classe Object, parente de la classe singleton de F
      1. Class //la class "Class" (toute les classes sont des instances de Class)

  Trouvée !


* _table de méthode (method_table)_

  Une table de méthode est une structure de données présente dans toutes les classe (et module)
  qui contient les méthodes définies pour cette classe.

  Dans Rubinius, une table de methode (method_table) est une instance de LookupTable.

* _MatzRuby_

  Voir MRI


* _MRI_
  
  MRI (Matz's Ruby Interpreter) est le nom donné à l'implémentation de l'interprétateur ruby écrit par Matz.
  Il s'agit d'un raccourci pour se référer à l'implémentation officiel de Ruby.
  Voir <http://ruby-lang.org>.


* _Appel privé (private send)_

  Un "appel privé" est un appel de méthode dans lequelle on est obligé d'omettre "le receveur", 
  c'est à dire l'objet sur lequel on appelle la méthode. Dans ce cas, l'objet est toujours +self+.

  Par exemple:

      class A
      private
        def you_are_mine
        end
      end

      class B < A
        def sunshine
          you_are_mine
        end
      end

      class C
        def dear
          today = B.new
          today.you_are_mine
        end
      end

  L'appel de +you_are_mine+ dans la méthode +sunshine+ est un appel privé. 
  L'appel de +today.you_are_mine+ échouera parce que les méthodes privées ne peuvent
  avoir de receveur explicite (l'objet "today" dans l'exemple).  
   

* _classe singleton_

  Une classe singleton est la classe dans laquelle les méthodes et les constantes 
  relative à une instance particulière. Tous les objets dans Ruby 
  peuvent en posséder une, cependant, elles ne sont créées que si nécessaire. 
  L'exemple ci-dessous montre une méthode +hello+ qui n'existe que sur un objet.
  Cette méthode est en fait définie dans la classe singleton de l'objet +obj+.

      obj = Object.new
      def obj.hello
        puts 'hi'
      end

  Comme les classes en Ruby sont aussi des objets, elles peuvent posséder leur classe singleton.
  En Ruby, ce qu'on appelle une methode de classe, est juste une méthode qui se trouve 
  dans la table des méthodes de la classe singleton. Dans l'exemple suivant, 
  la méthode +honk+ existe dans la class singleton de l'objet/classe +Car+. 

      class Car
        def self.honk
        end
      end
	
  Dans Rubinius, les classes singletons sont toutes des instances de la classe
  SingletonClass. La classe singleton d'un objet est accessible via la méthode 
  +singleton_class+. 
  
  On se réfère parfois à l'ensemble de ces concepts sous le nom de 
  "Meta-Object Protocol" ou pour faire court +MOP+.


* _superclass_

  En ruby la "superclass" est le nom de la class parente. La classe Object est à la racine
  de toute classe. En particulier si une classe n'hérite explicitement d'aucune classe, 
  elle hérite implicitement de la classe Object.
  
      class A
      end

      class B < A
      end

  Dans cet exemple, la classe A hérite de la class Object. Autrement dit, A.superclass == Object.
  La classe B hérite explicitement de A, donc B.superclass == A.
  
