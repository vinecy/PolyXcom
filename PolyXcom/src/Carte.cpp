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

#include <iostream>			// Utilisation des flux d'entr�es sorties de console
#include <cstdlib>			// Utilisation des biblio mathematiques
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
	_nameMap = "Map par d�faut";
	_dangerZone = true;

	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){							// initialisation de la carte
		_map[i] = new Affichable*[_sizeX];
		for( j = 0 ; j < _sizeX ; j++ ){
			_map[i][j] = &vide;
			_listSquareMap.push_back(RectangleShape(Vector2f(64,64)));
		}
	}
	cout << " + carte "<< _nameMap << " cr�e" << endl;
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
	_nameMap = "Map de taille fix�";
	_map = new Affichable **[_sizeY];
	_dangerZone = true;
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){							// initialisation de la carte
		_map[i] = new Affichable*[_sizeX];
		for( j = 0 ; j < _sizeX ; j++ ){
			_map[i][j] = &vide;
			_listSquareMap.push_back(RectangleShape(Vector2f(64,64)));
		}
	}
	cout << " + carte "<< _nameMap << " cr�e" << endl;
	cout << " + adresse de vide "<< &vide << endl;
}

/** Le constructeur Carte initialise le tableau contenant les objets affichables
  * en fonction du fichier name.txt
	 * @param name - nom du fichier � partir duquel on charge la taille de la carte
	 * @param x - la longueur de la carte
	 * @param y - la largeur de la carte
	 * @param dZ - bool�en indiquant si on est en zone de danger ou pas
	 * */
Carte::Carte( string name, int x , int y , bool dZ){
	_sizeX = x;
	_sizeY = y;
	_heightMap = 64*_sizeX;
	_widthMap = 64*_sizeY;
	_nameMap = name;
	_dangerZone = dZ;
	_map = new Affichable **[_sizeY];
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){							// initialisation de la carte
		_map[i] = new Affichable*[_sizeX];
		for( j = 0 ; j < _sizeX ; j++ ){
			_map[i][j] = &vide;
			_listSquareMap.push_back(RectangleShape(Vector2f(64,64)));
		}
	}
	cout << " + carte "<< _nameMap << " de taille " << _sizeX <<"*"<< _sizeY <<" cr�e" << endl;
	cout << " + adresse de vide "<< &vide << endl;
}

/** La m�thode updatePosition remet � jour la taille du graphe
  * */
void Carte::updatePosition(){
	_heightMap = 64*_sizeX*_zoom;
	_widthMap = 64*_sizeY*_zoom;
}

/** La m�thode moveIsPossible permet de v�rifier si la case (x,y) est franchissable ou pas
 	 * @param x,y - couple de coordonn�es � verifier
 	 * @return - il retourne 1 si le deplacement est possible
 	 *						 2 si le deplacement est possible mais on franchit une nouvelle map
 	 * 					     0 si les autres cas sont faux.
 	 * */
int Carte::moveIsPossible( int x , int y , bool canCrossMap){
	int rep;
	if( (x < 0) || (x >= _sizeX) || (y < 0) || (y >= _sizeY)) {	// si case destination en dehors de la carte,
		rep = 0;												// d�placement impossible
	} else {
		if( !(_map[x][y] == &vide) ){							// si obstacle sur la case destination,
			rep = 0;											// d�placement impossible
			if( _map[x][y]->get_ID() == 4 && canCrossMap){		// sauf si un portail est sur la case destination,
				rep = 2;										// alors deplacement possible mais on franchit une nouvelle map
			}
		} else {												// en dehors de tous les autres cas,
			rep = 1;											// on peut se d�placer
		}
	}
	return (rep);
}

/** La methode move_up deplace un perso vers le Nord
	 * @param &perso - adresse du perso � d�placer
	 * @param withUsePas - bool�en indiquant le d�placement utilise des PAs
	 * @param rep - adresse du portail qui va nous faire changer de Map qu'on retourne
	 * @return elle retourne 2 si on change de map,
	 * 						 1 si le d�placement a march� et
	 * 						 0 sinon
	 * */
