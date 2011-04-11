---
layout: doc_fr
title: Executez Rubinius
previous: Construction (Build)
previous_url: getting-started/building
next: Résolution des problèmes
next_url: getting-started/troubleshooting
---

Une fois que vous avez suivi les étapes pour construire (build) - et 
potentiellement installer - Rubinius, vous pouvez vérifier qu'il fonctionne:

    rbx -v

Rubinius fonctionne généralement comme Ruby en ligne de commande, par exemple

    rbx -e 'puts "Hello!"'

Pour executer un fichier ruby nommé 'code.rb': 

    rbx code.rb

Pour executer IRB:

    rbx

Si vous ajoutez le répertoire bin de Rubinius à votre PATH, Rubinius tournera
exactement comme la version MRI de Ruby. Il y a les même commandes `ruby`, 
`rake`, `gem`, `irb`, `ri`, et `rdoc`.                           


Vous pouvez ajouter le répertoire bin de Rubinius à votre PATH uniquement
si lorsque vous souhaitez travailler avec Rubinius. De cette façon,
vous n'interagisserez pas avec votre installation "normale" de ruby quand
vous ne souhaitez pas utiliser Rubinius.
