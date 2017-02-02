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
 * @file Partie.cpp
 * @brief La classe Partie permet de gérer la partie du joueur, la gestion des item, des cartes,
 * des ennemis, des heros, etc.
 */

#include "Partie.h"
#include "Fichier.h"

using namespace std;

#define ROWPLAYERBUTTOM_PXL 261	// n° de pixel sur l'axe x de la feuille de sprite pour les boutons du menu du joueur
#define ROWFIGHTBUTTOM_PXL 326	// n° de pixel sur l'axe x de la feuille de sprite pour les boutons du mode combat
#define COLUNN1_PXL   1		// n° de pixel de la colonne 1
#define COLUNN2_PXL 131		// n° de pixel de la colonne 2
#define COLUNN3_PXL 261		// n° de pixel de la colonne 3
#define COLUNN4_PXL 391		// n° de pixel de la colonne 4
#define COLUNN5_PXL 521		// n° de pixel de la colonne 5
#define COLUNN6_PXL 651		// n° de pixel de la colonne 6
#define COLUNN7_PXL 781		// n° de pixel de la colonne 7

#define ESPACE 20			// espacemment entre les boutons

static int size_window_X ;
static int size_window_Y ;
static int size_Map_part_X;
static int size_Map_part_Y;

/** Le constructeur Partie crée la partie en cours
  * */
Partie::Partie(int choix) {
	premiereApparition = true;
	if( choix == 1 ){
		newPartie();		// reinitialisation de la sauvegarde
		loadPartie();		// chargement du jeu
		Init();
	} else if( choix == 2 ){
		loadPartie();		// chargement du jeu
		Init();
	} else {
		cout << "ERREUR: choix erroné" << endl;
	}
	Init();
	cout << " + Partie construite " << endl;

}

/*** ******************************************************************************************************** ***/
/*** *********************** METHODES HERITES DE IHMstate *************************************************** ***/
/*** ******************************************************************************************************** ***/

/** La méthode Init initialise l'IHM de l'écran
  * */
void Partie::Init(){
	_mapCurrent._zoom = 1.0;
	cout << "Initialisation de la Partie " << endl;
	if (font.loadFromFile("src\\PressStart2P.ttf")){			// chargement de la police de caractère
		cout << "Init des chaines de caractères" << endl;
	} else {
		cout << "erreur de chargement de la police" << endl;
	}
	if( !i.loadFromFile("src\\sprite.png") ){					// chargement de la feuille de sprite
		cout << "feuille de sprite introuvable " << endl;
	} else {
		i.createMaskFromColor(Color::White);					// application d'un masque de transparance sur l'arrière fond
		t.loadFromImage(i);
		cout << "feuille de sprite crée " << endl;
	}
	InitHUD();				// Initialisation des éléments de l'interface utilisateur
	//InitMap();				// Initialisation des éléments de la partie Carte de l'IHM
	InitMenuQuitter();		// Initialisation du menu Quitter pour choix de quitter la partie
}

/** La méthode InitHUD initialise les éléments de l'interface utilisateur
  * */
void Partie::InitHUD(){
	textPV.setFont(font); textPV.setCharacterSize(22);
	textPA.setFont(font); textPA.setCharacterSize(22);
	textPV.setOutlineColor(Color::White);
	textPA.setOutlineColor(Color::White);

	textPV.setString(" .../... PV");
	textPA.setString(" .../... PA");

	PersoActif = RectangleShape(Vector2f(96,96));
	PersoActif.setFillColor(Color(128,128,128));

	ConteneurPVMAX = RectangleShape(Vector2f(300,40));
	ConteneurPVMAX.setOutlineColor(Color::Red);
	ConteneurPVMAX.setFillColor(Color(128,128,128,0));
	ConteneurPVMAX.setOutlineThickness(4.0);

	ConteneurPAMAX = RectangleShape(Vector2f(300,40));
	ConteneurPAMAX.setOutlineColor(Color::Green);
	ConteneurPAMAX.setFillColor(Color(128,128,128,0));
	ConteneurPAMAX.setOutlineThickness(4.0);

	ConteneurPV = RectangleShape(Vector2f(100,32));
	ConteneurPV.setOutlineColor(Color(128,128,128,0));
	ConteneurPV.setFillColor(Color::Red);
	ConteneurPV.setOutlineThickness(4.0);

	ConteneurPA = RectangleShape(Vector2f(100,32));
	ConteneurPA.setOutlineColor(Color(128,128,128,0));
	ConteneurPA.setFillColor(Color::Green);
	ConteneurPA.setOutlineThickness(4.0);

	boutonMenu[0].setTexture(t);
	boutonMenu[0].setScale(2,2);

	boutonMenu[1].setTexture(t);
	boutonMenu[1].setScale(2,2);

	boutonMenu[2].setTexture(t);
	boutonMenu[2].setScale(2,2);

	boutonMenu[3].setTexture(t);
	boutonMenu[3].setScale(2,2);

	boutonCC.setTexture(t);
	boutonCC.setScale(2,2);

	boutonTirer.setTexture(t);
	boutonTirer.setScale(2,2);

	boutonRecharger.setTexture(t);
	boutonRecharger.setScale(2,2);

	boutonGrenade.setTexture(t);
	boutonGrenade.setScale(2,2);

	boutonMedKit.setTexture(t);
	boutonMedKit.setScale(2,2);

	boutonChangerCompagnon.setTexture(t);
	boutonChangerCompagnon.setScale(2,2);

	boutonFinTour.setTexture(t);
	boutonFinTour.setScale(2,2);
}

/** La méthode InitHUD initialise les éléments de l'interface utilisateur
  * */
void Partie::InitMap(){
	//static int witdh_mapScreen
	//static int height_mapScreen

	//static RectangleShape dessinMap(Vector2f(_mapCurrent.get_sizeX()*64,_mapCurrent.get_sizeY())*64);

}

void Partie::InitMenuQuitter(){
	textMenuQuitter = Text("Voulez-vous vraiment quitter ?\nLes données non sauvegardées seront perdus",font,20);
	textOui = Text("Oui",font,20);
	textNon = Text("Non",font,20);
	menuQuitter = RectangleShape(Vector2f(textMenuQuitter.getGlobalBounds().width + ESPACE*2
										, textMenuQuitter.getGlobalBounds().height + 100));
	menuQuitter.setFillColor(unSelected);
	boutonOui = RectangleShape(Vector2f(textOui.getGlobalBounds().width + 5
									   , textOui.getGlobalBounds().height + 5));
	boutonNon = RectangleShape(Vector2f(textNon.getGlobalBounds().width + 5
									   , textNon.getGlobalBounds().height + 5));
}

void Partie::CleanUp(){
	cout << " ... Fermeture de la Partie " << endl;
}

void Partie::Pause(){

}

void Partie::Resume(){
	Init();
}

