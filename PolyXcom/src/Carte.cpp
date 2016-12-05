/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
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
 * @file Carte.cpp
 * @brief La classe Carte permet de gérer les objets dans le monde
 */

#include <iostream>
#include <cstdlib>
#include <assert.h>
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
	cout << " + carte de taille "<< _sizeX << "*" << _sizeY << " crée" << endl;
	cout << " + adresse de vide "<< &vide << endl;
}

/** La méthode display permet d'afficher la carte sur la console */
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
	cout << " *** fin affichage *** " << endl;
}

/** La méthode moveIsPossible permet de vérifier si la case (x,y) est franchissable ou pas
 	 * @param x,y - couple de coordonnées à verifier
 	 * @return - il retourne 1 et le deplacement est possible ou 0 sinon.
 	 * */
bool Carte::moveIsPossible( int x , int y ){
	bool rep = true ;
	if( !(_map[x][y] == &vide) ){			// si obstacle sur la case destination
		rep = false;
		cout << " obstacle détectée sur " << x << "," << y << endl;
	} else if( !( ( x>=0 && x<_sizeX ) && ( y>=0 && y<_sizeY ) ) ) {
		rep = false;						// si case destination en dehors de la carte
		cout << " on sort de la carte! sur " << x << "," << y << endl;
	} else {								// si le deplacement est possible
		cout << " aucun obstacle détectée" << endl;
	}
	return rep;
}

/** La méthode addItem permet d'ajouter un affichable sur la carte
 	 * @param &a - adresse de l'affichable à ajouter
 	 * */
void Carte::addItem( Affichable &a ){
	//cout << " la case " << a.get_x() << "," << a.get_y() << " pointe sur l'adresse " << _map[ a.get_x() ][ a.get_y() ] << endl;
	//cout << " addresse de l'affichable " << &a << endl;
	if( _map[ a.get_x() ][ a.get_y() ] != &vide ) {
		cout << "!!! on écrase un affichable déjà present !!!" << endl ;
	}
	_map[ a.get_x() ][ a.get_y() ] = &a;
	//cout << " la case " << a.get_x() << "," << a.get_y() << " pointe sur l'adresse " << _map[ a.get_x() ][ a.get_y() ] << endl;
}

/** La méthode moveItemTo permet de deplacer un affichable à un point sur la carte
 	 * @param *a - pointeur sur l'affichable à déplacer sur la carte
 	 * @param newX,newY - nouvelle coordonnées de l'objet à déplacer
 	 * */
void Carte::moveItemTo( int oldX, int oldY , int newX , int newY ){
	_map[ newX ][ newY ] = _map[ oldX ][ oldY ];
	_map[ oldX ][ oldY ] = &vide;

	_map[ newX ][ newY ]->set_x(newX);
	_map[ newX ][ newY ]->set_y(newY);
}

/** La méthode pathfinding permet de trouver le meilleur chemin d'un point A à un point B
 * sur la carte avec l'algorithme A*. Il retourne le chemin trouvé, c'est une liste de
 * coordonnées à suivre
 	 * @param xA,yA - Point de Départ
 	 * @param xB,yB - Point d'arrivée
 	 * @return - retourne une liste de paires de coordonnées
 	 * */
