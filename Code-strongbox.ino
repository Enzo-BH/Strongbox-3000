/* C++ code
CONSTANTE, VARIABLE GLOBALES */

int modelActuelle; //VARIABLE POUR DEFINIR LE MODEL ACTUELLE 

//BROCHE DES LEDS 
const int ledR1 = 7;
const int ledR2 = 6;
const int ledR3 = 5;
const int ledR4 = 4;
const int ledV = 3;

const int tabLedR[3]= {ledR1, ledR2, ledR3};
const int tabbtn[5] = {12, 11, 10, 9, 8}; //TABLEAU POUR DEFINIR LES BROCHES DES BOUTONS

int niveauxAssocies[8] = {1, 2, 3, 4, 5, 6, 1, 2}; //TABLEAU ASSOCIANT LE MODEL AU NIVEU DE SECURITE, EN FONCTION DE L'INDICE


bool Etape = true; //VARIABLES QUI SERT A VERIFIER SI UNE ETAPE DE LA VERIFICATION EST VALIDE

//TABLEAU DES QUESTIONS POUR MA1
const char* questions[] = {  
  "Quel est la reponse C ?",
  "Quelle est la couleur du cheval blanc d'Henry IV ?",
  "Quelle est la lettre de l'agent M ?"
};

//TAB DES REPONSES 
const char* reponses[3][4] = {   
  {"A", "B", "C", "D"},
  {"Noir", "Blanc", "Multicolor", "Gris"},
  {"L", "K", "M", "J"}
};

int bonnesReponses[] = {2, 1, 2}; // TAB DES INDEX DES BONNES REPS


//SETUP//
void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0)) ; //INITIALISATION DE LA FONCTION RANDOM
  
  //CONFIGURATION DES BOUTONS COMME ENTRE
  for (int i = 0; i < 11; i++) {
    pinMode(tabbtn[i], INPUT_PULLUP); }
  
  //CONFIGURATION DES LEDS COMME SORTIE
  pinMode(ledR1, OUTPUT);
  pinMode(ledR2, OUTPUT);
  pinMode(ledR3, OUTPUT);
  pinMode(ledR4, OUTPUT);
  pinMode(ledV, OUTPUT);
  
  //CREATION D'UNE VARIABLE QUI CALCUL LA TENSION AU PIN A0
  float res = ((float)(analogRead(0)*5)/1024);
  //AFFICHE LE RESULTAT
  Serial.println(res); 
  //ATTENTE DE 1 DEMI SECONDE 
  delay(500);     
  
  //APPEL LA FONCTION QUI NOUS RENVOIE LE MODEL
  verifModele(res);
  delay(1000);
    
  nvSecurite(modelActuelle);
}


//TOURNE EN BOUCLE
void loop()
{
}

//FONCTION QUI RENVOIE LE MODEL EN FONCTION DE L'INTENSITE
void verifModele(float resultat) {
  // BORNE INFERIEURE
  float min[8] = {0.0978, 1.4711, 2.1505, 2.8030, 2.9521, 3.1232, 3.3431, 3.5777};
  // BORNE SUPERIEURE
  float max[8] = {1.4663, 2.1476, 2.6513, 2.9472, 3.1183, 3.3382, 3.5728, 4.9951};

  bool trouve = false;  // VARIABLE QUI DEFINIE SI LE MODEL EST TROUVE

  for (int i = 0; i < 8; i++) {
    if (resultat >= min[i] && resultat <= max[i]) {
      Serial.print("C'est le modele : ");
      Serial.println(i + 1);
      modelActuelle = i + 1;
      trouve = true;  //MODEL EST TROUVE
      break;
    }
  }

  //AFFICHE UN MESSAGE SI AUCUN MODEL EST TROUVE
  if (!trouve) {
    Serial.println("aucune carte trouvee");
  }
}


