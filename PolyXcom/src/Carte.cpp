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

	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){							// initialisation de la carte
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
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){							// initialisation de la carte
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
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){							// initialisation de la carte
		_map[i] = new Affichable*[_sizeX];
		for( j = 0 ; j < _sizeX ; j++ ){
			_map[i][j] = &vide;
			_listSquareMap.push_back(RectangleShape(Vector2f(64,64)));
		}
	}
	cout << " + carte "<< _nameMap << " de taille " << _sizeX <<"*"<< _sizeY <<" crée" << endl;
	cout << " + adresse de vide "<< &vide << endl;
}

/** La méthode updatePosition remet à jour la taille du graphe
  * */
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
			if( _map[x][y]->get_ID() == 4 && canCrossMap){		// sauf si un portail est sur la case destination,
				rep = 2;										// alors deplacement possible mais on franchit une nouvelle map
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
	if( _map[ a.get_x() ][ a.get_y() ] != &vide ) {
		cout << "!!! on écrase un affichable déjà present !!!" << endl ;
	}
	_map[ a.get_x() ][ a.get_y() ] = &a;
}

/** La méthode removeAllItem permet de retirer l'affichable en argument dans la carte
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
 	 * @param oldX,oldY - ancienne coordonnées de l'objet à déplacer
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
 	 * @param oldX,oldY - ancienne coordonnées de l'objet à déplacer
 	 * @param newX,newY - nouvelle coordonnées de l'objet à déplacer
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


/** La méthode pathfinding permet de trouver le meilleur chemin d'un point A à un point B
  * sur la carte avec l'algorithme A*. Il retourne le chemin trouvé, c'est une liste de
  * coordonnées à suivre
 	 * @param xA,yA - Point de Départ
 	 * @param xB,yB - Point d'arrivée
 	 * @return - retourne une liste de paires de coordonnées
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
	enCours = &graphDeRecherche._graphe[xA][yA];	// Le noeud Courant le case de départ du chemin à trouver
	int xC = enCours->get_X(),						// Definition des Coordonnées du Noeud Courant
		yC = enCours->get_Y();
													// initialisation des listes de Noeuds
	list <Noeud> openList;							// Liste contenant les noeuds à traiter
	list <Noeud> closeList;							// Liste contenant les noeuds déjà traités
	list <Noeud> listeVoisin;						// Liste contenant les voisins du noeud courant
	list <pair<int , int> > pathList;				// Liste contenant le veritable chemin
																	// définition des itérateurs
	list<Noeud>::iterator openIt = openList.begin();				// il pointe tous au début de leur liste respective
	list<Noeud>::iterator closeIt = closeList.begin();
	list<Noeud>::iterator voisinIt = listeVoisin.begin();
	list <pair<int , int> >::iterator pathIt = pathList.begin();
	list<Noeud>::iterator nodelowestCost;			// Noeud contenant le noeud ayant le cout le plus faible

	//cout << "*** DEBUT DE L'ALGORITHME A* ***" << endl;

	openList.push_back(*enCours);					// on ajoute le noeud de départ dans la liste des Noeuds à traiter
	openIt = openList.begin();

	while( !openList.empty() ){					// Tant qu'il y a toujours des noeuds à traiter
		openIt = openList.begin();				// Au debut, on recherche dans la liste des noeuds à traiter,
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
		xC = (*nodelowestCost).get_X();				// on ressort avec les coordonnées du Noeud au plus faible cout
		yC = (*nodelowestCost).get_Y();
		enCours = &graphDeRecherche._graphe[xC][yC];// le noeud courant est le Noeud avec le cout le plus faible
		openList.erase(nodelowestCost);				// et on le retire des Noeuds à traiter
		closeList.push_front(*enCours);				// et on l'ajoute à la liste des Noeuds traités
		closeIt = closeList.begin();

		if( xC == xB && yC == yB ){					// le noeud courant est-il la cible ?
			pair<int,int> coord;						// si oui, alors on a trouvé le chemin
			int nextX,nextY;
			pathIt = pathList.begin();
			closeIt = closeList.begin();
			coord.first = (*closeIt).get_X();			// le premier Noeud de la liste des traites
			coord.second = (*closeIt).get_Y();			// est forcement la première case à franchir
			pathList.push_back(coord);					// après le noeud de départ
			closeIt++;										// on parcourt tous les Noeud traiteés et on verifie
			for(; closeIt != closeList.end(); closeIt++){	// qu'il n y a pas de diagonales à faire entre deux cases
				nextX = (*closeIt).get_X();
				nextY = (*closeIt).get_Y();
				if( ( (nextX - coord.first)==0 && ((nextY - coord.second)==1 ) )
				 || ( (nextX - coord.first)==1 && ((nextY - coord.second)==0 ) )
				 ||	( (nextX - coord.first)==0 && ((nextY - coord.second)==-1) )
				 ||	( (nextX - coord.first)==-1 && ((nextY - coord.second)==0) ) ){
					coord.first = nextX ;							// si le prochain est bien voisin est sur le même axe
					coord.second = nextY ;
					pathList.push_front(coord);						// on l'ajoute au chemin
				}
				if( nextX == xA && nextY == yA ) closeIt == closeList.end(); // si ce prochain était la case d'arrivée, on arrête
			}
			return (pathList);								// on retourne la liste
		}
																// on a pas encore trouvé le chemin
		listeVoisin.clear();
		list<Noeud> tps = graphDeRecherche.find_Voisin(xC, yC); // on recherche les voisins du Noeud Courant
		listeVoisin.splice(voisinIt, tps);
		voisinIt = listeVoisin.begin();

		int xD,yD;
		voisinIt = listeVoisin.begin();
		for( ; voisinIt != listeVoisin.end() ; voisinIt++ ){    // pour chaque voisin du noeud Courant;
			xD = (*voisinIt).get_X();
			yD = (*voisinIt).get_Y();
			if( graphDeRecherche._graphe[xD][yD].get_costFinal() == 0){		// si il n'a jamais été traité, on met à jour son coût
				graphDeRecherche._graphe[xD][yD].set_costFromBegin( abs(xD - xA) + abs(yD - yA) ); // depuis le début
				graphDeRecherche._graphe[xD][yD].set_costFromEnd( abs(xD - xB) + abs(yD - yB) );   // et depuis la fin
			} else if ( graphDeRecherche._graphe[xD][yD].get_costFinal() < 0 ){
				// Ce Voisin est infranchissable
			} else {
				// Sinon il a déjà été évalué
			}
		}

	//	cout << " ** Debut du traitement de chaque voisin de courant"<< endl;
		voisinIt = listeVoisin.begin();							// Pour chaque voisin du Noeud Courant
		for( ; voisinIt != listeVoisin.end() ; voisinIt++ ){		// on le traite selon plusieurs cas
			xD = (*voisinIt).get_X();
			yD = (*voisinIt).get_Y();
			bool rep1,rep2,rep3,rep4,rep5;
			// coût final négatif ?
			rep1 = (*voisinIt).get_costFinal() < 0;
			// présent dans la liste des Noeuds traités
			rep2 = graphDeRecherche.isInTheList(closeList ,(*voisinIt));
			// coût final du Voisin inférieur au noeud Courant
			rep3 = (graphDeRecherche._graphe[xD][yD].get_costFinal() <= graphDeRecherche._graphe[xC][yC].get_costFinal());
			// présent dans la liste des Noeuds à traiter
			rep4 = graphDeRecherche.isInTheList(openList ,(*voisinIt));
			// coût depuis la fin du Voisin inférieur au noeud Courant
			rep5 = (graphDeRecherche._graphe[xD][yD].get_costFromEnd() <= graphDeRecherche._graphe[xC][yC].get_costFromEnd());


			if( rep1 || rep2 ){ 			// si ce noeud est infranchissable ou déja traités, on ne fais rien
				//if( rep1 ) cout << "  > Oui, ce voisin est infranchissable" << endl;
				//if( rep2 ) cout << "  > Oui, ce voisin déjà traité" << endl;
						  // cout << "    donc voisin suivant" << endl;
			} else {						// sinon, il est donc franchissable et non traités
				if( rep3 || !rep4 ){		// si ce noeud a un cout <= au noeud courant et n'a pas été évalué
					if( rep3 ){
						// cout << "  > ce voisin a un cout <= au noeud courant" << endl ;
						if( rep5 ){
							//cout << "  > ce voisin a un coutFromEnd <= au noeud courant" << endl ;
							xC = xD;
							yC = yD;
							enCours = &graphDeRecherche._graphe[xD][yD];
						}
					}
					if( !rep4 ){	// Ce voisin n'a pas été traité
						// on l'ajoute dans la liste des noeuds à traiter
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
	cout << " Erreur : Impossible d'accéder à la cible " << endl;
	pair<int,int> rep;
	rep.first = -1; rep.second = -1;
	pathList.push_back(rep);
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
	int i = 0;
	while( (it != path.end()) && (rep == true) && (i<10000)){
		rep = (moveIsPossible( (*it).first, (*it).second , false) ) ;
		it++;
		i++;
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
