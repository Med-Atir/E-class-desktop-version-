# E-Class - Application Desktop de Gestion des Classes en Ligne

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt6-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![SQLite](https://img.shields.io/badge/SQLite-003B57?style=for-the-badge&logo=sqlite&logoColor=white)

Une application desktop légère et performante développée en **C++** permettant de dématérialiser et centraliser les échanges pédagogiques entre les professeurs et les étudiants. 

Développé dans le cadre du module Programmation Orientée Objet (Semestre 4) à la Faculté des Sciences d'El Jadida (Université Chouaib Doukkali).

## À Propos du Projet

L'enseignement supérieur nécessite un prolongement numérique rapide, organisé et accessible. La gestion manuelle (emails, clés USB, WhatsApp) montre rapidement ses limites et crée de la désorganisation. 

E-Class répond à cette problématique en proposant une solution centralisée, contrairement aux plateformes web lourdes. L'application se veut ergonomique et centrée sur les fonctionnalités essentielles, tout en offrant un contrôle de bas niveau sur les ressources matérielles grâce au C++.

## Architecture & Choix Techniques

Ce projet ne se contente pas d'être fonctionnel, il a été pensé avec une rigueur architecturale (Modélisation UML, Schéma Relationnel) :

*   **Architecture MVC Adaptée :** Le système sépare rigoureusement l'interface graphique (Vue) de la logique de contrôle et d'accès aux données (Modèle/Base de données). La classe DB agit comme contrôleur indépendant. L'avantage ? On peut migrer de SQLite vers PostgreSQL ou MySQL en modifiant une seule classe.
*   **Lazy Loading & Optimisation RAM :** Pourquoi stocker tous les objets associés dans la mémoire RAM pendant l'exécution au risque de la gaspiller ? L'approche adoptée ici consiste à ne stocker que l'ID des instances associées en base de données et à ne récupérer les informations nécessaires qu'au moment précis où l'on en a besoin.
*   **Gestion de la Mémoire (QWidgets) :** L'application utilise intensivement le polymorphisme et le casting dynamique (`dynamic_cast`) pour adapter les vues (ex: Dashboard Professeur vs Étudiant) à la volée. Pour éviter les fuites de mémoire lors de la navigation, l'attribut `Qt::WA_DeleteOnClose` est assigné aux fenêtres pour garantir leur destruction propre à la fermeture.

## Fonctionnalités Principales

### Espace Professeur
*   **Gestion des Classes :** Création de classes virtuelles avec génération de codes d'accès uniques (basés sur QDateTime).
*   **Ressources & Devoirs :** Upload de documents (.pdf, .docx, etc.) et de cours vidéos avec duplication et archivage locaux sécurisés. Attribution de devoirs avec gestion de *deadline* et consignes.
*   **Interactions :** Validation/Refus des demandes d'accès des étudiants.
*   **Communication :** Publication d'annonces globales et réponses centralisées aux questions des étudiants.

### Espace Étudiant
*   **Accès aux Cours :** Recherche de classes via le code unique et envoi de demandes d'inscription.
*   **Ressources :** Consultation et téléchargement des supports de cours, vidéos et devoirs.
*   **Suivi & Q&R :** Possibilité de poser des questions directement aux professeurs et de suivre l'état des réponses.
*   **Tableau de Bord :** Vue d'ensemble sur les annonces, les classes rejointes et l'activité.

## Environnement de Développement

*   **Langage :** C++ (Logique Back-end)
*   **Interface Graphique :** Framework Qt6 (Widgets, QSS pour le style CSS-like)
*   **Base de Données :** SQLite (DB Browser)
*   **Outils & Modélisation :** CLion, Qt Designer, Git, Astah UML

## Installation & Compilation

1. Assurez-vous d'avoir un compilateur C++ installé (GCC/MinGW) ainsi que CMake.
2. Installez les bibliothèques du Framework **Qt6** (incluant Qt SQL pour la gestion de la base de données).
3. Clonez ce dépôt :
   ```bash
   git clone https://github.com/votre-nom/e-class.git
   ```
4. Ouvrez le projet dans votre IDE (recommandé: CLion ou Qt Creator).
5. Compilez et exécutez le projet. *Note : La base de données SQLite `.db` doit être placée dans le répertoire d'exécution.*

## Licence

**All Rights Reserved.**
Aucune redistribution ou modification n'est autorisée sans l'accord préalable de l'auteur.

---
*Réalisé par Mohammed Atir.*