void nvSecurite(int model) {

  // Associe un niveau de sécurité correspondant au paramètre niveau
  int niveauSecurite = niveauxAssocies[model - 1];

  //APPEL LES FONCTIONS CORRESPONDANTES AUX NIVEAUX DE SECURITE
  switch (niveauSecurite) {
    //NIVEAU DE SECURITE 1
    case 1: 
      delay(1000); 				  //ATTENTE D'UNE SECONDE
      MA1();       				 //APPEL DE LA FONCTION MA1
      if (!Etape) break;		//SI LA FONCTION MA1 N'EST PAS VALIDE ALORS ARRETER
      delay(1000);
      MA3();
      Serial.println();						  //SAUT DE LIGNE
      Serial.println("Ouverture du coffre"); //MESSAGE DE REUSSITE
      break;					
    //NIVEAU DE SECURITE 2
    case 2:
      delay(1000);
      MA1();
      if (!Etape) break;
      delay(1000);
      MA4();
      Serial.println();						  
      Serial.println("Ouverture du coffre"); 
      break;
    //NIVEAU DE SECURITE 3
    case 3:
      delay(1000);
      MA2();
      if (!Etape) break;
      delay(1000);
      MA4();
      Serial.println();						  
      Serial.println("Ouverture du coffre"); 
      break;
    //NIVEAU DE SECURITE 4
    case 4:
      delay(1000);
      MA1();
      if (!Etape) break;
      delay(1000);
      MA2();
      if (!Etape) break;
      delay(1000);
      MA3();
      if (!Etape) break;
      delay(1000);
      MA4();
      Serial.println();						  
      Serial.println("Ouverture du coffre"); 
      break;
    //NIVEAU DE SECURITE 5
    case 5:
      delay(1000);
      MA1();
      if (!Etape) break;
      delay(1000);
      MA2();
      if (!Etape) break;
      delay(1000);
      MA3();
      if (!Etape) break;
      delay(1000);
      MA4();
      if (!Etape) break;
      delay(1000);
      MA5Basique();
      Serial.println();						  
      Serial.println("Ouverture du coffre"); 
      break;

    //NIVEAU DE SECURITE 6
    case 6:
      delay(1000);
      MA1();
      if (!Etape) break;
      delay(1000);
      MA2();
      if (!Etape) break;
      delay(1000);
      MA5Basique();
      Serial.println();						  
      Serial.println("Ouverture du coffre"); 
      break;

    //MESSAGE D'ERREUR SI AUCUNE DES VALEURS N'EST TROUVEE
    default:
      Serial.println("Erreur model introuvable");
  }
}


//FONCTION MA1 AUTHENTIFICATION PAR QUESTION/REPONSE
void MA1() {
  //INDEX ALEATOIRE QUI VA SERVIR A CHOISIR UNE QUESTION ALEATOIREMENT DANS LE TABLEAU DE QUESTION
  int index = random(0, 3);
  
  //SAUT DE LIGNE POUR UN AFFICHAGE PLUS CLAIRE
  Serial.println();

  //AFFICHE LA QUESTION
  Serial.println(questions[index]);

  //AFFICHE LES CHOIX DE REPONSE
  for (int i = 0; i < 4; i++) {
    Serial.print(i + 1);
    Serial.print(". ");
    Serial.println(reponses[index][i]);
  }

  //ATTEND UNE REPONSE DE L'UTILISATEUR
  while (Serial.available() == 0) {}
  int reponse = Serial.parseInt();

  //VERIFIE LA REPONSE
  if (reponse - 1 == bonnesReponses[index]) {
    Serial.println("Authentification reussie");
    Etape = true;
  } else {
    Serial.println("Authentification refusee");
    Etape = false;
  }
}

void MA2() {
  int tabCode[4];              // TABLEAU POUR STOCKER LE CODE GENERÉ
  int essaisRestant = 4;       // COMPTEUR D'ESSAIS RESTANTS
  bool codeCorrect = false;    // DÉFINIT SI LE CODE EST CORRECT (faux par défaut)
  
  // SAUT DE LIGNE POUR UN AFFICHAGE PLUS CLAIR
  Serial.println();
  
  // GÉNÈRE CHIFFRE PAR CHIFFRE UN CODE DE 4 CHIFFRES ALÉATOIREMENT
  Serial.print("Votre code est : ");
  for (int i = 0; i < 4; i++) {
    tabCode[i] = random(1, 5);  // PARTIE ALÉATOIRE ENTRE 1 ET 5 (exclus)
    Serial.print(tabCode[i]);   // AFFICHE LE CODE (pour simuler un envoi sur le téléphone de l'agent)
  }
  
  Serial.println();  // SAUT DE LIGNE POUR UN AFFICHAGE PLUS CLAIR
  
  // BOUCLE QUI VÉRIFIE SI IL RESTE DES ESSAIS
  while (essaisRestant > 0 && !codeCorrect) {
    bool correct = true;  // VARIABLE QUI SERT À DÉFINIR SI LE NUMÉRO INSCRIT PAR L'UTILISATEUR EST CORRECT

    // BOUCLE POUR VÉRIFIER CHAQUE CHIFFRE DU CODE
    for (int i = 0; i < 4; i++) {
      Serial.println();
      Serial.print("Appuyez sur le bouton correspondant au numero ");
      Serial.println(i + 1);

      bool btnPresse = false;  // VARIABLE QUI SERT À SAVOIR SI UN BOUTON EST PRESSÉ
      
      // ATTEND QUE L'UTILISATEUR APPUIE ET RELÂCHE UN BOUTON
      while (!btnPresse) {
        // VÉRIFIE POUR CHAQUE BOUTON SI IL EST APPUYÉ
        for (int j = 0; j < 4; j++) {
          if (digitalRead(tabbtn[j]) == LOW) {  // 'LOW' NOUS SIGNIFIE QU'IL EST APPUYÉ
            // Attendre que le bouton soit relâché
            while (digitalRead(tabbtn[j]) == LOW) {
              delay(10);  // Attente pour éviter le rebond
            }

            // VÉRIFICATION SI LE MAUVAIS BOUTON EST PRESSÉ
            if (j != tabCode[i] - 1) {
              correct = false;
              btnPresse = true;
              break;
            } else {
              // SI LE BON BOUTON EST PRESSÉ
              digitalWrite(tabLedR[i], HIGH);  // ALLUME LA LED ROUGE CORRESPONDANTE
              Serial.print("Correct pour le numéro ");
              Serial.println(i + 1);
              btnPresse = true;
            }
          }
        }
      }

      // SORT DE LA BOUCLE SI LE NUMÉRO EST MAUVAIS
      if (!correct) break;
    }

    // COMME LA BOUCLE DE VÉRIFICATION DES 4 CHIFFRES DU CODE EST FINIE
    // ON VÉRIFIE SI LE CODE COMPLET EST CORRECT
    if (correct) {
      codeCorrect = true;
      Serial.println("Code correct !");
      digitalWrite(ledR4, HIGH);
      digitalWrite(ledV, HIGH);  // ALLUMER LA LED VERTE
    } else {
      essaisRestant--;  // -1 AU NOMBRE D'ESSAIS RESTANTS
      Serial.print("Code incorrect, il reste ");  // AFFICHE LE NOMBRE D'ESSAIS RESTANTS
      Serial.print(essaisRestant);
      Serial.println(" essais");
    }

    // SI LE NB D'ESSAIS MAX EST ATTEINT
    if (essaisRestant == 0 && !codeCorrect) {
      Serial.println("Code incorrect, Authentification refusée.");
    }
  }
}


