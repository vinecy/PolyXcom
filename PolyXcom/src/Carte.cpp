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

#include <iostream>			// Utilisation des flux d'entrées sorties de console
#include <cstdlib>			// Utilisation des biblio mathematiques
#include <assert.h>			// Utilisation des assertations
#include <list>				// Utilisation des Listes

#include "Carte.h"
#include "Graphe.h"			// Carte Utilise Graphe
#include "Affichable.h"		// Carte pointe sur des affichables

using namespace std;

static Affichable vide;

/** Le constructeur Carte initialise le tableau contenant les objets affichables
  * */
Carte::Carte() {
	_sizeX = 4 ;
	_sizeY = 4 ;
	_heightMap = 64*_sizeX;
	_widthMap = 64*_sizeY;
	_map = new Affichable **[_sizeY];
	_nameMap = "Map par défaut";
	_dangerZone = true;

	// initialisation de la carte
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){
		_map[i] = new Affichable*[_sizeX];
		for( j = 0 ; j < _sizeX ; j++ ){
			_map[i][j] = &vide;
			_listSquareMap.push_back(RectangleShape(Vector2f(64,64)));
		}
	}
	cout << " + carte "<< _nameMap << " crée" << endl;
	cout << " + adresse de vide "<< &vide << endl;
}

/** Le constructeur Carte initialise le tableau contenant les objets affichables
	 * @param x - la longueur de la carte
	 * @param y - la largeur de la carte
	 * */
Carte::Carte( int x , int y ) {
	_sizeX = x ;
	_sizeY = y ;
	_heightMap = 64*_sizeX;
	_widthMap = 64*_sizeY;
	_nameMap = "Map de taille fixé";
	_map = new Affichable **[_sizeY];
	_dangerZone = true;
	// initialisation de la carte
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){
		_map[i] = new Affichable*[_sizeX];
		for( j = 0 ; j < _sizeX ; j++ ){
			_map[i][j] = &vide;
			_listSquareMap.push_back(RectangleShape(Vector2f(64,64)));
		}
	}
	cout << " + carte "<< _nameMap << " crée" << endl;
	cout << " + adresse de vide "<< &vide << endl;
}

/** Le constructeur Carte initialise le tableau contenant les objets affichables
  * en fonction du fichier name.txt
	 * @param name - nom du fichier à partir duquel on charge la taille de la carte
	 * @param x - la longueur de la carte
	 * @param y - la largeur de la carte
	 * @param dZ - booléen indiquant si on est en zone de danger ou pas
	 * */
Carte::Carte( string name, int x , int y , bool dZ){
	_sizeX = x;
	_sizeY = y;
	_heightMap = 64*_sizeX;
	_widthMap = 64*_sizeY;
	_nameMap = name;
	_dangerZone = dZ;
	_map = new Affichable **[_sizeY];
	// initialisation de la carte
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){
		_map[i] = new Affichable*[_sizeX];
		for( j = 0 ; j < _sizeX ; j++ ){
			_map[i][j] = &vide;
			_listSquareMap.push_back(RectangleShape(Vector2f(64,64)));
		}
	}
	cout << " + carte "<< _nameMap << " de taille " << _sizeX <<"*"<< _sizeY <<" crée" << endl;
	cout << " + adresse de vide "<< &vide << endl;
}

void Carte::updatePosition(){
	_heightMap = 64*_sizeX*_zoom;
	_widthMap = 64*_sizeY*_zoom;
}


/** La méthode moveIsPossible permet de vérifier si la case (x,y) est franchissable ou pas
 	 * @param x,y - couple de coordonnées à verifier
 	 * @return - il retourne 1 si le deplacement est possible
 	 *						 2 si le deplacement est possible mais on franchit une nouvelle map
 	 * 					     0 si les autres cas sont faux.
 	 * */
int Carte::moveIsPossible( int x , int y , bool canCrossMap){
	int rep;
	if( (x < 0) || (x >= _sizeX) || (y < 0) || (y >= _sizeY)) {	// si case destination en dehors de la carte,
		rep = 0;												// déplacement impossible
	} else {
		if( !(_map[x][y] == &vide) ){							// si obstacle sur la case destination,
			rep = 0;											// déplacement impossible
			if( _map[x][y]->get_ID() == 4 && canCrossMap){		// sauf si portail sur la case destination,
				rep = 2;										// deplacement possible mais on franchit une nouvelle map
			}
		} else {												// en dehors de tous les autres cas,
			rep = 1;											// on peut se déplacer
		}
	}
	return (rep);
}

