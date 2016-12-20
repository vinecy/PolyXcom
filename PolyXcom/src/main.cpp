/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 *
 *
 * Ce fichier est l'oeuvre d'élèves de Polytech Marseille. Il ne peut être
 * reproduit, utilisé ou modifié sans l'avis express de ses auteurs.
 */

/**
 * @author BARTHOLOMEAU Vincent <vincent.bartholomeau@etu.univ-amu.fr>
 * @author BISSUEL Valentin <valentin.bissuel@etu.univ-amu.fr>
 *
 * @version 0.0.1 / 24/11/2016
 *
 */

/**
 * @file main.c
 * @brief Le main permet de lancer le jeu.
 */

#include <cstdlib>
#include "Obstacle.h"
#include "Hero.h"
#include "Carte.h"
#include "Inventaire.h"
#include "Graphe.h"
#include "Ennemi.h"
#include "Fichier.h"
#include "Portail.h"


using namespace std;

#define DEPLACER 1
#define TIRER 2
#define CC 3
#define BONUS 4
#define CHANGER 5
#define NORTH 11
#define EAST 12
#define SOUTH 13
#define WEST 14
/*
int main_switch();
int move_switch();
bool end_team(list<Personnage*>team);
*/
/**********NOUVEAU*******************************************/

#define NEWGAME 1
#define LOADGAME 2
#define EXIT 3

#include <iostream>			// Bibliothèque pour ka console
#include <fstream>			// Bibliothèque pour les fichiers
#include "Partie.h"

int chooseMain();

int main(){
	cout << " lancement de PolyXcom " << endl;

	Partie game;
	bool endPolyXcom = 0;
	int choix;

	while(!endPolyXcom){
		do{
			//choix = chooseMain();
			choix = LOADGAME;
			switch(choix){
				case NEWGAME:
					cout << " * Nouvelle Partie " << endl;
					game.newPartie();
					game.loadPartie();
					game.launchPartie();
					choix = 0;
				break;
				case LOADGAME:
					cout << " * Charger Partie " << endl;
					game.loadPartie();
					game.launchPartie();
				break;
				case EXIT:
					cout << " * Bye " << endl;
					endPolyXcom = 1;
				break;
			}
		} while( choix != EXIT );
	}
}


int chooseMain ( void ){
	int reponse ;
	do {
		cout << "\n PolyXcom \n " << NEWGAME << " - Nouvelle Partie " << endl;
		cout << " " << LOADGAME  << " - Charger Partie " << endl;
		cout << " " << EXIT << " - Quitter \n  > ";
		cin >> reponse ;
	} while ( reponse < 0 || reponse > EXIT ) ;
	return( reponse ) ;
}

/********ANCIEN***********************/

/*int main()
{
	int choix;							//variables pour les switch
	int choix2;
	int choix4;

	list<Ennemi> 		tank_ennemi;	//conteneurs pour
	list<Hero>			tank_hero;		//le chargement a partir d'un fichier
	list<Obstacle>  	tank_obstacle;
	list<Carte>  		tank_carte;		// conteneur de cartes (l'actuel + les suivantes)
	list<string>  		collec_carte;	// liste de toutes les cartes du jeu
	list<Portail>  		tank_portail;		// conteneur de cartes (l'actuel + les suivantes)

	list<Personnage*>	team_hero;		//equipes de personnages//TODO refonte main
	list<Personnage*>	team_ennemi;

	list<Personnage*>::iterator ite_l;	//itérateur de personnage qui agit
	list<Personnage*>::iterator ite;	//iterateur divers
	list<Ennemi>::iterator ite_e;		//iterateur ennemi
	list<Hero>::iterator ite_h;			//iterateur hero
	list<Obstacle>::iterator ite_o;		//iterateur obstacle
	list<Carte>::iterator ite_c;		//iterateur carte
	list<string>::iterator ite_nm;		//iterateur string
	// Chargement de la Map

	// *** Chargment de la Map
	Fichier pathMap("World");					// Ouverture du fichier contenant les cartes en lecture
	pathMap.seekMap(collec_carte);				// Recherche de tous les noms de Map dans le fichier
	ite_nm = collec_carte.begin();				// Chargement du monde dit "exploration"
	pathMap.loadMap((*ite_nm),tank_carte,tank_ennemi,tank_hero,tank_obstacle,tank_portail);

	// Chargement de Team
	for(ite_e=tank_ennemi.begin();ite_e!=tank_ennemi.end();ite_e++){	//chargement ennemis
		team_ennemi.push_front(&(*ite_e));
	}
	for(ite_h=tank_hero.begin();ite_h!=tank_hero.end();ite_h++){		//chargement heros
		team_hero.push_front(&(*ite_h));
	}

	// Notre Carte actuel est la première
	ite_c = tank_carte.begin();
	while( ((*ite_c).get_nameMap() != "Luminy") && (ite_c != tank_carte.end()) ){
		ite_c++;
	}

	// ????

	list<Hero*>::iterator ite_el;
	ite_el = team_hero.begin();
	(*ite_el)->display_info();
	(*ite_el)->get_w().display_info();
*/