//FONCTION MA3 SCAN RETINIEN (SIMULEE PAR UN MESSAGE)
void MA3(){
  
  //SAUT A LA LIGNE POUR UN AFFICHAGE PLUS CLAIRE
  Serial.println();
  //AFFICHE CE MESSAGE POUR PLUS DE REALISME
  Serial.println("Approchez vous pour un scan retinien.");
  //DELAI D'UN SECONDE AVANT LE PROCHAIN MESSAGE
  delay(1000);
  Serial.println("...");
  delay(1000);
  Serial.println("Scan retinien reussi.");
  Etape = true;
}


//FONCTION MA4 SCAN DIGITAL (SIMULEE PAR UN MESSAGE)
void MA4(){
  
  //SAUT DE LIGNE POUR UN AFFICHAGE PLUS CLAIRE
  Serial.println();
  Serial.println("Approchez vous pour un scan digital.") ;
  //DELAI D'UN SECONDE AVANT LE PROCHAIN MESSAGE
  delay(1000);
  Serial.println("...") ;
  delay(1000);
  Serial.println("Scan digital reussi.") ;
  Etape = true;
}


//FONCTION MA5 BASIQUE
void MA5Basique() {
  
    //TABLEAU POUR STOCKER LES LETTRES QUI VONT ETRE VERIFIER  
    char lettreAttendue[16] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'}; 
   //EQUIVALENT POUR CARTE ID:  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16
  
    
    //SAUT DE LIGNE POUR UN AFFICHAGE PLUS CLAIRE
    Serial.println();
    //DEMANDE LE N° CARTE ID
    Serial.println("Entrez le numero de votre carte :") ;
    //BOUCLE NON BORNE QUI N'EXECUTE RIEN TANT QU'IL N'Y A PAS DE SAISI
    while (Serial.available() == 0) {}  
    //STOCK LE N° SAISIE PAR L'UTILISATEUR
    int chiffre = Serial.parseInt();          

    //VERIFIE SI LE CHIFFRE SAISIE PAR L'UTILISATEUR EST BIEN ENTRE 1 ET 16
    if (chiffre < 1 || chiffre > 16) {       // LE '||' SIGNIFIE 'OU'
        Serial.println("Numero invalide") ; //AFFICHE UNE ERREUR CAR LE CHIFFRE N'EST PAS ENTRE 1 ET 16
        return; //Stop la fonction
    }

    //DEMANDE LA LETTRE DE L'AGENT
    Serial.println("Entrez votre lettre d'agent :");
    while (Serial.available() == 0) {} 
    //STOCK LA LETTRE SAISIE PAR L'UTILISATEUR
    char lettre = Serial.read();               

    //VERIFICATION DE LA LETTRE ATTENDU (le '-1' est la pour retrouver la lettre au bon indice du tableau)
    if (lettre == lettreAttendue[chiffre - 1]) {
        Serial.println("Authentification reussie") ; //AFFICHE UN MESSAGE DE REUSSITE
        Etape = true;

     //SI IL N'Y A PAS DE CORRESPONDANCE
    } else {
        Serial.println("Correspondance incorrecte") ; //AFFICHE UN MESSAGE D'ERREUR
        Etape = false;
    }
}