/** La methode move_up deplace un perso vers le Nord
	 * @param &perso - adresse du perso à déplacer
	 * @param withUsePas - booléen indiquant le déplacement utilise des PAs
	 * @param rep - adresse du portail qui va nous faire changer de Map qu'on retourne
	 * @return elle retourne 2 si on change de map,
	 * 						 1 si le déplacement a marché et
	 * 						 0 sinon
	 * */
int Carte::move_up(Personnage &perso, bool isDangerZone)
{
	int repMove,
		x = perso.get_x(),
		y = perso.get_y();
	repMove = this->moveIsPossible( x , y + 1 , true);
	if( repMove == 1 ){
		if(isDangerZone) {
			perso.set_paCurrent( perso.get_paCurrent() - 1 );	// si zone de combat alors on consomme des PA
		}
		moveItemTo( x , y , x , y + 1 );
	} else if( repMove == 2 && !isDangerZone ){ 				// si mode exploration, on peut changer de Map
		moveItemTo( x , y , x , y + 1 );
	} else {
		repMove = 0;
		cout << "erreur" << endl;
	}
	return (repMove);
}
/** La methode move_down deplace un perso vers le Sud
	 * @param &perso - adresse du perso à déplacer
	 * @param withUsePas - booléen indiquant le déplacement utilise des PAs
	 * @param rep - adresse du portail qui va nous faire changer de Map qu'on retourne
	 * @return elle retourne 2 si on change de map,
	 * 						 1 si le déplacement a marché et
	 * 						 0 sinon
	 * */
int Carte::move_down(Personnage &perso, bool isDangerZone)
{
	int repMove,
		x = perso.get_x(),
		y = perso.get_y();
	repMove = this->moveIsPossible( x , y - 1 , true);
	if( repMove == 1 ){
		if(isDangerZone){
			perso.set_paCurrent( perso.get_paCurrent() - 1 );	// si zone de combat alors on consomme des PA
		}
		moveItemTo( x , y , x , y - 1 );
	} else if( repMove == 2 && !isDangerZone ){ 				// si mode exploration, on peut changer de Map
		moveItemTo( x , y , x , y - 1 );
	} else {
		repMove = 0;
		cout << "erreur" << endl;
	}
	return (repMove);
}
/** La methode move_left deplace un peros vers l'Ouest
	 * @param &perso - adresse du perso à déplacer
	 * @param withUsePas - booléen indiquant le déplacement utilise des PAs
	 * @param rep - adresse du portail qui va nous faire changer de Map qu'on retourne
	 * @return elle retourne 2 si on change de map,
	 * 						 1 si le déplacement a marché et
	 * 						 0 sinon
	 * */
int Carte::move_left(Personnage &perso, bool isDangerZone)
{
	int repMove,
		x = perso.get_x(),
		y = perso.get_y();
	repMove = this->moveIsPossible( x - 1 , y , true);
	if( repMove == 1 ){
		if(isDangerZone){
			perso.set_paCurrent( perso.get_paCurrent() - 1 );	// si zone de combat alors on consomme des PA
		}
		moveItemTo( x , y , x - 1 , y  );
	} else if( repMove == 2 && !isDangerZone ){ 				// si mode exploration, on peut changer de Map
		moveItemTo( x , y , x - 1 , y );
	} else {
		repMove = 0;
		cout << "erreur" << endl;
	}
	return (repMove);
}

/** La methode move_right deplace un perso vers l'Est
	 * @param &perso - adresse du perso à déplacer
	 * @param withUsePas - booléen indiquant le déplacement utilise des PAs
	 * @param rep - adresse du portail qui va nous faire changer de Map qu'on retourne
	 * @return elle retourne 2 si on change de map,
	 * 						 1 si le déplacement a marché et
	 * 						 0 sinon
	 * */