void Partie::HandleEvents(IHMmanager* game){
	Event event;
	Window *window = game->get_myWindow();
	int x,y;

	while(window->pollEvent(event)){				// dès qu'un evenement est déclenché
		switch (event.type){ 						// Selon le Type de l'évènement
			case Event::Closed : 					// si "Bouton de fermeture" activé
				cout << "Fermeture de Partie" << endl;
				game->CleanUp();
				break;
			case Event::KeyReleased : 				// "Appui sur une touche du clavier"
				switch (event.key.code){ 			// si la touche qui a été appuyée
					_ite_h=_tank_hero.begin();
					case Keyboard::Escape: 			// est "Echap"
						window->close();
						break;
					case Keyboard::Z:
						_mapCurrent.move_up((*_ite_h), _mapCurrent.get_dangerZone());
						break;
					case Keyboard::S:
						_mapCurrent.move_down((*_ite_h), _mapCurrent.get_dangerZone());
						break;
					case Keyboard::Q:
						_mapCurrent.move_left((*_ite_h), _mapCurrent.get_dangerZone());
						break;
					case Keyboard::D:
						_mapCurrent.move_right((*_ite_h), _mapCurrent.get_dangerZone());
						break;
					default:
						break;
				}
				break;
			case Event::MouseWheelScrolled : 				// "Mouvement sur la molette de la souris"
				float tps;
				tps = _mapCurrent._zoom + (0.5 * event.mouseWheelScroll.delta);
				if( (event.mouseWheelScroll.delta != 0) && tps >= 1 && tps <= 5){		// vers le bas (delta negatif)
					_mapCurrent._zoom = tps ;
				}
				break;
			case Event::MouseMoved :				// "Mouvement de la souris"
				x = event.mouseMove.x;
				y = event.mouseMove.y;
				//cout << x << " " << y << endl;
				if( boutonMenu[0].getGlobalBounds().contains(x, y) == true ){
					choix = 1;
				} else if( boutonMenu[1].getGlobalBounds().contains(x, y) == true ){
					choix = 2;
				} else if( boutonMenu[2].getGlobalBounds().contains(x, y) == true ){
					choix = 3;
				} else if( boutonMenu[3].getGlobalBounds().contains(x, y) == true ){
					choix = 4;
				} else if( boutonCC.getGlobalBounds().contains(x, y) == true ){
					choix = 5;
				} else if( boutonTirer.getGlobalBounds().contains(x, y) == true ){
					choix = 6;
				} else if( boutonRecharger.getGlobalBounds().contains(x, y) == true ){
					choix = 7;
				} else if( boutonGrenade.getGlobalBounds().contains(x, y) == true ){
					choix = 8;
				} else if( boutonMedKit.getGlobalBounds().contains(x, y) == true ){
					choix = 9;
				} else if( boutonChangerCompagnon.getGlobalBounds().contains(x, y) == true ){
					choix = 10;
				} else if( boutonFinTour.getGlobalBounds().contains(x, y) == true ){
					choix = 11;
				} else {
					choix = 0; valide = false;
				}


				if(fenetreActive == 4){
					if( boutonOui.getGlobalBounds().contains(x, y) == true ){
						choixYesNo = 1;
					} else if( boutonNon.getGlobalBounds().contains(x, y) == true ){
						choixYesNo = 2;
					} else {
						choixYesNo = 0; valide = false;
					}
				}

				break;
			case Event::MouseButtonPressed :		// "Appui sur un bouton de la souris
				switch (event.mouseButton.button){ 	// si le bouton qui a été préssée
					case Mouse::Left: 			    // est "Clic gauche"
						if( choix > 0)
						{
							valide = true;				// si la souris est sur un bouton de l'HUD
						} else if( choixYesNo > 0){
							valide = true; 				// si la souris est sur un bouton du menu quitter
						} else {						// sinon on clique dans une zone sans bouton


							float origineMapX = (game->get_myWindow()->getSize().x - ESPACE*2 - 96)/2 - (64*_mapCurrent._zoom*_mapCurrent.get_sizeX())/2;
							float origineMapY = (game->get_myWindow()->getSize().y - ESPACE*2 - 96)/2 + (64*_mapCurrent._zoom*_mapCurrent.get_sizeY())/2;
							int xcase = (event.mouseButton.x-origineMapX)/64;
							int ycase = (origineMapY-event.mouseButton.y)/64;
							//TODO deplacement

							cout << "\t\t\t\tdeplacement en "<< xcase << " " << ycase << endl;
							_ite_h=_tank_hero.begin();// ?
														//case actuelle
							int xcur = (*_ite_h).get_x();
							int ycur = (*_ite_h).get_y();
							cout << " \t\t\t\tposition actuelle "<< xcur << " " << ycur<< endl;
							cout << " \t\t\t\tdistance "<< (*_ite_h).distance(xcase, ycase)<<endl;
							if((*_ite_h).distance(xcase, ycase)<=2)
							{
								if (_mapCurrent.pathIsPossible(xcur, ycur, xcase, ycase))
								{
									cout<<"\t\t\t\tdéplacement accepté"<<endl;
									cout<<"\t\t\t\tmoove is possible retourne"<<_mapCurrent.pathIsPossible(xcur, ycur, xcase, ycase) <<"\n"<<endl;
									/*
									list <pair<int,int>> chemin=_mapCurrent.pathfinding(xcur,ycur,xcase,ycase);
									if((unsigned int)(*_ite_h).get_paCurrent()>=chemin.size())
									{
										(*_ite_h).set_x(chemin.back().first);
										(*_ite_h).set_y(chemin.back().second);
										cout << "\t\t\tdeplacement en "<< chemin.back().first << " " << chemin.back().second <<" terminé"<< endl;
									}
									*/
									(*_ite_h).set_x(xcase);
									(*_ite_h).set_y(ycase);
								}else{
									cout<<"\t\t\t\tdeplacement impossible\n"<<endl;
								}
							}
						}
						break;
					default :
						valide = false;
						break;
				}
				break;
			default :
				break;
		}
	}
}

void Partie::Update(IHMmanager* game){
	size_window_X = game->get_myWindow()->getSize().x;
	size_window_Y = game->get_myWindow()->getSize().y;
	size_Map_part_X = size_window_X - ESPACE*2 - boutonMenu[0].getGlobalBounds().width;
	size_Map_part_Y = size_window_Y - ESPACE*2 - boutonMenu[0].getGlobalBounds().height;

	UpdateMap(game);
	UpdateHUD(game);
	if(fenetreActive == 1){

	} else if(fenetreActive == 2){

	} else if(fenetreActive == 3){

	} else if(fenetreActive == 4){
		UpdateMenuQuitter(game);
	} else {
		if(premiereApparition == true){
			premiereApparition = false;
			// phase d'initialisation
			if(_mapCurrent.get_dangerZone() == false){
				// mode exploration
				cout << " Mode exploration " << endl;
				// TODO à remettre au propre
				_ite_l = _team_hero.begin();			// itérateur sur le héros principal car il est le seul à se déplacer
				_ite_l++;								// on retire les compagnons de la carte
				while( _ite_l != _team_hero.end()){
					_mapCurrent.removeItem(*(*_ite_l));
					_ite_l++;
				}
				_ite_h = _tank_hero.end();
				_ite_l = _team_hero.begin();
			} else {
				// mode combat

			}
		} else {

		}
	}
}