int Carte::move_up(Personnage &perso, bool isDangerZone)
{
	int repMove,
		x = perso.get_x(),
		y = perso.get_y();
	repMove = this->moveIsPossible( x , y + 1 , true);
	if( repMove == 1 ){
		if(isDangerZone){
			perso.set_paCurrent( perso.get_paCurrent() - 1 );	// si zone de combat alors on consomme des PA
		}
		moveItemTo( x , y , x , y + 1 );
	} else if( repMove == 2 && !isDangerZone ){ 				// si mode exploration, on peut changer de Map
		moveItemTo( x , y , x , y + 1 );
	} else {
		//cout << "ancien repmove "<< repMove<<endl;
		repMove = 0;
		//cout << "erreur" << endl;
	}
	return (repMove);
}
/** La methode move_down deplace un perso vers le Sud
	 * @param &perso - adresse du perso � d�placer
	 * @param withUsePas - bool�en indiquant le d�placement utilise des PAs
	 * @param rep - adresse du portail qui va nous faire changer de Map qu'on retourne
	 * @return elle retourne 2 si on change de map,
	 * 						 1 si le d�placement a march� et
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
	 * @param &perso - adresse du perso � d�placer
	 * @param withUsePas - bool�en indiquant le d�placement utilise des PAs
	 * @param rep - adresse du portail qui va nous faire changer de Map qu'on retourne
	 * @return elle retourne 2 si on change de map,
	 * 						 1 si le d�placement a march� et
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
	 * @param &perso - adresse du perso � d�placer
	 * @param withUsePas - bool�en indiquant le d�placement utilise des PAs
	 * @param rep - adresse du portail qui va nous faire changer de Map qu'on retourne
	 * @return elle retourne 2 si on change de map,
	 * 						 1 si le d�placement a march� et
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


/** La m�thode addItem permet d'ajouter un affichable sur la carte
 	 * @param &a - adresse de l'affichable � ajouter
 	 * */
void Carte::addItem( Affichable &a ){
	if( _map[ a.get_x() ][ a.get_y() ] != &vide ) {
		cout << "!!! on �crase un affichable d�j� present !!!" << endl ;
	}
	_map[ a.get_x() ][ a.get_y() ] = &a;
}

/** La m�thode removeAllItem permet de retirer l'affichable en argument dans la carte
 	 * @param &a - addresse de l'affichable � retirer
 	 * */
void Carte::removeItem( Affichable &a ){
	if( _map[ a.get_x() ][ a.get_y() ] == &vide ) {
		cout << "!!! il y a d�j� personne  !!!" << endl ;
	}
	_map[ a.get_x() ][ a.get_y() ] = &vide;
}

/** La m�thode removeAllItem permet d'enlever tous les objets de la carte
  * */
void Carte::removeAllItem(){
	int i,j;
	for( j = 0 ; j < _sizeY ; j++ ){
		for( i = 0 ; i < _sizeX ; i++ ){
			_map[i][j] = &vide;
		}
	}
}

/** La m�thode moveItemTo permet de deplacer un affichable
  * d'un point oldX,oldY � un point newX,newY sur la carte
 	 * @param oldX,oldY - ancienne coordonn�es de l'objet � d�placer
 	 * @param newX,newY - nouvelle coordonn�es de l'objet � d�placer
 	 * */
void Carte::moveItemTo( int oldX, int oldY , int newX , int newY ){
	_map[ newX ][ newY ] = _map[ oldX ][ oldY ];
	_map[ oldX ][ oldY ] = &vide;

	_map[ newX ][ newY ]->set_x(newX);
	_map[ newX ][ newY ]->set_y(newY);
}

/** La m�thode moveItemToWithMoveAnim permet de deplacer un affichable
  * d'un point oldX,oldY � un point newX,newY sur la carte avec actualisation de la carte
  * case par case
 	 * @param oldX,oldY - ancienne coordonn�es de l'objet � d�placer
 	 * @param newX,newY - nouvelle coordonn�es de l'objet � d�placer
 	 * */
void Carte::moveItemToWithMoveAnim( int oldX, int oldY , int newX , int newY ){
	list<pair<int,int> > path;
	list<pair<int,int> >::iterator ite_p;
	path = this->pathfinding(oldX,oldY,newX,newY);
	path.pop_back();

	ite_p = path.begin();
	ite_p++;
	for( ; ite_p != path.end() ; ite_p++){
		this->moveItemTo( oldX, oldY, (*ite_p).first, (*ite_p).second );
		oldX = (*ite_p).first;
		oldY = (*ite_p).second;
	}
}


