/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'�l�ves de Polytech Marseille. Il ne peut �tre
 * reproduit, utilis� ou modifi� sans l'avis express de ses auteurs.
 */

/**
 * @author BARTHOLOMEAU Vincent <vincent.bartholomeau@etu.univ-amu.fr>
 * @author BISSUEL Valentin <valentin.bissuel@etu.univ-amu.fr>
 *
 * @version 0.0.1 / 24/11/2016
 *
 */

/**
 * @file Carte.cpp
 * @brief La classe Carte permet de g�rer les objets dans le monde
 */

#include <iostream>
<<<<<<< HEAD
=======
#include <queue>
>>>>>>> refs/remotes/origin/PolyXcom
#include <list>
#include "Carte.h"
#include "Graphe.h"
#include "Noeud.h"
#include "Affichable.h"

using namespace std;

static Affichable vide;


/** Le constructeur Carte initialise le tableau contenant les objets affichables
	 * @param x - la longueur de la carte
	 * @param y - la largeur de la carte
	 * */
Carte::Carte( int x , int y ) {
	_sizeX = x ;
	_sizeY = y ;
	_map = new Affichable **[_sizeY];

	// initialisation de la carte
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){
		_map[i] = new Affichable*[_sizeX];
		for( j = 0 ; j < _sizeX ; j++ ){
			_map[i][j] = &vide;
		}
	}
	cout << " + carte de taille "<< _sizeX << "*" << _sizeY << " cr�e" << endl;
	cout << " + adresse de vide "<< &vide << endl;
}

/** La m�thode display permet d'afficher la carte sur la console */
void Carte::display( void ) {
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X

	cout << " *** affichage de la carte *** " << endl;
	cout << " ----------------- " << endl;
	for( i = _sizeY-1 ; i >= 0 ; i-- ){
		for( j = 0 ; j < _sizeX ; j++ ){
			cout << " | " << _map[j][i]->get_ID() ;
		}
		cout << " | "<< endl << " ----------------- " << endl;
	}
	cout << " *** _map avec l'adresse sur laquelle chaque case pointe *** " << endl;
	for( i = _sizeY-1 ; i >= 0 ; i-- ){
		for( j = 0 ; j < _sizeX ; j++ ){
			cout << _map[j][i] << " ";
		}
		cout << " \n "<< endl;
	}
	cout << " *** fin affichage *** " << endl;
}

/** La m�thode moveIsPossible permet de v�rifier si la case (x,y) est franchissable ou pas
 	 * @param x,y - couple de coordonn�es � verifier
 	 * @return - il retourne 1 et le deplacement est possible ou 0 sinon.
 	 * */
bool Carte::moveIsPossible( int x , int y ){
	bool rep = true ;

	if( !(_map[x][y] == &vide) ){
		// si obstacle sur la case destination
		rep = false;
		cout << " obstacle d�tect�e sur " << x << "," << y << endl;
	} else if( !( ( x>=0 && x<_sizeX ) && ( y>=0 && y<_sizeY ) ) ) {
		// si case destination en dehors de la carte
		rep = false;
		cout << " on sort de la carte! sur " << x << "," << y << endl;
	} else {
		cout << " aucun obstacle d�tect�e" << endl;
	}
	return rep;
}

/** La m�thode addItem permet d'ajouter un affichable sur la carte
 	 * @param &a - adresse de l'affichable � ajouter
 	 * */
void Carte::addItem( Affichable &a ){
	//cout << " la case " << a.get_x() << "," << a.get_y() << " pointe sur l'adresse " << _map[ a.get_x() ][ a.get_y() ] << endl;
	//cout << " addresse de l'affichable " << &a << endl;
	_map[ a.get_x() ][ a.get_y() ] = &a;
	//cout << " la case " << a.get_x() << "," << a.get_y() << " pointe sur l'adresse " << _map[ a.get_x() ][ a.get_y() ] << endl;
}

