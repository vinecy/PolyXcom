/*
 * Hero.cpp
 *
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

/**
 * @file Hero.cpp
 * @brief La classe Hero est la sous-classe de personnage que le joueur controle
 *
 */

#include<iostream>
#include<cstdlib>
#include"Hero.h"
using namespace std;

/** Le constructeur Hero cree un Hero et initialise ses attributs
	 * @param x - Abcisse du Hero
	 * @param y - Ordonnee du Hero
	 * @param ID - Type du Hero
	 * @param lev - Niveau du Hero
	 * @param str -	Force du Hero
	 * @param acc - Precition du Hero
	 * @param agi - Agilite du Hero
	 * @param end - Endurance du Hero
	 * @param luck - Chance du Hero
	 * @param inv - Inventaire du Hero
	 * @param nom - Nom du Hero*/
Hero::Hero(int x,int y,int ID,int lev,int str,int acc,int agi,int end,int luck,Inventaire inv,string nom):Personnage(x,y,ID,lev,str,acc,agi,end,luck,inv)
{
	_nom=nom;
	cout << " + Personnage hero crée" << endl;
}

/** La méthode near renvoie la liste d'ennemis proches
 * @param team - liste de tous les ennemis*/
/*
list<Personnage*> Hero::near(list<Personnage*> team)
{
	list<Personnage*>::iterator ite;
	list<Personnage*> l;
	for(ite=team.begin();ite!=team.end();ite++)
	{
		if(((((*ite)->get_x()+1==_coordX)||((*ite)->get_x()-1==_coordX))&&((*ite)->get_y()==_coordY)))
		{
			l.push_front((*ite));
		}
		else if(((((*ite)->get_y()+1==_coordY)||((*ite)->get_y()-1==_coordY))&&((*ite)->get_x()==_coordX)))
		{
			l.push_front((*ite));
		}
	}
	return(l);
}
*/
/** La méthode close_combat permet de taper des ennemis au corps a corps
 * @param proch - liste ennemis valides*/
/*
void Hero::close_combat(list<Personnage*> proch)
{
	if(proch.size()==0)		//pas d'ennemis adjacents
	{
		cout<<"Pas d'ennemi proche"<<endl;
	}
	else// ennemis, selection de la cible
	{
		list<Personnage*>::iterator ite;
		ite=proch.begin();
		cout<<"\t\tplus  ennemis valides :"<<endl;
		int taille = proch.size();
		int compteur=0;
		int choix3;
		int fini=0;
		while(!fini)
		{
			compteur++;
			cout<<"Ennemi sélectionné= "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
			cout<<"Coord= "<<(*ite)->get_x()<<"/"<<(*ite)->get_y()<<endl;
			cout<<"\t\t tapez 0 pour frapper cet ennemi"<<endl;
			cout<<"\t\t taper 1 pour changer d'ennemi"<<endl;
			cin>>choix3;
			if(!choix3)
			{
				(*ite)->set_pvCurrent((*ite)->get_pvCurrent()-3);
				if((*ite)->get_pvCurrent()<0)
				{
					(*ite)->set_pvCurrent(0);
				}
				cout<<"Ennemi touché! "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl; // affichage des PV restants
				_paCurrent=_paCurrent-3;
				fini=1;
			}else{

				if(compteur!=taille)
				{
					ite++;
				}
				else{
					fini=1;
					cout<<"\t\t Annulation"<<endl;
				}

			}
		}
	}
}
*/
/** La méthode shoot permet de tirer sur des ennemis
 * @param in_range - liste ennemis valides*/
/*
void Hero::shoot(list<Personnage*> in_range)
{
	if(in_range.size()==0)
	{
		cout<<"Pas d'ennemi a portée"<<endl;
	}
	else
	{
		list<Personnage*>::iterator ite;
		ite=in_range.begin();
		cout<<"\t\t ennemis valides :"<<endl;
		int taille = in_range.size();
		int compteur=0;
		int choix;
		int fini=0;
		while(!fini)//choix de l'ennemi
		{
			compteur++;
			cout<<"Ennemi sélectionné= "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
			cout<<"Coord= "<<(*ite)->get_x()<<"/"<<(*ite)->get_y()<<endl;
			cout<<"\t\t tapez 0 pour tirer sur cet ennemi"<<endl;
			cout<<"\t\t taper 1 pour changer d'ennemi"<<endl;
			cin>>choix;
			if(!choix)
			{
				(*ite)->set_pvCurrent((*ite)->get_pvCurrent()-4);
				if((*ite)->get_pvCurrent()<0)
				{
					(*ite)->set_pvCurrent(0);
				}
				cout<<"Ennemi touché! "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl; // affichage des PV restants
				_paCurrent=_paCurrent-4;
				(*ite)->get_inv()->get_weapon_c()->set_munCurrent((*ite)->get_inv()->get_weapon_c()->get_munCurrent()-1);
				(*ite)->get_inv()->get_weapon_c()->display_info();
				fini=1;
			}else{

				if(compteur!=taille)
				{
					ite++;
				}
				else{
					fini=1;
					cout<<"\t\t Annulation"<<endl;
				}

			}
		}
	}
}
*/
string Hero::get_name(void)					//getter
{
	return(_nom);
}

void Hero::set_name(string nom)				//setter
{
	_nom=nom;
}

/** La méthode display_info permet d'afficher les attributs de celui qui l'invoque dans la console */
void Hero::display_info(void)				//debug display
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"PV( "<<this->get_pvCurrent()<<" / "<<this->get_pvMax()<<" )"<<endl;
	cout<<"PA( "<<this->get_paCurrent()<<" / "<<this->get_paMax()<<" )"<<endl;
	cout<<"nom ( "<<this->get_name()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}



/** Le destructeur Hero*/
Hero::~Hero()								//destructor
{
	cout << " - Hero detruit" << endl;
}
