#include "joueur.h"



/*--------------------------------------------------------------------Fonctions cartes-------------------------------------------------------*/

void creationCartesJeu(Carte carte[])
{
	/*
	* Fonction de créations du jeu de carte.
	* 
	* La fonction reçoit en paramètre une liste de type de la strucutre de type carte. La fonction initialise deux tableaux statiques 
	* qui définissent le score d'une carte de '2' à 'A', l'autre tableau son symbole (pique, coeur, carreau et trèfle).
	* Une boucle for est ensuite fait pour initialiser toutes la liste des cartes du jeu avec son symbole et sa valeur.
	*/

	char typeRang[] = { '2','3','4','5','6','7','8','9','X','V','D','R','A' };
	char typeSymbole[] = { 'P','C','K','T' };

	for (int i = 0; i < NOMBRE_CARTES; i++)
	{
		carte[i].cartepiochee = CARTENONPIOCHEE;

		if (i < NOMBRE_RANG_CARTE)
		{
			carte[i].symbole = typeSymbole[0];
			carte[i].rang = typeRang[i];
		}
		else if (i < NOMBRE_RANG_CARTE*2)
		{
			carte[i].symbole = typeSymbole[1];
			carte[i].rang = typeRang[i- NOMBRE_RANG_CARTE];
		}
		else if (i < NOMBRE_RANG_CARTE*3)
		{
			carte[i].symbole = typeSymbole[2];
			carte[i].rang = typeRang[i- NOMBRE_RANG_CARTE*2];
		}
		else
		{
			carte[i].symbole = typeSymbole[3];
			carte[i].rang = typeRang[i- NOMBRE_RANG_CARTE*3];
		}
	}
}

//void affichageCartesJeu(const Carte carte[])
//{
//	/*
//	* Fonction d'affichage de toutes les cartes du jeu
//	*
//	* La fonction parcours toutes le liste de type carte envoyé en paramètre, la parcours et affiche chaque carte.
//	*/
//
//	for (int i = 0; i < NOMBRE_CARTES; i++)
//	{
//		printf("%c %c",carte[i].symbole, carte[i].rang);				
//	}
//}

void melangerCartesJeu(Carte listeCartes[])
{
	/*
	* Fonction de mélanges des cartes du jeu.
	* 
	* La fonction reçoit en paramètre la liste des cartes et mélange le tout afin que les cartes ne soit pas dans l'ordre de l'initialisation.
	* Dans un for on va parcourir la liste des cartes et inverser la place de chaque carte une fois avec une autre carte de la liste choisie au hasard.
	*/
	Carte tempo;
	int valEchange;

	for (int i = 0; i < NOMBRE_CARTES ; i++)
	{
		valEchange = valAleatoire(NOMBRE_CARTES);

		tempo = listeCartes[i];

		listeCartes[i] = listeCartes[valEchange];
		listeCartes[valEchange] = tempo;
	}
}


static void piocheListeCartesDecalage(Carte listeCartes[])
{
	/*
	* Fonction de décalage des cartes du début de la liste à la fin de la liste.
	* 
	* La fonction décale la carte en haut du paquet à la fin du paquet. Décalage de toutes les cartes d'un rang
	* et donc de la carte en position 0 en position max du tableau.
	* Le principe suit une pile FIFO.
	*/
	Carte tempo = listeCartes[0];

	for (int i = 0; i < NOMBRE_CARTES; i++)
	{
		if (i < NOMBRE_CARTES-1)
			listeCartes[i] = listeCartes[i + 1];
	}

	listeCartes[NOMBRE_CARTES - 1] = tempo;
}


void reinitialiserCartesPiochees(Carte listeCartes[])
{
	/*
	* Fonction qui remet toutes les cartes dans le paquet.
	* 
	* La fonction reçoit en paramètre une liste de cartes et les redéfinies à toutes le paramètres "cartepiochee" en CARTENONPIOCHEE
	*/
	for (int i = 0; i < NOMBRE_CARTES; i++)
	{
		listeCartes[i].cartepiochee = CARTENONPIOCHEE;
	}
}







/*--------------------------------------------------------------------Fonctions créations affichage joueurs------------------------------------------------------*/

