#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#include "joueur.h"


int main(int argc, int *argv[])
{
	int nbJoueurs=0;						//Initialisation du nombre de joueurs à 0
	
	srand(time(NULL)); //Initialisation de la donnée seed en fonctiond de l'heure du PC qui va permettre d'avoir une valeur pseudo-aléatoire à l'appel de rand()

	Carte listeCartes[NOMBRE_CARTES];		//Création du tableau des cartes
	Joueur listeJoueurs[NOMBRE_JOUEUR_MAX];	//Création du tableau des joueurs
	Joueur croupier = {"Croupier"};			//Création du croupier
	
	afficherMessageInitialisation();//Affichage message d'initialisation
	
	/*
	* Création des joueurs
	*/
	creerJoueurs(listeJoueurs,&nbJoueurs);	//Initialisation des joueurs en fonction du nb de joueur qui va être choisis
	//afficherJoueurs(listeJoueurs);			//Affiche les joueurs qui jouent


	/*
	* Création du croupier
	*/
	creationCroupier(croupier);				//Initialisation du croupier
	
	/*
	* Création des cartes du jeu sous forme de liste
	*/
	creationCartesJeu(listeCartes);			//Initialisation de toutes les cartes
	

	do
	{
		/*
		* Mélange du jeu avant chaque tour
		*/
		melangerCartesJeu(listeCartes);							//Mélange des cartes du jeu


		////////////////////////////
		/*
		* Début du jeu, pioche de deux cartes par tous les joueurs
		*/
		listeJoueursPiocheCartes(listeJoueurs, listeCartes);	//Pioche de cartes par tous les joueurs
		afficherMessageDistributionCartes();					//Affiche le message de distribution des cartes
		affichageCartesListeJoueurs(listeJoueurs);				//Affichage de toutes les cartes piochées par les joueurs
		calculListeJoueursNbPoints(listeJoueurs);				//calcul et affiche le nombre de points de tous les joueurs qui jouent

		/*
		* Le croupier pioche ses cartes
		*/
		joueurPiocheCartes(&croupier, listeCartes);				//Picohe de cartes par le croupier
		afficherCartesCroupier(croupier, 1);					//Affichage d'une carte du croupier et l'autre face cachée	
		calculJoueurNbPoints(&croupier);						//Calcul le nombre de points du croupier
		
		/*
		* Pioche pour le joueur jusqu'à un score satisfaisant
		*/
		affficherMessagePiocheJoueurs();						//Affichage message "PIOCHE JOUEURS"
		nouvellePiocheJoueur(listeJoueurs, listeCartes);		//Nouvelle pioche pour tous les joueurs

		/*
		* Pioche des joueurs ordi
		*/
		nouvellePiocheJoueursOrdi(listeJoueurs, listeCartes);	//Nouvelle pioches des joueurs ordinateurs

		/*
		* Pioche du croupier
		*/
		afficherCartesCroupier(croupier, 2);					//Affichage des deux cartes du croupier
		nouvellePiocheJoueurOrdi(&croupier, listeCartes);		//Pioche croupier de cartes si score inférieur à 17

		/*
		* Comparaison des scores des joueurs par rapport au croupier
		*/
		Sleep(3000); //Arrête le programme 3s
		afficherMessageComparaisonScore();						//Affichage du message "COMPARASION DES SCORES"
		comparerPointsJoueursCroupier(croupier, listeJoueurs);	//Comparer les points des joueurs au croupier

		/*
		* Remise des cartes dans le paquet
		*/
		reinitialiserCartesPiochees(listeCartes);				//Remet toutes les cartes dans le paquet

		/*
		* Fin tant que joueur veut jouer et qu'il a toujours des points
		*/
		demandeJoueurJoue(listeJoueurs);						//Demande au joueur, s'il veut rejouer
		Sleep(3000); //Arrête le programme 3s
		afficherMessageNouveauTour(listeJoueurs[0]);			//Affiche message de nouveau tour si le l'utilisateur rejoue un tour

	} while (listeJoueurs[0].joueurJoue==JOUEURJOUE);			//Boucle while de gestion de rejoue du joueur utilisateur

	afficherFinDePartie();
	Sleep(1500); //Arrête le programme 3s
}
