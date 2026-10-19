<p align="center">
  <img src="./media/photos/project/banner.jpg" alt="Rendu du bras robotique modulaire OnesArm" width="900"/>
</p>

<h1 align="center">OnesArm (珠联“臂”合)</h1>

<p align="center">
  <strong>Un bras robotique série modulaire et reconfigurable pour des tâches multi-scénarios</strong>
  <br>
  24 configurations articulaires, une interface tenon-mortaise et deux révisions matérielles documentées
</p>

<p align="center">
  <a href="./LICENSE.md"><img src="https://img.shields.io/badge/code-MIT-blue.svg" alt="Code : MIT"></a>
  <a href="./LICENSE-docs.md"><img src="https://img.shields.io/badge/docs%20%26%20CAD-CC%20BY%204.0-lightgrey.svg" alt="Documentation et CAO : CC BY 4.0"></a>
  <img src="https://img.shields.io/badge/CAD-SolidWorks-e63946" alt="SolidWorks">
  <img src="https://img.shields.io/badge/control-STM32%20%7C%20RP2040-00549f" alt="STM32 et RP2040">
  <img src="https://img.shields.io/badge/status-research%20prototype-orange" alt="Prototype de recherche">
</p>

<p align="center">
  <a href="./README.md">English</a> |
  <a href="./README.zh-CN.md">中文</a> |
  <a href="./README.fr.md">Français</a>
</p>

---

## À propos du projet

**OnesArm** (titre chinois : 珠联“臂”合) est un bras robotique série modulaire composé de modules d’articulation, de bielle et d’effecteur interchangeables. Au lieu d’une chaîne cinématique figée, le bras s’assemble par des interfaces normalisées **T/N à tenon et mortaise**. Pour le prototype à trois modules, l’orientation du module adjacent à la base est fixe et les deux autres modules choisissent chacun l’un de deux canaux perpendiculaires, ce qui donne

\[
N_3 = 3! \cdot 2^{3-1} = 24
\]

configurations articulaires. Les 24 assemblages existent en modèles SolidWorks.

Le projet a été développé par 郭沫晗 (Guo Mohan) au lycée n° 1 de Guyuan, Ningxia. Le rapport mentionne un premier prix au 38e Concours national chinois d’innovation scientifique et technologique des jeunes (2024). Le dépôt distingue ce qui est **documenté**, ce qui est **calculé** et ce qui n’est **pas mesuré**.

> **Deux révisions sont documentées.** La v1 utilise des servomoteurs PWM de 15 kgf·cm et un Raspberry Pi Pico W. La v2 utilise des moteurs pas à pas 42BYGH47, des réducteurs FLE-42-20 et une plateforme STM32 CAN. Elles ne sont pas compatibles broche à broche. Lire [`docs/errata.md`](docs/errata.md) avant toute commande.

## Caractéristiques principales

- **24 configurations articulaires** — trois modules interchangeables, deux canaux perpendiculaires, orientation adjacente à la base fixe.
- **Interface tenon-mortaise** — nœud T en haut, nœud N en bas, serrage par vis M5 ; inspirée de la queue d’aronde et de l’assemblage à mi-bois.
- **Deux générations d’entraînement documentées** — prototype servomoteur/Pico W et plateforme pas à pas/CAN avec alimentation 350 W.
- **Effecteurs multi-scénarios** — pince parallèle, sonde HC-SR04, capteur de gaz MQ et module stylo sur la même interface.
- **Dossier de fabrication ouvert** — sources SolidWorks, STEP/STL, Gerber, nomenclature et listes de fabrication.
- **Revue reproductible** — errata et vérifications Python pour les transformations DH, les limites articulaires, l’espace de travail et le cas de charge.

## Architecture du système

```text
                    ┌──────────────────────────────┐
                    │  Effecteur terminal           │
                    │  pince / ultrasons / gaz      │
                    └──────────────┬───────────────┘
                                   │ interface T/N
                    ┌──────────────┴───────────────┐
                    │  Module de bielle (XX/XY/court)│
                    └──────────────┬───────────────┘
                                   │
                    ┌──────────────┴───────────────┐
                    │  Module d’articulation (45°/90°)│
                    │  entraînement + roulement + PCB│
                    └──────────────┬───────────────┘
                                   │
                    ┌──────────────┴───────────────┐
                    │  Base + plateforme + alimentation│
                    └──────────────────────────────┘
```