void creerJoueurs(Joueur listeJoueurs[],int *nbJoueurs)
{
	/*
	* Fonction de création des joueurs.
	* 
	* La fonction reçoit en paramètre une liste de joueurs avec un nombre de joueurs à initialiser.
	* Un numéro est attribué à tous les joueurs ainsi qu'un nombre de jetons, un nombre de points initialiser à 0
	* car aucun joueurs n'a encore de cartes. Le dernier paramètre modifier est "joueurJoue" qui est passé à JOUEURJOUE.
	*/
	choixNbJoueurs(nbJoueurs);	

	for (int i = 0; i < *nbJoueurs; i++)
	{		
			listeJoueurs[i].nom[0] = 'J';
			listeJoueurs[i].nom[1] = 'o';
			listeJoueurs[i].nom[2] = 'u'; 
			listeJoueurs[i].nom[3] = 'e';
			listeJoueurs[i].nom[4] = 'u';
			listeJoueurs[i].nom[5] = 'r';
			listeJoueurs[i].nom[6] = ' ';
			listeJoueurs[i].nom[7] = convertIntToChar(i+1);
			listeJoueurs[i].nom[8] = '\0';

			listeJoueurs[i].nbJetons = NOMBRE_JETONS;
			listeJoueurs[i].nbPoints = 0;
			listeJoueurs[i].joueurJoue = JOUEURJOUE;	
			listeJoueurs[i].mise = 0;
	}
}

static void choixNbJoueurs(int* nbjoueurs)
{
	/*
	* Fonction de récupération du nombre de joueurs.
	* 
	* La fonction reçoit en pramètre un nombre de joueurs et le modifier en fonction de la sélection de l'utilisateur.
	*/
	int erreur;
	do
	{
		printf("Veuillez selectionner le nombre de joueur de 1 a 8 (hors croupier) : ");
		erreur = scanf("%1d", nbjoueurs);
		
		if (erreur != 1)
		{
			printf("Erreur saisie incorrecte, veuillez selectionner une variable de 1 a 8.\n");		
			*nbjoueurs = 0;
		}
		viderMemoireTampon();

	} while (*nbjoueurs < 1 || *nbjoueurs>8);
}

//void afficherJoueurs(const Joueur listeJoueurs[])
//{
//	/*
//	* Fonction d'affichage des joueurs qui jouent.
//	* 
//	* La fonction reçoit en paramètres la liste de joueurs avec leur numéro et leur nombre de jetons.
//	* Les joueurs ne sont affichés que si les joueurs ont le paramètre "joueurJoue" sur "JOUEURJOUE".
//	*/
//	for (int i = 0; i < NOMBRE_JOUEUR_MAX; i++)
//	{
//		if (listeJoueurs[i].joueurJoue == JOUEURJOUE)
//			printf("Le joueur \"%s\" joue.\n", listeJoueurs[i].nom);
//			//printf("Le joueur \"%s\" joue et a %d jetons.\n", listeJoueurs[i].nom, listeJoueurs[i].nbJetons);
//	}
//}


void affichageCartesJoueur(const Joueur* joueur)
{
	/*
	* Fonction d'afichage des cartes d'un joeur.
	* 
	* La fonction affiche le joueur si ce dernier joue, donc si le joueur a le paramètre "joueurJoue" sur "JOUEURJOUE".
	*/
	if (joueur->joueurJoue == JOUEURJOUE)
	{
		printf("Le %s a les cartes :\n%c %c\n", joueur->nom, joueur->carte[0].symbole, joueur->carte[0].rang);
		printf("%c %c\n", joueur->carte[1].symbole, joueur->carte[1].rang);
	}
}

void affichageCartesListeJoueurs(const Joueur listeJoueurs[])
{
	/*
	* Fonction pour l'affichage de tous les joueurs 
	* 
	* La fonction parcours la liste des joueurs envoyé en apramètre et appelle la fonction affichageCartesJoueur.
	*/
	for (int i = 0; i < NOMBRE_JOUEUR_MAX; i++)
	{
		affichageCartesJoueur(&listeJoueurs[i]);
	}
}






/*--------------------------------------------------------------------Fonctions création affichage croupier------------------------------------------------------*/