void Partie::UpdateHUD(IHMmanager* game){
	// mis à jour des positions des boutons de l'interface
	PersoActif.setPosition( 40 , (game->get_myWindow()->getSize().y - 40 - PersoActif.getSize().y));
	ConteneurPVMAX.setPosition( PersoActif.getGlobalBounds().left + PersoActif.getGlobalBounds().width + 40,
								PersoActif.getGlobalBounds().top + ConteneurPVMAX.getOutlineThickness());
	ConteneurPAMAX.setPosition( PersoActif.getGlobalBounds().left + PersoActif.getGlobalBounds().width + 40,
								PersoActif.getGlobalBounds().top + ConteneurPVMAX.getGlobalBounds().height + 4);

	ConteneurPV.setPosition( ConteneurPVMAX.getGlobalBounds().left + 8,
							 ConteneurPVMAX.getGlobalBounds().top + 8 );
	ConteneurPA.setPosition( ConteneurPAMAX.getGlobalBounds().left + 8,
							 ConteneurPAMAX.getGlobalBounds().top + 8 );

	textPV.setPosition(ConteneurPV.getGlobalBounds().left,
					   ConteneurPV.getGlobalBounds().top + ConteneurPV.getGlobalBounds().height/2 - textPV.getGlobalBounds().height/2 );
	textPA.setPosition(ConteneurPA.getGlobalBounds().left,
					   ConteneurPA.getGlobalBounds().top + ConteneurPA.getGlobalBounds().height/2 - textPA.getGlobalBounds().height/2 );

	boutonMenu[0].setPosition( (game->get_myWindow()->getSize().x - ESPACE - boutonMenu[0].getGlobalBounds().width),
								ESPACE );
	boutonMenu[1].setPosition( (game->get_myWindow()->getSize().x - ESPACE - boutonMenu[1].getGlobalBounds().width),
							   boutonMenu[0].getGlobalBounds().top + boutonMenu[0].getGlobalBounds().height + 10 );
	boutonMenu[2].setPosition( (game->get_myWindow()->getSize().x - ESPACE - boutonMenu[2].getGlobalBounds().width),
							   boutonMenu[1].getGlobalBounds().top + boutonMenu[1].getGlobalBounds().height + 10 );
	boutonMenu[3].setPosition( (game->get_myWindow()->getSize().x - ESPACE - boutonMenu[3].getGlobalBounds().width),
							   boutonMenu[2].getGlobalBounds().top + boutonMenu[2].getGlobalBounds().height + 10 );

	boutonFinTour.setPosition( (game->get_myWindow()->getSize().x) - ESPACE - boutonFinTour.getGlobalBounds().width ,
							   (game->get_myWindow()->getSize().y) - ESPACE - boutonFinTour.getGlobalBounds().height );
	boutonChangerCompagnon.setPosition( boutonFinTour.getGlobalBounds().left - ESPACE - boutonChangerCompagnon.getGlobalBounds().width,
										boutonFinTour.getGlobalBounds().top);
	boutonMedKit.setPosition( boutonChangerCompagnon.getGlobalBounds().left - ESPACE - boutonMedKit.getGlobalBounds().width,
							  boutonChangerCompagnon.getGlobalBounds().top);
	boutonGrenade.setPosition( boutonMedKit.getGlobalBounds().left - ESPACE - boutonGrenade.getGlobalBounds().width,
							   boutonMedKit.getGlobalBounds().top);
	boutonRecharger.setPosition( boutonGrenade.getGlobalBounds().left - ESPACE - boutonRecharger.getGlobalBounds().width,
								 boutonGrenade.getGlobalBounds().top);
	boutonTirer.setPosition( boutonRecharger.getGlobalBounds().left - ESPACE - boutonTirer.getGlobalBounds().width,
							 boutonRecharger.getGlobalBounds().top);
	boutonCC.setPosition( boutonTirer.getGlobalBounds().left - ESPACE - boutonCC.getGlobalBounds().width,
						  boutonTirer.getGlobalBounds().top);


	boutonMenu[0].setTextureRect(IntRect(COLUNN1_PXL,ROWPLAYERBUTTOM_PXL,64,64));
	boutonMenu[1].setTextureRect(IntRect(COLUNN2_PXL,ROWPLAYERBUTTOM_PXL,64,64));
	boutonMenu[2].setTextureRect(IntRect(COLUNN3_PXL,ROWPLAYERBUTTOM_PXL,64,64));
	boutonMenu[3].setTextureRect(IntRect(COLUNN4_PXL,ROWPLAYERBUTTOM_PXL,64,64));

	boutonFinTour.setTextureRect(IntRect(COLUNN7_PXL,ROWFIGHTBUTTOM_PXL,64,64));
	boutonChangerCompagnon.setTextureRect(IntRect(COLUNN6_PXL,ROWFIGHTBUTTOM_PXL,64,64));
	boutonMedKit.setTextureRect(IntRect(COLUNN5_PXL,ROWFIGHTBUTTOM_PXL,64,64));
	boutonGrenade.setTextureRect(IntRect(COLUNN4_PXL,ROWFIGHTBUTTOM_PXL,64,64));
	boutonRecharger.setTextureRect(IntRect(COLUNN3_PXL,ROWFIGHTBUTTOM_PXL,64,64));
	boutonTirer.setTextureRect(IntRect(COLUNN2_PXL,ROWFIGHTBUTTOM_PXL,64,64));
	boutonCC.setTextureRect(IntRect(COLUNN1_PXL,ROWFIGHTBUTTOM_PXL,64,64));

	switch(choix){
		case 1: boutonMenu[0].setTextureRect(IntRect(COLUNN1_PXL + 65 ,ROWPLAYERBUTTOM_PXL,64,64)); break;
		case 2: boutonMenu[1].setTextureRect(IntRect(COLUNN2_PXL + 65 ,ROWPLAYERBUTTOM_PXL,64,64)); break;
		case 3: boutonMenu[2].setTextureRect(IntRect(COLUNN3_PXL + 65 ,ROWPLAYERBUTTOM_PXL,64,64)); break;
		case 4: boutonMenu[3].setTextureRect(IntRect(COLUNN4_PXL + 65 ,ROWPLAYERBUTTOM_PXL,64,64)); break;
		case 5: boutonCC.setTextureRect(IntRect(COLUNN1_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		case 6: boutonTirer.setTextureRect(IntRect(COLUNN2_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		case 7: boutonRecharger.setTextureRect(IntRect(COLUNN3_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		case 8: boutonGrenade.setTextureRect(IntRect(COLUNN4_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		case 9: boutonMedKit.setTextureRect(IntRect(COLUNN5_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		case 10: boutonChangerCompagnon.setTextureRect(IntRect(COLUNN6_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		case 11: boutonFinTour.setTextureRect(IntRect(COLUNN7_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		default:
			break;
	}
	if(valide){											// si clic sur un bouton
		switch(choix){									// selon le bouton selectionné
			case 1:
				// TODO afficher Inventaire
				break;
			case 2:
				// TODO afficher Statistiques
				break;
			case 3:
				// TODO afficher Carte
				break;
			case 4:
				if(fenetreActive != 4) fenetreActive = 4;
				else fenetreActive = 0;
				valide = 0;
				break;
			case 5:
				// TODO afficher CC
				break;
			case 6:
				// TODO afficher Tirer
				break;
			case 7:
				// TODO afficher Recharger
				break;
			case 8:
				// TODO afficher Grenade
				break;
			case 9:
				// TODO afficher Medkit
				break;
			case 10:
				// TODO afficher Changer Compagnon
				break;
			case 11:
				// TODO afficher Fin du Tour
				break;
			default:

				break;
		}
	}
}

void Partie::UpdateMenuQuitter(IHMmanager*game){
	menuQuitter.setPosition((game->get_myWindow()->getSize().x - ESPACE*2 - 96)/2 - menuQuitter.getGlobalBounds().width/2
			  , (game->get_myWindow()->getSize().y - ESPACE*2 - 96)/2 - menuQuitter.getGlobalBounds().height/2
			  );
	textMenuQuitter.setPosition( menuQuitter.getPosition().x + 20
							   , menuQuitter.getPosition().y + 20);
	boutonOui.setPosition(menuQuitter.getGlobalBounds().left + ESPACE,
						  menuQuitter.getGlobalBounds().top + menuQuitter.getGlobalBounds().height - boutonOui.getGlobalBounds().height - ESPACE );
	boutonNon.setPosition(menuQuitter.getGlobalBounds().left + menuQuitter.getGlobalBounds().width - boutonNon.getGlobalBounds().width - ESPACE ,
						  menuQuitter.getGlobalBounds().top + menuQuitter.getGlobalBounds().height - boutonNon.getGlobalBounds().height - ESPACE );
	boutonOui.setFillColor(unSelected);
	boutonNon.setFillColor(unSelected);

	textOui.setPosition(boutonOui.getGlobalBounds().left + boutonOui.getGlobalBounds().width/2 - textOui.getGlobalBounds().width/2,
						boutonOui.getGlobalBounds().top + boutonOui.getGlobalBounds().height/2 - textOui.getGlobalBounds().height/2);
	textNon.setPosition(boutonNon.getGlobalBounds().left + boutonNon.getGlobalBounds().width/2 - textNon.getGlobalBounds().width/2,
						boutonNon.getGlobalBounds().top + boutonNon.getGlobalBounds().height/2 - textNon.getGlobalBounds().height/2);
	switch(choixYesNo){
		case 1: boutonOui.setFillColor(selected); break;
		case 2: boutonNon.setFillColor(selected); break;
		default:
			break;
	}
	if(valide){
		switch(choixYesNo){
			case 1:
				game->PopState();
				break;
			case 2:
				fenetreActive = 0;
				valide = 0;
				choixYesNo = 0;
				break;
			default:
				break;
		}
	}
}

void Partie::UpdateMap(IHMmanager* game){
	_mapCurrent.updatePosition();
	_mapCurrent._origXmap = size_Map_part_X/2 - _mapCurrent._widthMap/2;
	_mapCurrent._origYmap = size_Map_part_Y/2 + _mapCurrent._heightMap/2;

	int i,j;
	list<RectangleShape>::iterator itelistSquareMap = _mapCurrent._listSquareMap.begin();
	for(i = 0 ; i <_mapCurrent.get_sizeX() ; i++){
		for(j = 0 ; j < _mapCurrent.get_sizeY() ; j++){
			(*itelistSquareMap).setPosition(_mapCurrent._origXmap + i*64*_mapCurrent._zoom
										   ,_mapCurrent._origYmap - j*64*_mapCurrent._zoom);
			(*itelistSquareMap).setScale(_mapCurrent._zoom, _mapCurrent._zoom);
			(*itelistSquareMap).setOutlineThickness(1);
			(*itelistSquareMap).setOutlineColor(Color(Color::Cyan));
			(*itelistSquareMap).setFillColor(Color(0,0,0,0));
			itelistSquareMap++;
		}
	}
}


void Partie::Draw(IHMmanager* game){
	game->get_myWindow()->clear();

	DrawMap(game);
	DrawHUD(game);
	if(fenetreActive > 0) {
		DrawActiveFrame(game);
	}

	game->get_myWindow()->display();
}

void Partie::DrawActiveFrame(IHMmanager* game){
	if(fenetreActive == 1){

	} else if(fenetreActive == 2){

	} else if(fenetreActive == 3){

	} else if(fenetreActive == 4){
		game->get_myWindow()->draw(menuQuitter);
		game->get_myWindow()->draw(textMenuQuitter);
		game->get_myWindow()->draw(boutonOui);
		game->get_myWindow()->draw(boutonNon);
		game->get_myWindow()->draw(textOui);
		game->get_myWindow()->draw(textNon);
	}
}

void Partie::DrawHUD(IHMmanager* game){
	game->get_myWindow()->draw(PersoActif);
	game->get_myWindow()->draw(ConteneurPVMAX);
	game->get_myWindow()->draw(ConteneurPAMAX);
	game->get_myWindow()->draw(ConteneurPV);
	game->get_myWindow()->draw(ConteneurPA);
	game->get_myWindow()->draw(textPV);
	game->get_myWindow()->draw(textPA);

	game->get_myWindow()->draw(boutonFinTour) ;
	game->get_myWindow()->draw(boutonChangerCompagnon) ;
	game->get_myWindow()->draw(boutonMedKit) ;
	game->get_myWindow()->draw(boutonGrenade) ;
	game->get_myWindow()->draw(boutonRecharger) ;
	game->get_myWindow()->draw(boutonTirer) ;
	game->get_myWindow()->draw(boutonCC) ;

	for(Sprite g : boutonMenu) game->get_myWindow()->draw(g);
}

void Partie::DrawMap(IHMmanager* game){

	int i,j;
	list<RectangleShape>::iterator itelistSquareMap = _mapCurrent._listSquareMap.begin();
	for(i = 0 ; i <_mapCurrent.get_sizeX() ; i++){
		for(j = 0 ; j < _mapCurrent.get_sizeY() ; j++){
			game->get_myWindow()->draw((*itelistSquareMap));
			itelistSquareMap++;
		}
	}

	Sprite tpsSprite;
	list<Personnage*>::iterator ite_l = _team_hero.begin();

	for(ite_l = _team_hero.begin() ; ite_l != _team_hero.end() ; ite_l++){
		(*ite_l)->set_sprite(t);
		tpsSprite = (*ite_l)->get_sprite();
		tpsSprite.setScale(_mapCurrent._zoom, _mapCurrent._zoom);
		tpsSprite.setPosition(_mapCurrent._origXmap + 64*(_mapCurrent._zoom)*(*ite_l)->get_x()
							, _mapCurrent._origYmap - 64*(_mapCurrent._zoom)*(*ite_l)->get_y() );
		game->get_myWindow()->draw(tpsSprite);
	}
	list<Personnage*>::iterator ite_e = _team_ennemi.begin();
	for(ite_l = _team_ennemi.begin() ; ite_l != _team_ennemi.end() ; ite_l++){
		(*ite_l)->set_sprite(t);
		tpsSprite = (*ite_l)->get_sprite();
		tpsSprite.setScale(_mapCurrent._zoom, _mapCurrent._zoom);
		tpsSprite.setPosition(_mapCurrent._origXmap + 64*(_mapCurrent._zoom)*(*ite_l)->get_x()
							, _mapCurrent._origYmap - 64*(_mapCurrent._zoom)*(*ite_l)->get_y() );
		game->get_myWindow()->draw(tpsSprite);
	}

	/*list<Hero>::iterator ite_hero = _tank_hero.begin();
	list<Ennemi>::iterator ite_ennemi = _tank_ennemi.begin();
	while(ite_hero != _tank_hero.end()){
		(*ite_hero).set_sprite(t);
		tpsSprite = (*ite_hero).get_sprite();
		tpsSprite.setScale(_mapCurrent._zoom, _mapCurrent._zoom);
		tpsSprite.setPosition(_mapCurrent._origXmap + 64*(_mapCurrent._zoom)*(*ite_hero).get_x()
							, _mapCurrent._origYmap - 64*(_mapCurrent._zoom)*(*ite_hero).get_y() );
		game->get_myWindow()->draw(tpsSprite);
		Text t((*ite_hero).get_name(),font,12);
		t.setPosition(tpsSprite.getGlobalBounds().left, tpsSprite.getGlobalBounds().top);
		game->get_myWindow()->draw(t);
		ite_hero++;
	}
	while(ite_ennemi != _tank_ennemi.end()){
		(*ite_ennemi).set_sprite(t);
		tpsSprite = (*ite_ennemi).get_sprite();
		tpsSprite.setScale(_mapCurrent._zoom, _mapCurrent._zoom);
		tpsSprite.setPosition(_mapCurrent._origXmap - 1 + 63*_mapCurrent._zoom*(*ite_ennemi).get_x()
							,(_mapCurrent._origYmap + 1 - 64*_mapCurrent._zoom*((*ite_ennemi).get_y() + 1)) );
		game->get_myWindow()->draw(tpsSprite);
		Text t("Ennemy",font,12);
		t.setPosition(tpsSprite.getGlobalBounds().left, tpsSprite.getGlobalBounds().top);
		ite_ennemi++;
	}*/
}

/*** ******************************************************************************************************** ***/
/*** ******************************************************************************************************** ***/
/*** ******************************************************************************************************** ***/

/** La méthode newPartie permet d'initialiser le fichier contenant la sauvegarde
  * du joueur
  * */
void Partie::newPartie(void){
	Fichier pathFile("src\\Save.txt",1); 				// ouverture en lecture et ecriture de la sauvegarde
	pathFile.cleanFile();								// init de la sauvegarde
	pathFile.copyFile("src\\InitSave.txt");				// à partir du fichier de référence
}

/** La méthode loadPartie permet de charger le fichier contenant la sauvegarde
  * du joueur
  * */
void Partie::loadPartie(void){
	Fichier pathMap("src\\World.txt",0); 	// ouverture en lecture de la carte
	Fichier pathSave("src\\Save.txt",1); 	// ouverture en lecture et ecriture de la sauvegarde
	string nameCurrentMap;			// nom de la carte actuel
	pathSave.loadSave(nameCurrentMap,_tank_hero,_tank_portail_close); 		// recherche de la carte actuel dans la sauvegarde
	cout << " " << _tank_hero.size() << endl;
	pathMap.loadMap(nameCurrentMap, _mapCurrent, 	// chargement de la carte actuel
								    _tank_ennemi,	// avec la liste d'ennemi,
									_tank_hero,		// la liste d'héros,
									_tank_obstacle,	// la liste d'obstacle et
									_tank_portail);	// la liste de portails.

	cout << " " << _tank_hero.size() << endl;

	// ajout des ennemis sur la carte
	for(_ite_e = _tank_ennemi.begin();_ite_e!=_tank_ennemi.end();_ite_e++){
		_mapCurrent.addItem((*_ite_e));
	}
	_tank_hero.push_front(Hero(0,0,2,2,3,4,5,6,9,Inventaire(),"moi"));
	// ajout des héros sur la carte
	for(_ite_h = _tank_hero.begin(); _ite_h!=_tank_hero.end(); _ite_h++){
		_mapCurrent.addItem((*_ite_h));
	}

	// ajout des obstacles sur la carte
	for(_ite_o=_tank_obstacle.begin();_ite_o!=_tank_obstacle.end();_ite_o++){
		_mapCurrent.addItem((*_ite_o));
	}
	// ajout des portail sur la carte
	for(_ite_p=_tank_portail.begin();_ite_p!=_tank_portail.end();_ite_p++){
		_mapCurrent.addItem((*_ite_p));
		(*_ite_p).display();
	}
	// initialisation de la team d'ennemis sur la carte actuel
	_team_ennemi.clear();
	for(_ite_e = _tank_ennemi.begin() ; _ite_e != _tank_ennemi.end() ; _ite_e++){
		_team_ennemi.push_front( &(*_ite_e) );
	}
	// initialisation de la team de héros sur la carte actuel
	_team_hero.clear();
	for(_ite_h = _tank_hero.begin() ; _ite_h != _tank_hero.end() ; _ite_h++){
		_team_hero.push_front( &(*_ite_h) );
	}
	_ite_l = _team_hero.begin();
	cout << "fin loadPartie " << endl;
}

/** La méthode launchPartie permet de lancer le jeu en fonction de la sauvegarde
  * */
void Partie::launchPartie(void){
	bool exitGame = 0,									// boolean indiquant si on quitte le jeu
		 isDangerZone = _mapCurrent.get_dangerZone();	// boolean indiquant si on est en zone de combat ou non
	while(!exitGame){
		if( isDangerZone == true ){ 					// mode Combat
			cout << " Alerte! Ennemi en vue! " << endl;
			this->fightMode();
			//isDangerZone = false;
			cout << "gain de niveau " << endl;
		} else {										// mode Exploration
			cout << " RAS " << endl;
			this->explorationMode();
		}
		isDangerZone = _mapCurrent.get_dangerZone();
		//exitGame = true;
	}
}


// TODO URGENT AUSSI
void Partie::savePartie(void){

}

/** La méthode switchMap permet de changer de carte actuel à partir des données fourni par le
  * portail p
  	  * @param p - portail où le joueur se situe qui engendre le changement de carte*/
void Partie::switchMap( Portail p ){
	premiereApparition = true;
	_mapCurrent.removeAllItem();							// on retire tous le monde de la carte sans toucher au conteneur
	Fichier pathMap("src\\World.txt",0);							// chargement de la prochaine map
	//cout << "chargement de la map" << endl;
	pathMap.loadMap(p.get_nameNextMap(), _mapCurrent, _tank_ennemi, _tank_hero, _tank_obstacle, _tank_portail);
	//cout << "iterateur sur la map" << endl;
	/*_ite_c = _tank_carte.begin();						// itérateur sur la nouvelle carte
	while( ( _mapCurrent.get_nameMap() != p.get_nameNextMap() )
		&& ( _ite_c != _tank_carte.end()) ){
		_ite_c++;
	}*/
	_mapCurrent.display();

	// ajout des ennemis sur la carte
	for(_ite_e = _tank_ennemi.begin();_ite_e!=_tank_ennemi.end();_ite_e++){
		_mapCurrent.addItem((*_ite_e));
	}

	// ajout des obstacles sur la carte
	for(_ite_o=_tank_obstacle.begin();_ite_o!=_tank_obstacle.end();_ite_o++){
		_mapCurrent.addItem((*_ite_o));
	}
	// ajout des portail sur la carte
	for(_ite_p=_tank_portail.begin();_ite_p!=_tank_portail.end();_ite_p++){
		_mapCurrent.addItem((*_ite_p));
		(*_ite_p).display();
	}

	_mapCurrent.display();
	// recherche des points de spawn disponibles sur la carte
	//cout << "recherche des spawn pour héros sur "<< p.get_newX() << "," << p.get_newY() << endl;
	list<pair<int,int> > spawnList = _mapCurrent.seekSpawnPoint(p.get_newX(), p.get_newY(), 3);
	list<pair<int,int> >::iterator ite = spawnList.begin();
	for( ; ite != spawnList.end() ; ite++ ){
		cout << (*ite).first << "," << (*ite).second << endl;
	}

	// màj des coordonnées des héros sur la nouvelle carte
	ite = spawnList.begin();
	for(_ite_h = _tank_hero.begin();_ite_h!=_tank_hero.end();_ite_h++){
		(*_ite_h).set_x((*ite).first); (*_ite_h).set_y((*ite).second);
		ite++;
	}
	// ajout des héros sur la carte
	for(_ite_h = _tank_hero.begin();_ite_h!=_tank_hero.end();_ite_h++){
		_mapCurrent.addItem((*_ite_h));
	}
	_mapCurrent.display();
	// initialisation de la team d'ennemis sur la carte actuel
	_team_ennemi.clear();
	for(_ite_e = _tank_ennemi.begin() ; _ite_e != _tank_ennemi.end() ; _ite_e++){
		_team_ennemi.push_front( &(*_ite_e) );
	}
	// initialisation de la team de héros sur la carte actuel
	_team_hero.clear();
	for(_ite_h = _tank_hero.begin() ; _ite_h != _tank_hero.end() ; _ite_h++){
		_team_hero.push_front( &(*_ite_h) );
	}
}

/** La méthode explorationMode définit le mode exploration du jeu
  * */
void Partie::explorationMode(void){
	cout << " Mode exploration " << endl;
	int rep;
	bool endGame = 0,						// booléen indiquant si on quitte le jeu ou non
		 acrossNewMap = 0;					// booléen indiquant si on franchit une nouvelle carte ou non
	//int heroX,heroY;						// coordonnées du héro

	_ite_l = _team_hero.begin();			// itérateur sur le héros principal car il est le seul à se déplacer
	_ite_l++;								// on retire les compagnons de la carte
	while( _ite_l != _team_hero.end()){
		_mapCurrent.removeItem(*(*_ite_l));
		_ite_l++;
	}
	_ite_h = _tank_hero.end();
	_ite_l = _team_hero.begin();

	while(!acrossNewMap && !endGame){
		_mapCurrent.display();				// affichage de la carte
		rep = this->move_choice(0);			// choix du mouvement à faire
		if( rep == -1 ){					// si le joueur décide de quitter la partie
			cout << "Si vous quittez maintenant sans avoir sauvegarder la partie,";
			cout << "vous risquez de perdre votre progression. Quitter ? (Y/N)";
			string ans;
			cin >> ans;
			if(ans == "Y") endGame = true;
		} else if( rep == 2 ){									// si on franchit une nouvelle Map,
			acrossNewMap = true;
			cout << "on franchit une nouvelle map " << endl;
			_mapCurrent.display();
			cout << "recherche du portail" << endl;
			_ite_p = _tank_portail.begin();						// recherche du portail correspondant
			cout << "position du portail : " << (*_ite_p).get_x() << "," << (*_ite_p).get_y() << endl;
			cout << "position du heros : " <<   (*_ite_l)->get_x() << "," << (*_ite_l)->get_y() << endl;
			while( ( !( (*_ite_p).get_x() == (*_ite_l)->get_x() )&&( (*_ite_p).get_y() == (*_ite_l)->get_y()) )
				&& ( _ite_p != _tank_portail.end() )
			){
				_ite_p++;
			}
			cout << "position du portail : " << (*_ite_p).get_x() << "," << (*_ite_p).get_y() << endl;
			int newX = (*_ite_p).get_newX(),					// on extrait les infos de ce portail
				newY = (*_ite_p).get_newX();
			string nameNextMap = (*_ite_p).get_nameNextMap();
			cout << "ce portail pointe vers " << newX << "," << newY << "dans" << nameNextMap << endl;
			cout << "début du switch" << endl;

			switchMap((*_ite_p));
		}
	}
}

/** La méthode fightMode définit le mode combat du jeu
  * */
void Partie::fightMode(void){
	bool endFight = 0;						// booléen qui indique si c'est la fin du combat
	cout << " Mode Combat " << endl;

	while(!endFight){
		cout << "\t\t\t\t\t\t\t\tNouveau tour"<<endl;
		_ite_l = _team_hero.begin();		//_ite_l est le personnage actuel
		while(end_team(_team_hero)){		//tour des heros
			this->allieTour(endFight);
		}
		for(_ite=_team_hero.begin();_ite!=_team_hero.end();_ite++){//fin du tour: reinitialisation des PA
			(*_ite)->set_paCurrent((*_ite)->get_paMax());
		}
		_ite_l=_team_ennemi.begin();		//_ite_l est l'ennemi actuel
		while(end_team(_team_ennemi)){		//tour des ennemis
			cout<<"\t\t\t\t\t\t\t\tTour ennemi"<<endl;
			for(_ite_l=_team_ennemi.begin();_ite_l!=_team_ennemi.end();_ite_l++)
			{
				//(*_ite)->set_paCurrent(0);	//mise a 0 des PA des ennemis (passe le tour)
				list<Personnage*> in_range;	//creation de liste qui contiendra les ennemis a porte de tir
				for(_ite=_team_hero.begin();_ite!=_team_hero.end();_ite++){//TODO fonction?
					if(_mapCurrent.pathIsPossible((*_ite_l)->get_x(),(*_ite_l)->get_y(),(*_ite)->get_x(),(*_ite)->get_y())){
						in_range.push_front((*_ite));
					}
				}
				if((*_ite_l)->get_inv()->get_weapon_c()->get_munCurrent()==0 && (*_ite_l)->get_paCurrent()>4)
				{
					cout<<"je recharge"<<endl;
					(*_ite_l)->reload();
				}
				else if(((*_ite_l)->near(_team_hero)).size()!=0 && (*_ite_l)->get_paCurrent()>2)
				{
					cout<<"je tape"<<endl;
					list <Personnage*> temp = (*_ite_l)->near(_team_hero);
					(*_ite_l)->close_combat(temp);
				}
				else if(in_range.size()!=0 && (*_ite_l)->get_paCurrent()>4)
				{
					cout<<"je tire!"<<endl;
					(*_ite_l)->shoot(in_range);
				}
				else
				{
					cout<<"me deplacer"<<endl;//TODO deplacement
				}
				(*_ite_l)->set_paCurrent(0);
			}
		}
		for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++){
			(*_ite)->set_paCurrent((*_ite)->get_paMax());//fin du tour: reinitialisation des PA
		}
	}
	cout << " Combat Fini, tout le monde est mort " << endl;

	for(_ite_p=_tank_portail.begin();_ite_p!=_tank_portail.end();_ite_p++){
		(*_ite_p).display();
	}


	cout << "recherche du portail" << endl;
	_ite_p = _tank_portail.begin();						// recherche du portail correspondant
	(*_ite_p).display();
	(*_ite_p).display_info();
	cout << "position du portail : " << (*_ite_p).get_x() << "," << (*_ite_p).get_y() << endl;
	int newX = (*_ite_p).get_newX(),					// on extrait les infos de ce portail
		newY = (*_ite_p).get_newY();
	string nameNextMap = (*_ite_p).get_nameNextMap();
	cout << "ce portail pointe vers " << newX << "," << newY << "dans" << nameNextMap << endl;
	cout << "début du switch" << endl;

	switchMap((*_ite_p));
}

#define DEPLACER 1
#define TIRER 2
#define RECHARGER 3
#define CC 4
#define BONUS 5
#define CHANGER 6
/** La méthode allieTour définit le tour de l'allié et indique si c'est la fin du tour
 	 * @param &endTour - adresse du booléen qui indique si c'est la fin du tour ou pas
 	 * */
void Partie::allieTour(bool &endTour){
	int choix;
	cout<<"\t\t\t\t\t\t\t\tTour allié"<<endl;
	do{
		cout<<"\t\t\t\t\t\t\t\tPerso ("<<(*_ite_l)->get_x()<<","<<(*_ite_l)->get_y()<<")"<<endl;
		cout<<"\t\t\t\t\t\t\t\tPA restants= "<<(*_ite_l)->get_paCurrent()<<endl;
		_mapCurrent.display();								// affichage de la carte
		choix = main_switch();								// choix de l'action à faire
		switch (choix){
			case DEPLACER :
				this->move_choice(1);
				break;
			case TIRER :
				endTour = this->shoot_choice();
				break;
			case RECHARGER :
				endTour = this->reload();
				break;
			case CC :
				endTour = this->close_combat_choice();
				break;
			case BONUS :
				endTour = this->bonus_choice();
				break;
			case CHANGER :
				if( _team_hero.size() == 1 ){
					cout<<"Vous n'avez qu'un seul perso!";
				} else if( (*_ite_l) == _team_hero.back() ){
					_ite_l = _team_hero.begin();
				} else {
					_ite_l++;
				}
				break;
		}
	} while( choix != 0 );
	// reinitialisation des PA de la team Hero (force la fin du tour)
	for(_ite=_team_hero.begin();_ite!=_team_hero.end();_ite++){
		(*_ite)->set_paCurrent(0);
	}
}

/** La méthode main_switch invite le joueur à choisir une action à faire
 	 * @return elle retourne le choix saisit par le joueur
 	 * */
int Partie::main_switch ( void ){
	int reponse ;
	do {
		cout << "\nQue voulez-vous faire : \n " << DEPLACER << " - Se deplacer " << endl;
		cout << " " << TIRER  << " - Tirer " << endl;
		cout << " " << RECHARGER  << " - Recharger " << endl;
		cout << " " << CC << " - Corps à Corps " << endl;
		cout << " " << BONUS << " - Utiliser un Bonus " << endl;
		cout << " " << CHANGER << " - Changer de Personnage " << endl;
		cout << " Tapez 0 pour passer votre tour \n> ";
		cin >> reponse ;
	} while ( reponse < 0 || reponse > CHANGER ) ;
	return( reponse ) ;
}

#define NORTH 11
#define EAST 12
#define SOUTH 13
#define WEST 14
#define EXIT 10
/** La méthode move_choice gère le déplacement du héros en action dans le tour.
 	 * @param withUsePA - boolean qui indique si le mouvement consomme des PA.
 	 * @return elle retourne -1 si on annule l'action
	 * 						  0 si le déplacement est impossible
	 * 						  1 si le déplacement a fonctionné
	 * 						  2 si le déplacement engendre un changement de carte
 	 * */
int Partie::move_choice(bool withUsePA){
	int choix;
	int rep=0;//je c pas si c 0
	do{
		choix = move_switch();
		switch(choix){
		case NORTH:
			rep = _mapCurrent.move_up(*(*_ite_l), withUsePA);
			choix=10;
			break;
		case EAST:
			rep = _mapCurrent.move_right(*(*_ite_l), withUsePA);
			choix=10;
			break;
		case SOUTH:
			rep = _mapCurrent.move_down(*(*_ite_l), withUsePA);
			choix=10;
			break;
		case WEST:
			rep = _mapCurrent.move_left(*(*_ite_l), withUsePA);
			choix=10;
			break;
		case EXIT:
			rep = -1;
			break;
		}
	} while (choix != 10);
	return (rep);
}

/** La méthode move_switch invite le joueur à choisir le déplacement à faire
 	 * @return elle retourne le choix saisit par le joueur
 	 * */
int Partie::move_switch ( void ){
	int reponse ;
	do {
		cout << "\n\t\t\t\t\tOu voulez vous allez : \n\t\t\t\t\t" << NORTH << " - au Nord " << endl;
		cout << "\t\t\t\t\t" << EAST  << " - a l'Est " << endl;
		cout << "\t\t\t\t\t" << SOUTH << " - au Sud " << endl;
		cout << "\t\t\t\t\t" << WEST << " - a l'Ouest " << endl;
		cout << "\t\t\t\t\tTapez 10 pour annuler \n> ";
		cin >> reponse ;
	} while ( reponse < 10 || reponse > WEST ) ;
	return( reponse ) ;
}

/** La méthode shoot_choice gère le système de tir à distance du héros en action dans le tour.
 	 * @return elle retourne "vrai" si il n'y a plus d'ennemis et "false" sinon
 	 * */
bool Partie::shoot_choice( void ){
	if((*_ite_l)->get_paCurrent()>=4 && (*_ite_l)->get_inv()->get_weapon_c()->get_munCurrent()>0){
		list<Personnage*> in_range;	//creation de liste qui contiendra les ennemis a porte de tir
		for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++){
			if(_mapCurrent.pathIsPossible((*_ite_l)->get_x(),(*_ite_l)->get_y(),(*_ite)->get_x(),(*_ite)->get_y())){
				in_range.push_front((*_ite));
			}
		}
		(*_ite_l)->shoot(in_range);			//declanchement de l'action de tir
		list<Personnage*> temp;
		for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++){
			if((*_ite)->get_pvCurrent()>=1){ //si des ennemis sont morts, il sont supprimes de team ennemi
				temp.push_front(*_ite);
			} else {
				_mapCurrent.removeItem(*(*_ite));
			}
		}
		_team_ennemi=temp;
		if(_team_ennemi.size()==0){
			return (true);
		}
	}
	return (false);
}

bool Partie::reload()
{
	if((*_ite_l)->get_paCurrent()>=4){
		(*_ite_l)->reload();
	}
	return(false);
}

/** La méthode close_combat_choice gère le système de tir au càc du héros en action dans le tour.
 	 * @return elle retourne "vrai" si il n'y a plus d'ennemis et "false" sinon
 	 * */
bool Partie::close_combat_choice( void ){
	if((*_ite_l)->get_paCurrent()>=3){
		list<Personnage*> proch = (*_ite_l)->near(_team_ennemi); 	//proch est la liste des ennemi adjacents
		(*_ite_l)->close_combat(proch);								//declanchement de l'action cac
		list<Personnage*> temp;
		for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++){
			if((*_ite)->get_pvCurrent()>=1){						//si des ennemis sont morts, ils sont supprimes
				temp.push_front(*_ite);
			} else {
				_mapCurrent.removeItem(*(*_ite));
			}
		}
		_team_ennemi=temp;
		if(_team_ennemi.size()==0){
			return (true);
		}
	} else {
		cout<<"Pas assez de PA!"<<endl;
	}
	return (false);
}

bool Partie::bonus_choice( void ){
	int choice;
	cout<<" Taper 1 pour utiliser un medkit\n Tapez 2 pour utiliser une grenade\n Taper 0 pour quiter\n>"<<endl;
	(*_ite_l)->get_inv()->get_grenade()->add_number(1);
	cout<<(*_ite_l)->get_inv()->get_grenade()->get_number()<<" grenades et "<<(*_ite_l)->get_inv()->get_medkit()->get_uses()<<" medkit"<<endl;
	cin >> choice;
	if(choice==1)
	{
		(*_ite_l)->use_medkit();
		return (false);
	}
	else if(choice==2)
	{
		if((*_ite_l)->get_inv()->get_grenade()->get_number()>0)
		{
			int x;
			int y;
			cout<<" Entrer X puis Y\n>";		//demande au joueur ou il veux lancer la grenade
			cin >> x;
			cout<<" >";
			cin >> y;
			cout<< "\nX= "<<x<<" Y= "<<y<<endl;
			if(_mapCurrent.moveIsPossible(x,y,0)) //si il peux lancer la grenade
			{
				cout<<"possible!";
				list<Personnage*>::iterator p;
				int xcompt;
				int ycompt;
				for(xcompt=x-(*_ite_l)->get_inv()->get_grenade()->get_range();xcompt<=x+(*_ite_l)->get_inv()->get_grenade()->get_range();xcompt++)
				{
					for(ycompt=y-(*_ite_l)->get_inv()->get_grenade()->get_range();ycompt<=y+(*_ite_l)->get_inv()->get_grenade()->get_range();ycompt++)
					{
						if( !((xcompt < 0) || (xcompt >= _mapCurrent.get_sizeX()) || (ycompt < 0) || (ycompt >= _mapCurrent.get_sizeY())))
						{
							cout<<"\n\tX= "<<xcompt<<" Y= "<<ycompt<<endl;
							if(_mapCurrent.get_IDin(xcompt, ycompt)==1)
							{
								for(_ite_o=_tank_obstacle.begin();_ite_o!=_tank_obstacle.end();_ite_o++)
								{

									if(((*_ite_o).get_x()==x)||((*_ite_o).get_y()==y))
									{
										cout<<"Cet obstacle est modifié X= "<<(*_ite_o).get_x()<<" Y= "<<(*_ite_o).get_y()<<endl;
										(*_ite_o).set_destructible();//degats sur les obstacles
										(*_ite_o).display_info();
									}
								}
							}
							else if(_mapCurrent.get_IDin(xcompt, ycompt)==2)
							{
								for(p = _team_hero.begin() ; p != _team_hero.end() ; p++)
								{
									if((*p)->get_x()==x||(*p)->get_y()==y)
									{								//degats sur les heros
										cout<<"Ce hero est touché X= "<<(*p)->get_x()<<" Y= "<<(*p)->get_y()<<endl;
										(*p)->set_pvCurrent((*p)->get_pvCurrent()-(*_ite_l)->get_inv()->get_grenade()->get_dammage());
										(*p)->display_info();
									}
								}
							}
							else if(_mapCurrent.get_IDin(xcompt, ycompt)==3)
							{
								for(p = _team_ennemi.begin() ; p != _team_ennemi.end() ; p++)
								{
									if((*p)->get_x()==x||(*p)->get_y()==y)
									{								//degats sur les ennemis
										cout<<"Cet ennemis est touché X= "<<(*p)->get_x()<<" Y= "<<(*p)->get_y()<<endl;
										(*p)->set_pvCurrent((*p)->get_pvCurrent()-(*_ite_l)->get_inv()->get_grenade()->get_dammage());
										(*p)->display_info();
									}
								}
							}
						}
						else{cout<<"Pas traitéX= "<<xcompt<<" Y= "<<ycompt<<endl;}
					}
				}
				(*_ite_l)->get_inv()->get_grenade()->add_number(-1);
				if(_team_ennemi.size()==0){
					return (true);
				}
				return (false);//TODO cas suicide
			}
		}
		return (false);
	}
	else
	{
		return (false);
	}
}

/** La méthode end_team indique si la team à fini son tour
 	 * @return elle retourne "vrai" si c'est le cas et "false" sinon
 	 * */
bool Partie::end_team(list<Personnage*> team)
{
	if(team.size()==0){
		return(0);
	}
	list<Personnage*>::iterator ite;
	for(ite=team.begin();ite!=team.end();ite++){
		if((*ite)->get_paCurrent()==0){//si tout les perso de la team ont 0 PA
			return(0);
		}
	}
	return(1);
}

// le destructeur
Partie::~Partie() {
	cout << " - Partie detruite " << endl;
}

