# Conception mécanique

## 1. Taxonomie des modules

OnesArm est composé de quatre familles de modules :

1. **Base** — plaque en tôle ou imprimée, interface tenon-mortaise, quatre ventouses sur le prototype.
2. **Modules d’articulation** — variantes 45° et 90°, chacune avec entraînement, roulements et logement de carte.
3. **Modules de bielle** — bielle longue X-X, bielle longue X-Y et bielle courte intégrée. Les bielles longues utilisent une tôle d’aluminium 5052 de 5 mm et un tube en fibre de carbone de 50 × 46 mm ; la bielle courte est une pièce de tôle compacte.
4. **Effecteurs terminaux** — pince parallèle (objets ≤ 50 mm), module à ultrasons (HC-SR04), module de gaz (série MQ) et module stylo (fixation 16 mm).

![Bielle longue X-X](../../media/photos/reference/key_figures/fig5-1_xx_link_render.jpg)

![Bielle longue X-Y](../../media/photos/reference/key_figures/fig5-2_xy_link_render.jpg)

## 2. Interface T/N

L’interface s’inspire de deux assemblages en bois : le tenon en queue d’aronde (tête large, racine étroite) et l’assemblage à mi-bois en croix. Le connecteur supérieur est un nœud « T » ; l’inférieur un nœud « N ». Le nœud N coulisse sur le nœud T selon X ou Y : deux modules peuvent ainsi se rejoindre à 90° dans l’une ou l’autre direction. Quatre perçages M3 par face fixent l’entraînement ; une vis M5 serre la paire de modules. Un logement de carte de 30 mm × 58,72 mm (bas) et un logement en L (haut) maintiennent l’électronique dans la structure.

L’interface est **semi-rigide** par conception : elle reprend un moment de flexion tout en permettant une petite déformation. C’est utile pour la tolérance aux chocs, mais cela fragilise l’hypothèse de corps rigide utilisée en cinématique.

## 3. Bielles et matériaux

| Pièce | Matériau | Procédé | Remarques |
|---|---|---|---|
| Bielle longue X-X / X-Y | Tôle aluminium 5052 de 5 mm + tube carbone | Découpe/pliage tôle + collage du tube | Nœuds M5 ; 4 + 4 pièces |
| Bielle courte | Tôle aluminium 5052 de 5 mm | Tôlerie | 4 pièces |
| Plaque de base | Tôle aluminium 5052 de 5 mm | Tôlerie | 2 pièces |
| Boîtier d’articulation | Résine 9400A | Impression SLA | \(E=2,75\) GPa, \(\nu=0,44\) |
| Supports de capteurs | Résine 9400A | Impression SLA | Gaz, ultrasons, pince |
| Plateforme | Profilé aluminium 4040 | Découpe et boulonnage | Alimentation 350 W, trois plaques d’essai |

Le rapport 2024 décrit aussi des bielles imprimées. Le chapitre 5 de la révision 2025 remplace les bielles longues par la construction aluminium/carbone. Les deux jeux de CAO sont conservés ; les perçages ne sont pas forcément interchangeables.

## 4. Modules d’articulation et entraînements

| Révision | Entraînement | Réduction | Commande | Carte d’articulation |
|---|---|---|---|---|
| v1 | Servomoteur PWM 15 kgf·cm (5–9 V, 180°) | Interne | Raspberry Pi Pico W (RP2040) | Carte Joint A/B : 3 PWM, 5 LED, sélecteur 3 voies |
| v2 | Moteur pas à pas 42BYGH47 | Réducteur planétaire FLE-42-20, 1:20 | Module CAN STM32F103C8T6 ; contrôleur de bus STM32F407ZGT6 | Cartes Controller / Monitor, CAN TJA1050 |

La version v2 utilise un encodeur magnétique et un contrôleur en boucle fermée (modèle non précisé). Le servomoteur v1 a un couple de décrochage d’environ 1,47 N·m et une précision annoncée de 0,24°.

![Module d’entraînement](../../media/photos/reference/key_figures/fig5-4_drive_module_render.jpg)

**Conflit :** le dossier CAO s’appelle `FLE-42-20_42BYGH27`, alors que le rapport indique 42BYGH47. Les deux ne peuvent pas être la version courante. Il faut trancher avant commande, car la longueur du moteur et l’arbre modifient le boîtier.

## 5. Effecteurs terminaux