void creationCroupier(Joueur croupier)
{
	/*
	* Fonction de création du croupier.
	* 
	* La fonction crée le croupier en lui attribuant un nom et lui attribue
	* le nombre de point de base de 0 car le joueur n'a aps encore pioché.
	*/
	croupier.nom[0] = 'C';
	croupier.nom[1] = 'r';
	croupier.nom[2] = 'o';
	croupier.nom[3] = 'u';
	croupier.nom[4] = 'p';
	croupier.nom[5] = 'i';
	croupier.nom[6] = 'e';
	croupier.nom[7] = 'r';
	croupier.nom[8] = '\0';

	croupier.nbPoints = 0;
	croupier.joueurJoue = JOUEURJOUE;
}

void afficherCartesCroupier(const Joueur croupier, int nbCartesAffichees)
{
	/*
	* Fonction d'affichage des cartes du croupier.
	* 
	* La fonction reçoit en paramètre l'objet croupier et le nombre de cartes à afficher sous forme d'eniter.
	* Une seule carte du croupier est affichée si la valeur de "nbCartesAffichees" vaut 1, dans l'utre cas les deux cartes sont affichées.
	*/
	printf("Le %s a les cartes :\n%c %c\n", croupier.nom, croupier.carte[0].symbole, croupier.carte[0].rang);
	if (nbCartesAffichees==1)
		printf("? ?\n");
	else 
		printf("%c %c\n", croupier.carte[1].symbole, croupier.carte[1].rang);
}






/*--------------------------------------------------------------------Fonctions attribution cartes initiales------------------------------------------------------*/

void joueurPiocheCartes(Joueur *joueurPiochant, Carte listeCartes[])
{
	/*
	* Fonction de pioche d'un joueur.
	* 
	* La fonction reçoit en paramètre un joueur et la liste des cartes.
	* Le joueur est modifié afin de lui attribuer deux cartes, les deux en haut du paquet (en position 0 et 1 de la liste de cartes).
	* La fonction "piocheListeCartesDecalage" est appelée ensuite pour décaler les cartes de paquet et mettre les cartes piochés en dehors
	* portée des joueurs suivant qui pourraient piocher.
	*/
	joueurPiochant->carte[0] = listeCartes[0];
	listeCartes[0].cartepiochee = CARTEPIOCHEE;
	piocheListeCartesDecalage(listeCartes);
	joueurPiochant->carte[1] = listeCartes[0];
	listeCartes[0].cartepiochee = CARTEPIOCHEE;
	piocheListeCartesDecalage(listeCartes);
}

void listeJoueursPiocheCartes(Joueur joueurs[], Carte listeCartes[])
{
	/*
	* Fonction de pioche de la liste de joueurs
	* 
	* La fonction reçoit en paramètre la liste des joueurs et la parcours afin d'attribuer deux cartes de base
	* a chaque joueurs avec l'appel de la fonction "joueurPiocheCartes".
	*/
	for (int i = 0; i < NOMBRE_JOUEUR_MAX; i++)
	{
		if (joueurs[i].joueurJoue == JOUEURJOUE)
			joueurPiocheCartes(&joueurs[i], listeCartes);
	}
}







/*--------------------------------------------------------------------Calcul points joueurs------------------------------------------------------*/

void calculJoueurNbPoints(Joueur *joueur)
{
	/*
	* Fonction de calcul des points de base du joueur en fonction des cartes piochées.
	* 
	* La fonction reçoit en paramètre un joueur et modifier le paramètre du joueur nbPoints avec
	* la valeur des deux cartes que possède de base le joueur.
	*/
	joueur->nbPoints=calculJoueurNbPointsCharToInt(joueur->carte[0].rang)+ calculJoueurNbPointsCharToInt(joueur->carte[1].rang);
}

static int calculJoueurNbPointsCharToInt(char rang)
{
	/*
	* Fonction de conversion du rang d'un carte sous forme d'entier.
	* 
	* La foncton reçoit en paramètre le rang d'une carte sous forme de char et le converti en sa valeu réspective.
	*/
	switch (rang)
	{
	case('2'):
		return 2;
		break;
	case('3'):
		return 3;
		break;
	case('4'):
		return 4;
		break;
	case('5'):
		return 5;
		break;
	case('6'):
		return 6;
		break;
	case('7'):
		return 7;
		break;
	case('8'):
		return 8;
		break;
	case('9'):
		return 9;
		break;
	case('X'):
		return 10;
		break;
	case('V'):
		return 10;
		break;
	case('D'):
		return 10;
		break;
	case('R'):
		return 10;
		break;
	case('A'):
		return 11;
		break;
	default:
		return 0;
		break;
	}
}