list <pair<int , int>> Carte::pathfinding( int xA , int yA , int xB , int yB ){
	assert( this->moveIsPossible(xB, yB) == true);		// La cible doit être valide

	// initialisation du graphe
	Graphe graphDeRecherche(this);
	graphDeRecherche._graphe[xA][yA].set_costFromBegin(0);
	graphDeRecherche._graphe[xA][xA].set_costFromEnd( abs(xA - xB) + abs(yA - yB) );
	graphDeRecherche.display();

	// Definition du Noeud Courant
	cout << "creation du noeud courant..." << endl;
	Noeud *enCours = new Noeud;
	enCours = &graphDeRecherche._graphe[xA][yA];
	int xC = enCours->get_X(),
		yC = enCours->get_Y();
	cout << "... verification des pointeurs ..." << endl;
	cout << "@graphe = " << &graphDeRecherche._graphe[xA][yA] << endl;
	cout << "encours = "<< enCours << endl;

	// initialisation des listes de Noeuds
	cout << "creation des listes de Noeud..." << endl;
	list <Noeud> openList;					// Liste contenant les noeuds à traiter
	list <Noeud> closeList;					// Liste contenant les noeuds déjà traités
	list <Noeud> listeVoisin;				// Liste contenant les voisins du noeud courant
	list <pair<int , int>> pathList;		// Liste contenant le veritable chemin

	// définition des itérateurs
	cout << "... creation des iterateurs..." << endl;
	list<Noeud>::iterator openIt = openList.begin();
	list<Noeud>::iterator closeIt = closeList.begin();
	list<Noeud>::iterator voisinIt = listeVoisin.begin();
	list <pair<int , int>>::iterator pathIt = pathList.begin();
	list<Noeud>::iterator nodelowestCost;
	cout << "... verification des listes ..." << endl;
	cout << "size openList = " << openList.size() << endl;
	cout << "size closeList = " << closeList.size() << endl;
	cout << "size listeVoisin = " << listeVoisin.size() << endl;
	cout << "size pathList = " << pathList.size() << endl;

	cout << "*** DEBUT DE L'ALGORITHME A* ***" << endl;

	cout << "ajout du noeud de départ dans OpenList..." << endl;
	openList.push_back(*enCours);
	cout << " size openList = " << openList.size() << endl;
	openIt = openList.begin();
	cout << " openList contient :" << endl;
	for(; openIt != openList.end(); openIt++){
		cout << " * " ;
		(*openIt).display();
		cout << endl;
	}

	cout << " *** \n *** DEBUT DE L'ALGORITHME A* *** \n *** "<< endl;

	// Tant qu'il y a toujours des noeuds à traiter
	cout << " * Debut du while " << endl;
	while( !openList.empty() ){
		cout << " Liste non vide " << endl;
		graphDeRecherche.display();

		cout << " * Le noeud courant pointe sur le noeud avec le f_cost le plus faible" << endl;
		cout << "   Recherche du noeud ..." << endl;
		openIt = openList.begin();
		int H_cost_Min = _sizeX*_sizeY;
		int F_cost_Min = _sizeX*_sizeY;
		while(openIt != openList.end()){
			if( (*openIt).get_costFinal() <= F_cost_Min ){
				if( (*openIt).get_costFromEnd() <= H_cost_Min ){
					nodelowestCost = openIt;
					H_cost_Min = (*openIt).get_costFromEnd();
					F_cost_Min = (*openIt).get_costFinal();
				}
			}
			cout << "    It minimal : " ;
			(*nodelowestCost).display();
			cout << "\n    It actuel  : ";
			(*openIt).display();
			cout << endl;
			openIt++;
		}
		xC = (*nodelowestCost).get_X();
		yC = (*nodelowestCost).get_Y();
		enCours = &graphDeRecherche._graphe[xC][yC];
		cout << " > le noeud minimal est "<< enCours << endl;
		cout << " > le noeud minimal est "<< xC << "," << yC << endl;

		cout << " * On retire le Noeud courant de OpenList " << endl;
		cout << "   size openLIst preced = " << openList.size() << endl;
		openList.erase(nodelowestCost);
		cout << "   size openLIst actuel = " << openList.size() << endl;

		cout << " * Ajout du noeud Courant dans CloseList ..." << endl;
		cout << "   size closeList = " << closeList.size() << endl;
		closeList.push_front(*enCours);
		cout << "   size closeList = " << closeList.size() << endl;
		cout << "   ... verification de closeList " << endl;
		closeIt = closeList.begin();
		cout << "   closeList contient :" << endl;
		for(; closeIt != closeList.end(); closeIt++){
			cout << "  * " ;
			(*closeIt).display();
			cout << endl ;
		}

		// le noeud courant est-il la cible ?
		cout << " ** Debut du If \"le noeud courant est-il sur la cible\""<< endl;
		if( xC == xB && yC == yB ){
			cout << "  > Chemin trouvé !!!" << endl;
			cout << "    ... reconstitution du chemin " << endl;
			pair<int,int> coord;
			int nextX,nextY;
			pathIt = pathList.begin();
			closeIt = closeList.begin();
			coord.first = (*closeIt).get_X();
			coord.second = (*closeIt).get_Y();
			cout << "    ajout de " << coord.first << " " << coord.second << endl;
			pathList.push_back(coord);
			closeIt++;
			for(; closeIt != closeList.end(); closeIt++){
				nextX = (*closeIt).get_X();
				nextY = (*closeIt).get_Y();
				cout << "    verif de " << nextX << " " << nextY << endl;
				// on verifie que la prochaine trajectoire ne sera pas une diagonale
				//if( abs( ( nextX - coord.first) + ( nextY - coord.second) ) == 1  ){
				if( ( (nextX - coord.first)==0 && ((nextY - coord.second)==1 ) )
				 || ( (nextX - coord.first)==1 && ((nextY - coord.second)==0 ) )
				 ||	( (nextX - coord.first)==0 && ((nextY - coord.second)==-1) )
				 ||	( (nextX - coord.first)==-1 && ((nextY - coord.second)==0) ) ){
					cout << "    le prochain est bien voisin est sur le même axe" << endl;
					coord.first = nextX ;
					coord.second = nextY ;
					cout << "    ajout de " << coord.first << " " << coord.second << endl;
					pathList.push_front(coord);
				} else {
					cout << (nextX - coord.first) + (nextY - coord.second) <<  endl;
					cout << " prochain trop loin, on passe au suivant" << endl;
				}
				if( nextX == xA && nextY == yA ) closeIt == closeList.end();
			}
			return pathList;
		} else {
			cout << "  > Chemin pas encore trouvé " << endl;
		}
		cout << " ** FIN du If" << endl;


		cout << " * Recherche des voisins du Noeud Courant ..." << endl;
		cout << "   ... Nettoyage de listeVoisin ..." << endl;
		listeVoisin.clear();
		cout << "   listeVoisin vide ? " << listeVoisin.empty() << endl;
		listeVoisin.splice(voisinIt, graphDeRecherche.find_Voisin(xC,yC));
		cout << "   size listeVoisin = " << listeVoisin.size() << endl;
		cout << "   ... verification de listeVoisin " << endl;
		voisinIt = listeVoisin.begin();
		cout << "   listeVoisin contient : " << endl;
		for( ; voisinIt != listeVoisin.end() ; voisinIt++ ){
			cout << "   * " ;
			(*voisinIt).display();
			cout << endl;
		}
		cout << "   ... màj de _F _G _H pour chaque voisin du noeud Courant " << endl;
		int xD,yD;
		voisinIt = listeVoisin.begin();
		for( ; voisinIt != listeVoisin.end() ; voisinIt++ ){
			xD = (*voisinIt).get_X();
			yD = (*voisinIt).get_Y();
			cout << "   Voisin " << xD << "," << yD << endl;
			if( graphDeRecherche._graphe[xD][yD].get_costFinal() == 0){
				cout << "   > Ce Voisin n'a jamais été évalué" << endl;
				graphDeRecherche._graphe[xD][yD].set_costFromBegin( abs(xD - xA) + abs(yD - yA) );
				graphDeRecherche._graphe[xD][yD].set_costFromEnd( abs(xD - xB) + abs(yD - yB) );
				//(*voisinIt).set_costFromBegin(abs((xD+yD)-(xA+yA)));
				//(*voisinIt).set_costFromEnd(abs((xD+yD)-(xB+yB)));
				//cout << "   iT:";(*voisinIt).display();
				cout << "\n   après modif:\n   * " ;
				graphDeRecherche._graphe[xD][yD].display();
				cout << endl;
			} else if ( graphDeRecherche._graphe[xD][yD].get_costFinal() < 0 ){
				cout << "   > Ce Voisin est infranchissable" << endl;
			} else {
				cout << "   > Ce Voisin a déjà été évalué" << endl;
			}
		}
		graphDeRecherche.display();

		cout << " ** Debut du traitement de chaque voisin de courant"<< endl;
		voisinIt = listeVoisin.begin();
		for( ; voisinIt != listeVoisin.end() ; voisinIt++ ){
			xD = (*voisinIt).get_X();
			yD = (*voisinIt).get_Y();
			cout << "    Voisin " << xD << " , " << yD << endl;
			bool rep1,rep2,rep3,rep4,rep5;
			rep1 = (*voisinIt).get_costFinal() < 0;
			rep2 = graphDeRecherche.isInTheList(closeList ,(*voisinIt));
			rep3 = (graphDeRecherche._graphe[xD][yD].get_costFinal() <= graphDeRecherche._graphe[xC][yC].get_costFinal());
			rep4 = graphDeRecherche.isInTheList(openList ,(*voisinIt));
			rep5 = (graphDeRecherche._graphe[xD][yD].get_costFromEnd() <= graphDeRecherche._graphe[xC][yC].get_costFromEnd());

			cout << "    Ce voisin est infranchissable ? " << rep1 << endl;
			cout << "    Ce voisin est dans closeList  ? " << rep2 << endl;
			if( rep1 || rep2 ){
				if( rep1 ){
					cout << "  > Oui, ce voisin est infranchissable" << endl;
					cout << "    _F = " << (*voisinIt).get_costFinal() << endl;
				}
				if( rep2 ){
					cout << "  > Oui, ce voisin déjà traité" << endl;
				}
				cout << "    donc voisin suivant" << endl;
			} else {
				cout << "    le voisin est franchissable et non-traité " << endl;
				cout << "    Ce voisin a un cout <= au noeud courant ? " << rep3 << endl;
				cout << "    Ce voisin n'a pas été évalué ? " << !rep4 << endl;
				if( rep3 || !rep4 ){
					if( rep3 ){
						cout << "  > ce voisin a un cout <= au noeud courant" << endl ;
						if( rep5 ){
							cout << "  > ce voisin a un coutFromEnd <= au noeud courant" << endl ;
							xC = xD;
							yC = yD;
							enCours = &graphDeRecherche._graphe[xD][yD];
						}
					}
					if( !rep4 ){
						cout << "  > Ce voisin n'a pas été traité" << endl ;
						cout << "    ajout du voisin dans OpenList..." << endl;
						cout << "    size openList = " << openList.size() << endl;
						openList.push_back(graphDeRecherche._graphe[xD][yD]);
						cout << "    size openList = " << openList.size() << endl;
						openIt = openList.begin();
						cout << "    openList contient :" << endl;
						for(; openIt != openList.end(); openIt++){
							cout << "  * " ;
							(*openIt).display();
							cout << endl;
						}
					}
				} else {
					cout << "    Ce voisin n'est pas le plus court " << !rep4;
				}
			}
		}
		cout << " ** Fin du traitement" << endl;
		cout << " size actuel de openLIst = " << openList.size() << endl;
	}
	cout << " * Fin du while " << endl;
	cout << " Erreur : Impossible d'accéder à la cible " << endl;
	return pathList;
}

/** Retourne la longueur de la carte
 * */
int Carte::get_sizeX(void){
	return _sizeX;
}

/** Retourne la largeur de la carte
 * */
int Carte::get_sizeY(void){
	return _sizeY;
}

/** Retourne l'ID de l'objet dans la carte
 * */
int Carte::get_IDin(int x, int y){
	return _map[x][y]->get_ID();
}

/** Le destructeur de Carte
 * */
Carte::~Carte() {
	cout << " - carte de taille "<< _sizeX << "*" << _sizeY << " detruit" << endl;
}
