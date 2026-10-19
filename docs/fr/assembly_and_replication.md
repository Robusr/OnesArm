# Assemblage et reproduction

## 1. Choisir d’abord une révision

Ne pas mélanger v1 et v2.

- **v1** — servomoteurs PWM 15 kgf·cm, Raspberry Pi Pico W, cinq cartes de module, interconnexion peigne 16P. Configuration des chapitres 1–4 du rapport et de la soutenance 2024.
- **v2** — moteurs pas à pas 42BYGH47, réducteurs FLE-42-20, modules CAN STM32F103C8T6, contrôleur STM32F407ZGT6, cartes Controller/Monitor, alimentation 350 W. Configuration du chapitre 5.

Le dossier CAO s’appelle `FLE-42-20_42BYGH27` ; le texte indique 42BYGH47. Confirmer le moteur avant d’imprimer un boîtier.

## 2. Outils et matériaux

- Clés hexagonales M3/M5, tournevis, pince coupante, pied à coulisse.
- Station de soudage, flux, multimètre, alimentation de banc limitée en courant.
- Imprimante 3D (SLA pour la résine 9400A ; FDM pour essai à blanc uniquement).
- Découpe/pliage de tôle laser ; gabarit de coupe et collage du tube carbone.
- STM32CubeIDE ; MicroPython pour les bibliothèques Pico W.
- MATLAB avec Robotics Toolbox pour les scripts d’origine ; Python 3 pour les vérifications.

## 3. Fabrication

### 3.1 Impression 3D

- Utiliser les STEP de `mechanical/output/3dp/`. Premier lot : 17 types ; retirage : 8. Imprimer les boîtiers en résine 9400A avec la normale de couche perpendiculaire à la face de glissement T/N.
- Nettoyer les faces de glissement ; une surface rugueuse bloque le nœud N.
- Vérifier le diamètre des trous M3 après impression. Le rapport spécifie 3 mm de diamètre et 3 mm de profondeur.

### 3.2 Tôlerie

- Aluminium 5052 de 5 mm pour les bielles longues, les bielles courtes et les plaques de base.
- Ébavurer ; le tube carbone est collé dans la bielle, une bavure peut amorcer une fissure.
- Vérifier l’alignement des trous M5 avant pliage. La liste est dans `BOM/manufacturing/定做生产.md`.

### 3.3 Tube carbone

- Tube 50 × 46 mm, coupé aux longueurs de `BOM/manufacturing/碳管定做/清单.md`.
- Coller à l’époxy structural ; poncer et nettoyer l’aluminium et le tube avant collage.
- Laisser respirer pendant la polymérisation ; l’air emprisonné peut déformer la bielle.

### 3.4 Carte imprimée

- Commander à partir des Gerber de `electronics/output/gerber/`. Vérifier les couches de perçage et de contour avant paiement.
- Les cartes v1 datent de 2024-02/03 ; les cartes v2 Controller/Monitor de 2024-07. Ne pas les mélanger.
- Il n’y a pas de source EDA ; pour modifier une carte, la redessiner à partir des Gerber, de la nomenclature et des photos.

## 4. Assemblage mécanique

1. Monter les roulements et l’entraînement dans le boîtier ; vérifier la libre rotation avant de fermer.
2. Placer la carte dans son logement ; éloigner le FPC du roulement.
3. Faire glisser le nœud N dans le nœud T, régler l’orientation, insérer la vis M5 et serrer.
4. Construire la chaîne depuis la base ; garder les axes parallèles ou perpendiculaires selon le code d’assemblage choisi (par exemple AyCxBy-D).
5. Monter l’effecteur sur la dernière interface T/N.
6. Fixer la base sur la plateforme ; ventouses ou boulons sur la plaque d’essai.
7. Vérifier que chaque articulation atteint sa butée sans tirer sur un câble.

## 5. Câblage

- v1 : peigne 16P entre modules ; FPC 12P et XH 3P à l’intérieur ; 3 PWM + 5 LED + sélecteur par carte d’articulation.
- v2 : chaîne CAN avec TJA1050 ; alimentation 350 W par XT60 ; logique 5 V par LM2596.
- Repérer le point 1 de chaque connecteur. Le peigne n’a pas de protection contre l’inversion.
- Ajouter un soulagement de contrainte à l’articulation ; le faisceau ne doit pas porter la charge.

## 6. Firmware et logiciel

- STM32 : ouvrir le `.ioc` dans STM32CubeIDE, régénérer si nécessaire, compiler. Le code utilisateur est un squelette ; ajouter l’application PWM/CAN de la révision choisie.
- Pico W : copier les bibliothèques SSD1306/GNSS de `firmware/micropython/` ; écrire son propre `main.py`. Aucun `main.py` de commande du bras n’est fourni.
- MATLAB : ajouter `software/matlab/kinematics` au chemin et lancer `AyCxBy_D`. Tenir compte des problèmes connus de `software/README.md`.
- Vérification Python : `python scripts/verify_theory/report_checks.py` et `python -m unittest discover -s scripts/verify_theory -v`.

## 7. Procédure d’essai

1. **Banc** — une articulation, sans charge, faible vitesse. Vérifier sens, butée et courant.
2. **Module seul** — articulation + bielle, sans effecteur. Vérifier la vis T/N et le passage des câbles.
3. **Chaîne** — assembler la configuration 4 DDL AyCxBy-D. Parcourir lentement les limites.
4. **Effecteur** — ouverture/fermeture de la pince, distance ultrason, sortie du capteur de gaz, contact du stylo.
5. **Trajectoire** — commander une courte trajectoire articulaire ; enregistrer les angles réels si un retour existe.
6. **Charge** — seulement après avoir résolu la marge de l’actionneur ; préciser le point d’application et le bras de levier.

L’archive ne contient aucun critère d’acceptation. Ne pas recopier un « conforme » du rapport ; enregistrer ses propres mesures.

## 8. Problèmes connus avant construction

- L’équation (3.7) est singulière ; utiliser la DH standard et le script de vérification, pas la matrice imprimée.
- Les limites des articulations 3/4 diffèrent entre le tableau et MATLAB.
- L’indice d’« énergie » est un indicateur cinématique ; `Optimization.m` n’a pas de rapport.
- 10 N à 0,45 m valent environ 4,5 N·m, au-delà du couple de décrochage de 1,47 N·m d’un servomoteur.
- Aucune source EDA, aucun firmware de bras, aucune donnée mesurée.

Voir l’[errata](../errata.md) et la [vérification](../verification.md).