void calculListeJoueursNbPoints(Joueur listeJoueurs[])
{
	/*
	* Fonction de calcul des points de base des joueurs en fonction de leurs cartes piochées de base.
	* 
	* La fonction reçoit en paramètre la liste des joueurs et les parcours tous via un for afin de mettre 
	* à jour leur nombre de points de base en fonction de leurs cartes piochées de base, via l'appel de 
	* la fonction "calculJoueurNbPoints"
	*/
	for (int i = 0; i < NOMBRE_JOUEUR_MAX; i++)
	{
		if (listeJoueurs[i].joueurJoue == JOUEURJOUE)
			calculJoueurNbPoints(&listeJoueurs[i]);
	}
}






/*--------------------------------------------------------------------Nouvelle pioche joueurs------------------------------------------------------*/

void nouvellePiocheJoueur(Joueur listeJoueurs[], Carte listeCartes[])
{
	/*
	* Fonction de gestion d'une nouvelle pioche de l'utilisateur
	* 
	* La fonction reçoit en paramètre la liste des joueurs et la liste des cartes et va
	* traiter en fonction des cartes et du nombre de points le fait que le joueur puisse repiocher ou non
	* et s'il veut repiocher. La fonction prend en compte le nombre d'as qu'a le joueur afin que s'il possède 
	* un as au minimum et un score supérieur à 21, son nombre de points soit diminuer de 10 car la carte As prend 
	* une valeur de 11 à 1.
	*/
	if (listeJoueurs[0].joueurJoue == JOUEURJOUE)
	{
		affichageCartesJoueur(&listeJoueurs[0]);
		//Affichage des données du joueur
		printf("Nombre de point du %s est de %d\n", listeJoueurs[0].nom, listeJoueurs[0].nbPoints);
		printf("Gestion nouvelle pioche %s\n", listeJoueurs[0].nom);
		Sleep(1000);

		if (listeJoueurs[0].nbPoints == 21)//Cas où le joueur a de base le score maximum
		{
			printf("Vous avez le score maximum, vous ne pouvez pas repiocher.\n");
		}
		else//Cas où le joueur a un score différent de 21
		{
			int nbAs = 0;
			calculNbAs(listeJoueurs[0], &nbAs);//Relevée du nombre d'As de base du joueur

			if (nbAs == 2)//Cas où le joueur a deux As alors un de ses As passe à une valeur de 1, son nombre d'as est donc diminué de 1
			{
				printf("Vous avez un score de 22 car deux As, un va valoir 1 et vous pouvez repiocher si vous voulez. Vous avez donc un score de 12 actuellement.\n");
				nbAs = nbAs - 1;
				listeJoueurs[0].nbPoints = listeJoueurs[0].nbPoints - 10;
			}
			else//Cas où le jouer a un score inférieur à 21 avec moins de deux As
			{
				printf("Vous avez un score inferieur a 21 d'une valeur de %d, vous pouvez repiocher si vous voulez.\n", listeJoueurs[0].nbPoints);
			}

			/*
			* Gestion nouvelle pioche du joueur
			*/

			int repioche = ouiOuNonBool();//Demande au joueur s'il veut repicoher ou non
			Sleep(3000); //Arrête le programme 3s

			while (repioche == 1)//Si le joueur souhaite repiocher
			{
				//Pioche d'une nouvelle carte
				repioche = 0;
				Carte tempo = listeCartes[0];
				listeCartes[0].cartepiochee = CARTEPIOCHEE;
				piocheListeCartesDecalage(listeCartes);

				//Si la carte est un As alors on incrémente le nombre d'As du joueur
				if (tempo.rang == 'A')
					nbAs = nbAs + 1;

				//affichage de la carte piochée par le joueur
				printf("La carte piochee est : \n%c %c\n", tempo.symbole, tempo.rang);

				//Mise à jour des points du joueur
				listeJoueurs[0].nbPoints = listeJoueurs[0].nbPoints + calculJoueurNbPointsCharToInt(tempo.rang);

				//Affichage du nouveau score du joueur
				printf("Nouveau score du %s est de %d\n", listeJoueurs[0].nom, listeJoueurs[0].nbPoints);

				//Gestion du cas où le joueur a un score supérieur à 21 et un nombre d'As supérieur à 1
				if (listeJoueurs[0].nbPoints > 21 && nbAs > 0)
				{
					printf("Vous avez depasse 21 de score mais vous aviez un As qui valait encore 11 il est donc passe a une valeur de 1\n");
					nbAs = nbAs - 1;
					listeJoueurs[0].nbPoints = listeJoueurs[0].nbPoints - 10;
					printf("Nouveau score : %d\n", listeJoueurs[0].nbPoints);
				}

				//Gestion des autres cas
				if (listeJoueurs[0].nbPoints > 21)//Gestion du joueur, si son nombre de points est supérieur à 21 sans As
				{
					printf("Vous avez depasse le score max de 21 sans As, vous avez perdu ce tour\n");
				}
				else if (listeJoueurs[0].nbPoints == 21)//Gestion du joueur dans le cas où son score est de 21
				{
					printf("Vous avez un score de 21 le score maximum, vous ne pouvez plus repiocher a moins que vous vouliez perdre.\n");
					repioche = 0;
				}
				else//Gestion du joueur dans le cas où son score est inférieur à 21
				{
					printf("Voules-vous encore repiocher ?\n");
					repioche = ouiOuNonBool();
				}
			}
		}
		printf("\n\n");
		Sleep(1000);
	}
}






