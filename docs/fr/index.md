# OnesArm — Documentation technique (Français)

OnesArm (珠联“臂”合) est un bras robotique série modulaire et reconfigurable. Cette documentation complète le README du dépôt.

## Sommaire

- [Principe de fonctionnement](theory_of_operation.md) — structure modulaire, abstraction FCF, 24 combinaisons, cinématique DH, espace de travail, indice d’optimisation et statique.
- [Conception mécanique](mechanical_design.md) — bielles, articulations, interface T/N à tenon et mortaise, matériaux, effecteurs, plateforme et fabrication.
- [Électronique et commande](electronics_and_control.md) — plateforme v1 Pico W avec servomoteurs, plateforme v2 STM32 CAN avec moteurs pas à pas, cartes, interfaces et état du firmware.
- [Assemblage et reproduction](assembly_and_replication.md) — choix de la révision, fabrication, assemblage, câblage, analyse et essais.

## Documents de revue

- [Errata](../errata.md)
- [Vérification](../verification.md)
- [Glossaire](../glossary.md)
- [Références](../references/README.md)

Les tableaux de conception utilisent le millimètre ; les sorties de vérification utilisent le mètre. Les tableaux utilisent le degré ; les équations utilisent le radian. L’unité est précisée lorsqu’elle importe.
