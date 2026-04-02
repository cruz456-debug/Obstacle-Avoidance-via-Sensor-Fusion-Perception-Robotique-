# Obstacle-Avoidance-via-Sensor-Fusion-Perception-Robotique-
# Autonomous Robot Sensor Fusion for Obstacle Avoidance
**Projet de Systèmes Autonomes et Perception Robotique**

## Présentation du projet
Ce projet implémente un système de navigation autonome pour robot mobile, capable d'évoluer dans un environnement inconnu. La particularité technique réside dans l'utilisation de la **fusion de capteurs** (Sensor Fusion) pour pallier les limites individuelles des technologies de détection et garantir une prise de décision robuste en temps réel.

## Problématique Technique
En robotique, un seul type de capteur présente souvent des "angles morts" :
* **Ultrasons (HC-SR04) :** Sensibles aux surfaces inclinées et aux bruits ambiants.
* **Infrarouge (Sharp IR) :** Sensibles à la luminosité ambiante et à la couleur des objets.

L'objectif ici est de fusionner ces deux flux de données via un algorithme de pondération pour obtenir une estimation de distance plus fiable.

## Architecture Système
* **Microcontrôleur :** ESP32 (Choisi pour sa vitesse d'horloge et sa gestion des interruptions).
* **Capteurs :** * 1x Capteur à ultrasons HC-SR04 (Vision longue portée).
    * 1x Capteur Infrarouge Sharp GP2Y0A21 (Vision précise de proximité).
* **Actionneurs :** Pont en H (L298N) pilotant deux moteurs à courant continu (DC).

## Algorithme et Implémentation
Le firmware, développé en C++, repose sur les concepts suivants :
1. **Acquisition Synchrone :** Lecture alternée des capteurs pour éviter les interférences.
2. **Filtrage et Fusion :** Implémentation d'une fonction de fusion logicielle calculant une distance pondérée en fonction de la zone critique.
3. **Logique de Navigation :** Algorithme de contournement basé sur une machine à états (FSM - Finite State Machine) pour assurer la fluidité du mouvement.

## Compétences Validées
* **Traitement du Signal :** Linéarisation de courbes de réponse analogiques (IR) et filtrage de données.
* **Architecture Matérielle :** Intégration de périphériques hétérogènes sur un bus commun.
* **Génie Logiciel Embarqué :** Optimisation de la boucle de contrôle pour minimiser la latence de décision.

---
**Développeur :** Dylan Bassinga  
*Étudiant en Licence 3 Applied Informatics (ETSE) - ISM Dakar* *