/*--------------------------------------------------------------------Nouvelle pioche joueurs/croupier ordinateurs------------------------------------------------------*/

void nouvellePiocheJoueursOrdi(Joueur listeJoueurs[], Carte listeCartes[])
{
	/*
	* Fonction de nouvelle pioche des joueurs ordinateurs.
	* 
	* La fonction reçoit en paramètre la liste des joueurs et la parcours tout en appelant la fonction
	* "nouvellePiocheJoueurOrdi afin de les faire repiocher en fonction de leur score.
	* 
	*/
	for (int i = 1; i < NOMBRE_JOUEUR_MAX; i++)
	{
		if (listeJoueurs[i].joueurJoue == JOUEURJOUE)
		{
			affichageCartesJoueur(&listeJoueurs[i]);
			nouvellePiocheJoueurOrdi(&listeJoueurs[i],listeCartes);
			printf("\n\n");
			Sleep(1000);
		}
	}
}


void nouvellePiocheJoueurOrdi(Joueur *joueur, Carte listeCartes[])
{
	/*
	* Fonction de nouvelle pioche de cartes d'un ou du croupier.
	* 
	* La fonction reçoit en paramètre un joueur ou le corupier et lui fait repiocher 
	* une carte jusqu'à ce que le joueur ai un score supérieur ou égale à 17.
	*/

	//Affichage des données du joueur
	printf("Nombre de point du %s est de %d\n", joueur->nom, joueur->nbPoints);
	printf("Gestion nouvelle pioche %s\n", joueur->nom);
	Sleep(1000);

	if (joueur->nbPoints == 21)//Cas où le joueur a de base le score maximum
	{
		printf("Le %s a le score max de 21.\n",joueur->nom);
	}
	else//Cas où le joueur a un score différent de 21
	{
		int nbAs = 0;
		calculNbAs(*joueur, &nbAs);//Relevée du nombre d'As de base du joueur

		if (nbAs == 2)//Cas où le joueur a deux As alors un de ses As passe à une valeur de 1, son nombre d'as est donc diminué de 1
		{
			printf("Le %s a un score de 22 car deux As, un va valoir 1 et il peut repiocher si son score est inferieur a 17. Vous avez donc un score de 12 actuellement.\n",joueur->nom);
			nbAs = nbAs - 1;
			joueur->nbPoints = joueur->nbPoints - 10;
		}
		else//Cas où le jouer a un score inférieur à 21 avec moins de deux As
		{
			printf("Le %s a un score inferieur a 21 d'une valeur de %d.\n", joueur->nom,joueur->nbPoints);
		}

		/*
		* Gestion nouvelle pioche du joueur
		*/
		int repioche = 0;

		if (joueur->nbPoints < 17)
			repioche = 1;

		Sleep(3000); //Arrête le programme 3s

		while (repioche == 1)
		{
			repioche = 0;
			Carte tempo = listeCartes[0];
			listeCartes[0].cartepiochee = CARTEPIOCHEE;
			piocheListeCartesDecalage(listeCartes);

			if (tempo.rang == 'A')
				nbAs = nbAs + 1;

			printf("La carte piochee est : \n%c %c\n", tempo.symbole, tempo.rang);

			joueur->nbPoints = joueur->nbPoints + calculJoueurNbPointsCharToInt(tempo.rang);

			printf("Nouveau score du %s est de %d\n", joueur->nom, joueur->nbPoints);


			if (joueur->nbPoints > 21 && nbAs > 0)
			{
				printf("Le %s a depasse 21 de score mais avait un As qui valait encore 11 il est donc passe a une valeur de 1\n",joueur->nom);
				nbAs = nbAs - 1;
				joueur->nbPoints = joueur->nbPoints - 10;
				printf("Nouveau score : %d\n", joueur->nbPoints);
			}

			if (joueur->nbPoints > 21)
			{
				printf("Le %s a depasse le score max de 21 sans As.\n",joueur->nom);
			}
			else if (joueur->nbPoints == 21)
			{
				printf("La %s a un score de 21 le score maximum, il ne peut plus repiocher.\n",joueur->nom);
				repioche = 0;
			}
			else
			{
				if (joueur->nbPoints < 17)
					repioche = 1;
			}
		}
	}
}