int Carte::move_right(Personnage &perso, bool isDangerZone)
{
	int repMove,
		x = perso.get_x(),
		y = perso.get_y();
	repMove = this->moveIsPossible( x + 1 , y , true);
	if( repMove == 1 ){
		if(isDangerZone){
			perso.set_paCurrent( perso.get_paCurrent() - 1 );	// si zone de combat alors on consomme des PA
		}
		moveItemTo( x , y , x + 1 , y  );
	} else if( repMove == 2 && !isDangerZone ){ 				// si mode exploration, on peut changer de Map
		moveItemTo( x , y , x + 1 , y );
	} else {
		repMove = 0;
		cout << "erreur" << endl;
	}
	return (repMove);
}

/*
list<Personnage*> Carte::near(Personnage &cible, list<Personnage*> team)
{
	list<Personnage*>::iterator ite;
	list<Personnage*> l;
	for(ite=team.begin();ite!=team.end();ite++)
	{
		if(((((*ite)->get_x()+1==cible.get_x())||((*ite)->get_x()-1==cible.get_x()))&&((*ite)->get_y()==cible.get_y())))
		{
			l.push_front((*ite));
		}
		else if(((((*ite)->get_y()+1==cible.get_y())||((*ite)->get_y()-1==cible.get_y()))&&((*ite)->get_x()==cible.get_x())))
		{
			l.push_front((*ite));
		}
	}
	return(l);
}*/


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

/** La méthode removeAllItem permet un affichable en argument dans la carte
 	 * @param &a - addresse de l'affichable à retirer
 	 * */
void Carte::removeItem( Affichable &a ){
	if( _map[ a.get_x() ][ a.get_y() ] == &vide ) {
		cout << "!!! il y a déjà personne  !!!" << endl ;
	}
	_map[ a.get_x() ][ a.get_y() ] = &vide;
}

/** La méthode removeAllItem permet d'enlever tous les objets de la carte
  * */
void Carte::removeAllItem(){
	int i,j;
	for( j = 0 ; j < _sizeY ; j++ ){
		for( i = 0 ; i < _sizeX ; i++ ){
			_map[i][j] = &vide;
		}
	}
}

/** La méthode moveItemTo permet de deplacer un affichable
  * d'un point oldX,oldY à un point newX,newY sur la carte
 	 * @param *a - pointeur sur l'affichable à déplacer sur la carte
 	 * @param newX,newY - nouvelle coordonnées de l'objet à déplacer
 	 * */
void Carte::moveItemTo( int oldX, int oldY , int newX , int newY ){
	_map[ newX ][ newY ] = _map[ oldX ][ oldY ];
	_map[ oldX ][ oldY ] = &vide;

	_map[ newX ][ newY ]->set_x(newX);
	_map[ newX ][ newY ]->set_y(newY);
}

/** La méthode moveItemToWithMoveAnim permet de deplacer un affichable
  * d'un point oldX,oldY à un point newX,newY sur la carte avec actualisation de la carte
  * case par case
 	 * @param oldX,oldY- pointeur sur l'affichable à déplacer sur la carte
 	 * @param newX,newY - nouvelle coordonnées de l'objet à déplacer
 	 * */
void Carte::moveItemToWithMoveAnim( int oldX, int oldY , int newX , int newY ){
	list<pair<int,int> > path;
	list<pair<int,int> >::iterator ite_p;
	path = this->pathfinding(oldX,oldY,newX,newY);
	path.pop_back();

	cout << " le chemin à faire : " << endl;
	ite_p = path.begin();
	ite_p++;
	for( ; ite_p != path.end() ; ite_p++){
		cout << (*ite_p).first <<","<< (*ite_p).second << endl;
		this->moveItemTo( oldX, oldY, (*ite_p).first, (*ite_p).second );
		oldX = (*ite_p).first;
		oldY = (*ite_p).second;
		this->display();
	}
}


/** La méthode pathfinding permet de trouver le meilleur chemin d'un point A à un point B
  * sur la carte avec l'algorithme A*. Il retourne le chemin trouvé, c'est une liste de
  * coordonnées à suivre
 	 * @param xA,yA - Point de Départ
 	 * @param xB,yB - Point d'arrivée
 	 * @return - retourne une liste de paires de coordonnées
 	 * */
