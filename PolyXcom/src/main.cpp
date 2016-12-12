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
#include "Hero.h"
#include "Carte.h"
#include "Arme.h"
#include "Graphe.h"
#include "Ennemi.h"

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

	Carte Luminy( (int)4 , (int)4 );			//creatin de la carte

	list<Personnage*> team_hero;				//creation des listes d'equipes
	list<Personnage*> team_ennemi;

	Hero val(0,0,2,10,8,Arme(),"Valentin");		//creation des perso
	Ennemi pro(1,0,3,10,1,Arme());
	Ennemi gen(0,1,3,9,2,Arme());

	team_hero.push_front(&val);					// maj liste equipe
	team_ennemi.push_front(&pro);
	team_ennemi.push_front(&gen);


	Luminy.addItem(val);						//ajoute des perso
	Luminy.addItem(pro);
	Luminy.addItem(gen);

	list<Personnage*>::iterator ite;

	int token;
	token=3;
	while(token>0)			//TANT QUE Ennemis detruit ou Hero detruits
	{
		token--;
		cout<<"Nouveau tour"<<endl;
		while(val.get_paCurrent()>0)		//TANT QUE pa!=0 pour tous les hero
		{
			cout<<"Tour de val "<<endl;
			do {
				//cout << "-------------------------------------------------------------------------------- \n";
				cout<<"\t\t\t\t\tPA restants= "<<val.get_paCurrent()<<endl;
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
							val.move_up(Luminy);
							choix2=10;
							break;
						case EAST:
							val.move_right(Luminy);
							choix2=10;
							break;
						case SOUTH:
							val.move_down(Luminy);
							choix2=10;
							break;
						case WEST:
							val.move_left(Luminy);
							choix2=10;
							break;
						}
					}while (choix2 != 10 ) ;
					break;
				case TIRER:
					cout<<"peace man!"<<endl;
					break;
				case CC:
					list<Personnage*> proch = val.near(Luminy,team_ennemi);
					if(proch.size()==0)
					{
						cout<<"Pas d'ennemi proche"<<endl;
					}else if(proch.size()==1){
						proch.front()->set_pvCurrent(proch.front()->get_pvCurrent()-2);
						proch.front()->display_info();
					}else{
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
		val.set_paCurrent(val.get_paMax());			//TANT QUE pa!=0 pour tous les ennemis
		while(pro.get_paCurrent()>0)
		{
			cout<<"Tour de pro"<<endl;
			Luminy.display();
			/*
			pro.move_up(Luminy);
			if(pro.get_paCurrent()>0)
			{
				pro.move_left(Luminy);
				if(pro.get_paCurrent()>0)
				{
					pro.move_right(Luminy);
					if(pro.get_paCurrent()>0)
					{
						pro.move_down(Luminy);
					}
				}
			}
			*/
			pro.set_paCurrent(0);
		}
		pro.set_paCurrent(pro.get_paMax());
	}

}