/*--------------------------------------------------------------Comparaison points joueurs et croupier------------------------------------------------------*/

void comparerPointsJoueursCroupier(Joueur croupier, Joueur listeJoueurs[])
{
	/*
	* Fonction de comparaison du score du croupier avec les différents joueurs.
	* 
	* La focntion reçoit en paramètre le croupier ainsi que la liste des joueurs. Elle va ensuite parcorir la lsite
	* des joueurs via un for et comparer le score du joueur au croupier et déterminer lequel a perdu ou gagné ce tour.
	*/
	for (int i = 0; i < NOMBRE_JOUEUR_MAX; i++)
	{
		Sleep(1000); //Arrête le programme 3s
		if (listeJoueurs[i].joueurJoue == JOUEURJOUE)
		{
			if (croupier.nbPoints > 21)
			{
				if (listeJoueurs[i].nbPoints > 21)
					printf("Le %s garde ses points car le croupier a aussi perdu.\n", listeJoueurs[i].nom);
				else
					printf("Le %s gagne car le score du croupier est superieur a 21.\n", listeJoueurs[i].nom);
			}
			else if (croupier.nbPoints == 21)
			{
				if (listeJoueurs[i].nbPoints > 21)
					printf("Le %s a un score superieur a 21, il perd donc ce tour.\n", listeJoueurs[i].nom);
				else if (listeJoueurs[i].nbPoints == 21)
					printf("Le %s a le meme score que le croupier, aucun des deux ne perd.\n", listeJoueurs[i].nom);
				else
					printf("Le %s perd ce tour car le croupier a le score max.\n", listeJoueurs[i].nom);
			}
			else//Nombre du points du croupier inférieur à 21
			{
				if (listeJoueurs[i].nbPoints>21)
					printf("Le %s a un score superieur a 21, il perd donc ce tour.\n", listeJoueurs[i].nom);
				else if (croupier.nbPoints > listeJoueurs[i].nbPoints)
					printf("Le %s a le un score inferieur au croupier donc il perd ce tour.\n", listeJoueurs[i].nom);
				else if (croupier.nbPoints == listeJoueurs[i].nbPoints)
					printf("Le %s a le meme score que le croupier, aucun des deux ne perd.\n", listeJoueurs[i].nom);
				else//Le croupier a un score inférieur au joueur
					printf("Le %s a un nombre de points superieur a celui du croupier, il gagne donc ce tour.\n", listeJoueurs[i].nom);
			}
		}
	}
	printf("\n\n");
}



/*---------------------------------------------------------------Gestion nouveau tour---------------------------------------------------------------------*/