list <pair<int , int> > Carte::pathfinding( int xA , int yA , int xB , int yB ){
	//assert( this->moveIsPossible(xB, yB) == true);		// La cible doit être valide

	// initialisation du graphe
	Graphe graphDeRecherche(this);
	graphDeRecherche._graphe[xA][yA].set_costFromBegin(0);
	graphDeRecherche._graphe[xA][xA].set_costFromEnd( abs(xA - xB) + abs(yA - yB) );

	graphDeRecherche._graphe[xB][yB].set_costFromBegin( abs(xA - xB) + abs(yA - yB) );
	graphDeRecherche._graphe[xB][xB].set_costFromEnd(0);

	//graphDeRecherche.display();

	// Definition du Noeud Courant
//	cout << "creation du noeud courant..." << endl;
	Noeud *enCours = new Noeud;
	enCours = &graphDeRecherche._graphe[xA][yA];
	int xC = enCours->get_X(),
		yC = enCours->get_Y();
	//cout << "... verification des pointeurs ..." << endl;
//	cout << "@graphe = " << &graphDeRecherche._graphe[xA][yA] << endl;
//cout << "encours = "<< enCours << endl;

	// initialisation des listes de Noeuds
//	cout << "creation des listes de Noeud..." << endl;
	list <Noeud> openList;					// Liste contenant les noeuds à traiter
	list <Noeud> closeList;					// Liste contenant les noeuds déjà traités
	list <Noeud> listeVoisin;				// Liste contenant les voisins du noeud courant
	list <pair<int , int> > pathList;		// Liste contenant le veritable chemin

	// définition des itérateurs
	//cout << "... creation des iterateurs..." << endl;
	list<Noeud>::iterator openIt = openList.begin();
	list<Noeud>::iterator closeIt = closeList.begin();
	list<Noeud>::iterator voisinIt = listeVoisin.begin();
	list <pair<int , int> >::iterator pathIt = pathList.begin();
	list<Noeud>::iterator nodelowestCost;
//	cout << "... verification des listes ..." << endl;
	//cout << "size openList = " << openList.size() << endl;
	//cout << "size closeList = " << closeList.size() << endl;
	//cout << "size listeVoisin = " << listeVoisin.size() << endl;
	//cout << "size pathList = " << pathList.size() << endl;

	//cout << "*** DEBUT DE L'ALGORITHME A* ***" << endl;

	//cout << "ajout du noeud de départ dans OpenList..." << endl;
	openList.push_back(*enCours);
	//cout << " size openList = " << openList.size() << endl;
	openIt = openList.begin();
	//cout << " openList contient :" << endl;
	for(; openIt != openList.end(); openIt++){
		cout << " * " ;
		(*openIt).display();
		cout << endl;
	}

	//cout << " *** \n *** DEBUT DE L'ALGORITHME A* *** \n *** "<< endl;

	// Tant qu'il y a toujours des noeuds à traiter
//	cout << " * Debut du while " << endl;
	while( !openList.empty() ){
		//cout << " Liste non vide " << endl;
		//graphDeRecherche.display();

		//cout << " * Le noeud courant pointe sur le noeud avec le f_cost le plus faible" << endl;
		//cout << "   Recherche du noeud ..." << endl;
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
		//	cout << "    It minimal : " ;
		//	(*nodelowestCost).display();
			//cout << "\n    It actuel  : ";
		//	(*openIt).display();
			//cout << endl;
			openIt++;
		}
		xC = (*nodelowestCost).get_X();
		yC = (*nodelowestCost).get_Y();
		enCours = &graphDeRecherche._graphe[xC][yC];
	//	cout << " > le noeud minimal est "<< enCours << endl;
	//	cout << " > le noeud minimal est "<< xC << "," << yC << endl;

	//	cout << " * On retire le Noeud courant de OpenList " << endl;
	//	cout << "   size openLIst preced = " << openList.size() << endl;
		openList.erase(nodelowestCost);
	//	cout << "   size openLIst actuel = " << openList.size() << endl;

	//	cout << " * Ajout du noeud Courant dans CloseList ..." << endl;
	//	cout << "   size closeList = " << closeList.size() << endl;
		closeList.push_front(*enCours);
	//	cout << "   size closeList = " << closeList.size() << endl;
	//	cout << "   ... verification de closeList " << endl;
		closeIt = closeList.begin();
	//	cout << "   closeList contient :" << endl;
		/*for(; closeIt != closeList.end(); closeIt++){
			cout << "  * " ;
			(*closeIt).display();
			cout << endl ;
		}*/

		// le noeud courant est-il la cible ?
	//	cout << " ** Debut du If \"le noeud courant est-il sur la cible\""<< endl;
		if( xC == xB && yC == yB ){
			cout << "  > Chemin trouvé !!!" << endl;
		//	cout << "    ... reconstitution du chemin " << endl;
			pair<int,int> coord;
			int nextX,nextY;
			pathIt = pathList.begin();
			closeIt = closeList.begin();
			coord.first = (*closeIt).get_X();
			coord.second = (*closeIt).get_Y();
		//	cout << "    ajout de " << coord.first << " " << coord.second << endl;
			pathList.push_back(coord);
			closeIt++;
			for(; closeIt != closeList.end(); closeIt++){
				nextX = (*closeIt).get_X();
				nextY = (*closeIt).get_Y();
			//	cout << "    verif de " << nextX << " " << nextY << endl;
				// on verifie que la prochaine trajectoire ne sera pas une diagonale
				//if( abs( ( nextX - coord.first) + ( nextY - coord.second) ) == 1  ){
				if( ( (nextX - coord.first)==0 && ((nextY - coord.second)==1 ) )
				 || ( (nextX - coord.first)==1 && ((nextY - coord.second)==0 ) )
				 ||	( (nextX - coord.first)==0 && ((nextY - coord.second)==-1) )
				 ||	( (nextX - coord.first)==-1 && ((nextY - coord.second)==0) ) ){
				//	cout << "    le prochain est bien voisin est sur le même axe" << endl;
					coord.first = nextX ;
					coord.second = nextY ;
				//	cout << "    ajout de " << coord.first << " " << coord.second << endl;
					pathList.push_front(coord);
				} else {
					//cout << (nextX - coord.first) + (nextY - coord.second) <<  endl;
					//cout << " prochain trop loin, on passe au suivant" << endl;
				}
				if( nextX == xA && nextY == yA ) closeIt == closeList.end();
			}
			return (pathList);
		} else {
		//	cout << "  > Chemin pas encore trouvé " << endl;
		}
		//cout << " ** FIN du If" << endl;


	//	cout << " * Recherche des voisins du Noeud Courant ..." << endl;
		//cout << "   ... Nettoyage de listeVoisin ..." << endl;
		listeVoisin.clear();
		//cout << "   listeVoisin vide ? " << listeVoisin.empty() << endl;
		list<Noeud> tps = graphDeRecherche.find_Voisin(xC, yC);
		listeVoisin.splice(voisinIt, tps);
		//cout << "   size listeVoisin = " << listeVoisin.size() << endl;
		//cout << "   ... verification de listeVoisin " << endl;
		voisinIt = listeVoisin.begin();
		//cout << "   listeVoisin contient : " << endl;
		/*for( ; voisinIt != listeVoisin.end() ; voisinIt++ ){
			cout << "   * " ;
			(*voisinIt).display();
			cout << endl;
		}*/
		//cout << "   ... màj de _F _G _H pour chaque voisin du noeud Courant " << endl;
		int xD,yD;
		voisinIt = listeVoisin.begin();
		for( ; voisinIt != listeVoisin.end() ; voisinIt++ ){
			xD = (*voisinIt).get_X();
			yD = (*voisinIt).get_Y();
			//cout << "   Voisin " << xD << "," << yD << endl;
			if( graphDeRecherche._graphe[xD][yD].get_costFinal() == 0){
			//	cout << "   > Ce Voisin n'a jamais été évalué" << endl;
				graphDeRecherche._graphe[xD][yD].set_costFromBegin( abs(xD - xA) + abs(yD - yA) );
				graphDeRecherche._graphe[xD][yD].set_costFromEnd( abs(xD - xB) + abs(yD - yB) );
				//(*voisinIt).set_costFromBegin(abs((xD+yD)-(xA+yA)));
				//(*voisinIt).set_costFromEnd(abs((xD+yD)-(xB+yB)));
				//cout << "   iT:";(*voisinIt).display();
			//	cout << "\n   après modif:\n   * " ;
				//graphDeRecherche._graphe[xD][yD].display();
				//cout << endl;
			} else if ( graphDeRecherche._graphe[xD][yD].get_costFinal() < 0 ){
			//	cout << "   > Ce Voisin est infranchissable" << endl;
			} else {
			//	cout << "   > Ce Voisin a déjà été évalué" << endl;
			}
		}
		//graphDeRecherche.display();

	//	cout << " ** Debut du traitement de chaque voisin de courant"<< endl;
		voisinIt = listeVoisin.begin();
		for( ; voisinIt != listeVoisin.end() ; voisinIt++ ){
			xD = (*voisinIt).get_X();
			yD = (*voisinIt).get_Y();
		//	cout << "    Voisin " << xD << " , " << yD << endl;
			bool rep1,rep2,rep3,rep4,rep5;
			rep1 = (*voisinIt).get_costFinal() < 0;
			rep2 = graphDeRecherche.isInTheList(closeList ,(*voisinIt));
			rep3 = (graphDeRecherche._graphe[xD][yD].get_costFinal() <= graphDeRecherche._graphe[xC][yC].get_costFinal());
			rep4 = graphDeRecherche.isInTheList(openList ,(*voisinIt));
			rep5 = (graphDeRecherche._graphe[xD][yD].get_costFromEnd() <= graphDeRecherche._graphe[xC][yC].get_costFromEnd());

			//cout << "    Ce voisin est infranchissable ? " << rep1 << endl;
		//	cout << "    Ce voisin est dans closeList  ? " << rep2 << endl;
			if( rep1 || rep2 ){
				if( rep1 ){
				//	cout << "  > Oui, ce voisin est infranchissable" << endl;
				//	cout << "    _F = " << (*voisinIt).get_costFinal() << endl;
				}
				if( rep2 ){
				//	cout << "  > Oui, ce voisin déjà traité" << endl;
				}
				//cout << "    donc voisin suivant" << endl;
			} else {
				//cout << "    le voisin est franchissable et non-traité " << endl;
				//cout << "    Ce voisin a un cout <= au noeud courant ? " << rep3 << endl;
				//cout << "    Ce voisin n'a pas été évalué ? " << !rep4 << endl;
				if( rep3 || !rep4 ){
					if( rep3 ){
						//cout << "  > ce voisin a un cout <= au noeud courant" << endl ;
						if( rep5 ){
							//cout << "  > ce voisin a un coutFromEnd <= au noeud courant" << endl ;
							xC = xD;
							yC = yD;
							enCours = &graphDeRecherche._graphe[xD][yD];
						}
					}
					if( !rep4 ){
						//cout << "  > Ce voisin n'a pas été traité" << endl ;
						//cout << "    ajout du voisin dans OpenList..." << endl;
						//cout << "    size openList = " << openList.size() << endl;
						openList.push_back(graphDeRecherche._graphe[xD][yD]);
						//cout << "    size openList = " << openList.size() << endl;
						openIt = openList.begin();
						//cout << "    openList contient :" << endl;
						/*for(; openIt != openList.end(); openIt++){
							cout << "  * " ;
							(*openIt).display();
							cout << endl;
						}*/
					}
				} else {
					//cout << "    Ce voisin n'est pas le plus court " << !rep4;
				}
			}
		}
		//cout << " ** Fin du traitement" << endl;
		//cout << " size actuel de openLIst = " << openList.size() << endl;
	}
	//cout << " * Fin du while " << endl;
	cout << " Erreur : Impossible d'accéder à la cible " << endl;
	return (pathList);
}

