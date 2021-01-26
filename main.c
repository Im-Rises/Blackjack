#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#include "joueur.h"


int main(int argc, int *argv[])
{
	int nbJoueurs=0;						//Initialisation du nombre de joueurs � 0
	
	srand(time(NULL)); //Initialisation de la donn�e seed en fonctiond de l'heure du PC qui va permettre d'avoir une valeur pseudo-al�atoire � l'appel de rand()

	Carte listeCartes[NOMBRE_CARTES];		//Cr�ation du tableau des cartes
	Joueur listeJoueurs[NOMBRE_JOUEUR_MAX];	//Cr�ation du tableau des joueurs
	Joueur croupier = {"Croupier"};			//Cr�ation du croupier
	
	afficherMessageInitialisation();//Affichage message d'initialisation
	
	/*
	* Cr�ation des joueurs
	*/
	creerJoueurs(listeJoueurs,&nbJoueurs);	//Initialisation des joueurs en fonction du nb de joueur qui va �tre choisis
	//afficherJoueurs(listeJoueurs);			//Affiche les joueurs qui jouent


	/*
	* Cr�ation du croupier
	*/
	creationCroupier(croupier);				//Initialisation du croupier
	
	/*
	* Cr�ation des cartes du jeu sous forme de liste
	*/
	creationCartesJeu(listeCartes);			//Initialisation de toutes les cartes
	

	do
	{
		/*
		* M�lange du jeu avant chaque tour
		*/
		melangerCartesJeu(listeCartes);							//M�lange des cartes du jeu


		////////////////////////////
		/*
		* D�but du jeu, pioche de deux cartes par tous les joueurs
		*/
		listeJoueursPiocheCartes(listeJoueurs, listeCartes);	//Pioche de cartes par tous les joueurs
		afficherMessageDistributionCartes();					//Affiche le message de distribution des cartes
		affichageCartesListeJoueurs(listeJoueurs);				//Affichage de toutes les cartes pioch�es par les joueurs
		calculListeJoueursNbPoints(listeJoueurs);				//calcul et affiche le nombre de points de tous les joueurs qui jouent

		/*
		* Le croupier pioche ses cartes
		*/
		joueurPiocheCartes(&croupier, listeCartes);				//Picohe de cartes par le croupier
		afficherCartesCroupier(croupier, 1);					//Affichage d'une carte du croupier et l'autre face cach�e	
		calculJoueurNbPoints(&croupier);						//Calcul le nombre de points du croupier
		
		/*
		* Pioche pour le joueur jusqu'� un score satisfaisant
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
		nouvellePiocheJoueurOrdi(&croupier, listeCartes);		//Pioche croupier de cartes si score inf�rieur � 17

		/*
		* Comparaison des scores des joueurs par rapport au croupier
		*/
		Sleep(3000); //Arr�te le programme 3s
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
		Sleep(3000); //Arr�te le programme 3s
		afficherMessageNouveauTour(listeJoueurs[0]);			//Affiche message de nouveau tour si le l'utilisateur rejoue un tour

	} while (listeJoueurs[0].joueurJoue==JOUEURJOUE);			//Boucle while de gestion de rejoue du joueur utilisateur

	afficherFinDePartie();
	Sleep(1500); //Arr�te le programme 3s
}