/*
	bool cont=1;
	while(cont)
	{
		cout << "\t\t\t\t\t\t\t\tNouveau tour"<<endl;
		ite_l=team_hero.begin();
		while(end_team(team_hero))		//TANT QUE pa!=0 pour tous les hero
		{
			cout<<"\t\t\t\t\t\t\t\tTour allié"<<endl;
			do
			{
				cout<<"\t\t\t\t\t\t\t\tPerso "<<(*ite_l)->get_x()<<"/"<<(*ite_l)->get_y()<<endl;
				cout<<"\t\t\t\t\t\t\t\tPA restants= "<<(*ite_l)->get_paCurrent()<<endl;
				(*ite_c).display();
				choix = main_switch() ;
				switch (choix)
				{
				case DEPLACER :
					do
					{
						choix2 = move_switch();
						switch(choix2)
						{
						case NORTH:
							(*ite_c).move_up(*(*ite_l));
							choix2=10;
							break;
						case EAST:
							(*ite_c).move_right(*(*ite_l));
							choix2=10;
							break;
						case SOUTH:
							(*ite_c).move_down(*(*ite_l));
							choix2=10;
							break;
						case WEST:
							(*ite_c).move_left(*(*ite_l));
							choix2=10;
							break;
						}
					}while (choix2!=10);

					break;
				case TIRER:
					if((*ite_l)->get_paCurrent()>=4)
					{
						list<Personnage*> in_range;
						for(ite=team_ennemi.begin();ite!=team_ennemi.end();ite++)
						{
							if((*ite_c).pathIsPossible((*ite_l)->get_x(),(*ite_l)->get_y(),(*ite)->get_x(),(*ite)->get_y()))
							{
								in_range.push_front((*ite));
							}
						}
						(*ite_l)->shoot(in_range);
						list<Personnage*> temp;
						for(ite=team_ennemi.begin();ite!=team_ennemi.end();ite++)
						{
							if((*ite)->get_pvCurrent()>=1)
							{
								temp.push_front(*ite);
							}
							else
							{
								(*ite_c).removeItem(*(*ite));
							}
						}
						team_ennemi=temp;
						if(team_ennemi.size()==0)
						{
							cont=0;
						}
					}
					break;
				case CC:
					if((*ite_l)->get_paCurrent()>=3)
					{
						list<Personnage*> proch = (*ite_l)->near(team_ennemi);
						(*ite_l)->close_combat(proch);
						list<Personnage*> temp;
						for(ite=team_ennemi.begin();ite!=team_ennemi.end();ite++)
						{
							if((*ite)->get_pvCurrent()>=1)
							{
								temp.push_front(*ite);
							}
							else
							{
								(*ite_c).removeItem(*(*ite));
							}
						}
						team_ennemi=temp;
						if(team_ennemi.size()==0)
						{
							cont=0;
						}
					}
					else
					{
						cout<<"Pas assez de PA!"<<endl;
					}
					break;
				case BONUS:
					if((*ite_l)->get_paCurrent()>=2)
					{
						cout<<"Ce personnage a "<<(*ite_l)->get_grenade().get_number()<<" grenades ";
						cout<<"et "<<(*ite_l)->get_medkit().get_uses()<<" medkit"<<endl;
						cout<<"\t\t tapez 1 pour utiliser une grenade"<<endl;
						cout<<"\t\t tapez 2 pour utiliser un medkit"<<endl;
						cout<<"\t\t tapez 0 pour annuler"<<endl;
						cin>>choix4;
						if(choix4==1)
						{
							if((*ite_l)->get_grenade().get_number()>0)
							{
								//TODO implementation grenade
							}
							else
							{
								cout<<"Vous n'avez pas de Grenade!"<<endl;
							}
						}
						else if(choix4==2)
						{
							if((*ite_l)->get_medkit().get_uses()>0)
							{
								(*ite_l)->use_medkit();
							}
							else
							{
								cout<<"Vous n'avez pas de Medkit!"<<endl;
							}
						}
					}
					else
					{
						cout<<"Pas assez de PA!"<<endl;
					}
					break;
				case CHANGER:
					if(team_hero.size()==1)
					{
						cout<<"Vous n'avez qu'un seul perso!";
					}
					else if((*ite_l)==team_hero.back())
					{
						ite_l=team_hero.begin();
					}
					else
					{
						ite_l++;
					}
				}
			}while(choix!=0);
			for(ite=team_hero.begin();ite!=team_hero.end();ite++)
			{
				(*ite)->set_paCurrent(0);
			}
		}
		for(ite=team_hero.begin();ite!=team_hero.end();ite++)
		{
			(*ite)->set_paCurrent((*ite)->get_paMax());
		}
		ite_l=team_ennemi.begin();
		while(end_team(team_ennemi))
		{
			cout<<"\t\t\t\t\t\t\t\tTour ennemi"<<endl;
			//Luminy.display();
			for(ite=team_ennemi.begin();ite!=team_ennemi.end();ite++)
			{
				(*ite)->set_paCurrent(0);
			}
		}
		for(ite=team_ennemi.begin();ite!=team_ennemi.end();ite++)
		{
			(*ite)->set_paCurrent((*ite)->get_paMax());
		}
	}

}

int main_switch ( void ){
	int reponse ;
	do {
		cout << "\nQue voulez-vous faire : \n " << DEPLACER << " - Se deplacer " << endl;
		cout << " " << TIRER  << " - Tirer " << endl;
		cout << " " << CC << " - Corps à Corps " << endl;
		cout << " " << BONUS << " - Utiliser un Bonus  " << endl;
		cout << " " << CHANGER << " - Changer de Personnage " << endl;
		cout << " Tapez 0 pour passer votre tour \n> ";

		cin >> reponse ;

	}
	while ( reponse < 0 || reponse > CHANGER ) ;
	return( reponse ) ;
}

int move_switch ( void ){
	int reponse ;
	do {
		cout << "\n\t\t\t\t\tOu voulez vous allez : \n\t\t\t\t\t" << NORTH << " - au Nord " << endl;
		cout << "\t\t\t\t\t" << EAST  << " - a l'Est " << endl;
		cout << "\t\t\t\t\t" << SOUTH << " - au Sud " << endl;
		cout << "\t\t\t\t\t" << WEST << " - a l'Ouest " << endl;
		cout << "\t\t\t\t\tTapez 10 pour quitter le jeu \n> ";

		cin >> reponse ;

	}
	while ( reponse < 10 || reponse > WEST ) ;
	return( reponse ) ;
}

bool end_team(list<Personnage*> team)
{
	if(team.size()==0)
	{
		return(0);
	}
	list<Personnage*>::iterator ite;
	for(ite=team.begin();ite!=team.end();ite++)
	{
		if((*ite)->get_paCurrent()==0)
		{
			return(0);
		}
	}
	return(1);
}
*/