/** La méthode drawPath permet de tracer un segment entre deux points A et B
  * grace à l'Algorithme de tracé de segment de Bresenham
 	 * @param xA,yA - Point de Départ
 	 * @param xB,yB - Point d'arrivée
 	 * @return - retourne une liste de paires de coordonnées correspondant au segment tracé
 	 * */
list <pair<int , int> > Carte::drawPath( int xA, int yA, int xB, int yB ){
	list <pair<int , int> > path;	// liste de paire de coordonnées representant le segment tracé
	pair<int , int> coord;			// paire de coordonnées x,y
	int dx, dy;
	// Utilisation de l'Algorithme de tracé de segment de Bresenham
	dx = xB - xA;
	if( dx != 0 ){
		if( dx > 0 ){
			dy = yB - yA;
			if( dy != 0 ){
				if( dy > 0 ){		// vecteur oblique dans le 1er quadran (x > 0 et y > 0)
					if( dx >= dy ){ // vecteur diagonal proche de l’horizontale, dans le 1er octant
						int e = dx;
						dx = e * 2;
						dy = dy * 2;
						xA++;
						while( xA != xB ){
							e = e - dy;
							if(e < 0){
								yA++;
								e = e + dx;
							}
							coord.first = xA;
							coord.second = yA;
							path.push_back(coord);
							xA++;
						}
					} else {		// vecteur oblique proche de la verticale, dans le 2d octant
						int e = dy;
						dy = e * 2;
						dx = dx * 2;
						yA++;
						while( yA != yB ){
							e = e - dx;
							if(e < 0){
								xA++;
								e = e + dy;
							}
							coord.first = xA;
							coord.second = yA;
							path.push_back(coord);
							yA++;
						}
					}
				} else {			// vecteur oblique dans le 4e cadran (x > 0 et y < 0)
					if(dx >= -dy){	// vecteur diagonal proche de l’horizontale, dans le 8e octant
						int e = dx;
						dx = e * 2;
						dy = dy * 2;
						xA++;
						while( xA != xB ){
							e = e + dy;
							if(e < 0){
								yA--;
								e = e + dx;
							}
							coord.first = xA;
							coord.second = yA;
							path.push_back(coord);
							yA--;
						}
					} else {		// vecteur oblique proche de la verticale, dans le 7e octant
						int e = dy;
						dy = e * 2;
						dx = dx * 2;
						yA--;
						while( yA != yB ){
							e = e + dx;
							if(e > 0){
								xA++;
								e = e + dy;
							}
							coord.first = xA;
							coord.second = yA;
							path.push_back(coord);
							yA--;
						}
					}
				}
			} else {			// dy = 0 (et dx > 0)
				xA++;			// vecteur horizontal vers la droite
				while( xA != xB ){
					coord.first = xA;
					coord.second = yA;
					path.push_back(coord);
					xA++;
				}
			}
		} else {				// dx < 0
			dy = yB - yA;
			if( dy != 0 ){
				if( dy > 0 ){	// vecteur oblique dans le 2nd quadran
					if( -dx >= dy ){ // vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
						int e = dx;
						dx = e * 2;
						dy = dy * 2;
						xA--;
						while( xA != xB ){
							e = e + dy;
							if(e >= 0){
								yA++;
								e = e + dx ;
							}
							coord.first = xA;
							coord.second = yA;
							path.push_back(coord);
							xA--;
						}
					} else {	// vecteur oblique proche de la verticale, dans le 3e octant
						int e = dy;
						dy = e * 2;
						dx = dx * 2;
						yA++;
						while( yA != yB ){
							e = e + dx;
							if(e <= 0){
								xA--;
								e = e + dy ;
							}
							coord.first = xA;
							coord.second = yA;
							path.push_back(coord);
							yA++;
						}
					}
				} else {			// vecteur oblique dans le 3e cadran
					if(dx <= dy){   // vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
						int e = dx;
						dx = e * 2;
						dy = dy * 2;
						xA--;
						while( xA != xB ){
							e = e - dy;
							if(e >= 0){
								yA--;
								e = e + dx ;
							}
							coord.first = xA;
							coord.second = yA;
							path.push_back(coord);
							xA--;
						}
					} else { // vecteur oblique proche de la verticale, dans le 6e octant
						int e = dy;
						dy = e * 2;
						dx = dx * 2;
						yA--;
						while( yA != yB ){
							e = e - dx;
							if(e >= 0){
								xA--;
								e = e + dy ;
							}
							coord.first = xA;
							coord.second = yA;
							path.push_back(coord);
							yA--;
						}
					}
				}
			} else { 		// vecteur horizontal vers la gauche
				xA--;
				while( xA != xB ){
					coord.first = xA;
					coord.second = yA;
					path.push_back(coord);
					xA--;
				}
			}
		}
	} else { // dx = 0
		dy = yB - yA;
		if(dy != 0){
			if(dy > 0){ 	// vecteur vertical croissant
				yA++;
				while( yA != yB ){
					coord.first = xA;
					coord.second = yA;
					path.push_back(coord);
					yA++;
				}
			} else {		// verteur vertical decroissant
				yA--;
				while( yA != yB ){
					coord.first = xA;
					coord.second = yA;
					path.push_back(coord);
					yA--;
				}
			}
		}
	}
	return (path);
}