| Révision | Contrôleur | Entraînement | Bus de module | Alimentation |
|---|---|---|---|---|
| **v1** | Raspberry Pi Pico W (RP2040, Wi-Fi) | Servomoteur PWM 15 kgf·cm | Peigne 16P 2,54 mm | Rail servo 5–9 V |
| **v2** | Modules CAN STM32F103C8T6 + contrôleur STM32F407ZGT6 | 42BYGH47 + FLE-42-20 (1:20) | CAN (TJA1050) | 350 W continu, XT60 |

<p align="center">
  <img src="./media/photos/reference/key_figures/fig5-7_fcf_structure.png" alt="Face de connexion - canal de connexion - face de connexion" width="520"/>
  <img src="./media/photos/reference/key_figures/fig5-8_concat_structure.png" alt="Chaîne modulaire concaténée" width="520"/>
  <br>
  <em><strong>Figure 1 — Abstraction FCF.</strong> Chaque connexion est une face, un canal et une autre face. Les bielles longues ont six faces, les bielles courtes quatre, les articulations deux.</em>
</p>

<p align="center">
  <img src="./media/photos/reference/key_figures/fig5-4_drive_module_render.jpg" alt="Rendu du module d’entraînement" width="420"/>
  <img src="./media/photos/project/onesarm_prototype_small.jpg" alt="Prototype OnesArm" width="260"/>
  <br>
  <em><strong>Figure 2 — Module d’entraînement et prototype.</strong> Le prototype 2024 utilise des boîtiers imprimés, des bielles en tôle et une base à quatre ventouses. Le rendu v2 montre l’ensemble pas à pas/réducteur.</em>
</p>

## Théorie et conception

### Combinaisons modulaires

Le rapport abstrait la chaîne en **Face de connexion – Canal de connexion – Face de connexion** (FCF). Une bielle longue X-X ou X-Y a 6 faces × 4 canaux ; une bielle courte 4 × 4 ; une articulation 2 × 4. Pour le prototype à trois modules, le module 45° et les deux modules 90° peuvent être ordonnés de \(3!\) façons ; l’orientation adjacente à la base est fixe et les deux autres donnent \(2^2\). Le résultat est 24, vérifié par 24 assemblages CAO et 3 modèles d’articulation seule.

### Cinématique

La configuration analysée est **AyCxBy-D**, une chaîne à 4 DDL. La table 3-20 du rapport donne :

| \(i\) | \(d_i\) (mm) | \(a_i\) (mm) | \(\alpha_i\) | Plage du rapport |
|---:|---:|---:|---:|---|
| 1 | 95 | 0 | 90° | 0° |
| 2 | 0 | 113.5 | 90° | 0–180° |
| 3 | 21.34 | 88.5 | 90° | 0–180° |
| 4 | 0 | 152 | 0° | 0–180° |

La DH standard s’écrit

\[
T_i = \operatorname{Rot}_z(\theta_i)\,\operatorname{Trans}_z(d_i)\,
\operatorname{Trans}_x(a_i)\,\operatorname{Rot}_x(\alpha_i).
\]

Le rapport imprime un autre ordre, \(\operatorname{Rot}_z\operatorname{Rot}_x\operatorname{Trans}(a,0,0)\operatorname{Trans}(0,0,d)\), et l’équation (3.7) a une troisième colonne nulle. Les deux conventions donnent des positions différentes. Le dépôt utilise la DH standard pour la vérification et consigne l’écart dans [`docs/errata.md`](docs/errata.md).

<p align="center">
  <img src="./media/photos/reference/key_figures/fig3-29_workspaces.png" alt="Espaces de travail de quatre assemblages" width="760"/>
  <br>
  <em><strong>Figure 3 — Comparaison des espaces de travail.</strong> Quatre des 24 configurations : AyCxBy-D, AyCyBx-D, AyCxBx-D et AyCyBy-D. Ce sont des échantillons de simulation, pas des mesures. L’enveloppe aléatoire du modèle donne une portée maximale d’environ 0,45 m.</em>
</p>

L’indice d’« énergie » du rapport est une intégrale de l’accélération articulaire (ou de la vitesse, dans le panneau), pas une énergie électrique. Le dépôt le traite comme un **indicateur d’effort cinématique** et le dit explicitement.

## Structure du dépôt

