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
	_nom=nom;//TODO cont ref string
	cout << " + Personnage hero cr�e" << endl;
}

/** La m�thode near renvoie la liste d'ennemis proches
 * @param team - liste de tous les ennemis*/
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

/** La m�thode close_combat permet de taper des ennemis au corps a corps
 * @param proch - liste ennemis valides*/
void Hero::close_combat(list<Personnage*> proch)
{
	if(proch.size()==0)		//pas d'ennemis adjacents
	{
		cout<<"Pas d'ennemi proche"<<endl;
	}
	else if(proch.size()==1)//1 ennemi adjacent, attaque au cac
	{
		proch.front()->set_pvCurrent(proch.front()->get_pvCurrent()-2);
		cout<<proch.front()->get_pvCurrent()<<"/"<<proch.front()->get_pvMax();
		_paCurrent=_paCurrent-3;
	}
	else// + de 1 ennemis, selection de la cible
	{
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
			cout<<"Ennemi s�lectionn�= "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
			cout<<"Ennemi s�lectionn�= "<<(*ite)->get_paCurrent()<<"/"<<(*ite)->get_paMax()<<endl;
			cout<<"\t\t tapez 0 pour frapper cet ennemi"<<endl;
			cout<<"\t\t taper 1 pour changer d'ennemi"<<endl;
			cin>>choix3;
			if(!choix3)
			{
				(*ite)->set_pvCurrent((*ite)->get_pvCurrent()-2);
				cout<<"Ennemi touch�! "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl; // affichage des PV restants
				_paCurrent=_paCurrent-3;
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
}

/** La m�thode shoot permet de tirer sur des ennemis
 * @param in_range - liste ennemis valides*/
void Hero::shoot(list<Personnage*> in_range)
{
	if(in_range.size()==0)
	{
		cout<<"Pas d'ennemi a port�e"<<endl;
	}
	else if(in_range.size()==1)// un seul ennemi, tir
	{
		in_range.front()->set_pvCurrent(in_range.front()->get_pvCurrent()-4);
		cout<<in_range.front()->get_pvCurrent()<<"/"<<in_range.front()->get_pvMax();
		_paCurrent=_paCurrent-4;
	}
	else
	{
		list<Personnage*>::iterator ite;
		ite=in_range.begin();
		cout<<"\t\tplus de 1 ennemi :"<<endl;
		int taille = in_range.size();
		int compteur=0;
		int choix;
		int fini=0;
		while(!fini)//choix de l'ennemi
		{
			compteur++;
			cout<<"Ennemi s�lectionn�= "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
			cout<<"\t\t tapez 0 pour frapper cet ennemi"<<endl;
			cout<<"\t\t taper 1 pour changer d'ennemi"<<endl;
			cin>>choix;
			if(!choix)
			{
				(*ite)->set_pvCurrent((*ite)->get_pvCurrent()-4);
				if((*ite)->get_pvCurrent()<1)
				{
					cout<<"Ennemi tu�! "<<endl;
				}
				else
				{
					cout<<"Ennemi touch�! "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;//Affichage des PV restants
				}
				_paCurrent=_paCurrent-4;
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
}

string Hero::get_name(void)					//getter
{
	return(_nom);
}

void Hero::set_name(string nom)				//setter
{
	_nom=nom;
}

/** La m�thode display_info permet d'afficher les attributs de celui qui l'invoque dans la console */
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