/** La méthode pathIsPossible permet de confirmer si le chemin entre deux points
 * A et B ne presente aucun obstacle
 	 * @param xA,yA - Point de Départ
 	 * @param xB,yB - Point d'arrivée
 	 * @return - retourne 1 si c'est un chemin sans obstacle et
 	 * 					  0 sinon
 	 * */
bool Carte::pathIsPossible( int xA, int yA, int xB, int yB ){
	list<pair<int,int> > path = this->drawPath(xA, yA, xB, yB);
	list<pair<int,int> >::iterator it;
	it = path.begin();
	bool rep = true;

	while( it != path.end() && rep == true ){
		rep = (moveIsPossible( (*it).first, (*it).second , false) != 0) ;
		it++;
	}
	return (rep);
}

/** La méthode seekSpawnPoint permet de retourner les cases où on peut placer des
  * personnages autour d'un point xA,yA.
 	 * @param xA,yA - Point de Départ
 	 * @param xB,yB - Point d'arrivée
 	 * @param nb - nombre de personnages à placer
 	 * @return - retourne une liste de paire de coordonnées où on peut placer des personnages
 	 * */
list <pair<int , int> > Carte::seekSpawnPoint(int xA, int yA, int nb){
	list <pair<int , int> > rep;
	pair<int , int> tmp;
	int i,j,
		cont;
	cont = nb;
	i = (xA + 1);
	j = yA;
	cout << "test: " << i << " " << j ;
	if ( (moveIsPossible(i, j, false) == 1) && (cont>0) ){
		tmp.first = i; tmp.second = j;
		rep.push_back(tmp);
		cont--;
		cout << " -> valide" << endl;
	} else cout << " -> impossible" << endl;
	i = (xA - 1) ;
	j = yA ;
	cout << "test: " << i << " " << j ;
	if ( (moveIsPossible(i, j, false) == 1) && (cont>0)){
		tmp.first = i; tmp.second = j;
		rep.push_back(tmp);
		cont--;
		cout << " -> valide" << endl;
	} else cout << " -> impossible" << endl;
	i = xA;
	j = (yA + 1);
	cout << "test: " << i << " " << j ;
	if ( (moveIsPossible(i, j, false) == 1) && (cont>0)){
		tmp.first = i; tmp.second = j;
		rep.push_back(tmp);
		cont--;
		cout << " -> valide" << endl;
	} else cout << " -> impossible" << endl;
	i = xA;
	j = (yA - 1);
	cout << "test: " << i << " " << j ;
	if ( (moveIsPossible(i, j, false) == 1) && (cont>0)){
		tmp.first = i; tmp.second = j;
		rep.push_back(tmp);
		cont--;
		cout << " -> valide" << endl;
	} else cout << " -> impossible" << endl;
	return (rep);
}