/** La m�thode pathfinding permet de trouver le meilleur chemin d'un point A � un point B
  * sur la carte avec l'algorithme A*. Il retourne le chemin trouv�, c'est une liste de
  * coordonn�es � suivre
 	 * @param xA,yA - Point de D�part
 	 * @param xB,yB - Point d'arriv�e
 	 * @return - retourne une liste de paires de coordonn�es
 	 * */
list <pair<int , int> > Carte::pathfinding( int xA , int yA , int xB , int yB ){
	// initialisation du graphe
	Graphe graphDeRecherche(this);
	graphDeRecherche._graphe[xA][yA].set_costFromBegin(0);
	graphDeRecherche._graphe[xA][xA].set_costFromEnd( abs(xA - xB) + abs(yA - yB) );

	graphDeRecherche._graphe[xB][yB].set_costFromBegin( abs(xA - xB) + abs(yA - yB) );
	graphDeRecherche._graphe[xB][xB].set_costFromEnd(0);
	//graphDeRecherche.display();

	Noeud *enCours = new Noeud;						// Definition du Noeud Courant
	enCours = &graphDeRecherche._graphe[xA][yA];	// Le noeud Courant le case de d�part du chemin � trouver
	int xC = enCours->get_X(),						// Definition des Coordonn�es du Noeud Courant
		yC = enCours->get_Y();
													// initialisation des listes de Noeuds
	list <Noeud> openList;							// Liste contenant les noeuds � traiter
	list <Noeud> closeList;							// Liste contenant les noeuds d�j� trait�s
	list <Noeud> listeVoisin;						// Liste contenant les voisins du noeud courant
	list <pair<int , int> > pathList;				// Liste contenant le veritable chemin
																	// d�finition des it�rateurs
	list<Noeud>::iterator openIt = openList.begin();				// il pointe tous au d�but de leur liste respective
	list<Noeud>::iterator closeIt = closeList.begin();
	list<Noeud>::iterator voisinIt = listeVoisin.begin();
	list <pair<int , int> >::iterator pathIt = pathList.begin();
	list<Noeud>::iterator nodelowestCost;			// Noeud contenant le noeud ayant le cout le plus faible

	//cout << "*** DEBUT DE L'ALGORITHME A* ***" << endl;

	openList.push_back(*enCours);					// on ajoute le noeud de d�part dans la liste des Noeuds � traiter
	openIt = openList.begin();

	while( !openList.empty() ){					// Tant qu'il y a toujours des noeuds � traiter
		openIt = openList.begin();				// Au debut, on recherche dans la liste des noeuds � traiter,
		int H_cost_Min = _sizeX*_sizeY;			// le Noeud avec le cout depuis le debut le plus faible
		int F_cost_Min = _sizeX*_sizeY;			// et avec le cout depuis la fin le plus faible
		while(openIt != openList.end()){				// recherche classique du Noeud Minimal
			if( (*openIt).get_costFinal() <= F_cost_Min ){
				if( (*openIt).get_costFromEnd() <= H_cost_Min ){
					nodelowestCost = openIt;
					H_cost_Min = (*openIt).get_costFromEnd();
					F_cost_Min = (*openIt).get_costFinal();
				}
			}
			openIt++;
		}
		xC = (*nodelowestCost).get_X();				// on ressort avec les coordonn�es du Noeud au plus faible cout
		yC = (*nodelowestCost).get_Y();
		enCours = &graphDeRecherche._graphe[xC][yC];// le noeud courant est le Noeud avec le cout le plus faible
		openList.erase(nodelowestCost);				// et on le retire des Noeuds � traiter
		closeList.push_front(*enCours);				// et on l'ajoute � la liste des Noeuds trait�s
		closeIt = closeList.begin();

		if( xC == xB && yC == yB ){					// le noeud courant est-il la cible ?
			pair<int,int> coord;						// si oui, alors on a trouv� le chemin
			int nextX,nextY;
			pathIt = pathList.begin();
			closeIt = closeList.begin();
			coord.first = (*closeIt).get_X();			// le premier Noeud de la liste des traites
			coord.second = (*closeIt).get_Y();			// est forcement la premi�re case � franchir
			pathList.push_back(coord);					// apr�s le noeud de d�part
			closeIt++;										// on parcourt tous les Noeud traite�s et on verifie
			for(; closeIt != closeList.end(); closeIt++){	// qu'il n y a pas de diagonales � faire entre deux cases
				nextX = (*closeIt).get_X();
				nextY = (*closeIt).get_Y();
				if( ( (nextX - coord.first)==0 && ((nextY - coord.second)==1 ) )
				 || ( (nextX - coord.first)==1 && ((nextY - coord.second)==0 ) )
				 ||	( (nextX - coord.first)==0 && ((nextY - coord.second)==-1) )
				 ||	( (nextX - coord.first)==-1 && ((nextY - coord.second)==0) ) ){
					coord.first = nextX ;							// si le prochain est bien voisin est sur le m�me axe
					coord.second = nextY ;
					pathList.push_front(coord);						// on l'ajoute au chemin
				}
				if( nextX == xA && nextY == yA ) closeIt == closeList.end(); // si ce prochain �tait la case d'arriv�e, on arr�te
			}
			return (pathList);								// on retourne la liste
		}
																// on a pas encore trouv� le chemin
		listeVoisin.clear();
		list<Noeud> tps = graphDeRecherche.find_Voisin(xC, yC); // on recherche les voisins du Noeud Courant
		listeVoisin.splice(voisinIt, tps);
		voisinIt = listeVoisin.begin();

		int xD,yD;
		voisinIt = listeVoisin.begin();
		for( ; voisinIt != listeVoisin.end() ; voisinIt++ ){    // pour chaque voisin du noeud Courant;
			xD = (*voisinIt).get_X();
			yD = (*voisinIt).get_Y();
			if( graphDeRecherche._graphe[xD][yD].get_costFinal() == 0){		// si il n'a jamais �t� trait�, on met � jour son co�t
				graphDeRecherche._graphe[xD][yD].set_costFromBegin( abs(xD - xA) + abs(yD - yA) ); // depuis le d�but
				graphDeRecherche._graphe[xD][yD].set_costFromEnd( abs(xD - xB) + abs(yD - yB) );   // et depuis la fin
			} else if ( graphDeRecherche._graphe[xD][yD].get_costFinal() < 0 ){
				// Ce Voisin est infranchissable
			} else {
				// Sinon il a d�j� �t� �valu�
			}
		}

	//	cout << " ** Debut du traitement de chaque voisin de courant"<< endl;
		voisinIt = listeVoisin.begin();							// Pour chaque voisin du Noeud Courant
		for( ; voisinIt != listeVoisin.end() ; voisinIt++ ){		// on le traite selon plusieurs cas
			xD = (*voisinIt).get_X();
			yD = (*voisinIt).get_Y();
			bool rep1,rep2,rep3,rep4,rep5;
			// co�t final n�gatif ?
			rep1 = (*voisinIt).get_costFinal() < 0;
			// pr�sent dans la liste des Noeuds trait�s
			rep2 = graphDeRecherche.isInTheList(closeList ,(*voisinIt));
			// co�t final du Voisin inf�rieur au noeud Courant
			rep3 = (graphDeRecherche._graphe[xD][yD].get_costFinal() <= graphDeRecherche._graphe[xC][yC].get_costFinal());
			// pr�sent dans la liste des Noeuds � traiter
			rep4 = graphDeRecherche.isInTheList(openList ,(*voisinIt));
			// co�t depuis la fin du Voisin inf�rieur au noeud Courant
			rep5 = (graphDeRecherche._graphe[xD][yD].get_costFromEnd() <= graphDeRecherche._graphe[xC][yC].get_costFromEnd());


			if( rep1 || rep2 ){ 			// si ce noeud est infranchissable ou d�ja trait�s, on ne fais rien
				//if( rep1 ) cout << "  > Oui, ce voisin est infranchissable" << endl;
				//if( rep2 ) cout << "  > Oui, ce voisin d�j� trait�" << endl;
						  // cout << "    donc voisin suivant" << endl;
			} else {						// sinon, il est donc franchissable et non trait�s
				if( rep3 || !rep4 ){		// si ce noeud a un cout <= au noeud courant et n'a pas �t� �valu�
					if( rep3 ){
						// cout << "  > ce voisin a un cout <= au noeud courant" << endl ;
						if( rep5 ){
							//cout << "  > ce voisin a un coutFromEnd <= au noeud courant" << endl ;
							xC = xD;
							yC = yD;
							enCours = &graphDeRecherche._graphe[xD][yD];
						}
					}
					if( !rep4 ){	// Ce voisin n'a pas �t� trait�
						// on l'ajoute dans la liste des noeuds � traiter
						openList.push_back(graphDeRecherche._graphe[xD][yD]);
						openIt = openList.begin();
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
	cout << " Erreur : Impossible d'acc�der � la cible " << endl;
	pair<int,int> rep;
	rep.first = -1; rep.second = -1;
	pathList.push_back(rep);
	return (pathList);
}

/** La m�thode drawPath permet de tracer un segment entre deux points A et B
  * grace � l'Algorithme de trac� de segment de Bresenham
 	 * @param xA,yA - Point de D�part
 	 * @param xB,yB - Point d'arriv�e
 	 * @return - retourne une liste de paires de coordonn�es correspondant au segment trac�
 	 * */
list <pair<int , int> > Carte::drawPath( int xA, int yA, int xB, int yB ){
	list <pair<int , int> > path;	// liste de paire de coordonn�es representant le segment trac�
	pair<int , int> coord;			// paire de coordonn�es x,y
	int dx, dy;
	// Utilisation de l'Algorithme de trac� de segment de Bresenham
	dx = xB - xA;
	if( dx != 0 ){
		if( dx > 0 ){
			dy = yB - yA;
			if( dy != 0 ){
				if( dy > 0 ){		// vecteur oblique dans le 1er quadran (x > 0 et y > 0)
					if( dx >= dy ){ // vecteur diagonal proche de l�horizontale, dans le 1er octant
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
					if(dx >= -dy){	// vecteur diagonal proche de l�horizontale, dans le 8e octant
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
							xA++;
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
					if( -dx >= dy ){ // vecteur diagonal ou oblique proche de l�horizontale, dans le 4e octant
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
					if(dx <= dy){   // vecteur diagonal ou oblique proche de l�horizontale, dans le 5e octant
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

/** La m�thode pathIsPossible permet de confirmer si le chemin entre deux points
 * A et B ne presente aucun obstacle
 	 * @param xA,yA - Point de D�part
 	 * @param xB,yB - Point d'arriv�e
 	 * @return - retourne 1 si c'est un chemin sans obstacle et
 	 * 					  0 sinon
 	 * */
bool Carte::pathIsPossible( int xA, int yA, int xB, int yB ){

	list<pair<int,int> > path = this->drawPath(xA, yA, xB, yB);

	list<pair<int,int> >::iterator it;
	it = path.begin();
	bool rep = true;
	int i = 0;
	while( (it != path.end()) && (rep == true) && (i<10000)){
		rep = (moveIsPossible( (*it).first, (*it).second , false) ) ;
		it++;
		i++;
	}
	return (rep);
}

/** La m�thode seekSpawnPoint permet de retourner les cases o� on peut placer des
  * personnages autour d'un point xA,yA.
 	 * @param xA,yA - Point de D�part
 	 * @param xB,yB - Point d'arriv�e
 	 * @param nb - nombre de personnages � placer
 	 * @return - retourne une liste de paire de coordonn�es o� on peut placer des personnages
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
	i = (xA + 1);
	j = (yA + 1);
	cout << "test: " << i << " " << j ;
	if ( (moveIsPossible(i, j, false) == 1) && (cont>0) ){
		tmp.first = i; tmp.second = j;
		rep.push_back(tmp);
		cont--;
		cout << " -> valide" << endl;
	} else cout << " -> impossible" << endl;
	i = (xA - 1) ;
	j = (yA + 1);
	cout << "test: " << i << " " << j ;
	if ( (moveIsPossible(i, j, false) == 1) && (cont>0)){
		tmp.first = i; tmp.second = j;
		rep.push_back(tmp);
		cont--;
		cout << " -> valide" << endl;
	} else cout << " -> impossible" << endl;
	i = (xA + 1);
	j = (yA - 1);
	cout << "test: " << i << " " << j ;
	if ( (moveIsPossible(i, j, false) == 1) && (cont>0)){
		tmp.first = i; tmp.second = j;
		rep.push_back(tmp);
		cont--;
		cout << " -> valide" << endl;
	} else cout << " -> impossible" << endl;
	i = (xA - 1);
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


/** La m�thode display permet d'afficher la carte sur la console */
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