/** La m�thode moveItemTo permet de deplacer un affichable � un point sur la carte
 	 * @param *a - pointeur sur l'affichable � d�placer sur la carte
 	 * @param newX,newY - nouvelle coordonn�es de l'objet � d�placer
 	 * */
void Carte::moveItemTo( int oldX, int oldY , int newX , int newY ){
	//cout << "m�j des coordonnes" << endl;

	//cout << "adresse de l'objet � deplacer " <<_map[ oldX ][ oldY ] << endl;
	//cout << "coordonnes de l'objet : "<< oldX << " " << oldX << endl;
	//cout << "coordonnes de l'objet : "<< _map[ oldX ][ oldY ]->get_x() << " " << _map[ oldX ][ oldY ]->get_y() << endl;

	_map[ newX ][ newY ] = _map[ oldX ][ oldY ];
	_map[ oldX ][ oldY ] = &vide;

	_map[ newX ][ newY ]->set_x(newX);
	_map[ newX ][ newY ]->set_y(newY);

	//cout << "adresse de l'objet � la nvlle position "<< _map[ oldX ][ oldY ] << endl;
	//cout << "adresse de l'objet � l'ancienne position "<< _map[ oldX ][ oldY ] << endl;
	//cout << "coordonnes de l'objet : "<< _map[ newX ][ newY ]->get_x() << " " << _map[ newX ][ newY ]->get_y() << endl;
}

