/*
 * Ennemi.cpp
 *
 *
 *  Created on: 27 nov. 2016
 *      Author: Vincent
 */


/**
 * @file Ennemi.cpp
 * @brief La classe Ennemi est la sous-classe de personnage que les hero doivent battre
 *
 */

#include "Ennemi.h"

using namespace std;


Ennemi::Ennemi()
{

}

/** Le constructeur Ennemi cree un ennemi et initialise ses attributs
	 * @param x - Abcisse de l'ennemi
	 * @param y - Ordonnee de l'ennemi
	 * @param ID - Type de l'ennemi
	 * @param lev - Niveau de l'ennemi
	 * @param str -	Force de l'ennemi
	 * @param acc - Precition de l'ennemi
	 * @param agi - Agilite de l'ennemi
	 * @param end - Endurance de l'ennemi
	 * @param luck - Chance de l'ennemi
	 * @param inv  Inventaire de l'ennemi-*/
Ennemi::Ennemi(int x,int y,int ID,int lev,int str,int acc,int agi,int end,int luck,Inventaire inv):Personnage(x,y,ID,lev,str,acc,agi,end,luck,inv)
{
	cout << " + Personnage ennemi crée" << endl;
}

/** La méthode display_info permet d'afficher les attributs de celui qui l'invoque dans la console */
void Ennemi::display_info(void)
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"PV( "<<this->get_pvCurrent()<<" / "<<this->get_pvMax()<<" )"<<endl;
	cout<<"PA( "<<this->get_paCurrent()<<" / "<<this->get_paMax()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}
/** La méthode begin AI commence l'algorithme de choix de l action par l'AI*/
void Ennemi::begin_IA()
{
	cout<<"begin!"<<endl;
}
/** La méthode near renvoie la liste d'ennemis proches
 * @param team - liste de tous les ennemis*/
list<Personnage*> Ennemi::near(list<Personnage*> team)
{
	list<Personnage*>::iterator ite;
	list<Personnage*> l;
	for(ite=team.begin();ite!=team.end();ite++)//recherche des héros adjacents
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

/** La méthode close_combat permet de taper des Heros au corps a corps
 * @param proch - liste Heros valides*/
void Ennemi::close_combat(list<Personnage*> proch)
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

/** La méthode shoot permet de tirer sur des Heros
 * @param in_range - liste Heros valides*/
void Ennemi::shoot(list<Personnage*> in_range)
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

/** Le destructeur Ennemi*/
Ennemi::~Ennemi()				//destructor
{
	cout << " - Personnage ennemi detruit" << endl;
}