```text
OnesArm/
├── BOM/                    synthèse + listes de fabrication originales
├── electronics/            Gerber, nomenclature et sérigraphie ; pas de source EDA
├── mechanical/
│   ├── source/             pièces et assemblages SolidWorks
│   ├── output/             exports STEP, STL et fabrication
│   └── analysis/fea/       images EF exportées
├── firmware/               projets STM32 CubeMX + bibliothèques MicroPython
├── software/               scripts MATLAB de cinématique
├── docs/
│   ├── en/ zh-CN/ fr/      documentation longue en trois langues
│   ├── errata.md           revue théorique et des preuves
│   ├── verification.md     vérifications numériques et résultats
│   ├── report/             rapport 2025 et soutenance
│   └── archive/            rapport 2024, journal, concept associé
├── media/
│   ├── photos/project/     rendus, prototype, PCB et photos d’essai
│   ├── photos/reference/   figures du rapport et figures clés
│   ├── gifs/               quatre GIF de démonstration
│   ├── videos/             MP4 originaux (ignorés par Git)
│   └── source/             fichiers de panneaux éditables (ignorés par Git)
├── data/                   pas de données mesurées (documenté)
├── scripts/verify_theory/  vérifications et tests Python
├── README.md README.zh-CN.md README.fr.md
├── MIGRATION_NOTES.md CHANGELOG.md CONTRIBUTING.md
├── LICENSE.md LICENSE-docs.md
├── .gitignore .gitattributes
└── .github/
```

## Nomenclature

Une synthèse est dans [`BOM/onesarm_bom.md`](BOM/onesarm_bom.md), la version lisible par machine dans [`BOM/onesarm_bom.csv`](BOM/onesarm_bom.csv). Les listes originales sont dans [`BOM/manufacturing/`](BOM/manufacturing/).

| Groupe | Éléments principaux | Quantité |
|---|---|---|
| Bielles longues | X-X et X-Y, aluminium 5052 de 5 mm + tube carbone | 4 + 4 |
| Bielles courtes | Aluminium 5052 de 5 mm | 4 |
| Articulations | 45° × 1, 90° × 2 | 3 |
| Entraînement v1 | Servomoteur PWM 15 kgf·cm | 3 |
| Entraînement v2 | 42BYGH47 + FLE-42-20 (1:20) | 3 ensembles |
| Commande | Pico W (v1) ou plateforme STM32 CAN (v2) | 1 ensemble |
| Plateforme | Profilé aluminium 4040, alimentation 350 W | 1 |
| Effecteurs | pince, ultrasons, gaz, stylo | 4 modules |

L’archive ne donne ni masse totale, ni charge utile, ni puissance mesurée.

## Démarrage

1. **Choisir une révision.** v1 (servo/Pico W) ou v2 (pas à pas/CAN). Ne pas mélanger les cartes.
2. **Construire la mécanique.** Imprimer les boîtiers, découper/plier les bielles, coller les tubes carbone et monter la visserie selon [`docs/fr/assembly_and_replication.md`](docs/fr/assembly_and_replication.md).
3. **Fabriquer l’électronique.** Commander les Gerber et monter la nomenclature. Sans source EDA, vérifier les photos des cartes.
4. **Lancer l’analyse.** Scripts MATLAB dans `software/matlab/kinematics/` ; vérifications Python dans `scripts/verify_theory/`.
5. **Mettre sous tension une articulation à la fois.** Le firmware archivé est un squelette ; ajouter l’application PWM ou CAN de la révision.

```bash
# vérifications indépendantes (sans MATLAB)
python scripts/verify_theory/report_checks.py
python -m unittest discover -s scripts/verify_theory -v
```

## Démonstration et essais

Les GIF ci-dessous sont des **démonstrations au banc**, pas des expériences contrôlées. Ils montrent le bras en mouvement, l’écran OLED/GNSS du contrôleur d’extension, la pince/le module stylo et une vue de simulation. Aucune charge utile ni répétabilité mesurée n’est revendiquée.

<p align="center">
  <img src="./media/gifs/onesarm_motion.gif" alt="Démonstration de mouvement" width="360"/>
  <img src="./media/gifs/onesarm_gripper.gif" alt="Démonstration de la pince" width="320"/>
</p>

<p align="center">
  <img src="./media/gifs/onesarm_electronics.gif" alt="Démonstration électronique et OLED" width="420"/>
  <img src="./media/gifs/onesarm_simulation.gif" alt="Vue de simulation" width="420"/>
</p>

<p align="center">
  <img src="./media/photos/project/scene_module_assembly_small.jpg" alt="Assemblage de modules" width="420"/>
  <img src="./media/photos/project/modular_assembly_diagram_small.jpg" alt="Schéma des 24 assemblages" width="420"/>
  <br>
  <em><strong>Figure 4 — Vues d’assemblage.</strong> À gauche : empilement de modules. À droite : les 24 combinaisons permutation/orientation de l’étude.</em>
</p>

## Spécifications