void Carte::pathfinding( int xA , int yA , int xB , int yB ){
	Graphe graphDeRecherche(this);
	graphDeRecherche.display();									// initialisation du graphe

	Noeud *depart = new Noeud,
		  *enCours = new Noeud,
		  //*voisin = new Noeud,
		  *arrivee = new Noeud;
	*depart = graphDeRecherche._graphe[xA][yA];				// depart pointe sur la case de d�part
	*arrivee= graphDeRecherche._graphe[xB][yB];				// arrivee pointe sur la case de fin

	int costFromEnd = (arrivee->get_X() + arrivee->get_Y())
					- (depart->get_X() + depart->get_Y());
	depart->set_costFromEnd(costFromEnd);

	int coordCX,coordCY;

	//cout << depart->get_X() << "," << depart->get_Y() << endl;
	//cout << arrivee->get_X() << "," << arrivee->get_Y() << endl;

	// Utilisation de l'algorithme A*
	list <Noeud> noeudsAtraiter;
	list <Noeud> noeudsTraites;
	list <Noeud> listeVoisin;
	noeudsAtraiter.push_front(*depart);

	// Tant qu'il y a toujours des noeuds � traiter
	while( !noeudsAtraiter.empty() ){
		cout << " Liste pas encore vide " << endl;
		*enCours = noeudsAtraiter.front();

		//cout << enCours->get_X()<< " " << enCours->get_Y() << endl;
		noeudsAtraiter.pop_front();
		//cout << enCours->get_X()<< " " << enCours->get_Y() << endl;
		noeudsTraites.push_front(*enCours);
		//graphDeRecherche.display();
		//cout << noeudsTraites.size() << endl;
		coordCX = enCours->get_X();
		coordCY = enCours->get_Y();

		// le noeud courant est-il la cible ?
		if( coordCX == arrivee->get_X()
			&& coordCY == arrivee->get_Y()){
			cout << "Chemin trouv� !!!" << endl;
			list <Affichable> Chemin;
			/*
			 * TODO faire le retour du chemin � partir
			 * de ClosedList
			 */
			//return Chemin;
		}

		// Recherche des voisins du noeud courant
		if( coordCX != _sizeX-1 ){
			graphDeRecherche._graphe[coordCX + 1][coordCY].set_costFromBegin(enCours->get_costFromBegin() + 1);
			listeVoisin.push_front(graphDeRecherche._graphe[coordCX + 1][coordCY] );
			if( coordCY != _sizeY-1 ){
				graphDeRecherche._graphe[coordCX + 1][coordCY + 1].set_costFromBegin(enCours->get_costFromBegin() + 2);
				listeVoisin.push_front(graphDeRecherche._graphe[coordCX + 1][coordCY+ 1] );
			}
			if( coordCY != 0 ){
				graphDeRecherche._graphe[coordCX + 1][coordCY - 1].set_costFromBegin(enCours->get_costFromBegin() + 2);
				listeVoisin.push_front(graphDeRecherche._graphe[coordCX + 1][coordCY - 1] );
			}
		} else if( coordCX != 0 ){
			graphDeRecherche._graphe[coordCX - 1][coordCY].set_costFromBegin(enCours->get_costFromBegin() + 1);
			listeVoisin.push_front(graphDeRecherche._graphe[coordCX - 1][coordCY] );
			if( coordCY != _sizeY-1 ){
				graphDeRecherche._graphe[coordCX - 1][coordCY + 1].set_costFromBegin(enCours->get_costFromBegin() + 2);
				listeVoisin.push_front(graphDeRecherche._graphe[coordCX - 1][coordCY + 1] );
			}
			if( coordCY != 0 ){
				graphDeRecherche._graphe[coordCX - 1][coordCY - 1].set_costFromBegin(enCours->get_costFromBegin() + 2);
				listeVoisin.push_front(graphDeRecherche._graphe[coordCX - 1][coordCY - 1] );
			}
		} else {
			if( coordCY != _sizeY-1 ){
				graphDeRecherche._graphe[coordCX][coordCY + 1].set_costFromBegin(enCours->get_costFromBegin() + 1);
				listeVoisin.push_front(graphDeRecherche._graphe[coordCX][coordCY + 1] );
			}
			if( coordCY != 0 ){
				graphDeRecherche._graphe[coordCX][coordCY - 1].set_costFromBegin(enCours->get_costFromBegin() + 1);
				listeVoisin.push_front(graphDeRecherche._graphe[coordCX][coordCY - 1] );
			}
		}

		listeVoisin.begin();
		/*while( listeVoisin.get_allocator() != listeVoisin.back() ){
			*voisin = listeVoisin.get_allocator();
			cout << "voisin: " << voisin->get_X()<< "'" << voisin->get_Y() << endl;
			if( voisin->get_heuristic() < 0
			 && noeudsTraites.sort ){

			}

			if( voisin->get_heuristic()<0 ){
				listeVoisin = listeVoisin.back();
			}

		}*/
	}
	//return list<Affichable>;
}

int Carte::get_sizeX(void){
	return _sizeX;
}

int Carte::get_sizeY(void){
	return _sizeY;
}

int Carte::get_IDin(int x, int y){
	return _map[x][y]->get_ID();
}

std::list <Affichable*> Carte::list_cc(int x,int y)
{
	std::list <Affichable*> a;
	if(x!=_sizeX)
	{
		if((_map[x+1][y]!=&vide) && (_map[x+1][y]->get_ID()==03))
		{
			a.push_front(_map[x+1][y]);
		}
	}
	if(y!=_sizeY)
	{
		if((_map[x][y+1]!=&vide)&& (_map[x+1][y]->get_ID()==03))
		{
			a.push_front(_map[x][y+1]);
		}
	}
	if(x!=0)
	{
		if((_map[x-1][y]!=&vide)&&(_map[x+1][y]->get_ID()==03))
		{
			a.push_front(_map[x-1][y]);
		}
	}
	if(y!=0)
	{
		if((_map[x][y-1]!=&vide)&& (_map[x+1][y]->get_ID()==03))
		{
			a.push_front(_map[x][y-1]);
		}
	}
	return(a);
}

/** Le destructeur Carte */
Carte::~Carte() {
	cout << " - carte de taille "<< _sizeX << "*" << _sizeY << " detruit" << endl;
}
