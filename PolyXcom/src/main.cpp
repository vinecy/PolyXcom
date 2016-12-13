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

int main_switch();
int move_switch();
bool end_team(list<Personnage*>team);

int main() {
	int choix;
	int choix2;


	list<Ennemi> 		tank_ennemi;
	list<Hero>			tank_hero;
	list<Obstacle>  	tank_obstacle;

	list<Personnage*>	team_hero;
	list<Personnage*>	team_ennemi;

	list<Personnage*>::iterator ite_l;
	list<Personnage*>::iterator ite;
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

	bool cont=1;
	while(cont)
	{
		cout<<"Nouveau tour"<<endl;
		ite_l=team_hero.begin();
		while(end_team(team_hero))		//TANT QUE pa!=0 pour tous les hero
		{
			cout<<"Tour de "<<(*ite_l)->get_x()<<"/"<<(*ite_l)->get_y()<<endl;
			do
			{
				cout<<"\t\t\t\t\tPA restants= "<<(*ite_l)->get_paCurrent()<<endl;
				Luminy.display();
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
							Luminy.move_up(*(*ite_l));
							choix2=10;
							break;
						case EAST:
							Luminy.move_right(*(*ite_l));
							choix2=10;
							break;
						case SOUTH:
							Luminy.move_down(*(*ite_l));
							choix2=10;
							break;
						case WEST:
							Luminy.move_left(*(*ite_l));
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
							if(Luminy.pathIsPossible((*ite_l)->get_x(),(*ite_l)->get_y(),(*ite)->get_x(),(*ite)->get_y()))
							{
								in_range.push_front((*ite));
							}
						}
						(*ite_l)->shoot(in_range);
						for(ite=team_ennemi.begin();ite!=team_ennemi.end();ite++)
						{
							if((*ite)->get_pvCurrent()<=0)
							{
								cout<<"On eleve "<<endl;
								(*ite)->display_info();

								Luminy.removeItem(*(*ite));
								team_ennemi.remove((*ite));


								cout<<"il reste "<<team_ennemi.size()<<"ennemis"<<endl;

							}
						}
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

						for(ite=team_ennemi.begin();ite!=team_ennemi.end();ite++)
						{
							if((*ite)->get_pvCurrent()<0)
							{
								Luminy.removeItem(*(*ite));
							}
							if(team_ennemi.size()==0)
							{
								cont=0;
							}
						}
					}
					else
					{
						cout<<"Pas assez de PA!"<<endl;
					}
				}
			}while(choix!=0);
			(*ite_l)->set_paCurrent((*ite_l)->get_paMax());			//TANT QUE pa!=0 pour tous les ennemis
			list<Personnage*>::iterator ite_l;
			ite_l=team_ennemi.begin();
			while(end_team(team_ennemi))
			{
				cout<<"Tour de pro"<<endl;
				Luminy.display();
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
}

int main_switch ( void ){
	int reponse ;
	do {
		cout << "\nQue voulez-vous faire : \n " << DEPLACER << " - Se deplacer " << endl;
		cout << " " << TIRER  << " - Tirer " << endl;
		cout << " " << CC << " - Corps à Corps " << endl;
		cout << " Tapez 0 pour passer votre tour \n> ";

		cin >> reponse ;

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

	}
	while ( reponse < 10 || reponse > WEST ) ;
	return( reponse ) ;
}

bool end_team(list<Personnage*> team)
{
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
