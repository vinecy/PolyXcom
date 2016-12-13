/*
 * Hero.cpp
 *
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#include<iostream>
#include"Hero.h"
using namespace std;

/** Le constructeur Hero cree un personnage et initialise ses attributs
	 * @param x - Points de Vie max du perso
	 * @param Y - Points d'Action max du perso
	 * @param ID - Type du hero
	 * @param pv - Points de Vie max du perso
	 * @param pa - Points d'Action max du perso
	 * @param arme - Arme par defaut du hero
	 * @param _nom - Nom du perso	*/
Hero::Hero(int x,int y,int ID,int pv,int pa,Arme arme,string nom):Personnage(x,y,ID,pv,pa,arme)
{
	_nom=nom;
}

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

void Hero::close_combat(list<Personnage*> proch)
{
	if(proch.size()==0)
	{
		cout<<"Pas d'ennemi proche"<<endl;
	}else if(proch.size()==1){
		proch.front()->set_pvCurrent(proch.front()->get_pvCurrent()-2);
		cout<<proch.front()->get_pvCurrent()<<"/"<<proch.front()->get_pvMax();
		_paCurrent=_paCurrent-3;
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

void Hero::shoot(list<Personnage*> in_range)
{
	if(in_range.size()==0)
	{
		cout<<"Pas d'ennemi proche"<<endl;
	}else if(in_range.size()==1){
		in_range.front()->set_pvCurrent(in_range.front()->get_pvCurrent()-4);
		cout<<in_range.front()->get_pvCurrent()<<"/"<<in_range.front()->get_pvMax();
		_paCurrent=_paCurrent-4;
	}else{
		list<Personnage*>::iterator ite;
		ite=in_range.begin();
		cout<<"\t\tplus de 1 ennemi :"<<endl;
		int taille = in_range.size();
		int compteur=0;
		int choix;
		int fini=0;
		while(!fini)
		{
			compteur++;
			cout<<"Ennemi sélectionné= "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
			cout<<"\t\t tapez 0 pour frapper cet ennemi"<<endl;
			cout<<"\t\t taper 1 pour changer d'ennemi"<<endl;
			cin>>choix;
			if(!choix)
			{
				(*ite)->set_pvCurrent((*ite)->get_pvCurrent()-4);
				cout<<"Ennemi touché! "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
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
	cout << "Hero detruit" << endl;
}
