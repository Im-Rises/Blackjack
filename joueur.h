#ifndef DEF_JOUEUR
#define DEF_JOUEUR

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define NOMBRE_SYMBOLE_CARTE 4
#define NOMBRE_RANG_CARTE 13
#define NOMBRE_CARTES (NOMBRE_SYMBOLE_CARTE*NOMBRE_RANG_CARTE)
#define NOMBRE_JETONS 20
#define NOMBRE_JOUEUR_MAX 8


/*--------------------------------------------------------------------Enumerations-------------------------------------------------------*/

//Création d'une énumération qui indique si la carte est piochée ou non
typedef enum Pioche Pioche;
enum Pioche
{
	CARTEPIOCHEE = 1, CARTENONPIOCHEE = 0
};

typedef enum Joue Joue;
enum Joue
{
	JOUEURJOUE = 1, JOUEURJOUEPAS = 0
};



/*--------------------------------------------------------------------Strucutres-------------------------------------------------------*/

typedef struct Carte Carte;
struct Carte
{
	Pioche cartepiochee;			//Carte piochée par un joueur pour une valeur de 1 sinon 0
	char symbole;					//Symbole de la carte P, C, K , T correspondant réspectivement à Pic, Coeur, Carreau, Trèfle
	char rang;						//Rang de la carte 2, 3, 4, 5, 6, 7, 8, 9, 10 ainsi que les figures, Valet, Dame et Roi (le 10 est réprésenté par un X)
};

typedef struct Joueur Joueur;
struct Joueur
{
	char nom[10];					//Nom des joueurs avec un numéro excepté le croupier qui s'appelle "croupier"
	Joue joueurJoue;				//Donne l'indication si le joueur joue ou non
	int nbJetons;					//Nombre de jetons du joueur
	Carte carte[2];					//Les deux cartes piochées par le joueur
	int nbPoints;					//Nombre de points du joueur (calculés en fonction des cartes)
	int mise;						//Mise du joueur (non pris en compte actuellement)
};







/*-------------------------------------------------------------------------Fonctions cartes-------------------------------------------------------*/

void creationCartesJeu(Carte carte[]);

//void affichageCartesJeu(const Carte carte[]);

void melangerCartesJeu(Carte listeCartes[]);

static void piocheListeCartesDecalage(Carte listeCartes[]);

void reinitialiserCartesPiochees(Carte listeCartes[]);




/*------------------------------------------------------------------Fonctions créations affichage joueurs------------------------------------------------------*/

void creerJoueurs(Joueur listeJoueurs[], int *nbJoueurs);

static void choixNbJoueurs(int* nbJoueurs);

//void afficherJoueurs(const Joueur listeJoueurs[]);

void affichageCartesJoueur(const Joueur* joueur);

void affichageCartesListeJoueurs(const Joueur listeJoueurs[]);



/*-------------------------------------------------------------------Fonctions création affichage croupier------------------------------------------------------*/

void creationCroupier(Joueur croupier);

void afficherCartesCroupier(const Joueur croupier,int nbCartesAffichees);



/*------------------------------------------------------------------Fonctions attribution cartes initiales------------------------------------------------------*/

void joueurPiocheCartes(Joueur* joueurPiochant, Carte listeCartes[]);

void listeJoueursPiocheCartes(Joueur joueurs[], Carte listeCartes[]);




/*-------------------------------------------------------------------------Calcul points joueurs------------------------------------------------------*/

void calculJoueurNbPoints(Joueur* joueur);

void calculListeJoueursNbPoints(Joueur listeJoueurs[]);

static int calculJoueurNbPointsCharToInt(char rang);



/*-------------------------------------------------------------------------Nouvelle pioche joueurs------------------------------------------------------*/

void nouvellePiocheJoueur(Joueur listeJoueurs[], Carte listeCartes[]);



/*---------------------------------------------------------------------Nouvelle pioche joueurs ordinateur------------------------------------------------------*/

void nouvellePiocheJoueursOrdi(Joueur listeJoueurs[], Carte listeCartes[]);

void nouvellePiocheJoueurOrdi(Joueur *croupier, Carte listeCartes[]);


/*--------------------------------------------------------------Comparasaion points joueurs/croupier et croupier------------------------------------------------------*/

void comparerPointsJoueursCroupier(Joueur croupier, Joueur listeJoueurs[]);


/*--------------------------------------------------------------------------Gestion nouveau tour---------------------------------------------------------------------*/

void demandeJoueurJoue(Joueur listeJoueurs[]);


/*----------------------------------------------------------------------------Fonction autres------------------------------------------------------------------*/

static void calculNbAs(Joueur joueur, int* nbAs);

static char convertIntToChar(int entier);

int ouiOuNonBool();

void viderMemoireTampon();

int valAleatoire(const int valMax);


/*---------------------------------------------------------------------Fonction pour séparation des étapes------------------------------------------------------------------*/

void afficherMessageInitialisation();

void afficherMessageDistributionCartes();

void affficherMessagePiocheJoueurs();

void afficherMessageComparaisonScore();

void afficherMessageNouveauTour(Joueur joueur);

void afficherFinDePartie();



#endif