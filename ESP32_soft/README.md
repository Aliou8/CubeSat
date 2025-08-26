# CubeSat ESP32 Software

Ce dépôt contient le code source pour le logiciel embarqué du CubeSat basé sur une carte ESP32.

## Objectif
Développer et maintenir le firmware du CubeSat pour la gestion des capteurs, la communication et le contrôle des sous-systèmes.

## Prérequis
- ESP32 (carte de développement)
- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/fr/latest/) ou Arduino IDE
- CMake, Python 3.x (pour ESP-IDF)

## Installation
1. Cloner ce dépôt :
   ```bash
   git clone https://github.com/votre-utilisateur/CubeSat.git
   ```
2. Installer l'ESP-IDF ou l'IDE Arduino selon votre environnement.

## Compilation et Flash
- Avec ESP-IDF :
   ```bash
   idf.py build
   idf.py -p PORT flash
   ```
- Avec Arduino IDE :
   - Ouvrir le dossier dans l'IDE et téléverser sur la carte.

## Structure du projet
- `main/` : Code source principal
- `components/` : Modules additionnels
- `build/` : Fichiers générés (ignorés par git)