- **Pince parallèle** — entraînée par vis, deux mâchoires, objets jusqu’à 50 mm. La CAO contient la vis, le palier, l’accouplement, les bielles internes et les mâchoires.
- **Module à ultrasons** — HC-SR04 dans un support imprimé, déclenchement/écho numériques.
- **Module de gaz** — capteur analogique de la série MQ dans un boîtier ventilé.
- **Module stylo** — fixation de 16 mm pour les essais d’écriture et de trajectoire.

![Prototype](../../media/photos/project/onesarm_prototype_small.jpg)

Chaque effecteur se monte sur la même interface T/N qu’un module d’articulation : le changement d’outil ne demande pas de nouvelle conception de poignet.

## 6. Plateforme de travail

La plateforme v2 utilise un profilé aluminium 4040, une alimentation continue de 350 W, trois plaques de positionnement et un contrôleur CAN STM32F407ZGT6. La plateforme v1 reprend le même principe avec la carte de base Pico W et trois plaques d’essai. C’est un banc fixe, pas une base mobile.

## 7. Dossier de fabrication

- **Impression 3D :** 17 types de pièces au premier lot, 8 au retirage. Les notes d’impression donnent les quantités des pièces structurelles. Les STEP sont dans `mechanical/output/3dp/` ; les STL dans `mechanical/output/3dp/stl_current/`.
- **Tôlerie :** 10 connecteurs de bielle, 6 supports moteur, 6 plaques de bride, 4 connecteurs de bielle courte et 1 support de base. Les STEP sont dans `mechanical/output/sheet_metal/`.
- **Tube carbone :** 2 XX, 2 XY, 2 courts et 1 base, tous en 50 × 46 mm. Les STEP sont dans `mechanical/output/carbon_tube/`.
- **Plateforme :** 3 plaques d’essai, support d’alimentation et support de contrôleur. Les STEP sont dans `mechanical/output/platform/`.

Les listes originales et leurs images sont dans `BOM/manufacturing/`. Elles donnent des quantités, pas de tolérances ni d’état de surface ; à compléter avant un envoi en fabrication.

## 8. Inventaire CAO

L’archive contient 184 SLDPRT, 69 SLDASM, 49 STEP et 12 STL. La copie classée est dans `mechanical/source/` et `mechanical/output/`. Les 24 assemblages simplifiés sont rangés par permutation :

```text
assemblies/simplified_24/装配/
├── ABC/  AyBxCx, AyBxCy, AyByCx, AyByCy
├── ACB/  AyCxBx, AyCxBy, AyCyBx, AyCyBy
├── BAC/  ByAxCx, ByAxCy, ByAyCx, ByAyCy
├── BCA/  ByCxAx, ByCxAy, ByCyAx, ByCyAy
├── CAB/  CyAxBx, CyAxBy, CyAyBx, CyAyBy
└── CBA/  CyBxAx, CyBxAy, CyByAx, CyByAy
```

## 9. Séquence d’assemblage (aperçu)

1. Imprimer les boîtiers d’articulation et les supports de capteurs ; nettoyer les faces de glissement T/N.
2. Découper et plier les bielles aluminium ; coller les tubes carbone ; vérifier l’alignement des trous M5.
3. Monter les roulements et l’entraînement dans un boîtier.
4. Faire glisser le nœud N dans le nœud T, insérer la vis M5 et régler l’orientation relative.
5. Répéter le long de la chaîne ; monter la base et l’effecteur choisi.
6. Passer le faisceau FPC/XH dans les fenêtres de bielle ; ne pas pincer les fils à l’articulation.
7. Fixer les cartes dans leurs logements et connecter le faisceau de module.
8. Monter la plateforme, l’alimentation et l’arrêt d’urgence avant la mise sous tension.

La procédure détaillée est dans [assembly_and_replication.md](assembly_and_replication.md).

## 10. Risques mécaniques connus

- L’interface T/N semi-rigide n’est pas un roulement de précision ; la répétabilité après remontage n’est pas mesurée.
- Le boîtier en résine imprimée est le point faible sous 10 N ; le rapport ne donne pas de coefficient de sécurité.
- Le conflit 42BYGH27/47 peut empêcher la fermeture d’une articulation.
- Le collage du tube carbone et les tolérances de pliage ne sont pas spécifiés.
- L’alimentation 350 W et les connecteurs XT60 sont propres à la v2 ; vérifier l’entrée des cartes v1 avant réemploi.
