/*
 * Ennemi.cpp
 *
 *
 *  Created on: 27 nov. 2016
 *      Author: Vincent
 */

#include "Ennemi.h"

using namespace std;
Ennemi::Ennemi()
{

}

/** Le constructeur Ennemi cree un ennemi et initialise ses attributs
	 * @param x - Points de Vie max du perso
	 * @param y - Points d'Action max du perso
	 * @param ID - Type de l'ennemi
	 * @param pvMax - Points de Vie max du perso
	 * @param paMax - Points d'Action max du perso
	 * @param arme - Arme par defaut de l'ennemi*/
Ennemi::Ennemi(int x,int y,int ID,int lev,int str,int acc,int agi,int end,int luck,Arme arme):Personnage(x,y,ID,lev,str,acc,agi,end,luck,arme)
{
}

/** La m�thode display_info permet d'afficher les attributs de celui qui l'invoque dans la console */
void Ennemi::display_info(void)
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"PV( "<<this->get_pvCurrent()<<" / "<<this->get_pvMax()<<" )"<<endl;
	cout<<"PA( "<<this->get_paCurrent()<<" / "<<this->get_paMax()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}
/** La m�thode begin AI commence l'algorithme de choix de laction par l'AI*/
void Ennemi::begin_IA()
{
	cout<<"begin!"<<endl;
}

list<Personnage*> Ennemi::near(list<Personnage*> team)
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
			cout<<"Ennemi s�lectionn�= "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
			cout<<"\t\t tapez 0 pour frapper cet ennemi"<<endl;
			cout<<"\t\t taper 1 pour changer d'ennemi"<<endl;
			cin>>choix3;
			if(!choix3)
			{
				(*ite)->set_pvCurrent((*ite)->get_pvCurrent()-2);
				cout<<"Ennemi touch�! "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
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
			cout<<"Ennemi s�lectionn�= "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
			cout<<"\t\t tapez 0 pour frapper cet ennemi"<<endl;
			cout<<"\t\t taper 1 pour changer d'ennemi"<<endl;
			cin>>choix;
			if(!choix)
			{
				(*ite)->set_pvCurrent((*ite)->get_pvCurrent()-4);
				cout<<"Ennemi touch�! "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
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
	cout << "Personnage ennemi" << endl;
}

