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

#include <iostream>
#include "Obstacle.h"
#include "Hero.h"
#include "Carte.h"
#include "Arme.h"
#include "Graphe.h"
#include "Ennemi.h"
#include "Fichier.h"

using namespace std;

#define DEPLACER 1
#define TIRER 2
#define CC 3
#define NORTH 11
#define EAST 12
#define SOUTH 13
#define WEST 14

int main_switch ( void ){
	int reponse ;
	do {
		cout << "\nQue voulez-vous faire : \n " << DEPLACER << " - Se deplacer " << endl;
		cout << " " << TIRER  << " - Tirer " << endl;
		cout << " " << CC << " - Corps à Corps " << endl;
		cout << " Tapez 0 pour passer votre tour \n> ";

		cin >> reponse ;
		//clean_stdin();
	}
	while ( reponse < 0 || reponse > CC ) ;
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
		//clean_stdin();
	}
	while ( reponse < 10 || reponse > WEST ) ;
	return( reponse ) ;
}

int main() {
	int choix;
	int choix2;

	//system("cls");

	//Carte Luminy( (int)4 , (int)4 );			//creatin de la carte

	list<Ennemi> 		tank_ennemi;			//
	list<Hero>			tank_hero;
	list<Obstacle>  	tank_obstacle;

	list<Personnage*>	team_hero;				//creation des listes d'equipes
	list<Personnage*>	team_ennemi;

	list<Personnage*>::iterator ite_l;
	list<Ennemi>::iterator ite_e;
	list<Hero>::iterator ite_h;
	list<Obstacle>::iterator ite_o;

	Fichier pathMap("Luminy");
	Carte Luminy("Luminy");
	pathMap.loadMap(Luminy,tank_ennemi,tank_hero,tank_obstacle);


	for(ite_e=tank_ennemi.begin();ite_e!=tank_ennemi.end();ite_e++)
	{
		Luminy.addItem((*ite_e));
		team_ennemi.push_front(&(*ite_e));
	}
	for(ite_h=tank_hero.begin();ite_h!=tank_hero.end();ite_h++)
	{
		Luminy.addItem((*ite_h));
		team_hero.push_front(&(*ite_h));
	}
	for(ite_o=tank_obstacle.begin();ite_o!=tank_obstacle.end();ite_o++)
	{
		Luminy.addItem((*ite_o));
	}


	int token;
	token=3;
	while(token>0)			//TANT QUE Ennemis detruit ou Hero detruits
	{
		token--;
		cout<<"Nouveau tour"<<endl;
		ite_l=team_hero.begin();
		while((*ite_l)->get_paCurrent()>0)		//TANT QUE pa!=0 pour tous les hero
		{
			cout<<"Tour de val "<<endl;
			do {
				//cout << "-------------------------------------------------------------------------------- \n";
				cout<<"\t\t\t\t\tPA restants= "<<(*ite_l)->get_paCurrent()<<endl;
				Luminy.display();
				choix = main_switch() ;
				switch ( choix ){
				case DEPLACER :
					do
					{
						choix2 = move_switch();
						switch(choix2)
						{
						case NORTH:
							(*ite_l)->move_up(Luminy);
							choix2=10;
							break;
						case EAST:
							(*ite_l)->move_right(Luminy);
							choix2=10;
							break;
						case SOUTH:
							(*ite_l)->move_down(Luminy);
							choix2=10;
							break;
						case WEST:
							(*ite_l)->move_left(Luminy);
							choix2=10;
							break;
						}
					}while (choix2 != 10 ) ;
					break;
				case TIRER:
					cout<<"peace man!"<<endl;
					break;
				case CC:
					list<Personnage*> proch = (*ite_l)->near(Luminy,team_ennemi);
					if(proch.size()==0)
					{
						cout<<"Pas d'ennemi proche"<<endl;
					}else if(proch.size()==1){
						proch.front()->set_pvCurrent(proch.front()->get_pvCurrent()-2);
						proch.front()->display_info();
					}else{
						list<Personnage*>::iterator ite;
						ite=proch.begin();
						cout<<"\t\tplus de 1 ennemi :"<<endl;
						int taille = proch.size();
						int compteur=0;
						int choix3;
						int fini=0;
						while(!fini)
						{
							compteur++;
							cout<<"Ennemi sélectionné= "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
							cout<<"\t\t tapez 0 pour frapper cet ennemi"<<endl;
							cout<<"\t\t taper 1 pour changer d'ennemi"<<endl;
							cin>>choix3;
							if(!choix3)
							{
								(*ite)->set_pvCurrent((*ite)->get_pvCurrent()-2);
								cout<<"Ennemi touché! "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
								fini=1;
							}else{

								if(compteur!=taille)
								{
									ite++;
								}
								else{
									fini=1;
								}

							}
						}
					}
					break;
				}
			} while ( choix != 0 ) ;
		}
		(*ite_l)->set_paCurrent((*ite_l)->get_paMax());			//TANT QUE pa!=0 pour tous les ennemis
		list<Personnage*>::iterator ite_l;
		ite_l=team_ennemi.begin();
		while((*ite_l)->get_paCurrent()>0)
		{
			cout<<"Tour de pro"<<endl;
			Luminy.display();
			(*ite_l)->set_paCurrent(0);
		}
		(*ite_l)->set_paCurrent((*ite_l)->get_paMax());
	}

}






