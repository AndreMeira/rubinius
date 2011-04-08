---
layout: doc_fr
title: Compilateur de Bytecode
previous: Machine Virtuelle - Logique de distribution personnalisée
previous_url: virtual-machine/custom-dispatch-logic
next: Analyseur grammatical (Parser)
next_url: bytecode-compiler/parser
review: true
---

Le compilateur de Rubinius converti du code source ruby en bytecode que la 
machine virtuelle peut executer. Il utilise une série d'étape pour transformer
l'entrée dans une forme que la machine virtuelle peut comprendre.

Chaque étape est découplée du reste du processus -
chacune attend une forme particulière d'entrée et envoie sa sortie à l'étape suivante.
Cela rend le processus de compilation relativement configurable, 
et vous pouvez agir sur n'importe quelle étape aisément.

Chaque étape du processus reçoit une entrée, s'execute et passe sa sortie
à l'étape suivante. Les étapes par défaut, ainsi que leurs entrée/sorties,
sont illustrées ci-dessous.

<div style="text-align: center; width: 100%">
  <img src="/images/compilation_process.png" alt="Compilation process" />
</div>

1. [Etape d'analyse grammaticale (Parser)](/doc/en/bytecode-compiler/parser/)
1. [AST](/doc/en/bytecode-compiler/ast/)
1. [Etape de génération](/doc/en/bytecode-compiler/generator/)
1. [Etaper d'encodage](/doc/en/bytecode-compiler/encoder/)
1. [Etape de paquetage](/doc/en/bytecode-compiler/packager/)
1. [Etape d'écriture](/doc/en/bytecode-compiler/writer/)
1. Printers
1. [Transformations](/doc/en/bytecode-compiler/transformations/)
1. [Personnalisation du Pipeline](/doc/en/bytecode-compiler/customization/)