void demandeJoueurJoue(Joueur listeJoueurs[])
{
	/*
	* Fonction de demande au joueur s'il rejoue.
	* 
	* La fonction reçoit en paramètre la liste des joueurs et demande à l'uilisateur (listeJoueurs[0])
	* s'il souhaite continuer à jouer. Si'l souhaite continuer à jouer son paramètren "joueurJoue" passe
	* à "JOUEURJOUE" sinon à "JOUEURJOUEPAS".
	*/
	printf("Voulez-vous rejouer ?\n");
	if (ouiOuNonBool())
		listeJoueurs[0].joueurJoue = JOUEURJOUE;
	else
		listeJoueurs[0].joueurJoue = JOUEURJOUEPAS;
}




/*--------------------------------------------------------------------------Fonction autres------------------------------------------------------------------*/

static void calculNbAs(Joueur joueur, int* nbAs)
{
	/*
	* Fonction de calucl du nombre d'As du joueur envoyé en paramètre (croupier inclus)
	* 
	* La fonction reçoit en paramètre un joueur et un entier appelé nbAs et change sa valeur de 0, 1 à 2
	* en fonction du nombre d'As su joueur envoyé en paramètre.
	*/
	for (int i = 0; i < 2; i++)
	{
		if (joueur.carte[i].rang == 'A')
			*nbAs = *nbAs + 1;
	}
}

static char convertIntToChar(int entier)
{
	/*
	* Fonction de conversion d'un entier sous forme de char.
	* 
	* La fonction reçoit en paramètre un entier et le convertie en retour de fonction en char.
	*/
	char resultat;

	switch (entier)
	{
	case (1):
		resultat = '1';
		break;
	case (2):
		resultat = '2';
		break;
	case (3):
		resultat = '3';
		break;
	case (4):
		resultat = '4';
		break;
	case (5):
		resultat = '5';
		break;
	case (6):
		resultat = '6';
		break;
	case (7):
		resultat = '7';
		break;
	case (8):
		resultat = '8';
		break;
	case (9):
		resultat = '9';
		break;
	default:
		resultat = '0';
		break;
	}

	return resultat;
}

int ouiOuNonBool()
{
	/*
	* Fonction de récupération de réponse Oui ou Non de l'utilisateur.
	* 
	* La fonction renvoie sous forme d'entier (booléen) la réponse de l'utilisateur à une question
	* qui doit se répondre par oui ou non. L'entier retoruné vaut 0 si c'est un "non" et 1 si c'est un "oui".
	*/
	int erreur;
	char reponse;
	do
	{
		printf("(appuyez sur O pour oui et N pour non)\n");
		erreur = scanf("%1c", &reponse);

		if (erreur != 1)
		{
			printf("Erreur saisie incorrecte, veuillez selectionner la lettre O ou N.\n");
		}
		viderMemoireTampon();

	} while (reponse != 'O' && reponse != 'o' && reponse != 'N' && reponse != 'n');

	if (reponse == 'O' || reponse == 'o')
		return 1;
	else
		return 0;
}

void viderMemoireTampon()
{
	/*
	* Fonction de vidage mémoire tampon
	* 
	* La fonction sert à vider la mémoire tampon afin d'éviter la surcharge de caractère non voulus
	* lors de la lecture d'une réponse de l'utilisateur.
	*/
	scanf("%*[^\n]");
	getchar();
}

int valAleatoire(const int valMax)
{
	/*
	* Fonction de génération d'une valeur aléatoire entre 0 et la valeur envoyé en paramètre.
	*/
	return rand() % (valMax);//On récupère le reste de la division de notre varibale aléatoire par la variable max-1 voulue
}



/*---------------------------------------------------------------------Fonction pour séparation des étapes------------------------------------------------------------------*/

void afficherMessageInitialisation()
{
	printf("I - INITIALISATION :\n\n");
}

void afficherMessageDistributionCartes()
{
	printf("\n\n\nII - DISTRIBUTION DES CARTES :\n\n");
}

void affficherMessagePiocheJoueurs()
{
	printf("\n\n\nIII - PIOCHE JOUEURS\n\n");
}

void afficherMessageComparaisonScore()
{
	printf("\n\n\nIV - COMPARAISON SCORES\n\n");
}

void afficherMessageNouveauTour(Joueur joueur)
{
	if (joueur.joueurJoue == JOUEURJOUE)
		printf("\n\n\nI - NOUVEAU TOUR\n\n");
}

void afficherFinDePartie()
{
	printf("\n\n\nFIN DE PARTIE\n");
}