/** La méthode display permet d'afficher la carte sur la console */
void Carte::display( void ) {
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	cout << " *** affichage de " << _nameMap << " *** " << endl;
	cout << " ----------------- " << endl;
	for( i = _sizeY-1 ; i >= 0 ; i-- ){
		for( j = 0 ; j < _sizeX ; j++ ){
			cout << " | " << _map[j][i]->get_ID() ;
		}
		cout << " | "<< endl << " ----------------- " << endl;
	}
	cout << " *** fin affichage *** " << endl;
}

/** Retourne la longueur de la carte
 * */
int Carte::get_sizeX(void){
	return (_sizeX);
}

/** Retourne la largeur de la carte
 * */
int Carte::get_sizeY(void){
	return (_sizeY);
}

string Carte::get_nameMap(void){
	return (_nameMap);
}

bool Carte::get_dangerZone(void){
	return (_dangerZone);
}

/** Retourne l'ID de l'objet dans la carte
 * */
int Carte::get_IDin(int x, int y){
	return (_map[x][y]->get_ID());
}

void Carte::set_sizeX(int value){
	_sizeX = value;
}

void Carte::set_sizeY(int value){
	_sizeY = value;
}


/** Le destructeur de Carte
 * */
Carte::~Carte() {
	cout << " - carte de taille "<< _sizeX << "*" << _sizeY << " detruit" << endl;
}