| Paramètre | Valeur | Source |
|---|---|---|
| Configuration analysée | AyCxBy-D, 4 DDL | Rapport §3.3 |
| Longueurs \(d_1, a_2, d_3, a_3, a_4\) | 95 ; 113,5 ; 21,34 ; 88,5 ; 152 mm | Rapport table 3-20 |
| Somme des bielles | 354 mm | Calcul |
| Portée maximale du modèle | environ 450 mm | Calcul, 10 000 échantillons |
| Limites du rapport | q1 0°, q2–q4 0–180° | Rapport table 3-20 |
| Limites MATLAB | q1 0°, q2 0–180°, q3/q4 ±90° | `software/matlab/kinematics` (conflit) |
| Assemblages | 24 combinaisons | \(3!\,2^{2}\) ; 24 fichiers CAO |
| Matériau EF | résine 9400A, \(E=2,75\) GPa, \(\nu=0,44\), 1150 kg/m³ | Rapport table 3-1 |
| Charge EF | 10 N sur chaque face supérieure d’articulation | Rapport §3.1.2 |
| Servomoteur v1 | 15 kgf·cm (1,47 N·m) au décrochage, 0,16 s/60° à 6 V | Rapport §2.3.1 |
| Entraînement v2 | 42BYGH47 + FLE-42-20, 1:20 | Rapport §5.2.2 |
| Contrôleur | Pico W (v1) / STM32F103 + STM32F407 CAN (v2) | Rapport §2.3.2 / §5.2.2 |
| Plateforme | Profilé 4040, alimentation 350 W | Rapport §5.2.3 |
| Charge utile, masse, répétabilité, puissance mesurées | **Non disponibles** | Pas de journal de mesure |

## Errata et problèmes connus

- L’équation (3.7) du rapport a un bloc de rotation singulier (troisième colonne nulle).
- Le rapport utilise un ordre DH non standard ; MATLAB utilise la DH standard. Les positions diffèrent.
- Les limites des articulations 3/4 diffèrent entre le tableau et MATLAB.
- La formule générale (3.11) ne redonne pas 24 ; l’équation (3.1) et la CAO le font.
- L’indice d’« énergie » est un indicateur cinématique ; `Optimization.m` est un visualiseur MediaPipe, pas cette optimisation.
- 10 N à 0,354–0,450 m valent 3,54–4,50 N·m, au-delà du couple de décrochage de 1,47 N·m d’un servomoteur.
- Les projets STM32 sont des squelettes ; aucun firmware de bras ni `main.py` MicroPython n’est fourni.
- Aucune source EDA, aucune donnée mesurée.

Voir [`docs/errata.md`](docs/errata.md) et [`docs/verification.md`](docs/verification.md).

## Feuille de route

1. Figer la révision matérielle et résoudre 42BYGH27/47.
2. Adopter une seule convention DH, régénérer les figures et implémenter la cinématique inverse et l’indicateur d’effort sur les 24 assemblages.
3. Ajouter un chemin firmware PWM/CAN minimal et un journal de suivi articulaire mesuré.
4. Retrouver la source EDA et publier une révision de cartes fabricable.
5. Mesurer charge utile, répétabilité, masse et puissance à un bras de levier défini.

## Contribution

Voir [`CONTRIBUTING.md`](CONTRIBUTING.md). Ne pas ajouter de nombres non mesurés ni de figures tierces sans mention de licence.

## Licence

- **Code, firmware et scripts :** [MIT](LICENSE.md).
- **Documentation, CAO originale, photos et schémas :** [CC BY 4.0](LICENSE-docs.md).
- **Figures, articles, vidéos et marques tierces :** exclus des deux licences. Voir [`docs/references/README.md`](docs/references/README.md).

L’auteur doit confirmer le choix de licence avant une publication publique.

## Remerciements

- **Auteur :** 郭沫晗 (Guo Mohan), lycée n° 1 de Guyuan, Ningxia.
- **Enseignants et mentors :** 马博伟 (atelier de robotique du lycée), 杨旭 (Université des sciences et technologies électroniques de Chine), 邵金龙 (Université du Ningxia), selon les remerciements du rapport.
- **Concours :** 38e Concours national chinois d’innovation scientifique et technologique des jeunes (2024).
- **Références :** littérature sur les robots continus, les bras modulaires, les assemblages tenon-mortaise et les robots serpentins, listée dans [`docs/references/README.md`](docs/references/README.md).
- **Outils :** SolidWorks, MATLAB Robotics Toolbox, EasyEDA/LCEDA, STM32CubeIDE, MicroPython, ffmpeg et Pillow.
