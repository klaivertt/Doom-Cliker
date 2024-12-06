# 🕹️ Projet Étudiant : DOOM 🎮

Bienvenue dans ce projet étudiant où j'ai exploré la programmation graphique avec **CSFML** !  
Ce projet vise à gérer un **ennemi interactif** doté de différents états et comportements dynamiques et de gérer les colission point pixel. 🚀

---

## 🌟 Objectifs du Projet

L'objectif principal était d'acquérir des compétences pratiques pour :  
- 🎨 **Manipuler des sprites, textures et images** dans CSFML.  
- 🎯 Implémenter une **détection précise des collisions** (rectangulaire et au pixel près).  
- 🔄 Créer et gérer des **états dynamiques** : `idle`, `walk`, `hurt`, `attack`.  
- 💥 Concevoir une **détection de dégâts localisés** sur les sprites.  
- 🧩 Structurer et modulariser un projet de jeu vidéo.  

---

## 🧩 Fonctionnalités Implémentées

### 🖱️ **Détection de Collisions**
- **Hitbox Rectangulaire** : Une collision simple pour détecter si l'ennemi est touché.  
- **Détection au Pixel Près** : Pour une précision maximale, en analysant les pixels actifs du sprite.  

### 🔴 **Gestion des États : `idle` et `hurt`**
- L'ennemi commence en état `idle`.  
- Lorsqu'il est touché :
  - Passe en état `hurt` avec un **sprite modifié** pour indiquer les dégâts.  
  - Retourne automatiquement à `idle` après **0,5 seconde**.  

### 🚶 **Déplacement de l'Ennemi (`walk`)**
- Déplacement continu **de gauche à droite**.  
- **Changement de direction** lorsqu'il touche un bord de l'écran :
  - Orientation correcte du sprite avec `sfImage_flipHorizontally()`.  

### ⚔️ **Mécanique d'Attaque**
- L'ennemi peut entrer en état `attack` après un **délai aléatoire** (entre **2 et 5 secondes**).  
- Pendant l'attaque :
  - L'ennemi **cesse de se déplacer**.  
  - Retourne à l'état `walk` après **1 seconde**.  

### 🎯 **Dégâts Localisés**
- **Détection avancée des zones touchées** sur le sprite (par exemple, tête, corps, etc.).  
- Utilisation de `sfImage_createFromFile()` pour charger des images spéciales avec des parties colorées permettant d'identifier la zone impactée.  

---

## 🛠️ Technologies Utilisées

- **Langage** : C  
- **Bibliothèque graphique** : [CSFML](https://www.sfml-dev.org/)  

---

## 🚀 Ce que J'ai Appris  

- 📏 **Gestion des collisions** : passage de la détection simple à une précision au pixel près.  
- 🔄 **Transitions entre états dynamiques** : gestion fluide des animations et des comportements.  
- 🖼️ **Symétrie et orientation des sprites** : utilisation de `sfImage_flipHorizontally()`.  
- 🎮 **Structuration d'un projet de jeu vidéo** : organisation claire et modulaire du code.  

---
