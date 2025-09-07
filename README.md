# 🔐 Coffre-fort sécurisé simulé avec Arduino et Tinkercad

👉 [Lien vers le projet Tinkercad](https://www.tinkercad.com/things/kermqztGPgL-strongbox-3000)

## 📖 Description
Ce projet est une **simulation de système de sécurité multi-niveaux** réalisée sur Tinkercard.  
Le montage utilise des **LEDs, boutons poussoirs et un Arduino UNO** pour simuler différents niveaux d’authentification (questions/réponses, code secret, scan rétinien, empreinte digitale, carte d’identification, etc.).  

L’objectif est de créer un **coffre-fort virtuel** qui ne s’ouvre qu’après avoir franchi correctement les étapes de sécurité.

---

## ⚙️ Fonctionnalités principales
- Détection du modèle via la **tension analogique** sur `A0`.
- Attribution automatique d’un **niveau de sécurité** selon le modèle détecté.
- Plusieurs méthodes d’authentification simulées :
  - **MA1** : Question à choix multiple.
  - **MA2** : Code secret généré aléatoirement (4 chiffres).
  - **MA3** : Scan rétinien (simulé par messages série).
  - **MA4** : Scan digital (simulé par messages série).
  - **MA5** : Vérification par numéro de carte et lettre d’agent.
- Affichage des résultats et interactions via le **Moniteur Série** d’Arduino.

---

## 🖼️ Montage sur Tinkercad
Le circuit contient :
- 1 x Arduino UNO  
- 4 x LEDs rouges  
- 1 x LED verte  
- 5 x boutons poussoirs  
- Résistances et câblage adaptés  

---

## Utilisation
1. Importez le code dans l’IDE Arduino ou collez-le dans Tinkercad.  
2. Lancez la simulation.  
3. Ouvrez le **Moniteur Série (9600 bauds)** pour suivre les instructions.  
4. Suivez les étapes d’authentification selon le niveau de sécurité attribué.  
