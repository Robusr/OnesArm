# Électronique et commande

## 1. Deux révisions

OnesArm possède deux plateformes électroniques documentées. Elles ne sont pas compatibles broche à broche.

| Élément | v1 (2024, rapport ch. 2–4) | v2 (à partir de 2024-07, rapport ch. 5) |
|---|---|---|
| Contrôleur | Raspberry Pi Pico W (RP2040, 133 MHz, Wi-Fi) | Modules CAN STM32F103C8T6 + contrôleur STM32F407ZGT6 |
| Entraînement | Servomoteur PWM 15 kgf·cm | Moteur pas à pas 42BYGH47 + FLE-42-20 (1:20) |
| Retour | Interne au servomoteur | Encodeur magnétique, contrôleur en boucle fermée |
| Bus inter-modules | Peigne 16P 2,54 mm | CAN (émetteurs-récepteurs TJA1050) |
| Alimentation des modules | Rail servo 5–9 V | Alimentation 350 W, XT60 |
| Cartes | Base, Joint A, Joint B, Holder/Sensor, Expand Controller | OnesArm Controller, OnesArm Monitor |

## 2. Architecture v1

La carte de base Pico W expose des extensions SPI et I2C ainsi qu’une entrée d’alimentation séparée. Les cartes Joint A/B offrent chacune trois sorties PWM, cinq LED d’état et un sélecteur de signal servo à trois voies, réglé par cavalier. La carte Holder/Sensor fournit deux entrées ADC et trois sorties PWM. L’Expand Controller ajoute un module GNSS, un OLED monochrome de 0,96 pouce, un peigne 8 × 2P pour le débogage des modules et une entrée USB Type-B.

![Carte d’articulation](../../media/photos/reference/key_figures/fig2-19_pcb_joint_module.png)

![Carte de base](../../media/photos/reference/key_figures/fig2-19_pcb_base_module.png)

Le câblage interne utilise du FPC 12P 1 mm et du XH 3P 2,54 mm ; les modules se connectent par peigne 16P 2,54 mm. Le connecteur est compact mais non détrompé : repérer le point 1 sur chaque câble.

## 3. Architecture v2

Les cartes Controller et Monitor utilisent un émetteur-récepteur CAN TJA1050, un abaisseur LM2596-5.0, des connecteurs XT60, des peignes 2 × 20 et 2 × 29, quatre boutons et des LED d’état. La nomenclature ne liste pas de microcontrôleur : les modules STM32 se brochètent sur les peignes. L’alimentation 350 W alimente les drivers de moteurs pas à pas et le contrôleur de bus.

Le débit CAN, les identifiants de nœud, la terminaison et le format des messages ne sont **pas documentés** dans l’archive. À définir avant de connecter plusieurs modules.

## 4. Alimentation

- v1 : rail servo 5–9 V ; le Pico W demande une alimentation régulée de 5 V. L’Expand Controller accepte une alimentation USB Type-B.
- v2 : alimentation 350 W via XT60 ; le LM2596 fournit le 5 V logique. Vérifier la plage d’entrée de chaque driver avant mise sous tension.
- Ajouter fusible, protection contre l’inversion de polarité et arrêt d’urgence. L’archive ne les montre pas sur les cartes.

## 5. État du firmware

| Projet | État |
|---|---|
| `firmware/stm32/demo_LED` | Squelette CubeMX ; boucle utilisateur vide |
| `firmware/stm32/demo_LED1` | Squelette CubeMX |
| `firmware/stm32/demo_test` | Squelette GPIO + RTC |
| `firmware/stm32/Key` | Driver de bouton avec erreurs de compilation ; en-tête vide |
| `firmware/stm32/KeyLED` | Code utilisateur vide |
| `firmware/stm32/彩色液晶屏驱动...` | Projet de driver LCD ; vérifier le câblage |

CAN est commenté dans toutes les configurations HAL. Il n’existe ni code PWM servo, ni génération d’impulsions pas à pas, ni application CAN. Les projets servent de référence d’horloge et de broches, pas de contrôleur fonctionnel.

MicroPython ne contient qu’un driver OLED SSD1306 et les bibliothèques GNSS L76X/micropyGPS. Il n’y a ni `main.py` ni cinématique du bras. L’affirmation du rapport sur un essai MicroPython en boucle ouverte n’est pas étayée par le code archivé. Voir l’[errata E-11](../errata.md).

## 6. Ordre de mise sous tension

1. Inspecter les ponts de soudure et la polarité ; ne pas encore insérer le module MCU.
2. Appliquer 5 V avec une alimentation limitée en courant ; vérifier le rail 3,3 V et la consommation.
3. Insérer le module MCU et flasher un test LED issu du projet CubeMX correspondant.
4. Tester une voie servo ou pas à pas au banc, sans le bras.
5. Connecter un module d’articulation, vérifier le signal CAN ou PWM, puis ajouter le suivant.
6. Seulement ensuite assembler le bras et lancer une trajectoire lente de faible amplitude.

## 7. Sources de conception manquantes

Seuls les Gerber, la nomenclature et les modèles d’encombrement SolidWorks des cartes sont présents. Il n’y a ni projet EasyEDA/Altium/KiCad ni schéma PDF : les cartes ne peuvent pas être modifiées ni régénérées. Retrouver la source EDA avant de publier une version fabricable. Voir l’[errata E-14](../errata.md).

## 8. Nomenclature

Voir [`../../BOM/onesarm_bom.md`](../../BOM/onesarm_bom.md) pour le résumé et [`../../electronics/output/bom/`](../../electronics/output/bom/) pour les nomenclatures PCB originales.
