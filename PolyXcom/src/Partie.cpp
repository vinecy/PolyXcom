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
#include <windows.h>
#include <cstdlib>
#include <sstream>
#include <string>

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
#define PXL_PV 25			// taille d'un point de PV/PA en pxl dans la barre de PV/PA

static int size_window_X ;
static int size_window_Y ;
static int size_Map_part_X;
static int size_Map_part_Y;

static RectangleShape PersoActif;				// Element de l'HUD
static Text namePersoActif;
static RectangleShape WeaponActif;
static Text textAmmunation;
static RectangleShape ConteneurPVMAX;
static RectangleShape ConteneurPV;
static Text textPV;
static RectangleShape ConteneurPAMAX;
static RectangleShape ConteneurPA;
static Text textPA;
static Sprite boutonMenu[4];
static Sprite boutonCC;
static Sprite boutonTirer;
static Sprite boutonRecharger;
static Sprite boutonGrenade;
static Sprite boutonMedKit;
static Sprite boutonChangerCompagnon;
static Sprite boutonFinTour;

static Image i;								// Image contenant le sprite
static Texture t;								// Texture contenant la feuille de sprite
static Font font;								// Police de caractère

static RectangleShape menuQuitter;				// Element du menu Quitter
static RectangleShape boutonOui;
static RectangleShape boutonNon;
static Text textMenuQuitter;
static Text textOui;
static Text textNon;

static const int nbRectStats = 11;					// Element du menu Stats
static const int nbtextStats = 16;
static RectangleShape rectStats[nbRectStats*3];
static Text textStats[nbtextStats*3];
static Sprite spritePersoActuel[3];

					// Element du menu Carte

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


	InitMenuStats();
	InitMenuQuitter();		// Initialisation du menu Quitter pour choix de quitter la partie
}

/** La méthode InitHUD initialise les éléments de l'interface utilisateur
  * */
void Partie::InitHUD(){
	textPV = Text(" .../... PV",font,22); textPV.setOutlineColor(Color::White);
	textPA = Text(" .../... PV",font,22); textPA.setOutlineColor(Color::White);
	namePersoActif = Text((*_ite_l)->get_name(),font,18);

	PersoActif = RectangleShape(Vector2f(128,128));
	PersoActif.setFillColor(Color(unSelected));
	WeaponActif = RectangleShape(Vector2f(200,128));
	WeaponActif.setFillColor(Color(unSelected));
	textAmmunation = Text(" .../... PV",font,22); textAmmunation.setOutlineColor(Color::White);

	ConteneurPVMAX = RectangleShape(Vector2f(300,40));
	ConteneurPVMAX.setOutlineColor(Color::Red);
	ConteneurPVMAX.setFillColor(Color(128,128,128,0));
	ConteneurPVMAX.setOutlineThickness(4.0);

	ConteneurPAMAX = RectangleShape(Vector2f(300,40));
	ConteneurPAMAX.setOutlineColor(Color(81,160,33));
	ConteneurPAMAX.setFillColor(Color(128,128,128,0));
	ConteneurPAMAX.setOutlineThickness(4.0);

	ConteneurPV = RectangleShape(Vector2f(100,32));
	ConteneurPV.setOutlineColor(Color(128,128,128,0));
	ConteneurPV.setFillColor(Color::Red);
	ConteneurPV.setOutlineThickness(4.0);

	ConteneurPA = RectangleShape(Vector2f(100,32));
	ConteneurPA.setOutlineColor(Color(128,128,128,0));
	ConteneurPA.setFillColor(Color(81,160,33));
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

void Partie::InitMenuStats(){
	// Init Fenetre Stats
	rectStats[0].setFillColor(unSelected);

	for(int j = 0 ; j <3 ; j++){
		// Nom du Personnage
		textStats[j*nbtextStats] = Text("none",font,20);
		textStats[j*nbtextStats].setFillColor(Color::White);

		// Representation des Stats
		for(int i = 1 ; i <= 5 ; i++){
			rectStats[j*nbRectStats + i] = RectangleShape(Vector2f(150,PXL_PV));
			rectStats[j*nbRectStats + i].setFillColor(Color(0,100,255));
			textStats[j*nbtextStats + i] = Text("...",font,20);
			textStats[j*nbtextStats + i+5] = Text("...",font,20);
		}
		rectStats[j*nbRectStats + 6] = RectangleShape(Vector2f( 5*(rectStats[1].getSize().x) + ESPACE*5 + 20,
												1));
		rectStats[j*nbRectStats + 7] = RectangleShape(Vector2f( 1, PXL_PV*5 + 20 + 20 ));
		rectStats[j*nbRectStats + 6].setFillColor(Color::White);
		rectStats[j*nbRectStats + 7].setFillColor(Color::White);
	}
}

void Partie::InitMenuCarte(){
	// Init Fenetre Stats


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
					case Keyboard::Escape: 			// est "Echap"
						window->close();
						break;

					case Keyboard::Z:
						if(_mapCurrent.get_dangerZone()==false)
						{
							if((*_ite_h).get_y()!=_mapCurrent.get_sizeY()-1)
							{
								if(_mapCurrent.get_IDin((*_ite_h).get_x(), (*_ite_h).get_y()+1)==0)
								{
									_mapCurrent.move_up((*_ite_h), _mapCurrent.get_dangerZone());
								}else if (_mapCurrent.get_IDin((*_ite_h).get_x(), (*_ite_h).get_y()+1)==4 && _mapCurrent.get_dangerZone()==0)
								{
									list<Portail> ::iterator tmp;
									for(tmp=_tank_portail.begin();tmp!=_tank_portail.end();tmp++)
									{
										if( (*tmp).get_x()==(*_ite_h).get_x() &&(*tmp).get_y()==(*_ite_h).get_y()+1)
										{
											_ite_p= tmp;
										}
									}
									switchMap((*_ite_p));
								}
							}
						}
						else
						{
							if((*_ite_l)->get_y()!=_mapCurrent.get_sizeY()-1 && ((*_ite_l)->get_paCurrent()>0))
							{
								if(_mapCurrent.get_IDin((*_ite_l)->get_x(), (*_ite_l)->get_y()+1)==0)
								{
									_mapCurrent.move_up(*(*_ite_l), _mapCurrent.get_dangerZone());
								}
							}
						}
						break;

					case Keyboard::S:
						if(_mapCurrent.get_dangerZone()==false)
						{
							if((*_ite_h).get_y()!=0)
							{
								if(_mapCurrent.get_IDin((*_ite_h).get_x(), (*_ite_h).get_y()-1)==0)
								{
									_mapCurrent.move_down((*_ite_h), _mapCurrent.get_dangerZone());
								}else if (_mapCurrent.get_IDin((*_ite_h).get_x(), (*_ite_h).get_y()-1)==4 && _mapCurrent.get_dangerZone()==0)
								{
									list<Portail> ::iterator tmp;
									for(tmp=_tank_portail.begin();tmp!=_tank_portail.end();tmp++)
									{
										if( (*tmp).get_x()==(*_ite_h).get_x() &&(*tmp).get_y()==(*_ite_h).get_y()-1)
										{
											_ite_p= tmp;
										}
									}
									switchMap((*_ite_p));
								}
							}
						}
						else
						{
							if((*_ite_l)->get_y()!=0 && ((*_ite_l)->get_paCurrent()>0))
							{
								if(_mapCurrent.get_IDin((*_ite_l)->get_x(), (*_ite_l)->get_y()-1)==0)
								{
									_mapCurrent.move_down(*(*_ite_l), _mapCurrent.get_dangerZone());
								}
							}
						}
						break;

					case Keyboard::Q:
						if(_mapCurrent.get_dangerZone()==false)
						{
							if((*_ite_h).get_x()!=0)
							{
								if(_mapCurrent.get_IDin((*_ite_h).get_x()-1, (*_ite_h).get_y())==0)
								{
									_mapCurrent.move_left((*_ite_h), _mapCurrent.get_dangerZone());
								}else if (_mapCurrent.get_IDin((*_ite_h).get_x()-1, (*_ite_h).get_y())==4 && _mapCurrent.get_dangerZone()==0)
								{
									list<Portail> ::iterator tmp;
									for(tmp=_tank_portail.begin();tmp!=_tank_portail.end();tmp++)
									{
										if( (*tmp).get_x()==(*_ite_h).get_x()-1 &&(*tmp).get_y()==(*_ite_h).get_y())
										{
											_ite_p= tmp;
										}
									}
									switchMap((*_ite_p));
								}
							}
						}
						else
						{
							if((*_ite_l)->get_x()!=0 && ((*_ite_l)->get_paCurrent()>0))
							{
								if(_mapCurrent.get_IDin((*_ite_l)->get_x()-1, (*_ite_l)->get_y())==0)
								{
									_mapCurrent.move_left(*(*_ite_l), _mapCurrent.get_dangerZone());
								}
							}
						}
						break;

					case Keyboard::D:
						if(_mapCurrent.get_dangerZone()==false)
						{
							if((*_ite_h).get_x()!=_mapCurrent.get_sizeX()-1)
							{
								if(_mapCurrent.get_IDin((*_ite_h).get_x()+1, (*_ite_h).get_y())==0)
								{
									_mapCurrent.move_right((*_ite_h), _mapCurrent.get_dangerZone());
								}else if (_mapCurrent.get_IDin((*_ite_h).get_x()+1, (*_ite_h).get_y())==4 && _mapCurrent.get_dangerZone()==0)
								{
									list<Portail> ::iterator tmp;
									for(tmp=_tank_portail.begin();tmp!=_tank_portail.end();tmp++)
									{
										if( (*tmp).get_x()==(*_ite_h).get_x()+1 &&(*tmp).get_y()==(*_ite_h).get_y())
										{
											_ite_p= tmp;
										}
									}
									switchMap((*_ite_p));
								}
							}
						}
						else
						{
							if((*_ite_l)->get_x()!=_mapCurrent.get_sizeX()-1 && ((*_ite_l)->get_paCurrent()>0))
							{
								if(_mapCurrent.get_IDin((*_ite_l)->get_x()+1, (*_ite_l)->get_y())==0)
								{
									_mapCurrent.move_right(*(*_ite_l), _mapCurrent.get_dangerZone());
								}
							}
						}
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
							int xcase = ((event.mouseButton.x-_mapCurrent._origXmap)/64)/_mapCurrent._zoom;
							int ycase = ((_mapCurrent._origYmap-event.mouseButton.y)/64)/_mapCurrent._zoom;
							cout << "\t\t\t\tdeplacement en "<< xcase << " " << ycase << endl;
							int xcur, ycur;
							if( _mapCurrent.get_dangerZone()==false)
							{
								xcur = (*_ite_h).get_x();
								ycur = (*_ite_h).get_y();
							}
							else
							{
								xcur = (*_ite_l)->get_x();
								ycur = (*_ite_l)->get_y();
							}
							cout << " \t\t\t\tposition actuelle "<< xcur << " " << ycur<< endl;
							//cout << " \t\t\t\tdistance "<< (*_ite_h).distance(xcase, ycase)<<endl;
							if(STATE_CC==false)
							{
								if(STATE_TIR==false)
								{
									if(xcase>=0 && ycase>=0 && xcase<_mapCurrent.get_sizeX() && ycase<_mapCurrent.get_sizeY())
									{//Cas déplacement hors combat
										list <pair<int,int>> chemin=_mapCurrent.pathfinding(xcur,ycur,xcase,ycase);
										if (chemin.back().first!=-1)
										{
											if( _mapCurrent.get_dangerZone()==false)
											{
												if(_mapCurrent.get_IDin(chemin.back().first, chemin.back().second)==0)
												{
													_mapCurrent.moveItemTo(xcur, ycur, chemin.back().first, chemin.back().second);
												}
												else if(_mapCurrent.get_IDin(chemin.back().first, chemin.back().second)==4 && _mapCurrent.get_dangerZone()==false)
												{
													list<Portail> ::iterator tmp;
													for(tmp=_tank_portail.begin();tmp!=_tank_portail.end();tmp++)
													{
														if( (*tmp).get_x()==chemin.back().first &&(*tmp).get_y()==chemin.back().second)
														{
															_ite_p= tmp;
														}
													}
													switchMap((*_ite_p));
												}
											}
											else
											{//cas deplacement en combat
												int distance =(*_ite_l)->distance(chemin.back().first, chemin.back().second);
												if(_mapCurrent.get_IDin(chemin.back().first, chemin.back().second)==0
														&& distance <= (*_ite_l)->get_paCurrent())
												{
													_mapCurrent.moveItemTo(xcur, ycur, chemin.back().first, chemin.back().second);
													(*_ite_l)->set_paCurrent((*_ite_l)->get_paCurrent()-distance);
													//(*_ite_l)->display_info();
												}
											}
										}
									}
								}
								else
								{//cas tir
									if((_mapCurrent.get_IDin(xcase,ycase)==3) && (_mapCurrent.pathIsPossible(xcur, ycur, xcase, ycase)))
									{
										for(list<Ennemi*>::iterator _itmp=_team_ennemi.begin(); _itmp!=_team_ennemi.end();_itmp++)
										{
											if((*_itmp)->get_x()==xcase && (*_itmp)->get_y()==ycase)
											{
												_ite_ee=_itmp;
											}
										}
										if((*_ite_ee)->get_x()==xcase && (*_ite_ee)->get_y()==ycase)
										{
											int alea = rand()%10;
											if(alea<=(*_ite_l)->get_luck())
											{
												cout <<"CRITIQUE !!"<< (*_ite_l)->get_luck()<< " / "<< alea<<endl;
											}
											else
											{
												cout <<"non crit"<< (*_ite_l)->get_luck()<< " / "<< alea<<endl;
											}
											(*_ite_ee)->set_pvCurrent(
													(*_ite_ee)->get_pvCurrent()-
													( ((*_ite_l)->get_inv()->get_weapon_c()->get_degats()) *
															( (alea<=((*_ite_l)->get_accuracy()+5)) * (1+(alea<=(*_ite_l)->get_luck())) ) ));

											if((*_ite_ee)->get_pvCurrent()<0)
											{
												(*_ite_ee)->set_pvCurrent(0);
											}
											(*_ite_l)->set_paCurrent((*_ite_l)->get_paCurrent()-4);
											(*_ite_l)->get_inv()->get_weapon_c()->set_munCurrent(
													(*_ite_l)->get_inv()->get_weapon_c()->get_munCurrent()-1);
											STATE_TIR=false;
										}
									}
								}
							}
							else
							{// cas cc
								if((_mapCurrent.get_IDin(xcase,ycase)==3) && ((*_ite_l)->distance(xcase, ycase)==1))
								{
									for(list<Ennemi*>::iterator _itmp=_team_ennemi.begin(); _itmp!=_team_ennemi.end();_itmp++)
									{
										if((*_itmp)->get_x()==xcase && (*_itmp)->get_y()==ycase)
										{
											_ite_ee=_itmp;
										}
									}
									if((*_ite_ee)->get_x()==xcase && (*_ite_ee)->get_y()==ycase)
									{
										int crit = rand()%10;
										if(crit<=(*_ite_l)->get_luck())
										{
											cout << (*_ite_l)->get_luck()<< " / "<< crit<<endl;
											cout<< "CRITIQUE !!\n";
										}
										(*_ite_ee)->set_pvCurrent((*_ite_ee)->get_pvCurrent()-(*_ite_l)->get_str()*(1+(crit<=(*_ite_l)->get_luck())));
										if((*_ite_ee)->get_pvCurrent()<0)
										{
											(*_ite_ee)->set_pvCurrent(0);
										}
										(*_ite_l)->set_paCurrent((*_ite_l)->get_paCurrent()-3);
										STATE_CC=false;
									}
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
		UpdateMenuStats(game);
	} else if(fenetreActive == 4){
		UpdateMenuQuitter(game);
	} else {
		if(premiereApparition == true){
			premiereApparition = false;
			// phase d'initialisation
			if(_mapCurrent.get_dangerZone() == false){
				// mode exploration
				cout << " Mode exploration " << endl;
				_ite_h = _tank_hero.begin();
			} else {
				// mode combat
				cout << " Mode combat " << endl;
				STATE_CC=false;
				STATE_TIR=false;
			}
		} else {

		}
	}
}

void Partie::UpdateHUD(IHMmanager* game){
	// mis à jour des positions des boutons de l'interface
	PersoActif.setPosition( ESPACE , (game->get_myWindow()->getSize().y - ESPACE - PersoActif.getSize().y));
	namePersoActif.setString((*_ite_l)->get_name());
	namePersoActif.setPosition( PersoActif.getGlobalBounds().left + PersoActif.getGlobalBounds().width/2 - namePersoActif.getGlobalBounds().width/2 + 12
			, PersoActif.getGlobalBounds().top - 10 - namePersoActif.getGlobalBounds().height );

	ConteneurPVMAX.setSize(Vector2f( (*_ite_l)->get_pvMax() * PXL_PV  ,50));
	ConteneurPVMAX.setPosition( PersoActif.getGlobalBounds().left + PersoActif.getGlobalBounds().width + 40,
			PersoActif.getGlobalBounds().top + ConteneurPVMAX.getOutlineThickness());
	ConteneurPAMAX.setSize(Vector2f( (*_ite_l)->get_paMax() * PXL_PV  ,50));
	ConteneurPAMAX.setPosition( PersoActif.getGlobalBounds().left + PersoActif.getGlobalBounds().width + 40,
			PersoActif.getGlobalBounds().top + PersoActif.getGlobalBounds().height - ConteneurPAMAX.getGlobalBounds().height + ConteneurPAMAX.getOutlineThickness());

	ConteneurPV.setSize(Vector2f( ((*_ite_l)->get_pvCurrent() * PXL_PV - 8) ,42));
	ConteneurPA.setSize(Vector2f( ((*_ite_l)->get_paCurrent() * PXL_PV - 8) ,42));
	stringstream ss[6];
	ss[0] << (*_ite_l)->get_pvCurrent();
	ss[1] << (*_ite_l)->get_pvMax();
	ss[2] << (*_ite_l)->get_paCurrent();
	ss[3] << (*_ite_l)->get_paMax();
	ss[4] << (*_ite_l)->get_inv()->get_weapon_c()->get_munCurrent();
	ss[5] << (*_ite_l)->get_inv()->get_weapon_c()->get_munMax();
	textPV.setString( ss[0].str() + "/" + ss[1].str() + " PV");
	textPA.setString( ss[2].str() + "/" + ss[3].str() + " PA");
	textAmmunation.setString( ss[4].str() + "/" + ss[5].str() + " mun");


	ConteneurPV.setPosition( ConteneurPVMAX.getGlobalBounds().left + 8,
			ConteneurPVMAX.getGlobalBounds().top + 8 );
	ConteneurPA.setPosition( ConteneurPAMAX.getGlobalBounds().left + 8,
			ConteneurPAMAX.getGlobalBounds().top + 8 );

	textPV.setPosition(ConteneurPV.getGlobalBounds().left + 10,
			ConteneurPV.getGlobalBounds().top + ConteneurPV.getGlobalBounds().height/2 - textPV.getGlobalBounds().height/2 );
	textPA.setPosition(ConteneurPA.getGlobalBounds().left + 10,
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
	WeaponActif.setPosition( boutonCC.getGlobalBounds().left - ESPACE - WeaponActif.getGlobalBounds().width,
							  boutonCC.getGlobalBounds().top);
	textAmmunation.setPosition( WeaponActif.getGlobalBounds().left + WeaponActif.getGlobalBounds().width - ESPACE - textAmmunation.getGlobalBounds().width,
								WeaponActif.getGlobalBounds().top + WeaponActif.getGlobalBounds().height - textAmmunation.getGlobalBounds().height - ESPACE);


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
		case 1://inv
		if(fenetreActive != 1) fenetreActive = 1;
		else fenetreActive = 0;
		valide = 0;
		break;
		case 2://carte
			if(fenetreActive != 2) fenetreActive = 2;
			else fenetreActive = 0;
			valide = 0;
			break;
		case 3://stat
			if(fenetreActive != 3) fenetreActive = 3;
			else fenetreActive = 0;
			valide = 0;
			break;
		case 4://quitter
			if(fenetreActive != 4) fenetreActive = 4;
			else fenetreActive = 0;
			valide = 0;
			break;
		case 5:
			//  afficher CC
			if ( _mapCurrent.get_dangerZone()==true)
			{
				if(( STATE_CC==false) && (*_ite_l)->get_paCurrent()>=3)
				{
					STATE_CC=true;
					cout << " THIS IS OOOON!"<< endl;
				}
				else
				{
					STATE_CC=false;
					cout << " Ok..."<< endl;
				}
			}
			Sleep(500);
			break;
		case 6:
			//afficher Tirer
			if ( _mapCurrent.get_dangerZone()==true)
			{
				if(( STATE_TIR==false) && ((*_ite_l)->get_paCurrent()>=4))
				{
					STATE_TIR=true;
					cout <<" Locked and loaded !"<<endl;
				}
				else
				{
					STATE_TIR=false;
					cout << "Peace man!"<< endl;
				}
			}
			Sleep(500);
			break;
		case 7:
			// afficher Recharger
			if(	_mapCurrent.get_dangerZone()==true &&(*_ite_l)->get_paCurrent()>=2)
			{
				(*_ite_l)->get_inv()->get_weapon_c()->set_munCurrent(
						(*_ite_l)->get_inv()->get_weapon_c()->get_munMax());
			}
			Sleep(500);
			break;
		case 8:
			// TODO afficher Grenade
			break;
		case 9:
			// afficher Medkit
			if(	_mapCurrent.get_dangerZone()==true &&
					(*_ite_l)->get_inv()->get_medkit()->get_uses()>=1 &&
					(*_ite_l)->get_paCurrent()>=2)
			{
				(*_ite_l)->set_pvCurrent((*_ite_l)->get_pvCurrent()+2);
				if ((*_ite_l)->get_pvCurrent()>(*_ite_l)->get_pvMax())
				{
					(*_ite_l)->set_pvCurrent((*_ite_l)->get_pvMax());
				}
				(*_ite_l)->set_paCurrent((*_ite_l)->get_paCurrent()-2);
				(*_ite_l)->get_inv()->get_medkit()->add_uses(-1);
			}
			Sleep(500);
			break;
		case 10:
			//  afficher Changer Compagnon
			cout << "actuellement avec ";
			(*_ite_l)->display_info();
			if(_mapCurrent.get_dangerZone()==true)
			{
				if(	*(_ite_l)==_team_hero.back())
				{
					_ite_l=_team_hero.begin();
				}
				else
				{
					_ite_l++;
				}
			}
			cout << "\n maintenant avec ";
			(*_ite_l)->display_info();
			STATE_CC=false;
			STATE_TIR=false;
			Sleep(500);
			break;
		case 11:
		{
			// afficher Fin du Tour
			STATE_CC=false;
			STATE_TIR=false;

			list<Hero*> temph;
			list<Ennemi*> tempe;

			for (_ite_l=_team_hero.begin();_ite_l!=_team_hero.end();_ite_l++)
			{
				(*_ite_l)->set_paCurrent(0);
				if((*_ite_l)->get_pvCurrent()>0)
				{
					temph.push_front(*_ite_l);
				}
			}
			for (_ite_ee=_team_ennemi.begin(); _ite_ee!=_team_ennemi.end();_ite_ee++)
			{
				if((*_ite_ee)->get_pvCurrent()>0)
				{
					tempe.push_front(*_ite_ee);
				}
			}
			_team_ennemi=tempe;
			_team_hero=temph;
			if(_team_ennemi.size()==0)
			{
				cout << "WIIIIIIIIIIIIIIIIIIIIIIIn\n";
				//todo fermer portail
				switchMap(_tank_portail.front());
			}
			for (_ite_ee=_team_ennemi.begin(); _ite_ee!=_team_ennemi.end();_ite_ee++)
			{
				if((*_ite_ee)->get_inv()->get_weapon_c()->get_munCurrent()==0 && (*_ite_ee)->get_paCurrent()>=2)
				{
					(*_ite_ee)->get_inv()->get_weapon_c()->set_munCurrent(
							(*_ite_ee)->get_inv()->get_weapon_c()->get_munMax());
				}
				int cible=rand()%10;
				list<Hero*>::iterator tmp= _team_hero.begin();
				while(cible==0)
				{
					if(tmp==_team_hero.end())
					{
						tmp= _team_hero.begin();
					}
					tmp++;
					cible--;
				}
				if( ((*_ite_ee)->get_paCurrent()>=4)&&((*_ite_ee)->get_inv()->get_weapon_c()->get_munCurrent()>=1)
						&& (_mapCurrent.pathIsPossible((*_ite_ee)->get_x(), (*_ite_ee)->get_y(),
								(*tmp)->get_x(), (*tmp)->get_y())))
				{
					//cout<< " je vias tirer sur "<<(*tmp)->get_x()<< " "<<  (*tmp)->get_y()<<endl;
					(*_ite_ee)->get_inv()->get_weapon_c()->set_munCurrent(
							(*_ite_ee)->get_inv()->get_weapon_c()->get_munCurrent()-1);
					(*_ite_ee)->set_paCurrent((*_ite_ee)->get_paCurrent());
					cout<<" yo";
					(*tmp)->set_pvCurrent((*tmp)->get_pvCurrent()-( ((*_ite_ee)->get_inv()->get_weapon_c()->get_degats()) *( (cible<=((*_ite_ee)->get_accuracy()+5)) * (1+(cible<=(*_ite_ee)->get_luck())) ) ));
					cout << "lo\n";
				}
				if((*_ite_ee)->get_paCurrent()>=1)
				{
					list<pair<int,int>> chemin = _mapCurrent.pathfinding((*_ite_ee)->get_x(),
							(*_ite_ee)->get_y(),(*tmp)->get_x(), (*tmp)->get_y());
					if(chemin.front().first!=-1)
					{
						list<pair<int,int>>::iterator tmpl=chemin.begin();
						while ( (*_ite_ee)->get_paCurrent()!=0 && tmpl!=chemin.end())
						{
							_mapCurrent.moveItemToWithMoveAnim((*_ite_ee)->get_x(), (*_ite_ee)->get_y(),(*tmpl).first, (*tmpl).second);
							//cout<< "on veux se deplacer de "<<(*_ite_ee)->get_x()<< " "<< << " en "<< (*tmpl).first<<" "<<(*tmpl).second<<endl;
							(*_ite_ee)->set_paCurrent((*_ite_ee)->get_paCurrent()-1);
							tmpl++;
						}
					}
				}
			}

			for (_ite_l=_team_hero.begin();_ite_l!=_team_hero.end();_ite_l++)
			{
				(*_ite_l)->set_paCurrent((*_ite_l)->get_paMax());
				if((*_ite_l)->get_pvCurrent()>0)
				{
					temph.push_front(*_ite_l);//back
				}
			}
			for (_ite_ee=_team_ennemi.begin(); _ite_ee!=_team_ennemi.end();_ite_ee++)
			{
				if((*_ite_ee)->get_pvCurrent()>0)
				{
					tempe.push_front(*_ite_ee);
				}
			}
			_team_ennemi=tempe;
			_team_hero=temph;
			if( _team_hero.size()==0)
			{
				cout <<" loooooooooooooose\n";
				game->PopState();
			}
			_ite_l=_team_hero.begin();
		}
		break;
		default:

			break;
		}
	}
}

void Partie::UpdateMenuStats(IHMmanager* game){
	list<Hero>::iterator iteh = _tank_hero.begin();

	rectStats[0].setSize(Vector2f(size_Map_part_X*0.80 , size_Map_part_Y*0.80));
	rectStats[0].setPosition((game->get_myWindow()->getSize().x - ESPACE*2 - 96)/2 - rectStats[0].getGlobalBounds().width/2
						   , (game->get_myWindow()->getSize().y - ESPACE*2 - 96)/2 - rectStats[0].getGlobalBounds().height/2
						     );

	for(int j = 0 ; j < 3 ; j++){
		spritePersoActuel[j] = (*iteh)._sprite;
		textStats[j*nbtextStats].setString((*iteh).get_name());
		spritePersoActuel[j].setScale(3,3);
		if(j == 0){
			spritePersoActuel[j].setPosition( rectStats[0].getGlobalBounds().left + 10
									    	, rectStats[0].getGlobalBounds().top + (rectStats[0].getGlobalBounds().height/6 - spritePersoActuel[j].getGlobalBounds().height/2 ));
		} else {
			spritePersoActuel[j].setPosition( rectStats[0].getGlobalBounds().left + 10
											, spritePersoActuel[j-1].getGlobalBounds().top + (spritePersoActuel[j-1].getGlobalBounds().height) + ESPACE);
		}

		textStats[j*nbtextStats].setPosition( spritePersoActuel[j].getGlobalBounds().left + spritePersoActuel[j].getGlobalBounds().width/2 - textStats[j*nbtextStats].getGlobalBounds().width/2
											, spritePersoActuel[j].getGlobalBounds().top - 10);
		// Axe des X
		rectStats[j*nbRectStats + 6] = RectangleShape(Vector2f( 5*(rectStats[j*nbRectStats + 1].getSize().x) + PXL_PV*5 + ESPACE*8, 1));
		// Axe des Y
		rectStats[7] = RectangleShape(Vector2f( 1, PXL_PV*5 + 20 + 20 ));

		rectStats[7].setPosition( spritePersoActuel[j].getGlobalBounds().left + spritePersoActuel[j].getGlobalBounds().width + ESPACE*2
								, rectStats[0].getGlobalBounds().top + (rectStats[0].getGlobalBounds().height/2 - rectStats[j*nbRectStats + 7].getGlobalBounds().height/2));
		rectStats[6].setPosition( rectStats[j*nbRectStats + 7].getGlobalBounds().left - ESPACE
								, rectStats[j*nbRectStats + 7].getGlobalBounds().top + rectStats[j*nbRectStats + 7].getGlobalBounds().height - ESPACE);

		stringstream ss;
		ss << (*iteh).get_strength();
		textStats[j*nbtextStats + 1].setString( ss.str() ); textStats[j*nbtextStats + 6].setString( "Force" );
		ss.str(string()); ss << (*iteh).get_accuracy();
		textStats[j*nbtextStats + 2].setString( ss.str() ); textStats[j*nbtextStats + 7].setString( "Precision" );
		ss.str(string()); ss << (*iteh).get_endurance();
		textStats[j*nbtextStats + 3].setString( ss.str() ); textStats[j*nbtextStats + 8].setString( "Endurance" );
		ss.str(string()); ss << (*iteh).get_agility();
		textStats[j*nbtextStats + 4].setString( ss.str() ); textStats[j*nbtextStats + 9].setString( "Agilité" );
		ss.str(string()); ss << (*iteh).get_luck();
		textStats[j*nbtextStats + 5].setString( ss.str() ); textStats[j*nbtextStats + 10].setString( "Chance" );

		rectStats[j*nbRectStats + 1].setSize(Vector2f( 150 , PXL_PV*((*iteh).get_strength()) ));
		rectStats[j*nbRectStats + 2].setSize(Vector2f( 150 , PXL_PV*((*iteh).get_accuracy()) ));
		rectStats[j*nbRectStats + 3].setSize(Vector2f( 150 , PXL_PV*((*iteh).get_endurance()) ));
		rectStats[j*nbRectStats + 4].setSize(Vector2f( 150 , PXL_PV*((*iteh).get_agility()) ));
		rectStats[j*nbRectStats + 5].setSize(Vector2f( 150 , PXL_PV*((*iteh).get_luck()) ));

		rectStats[j*nbRectStats + 1].setPosition( rectStats[j*nbRectStats + 7].getGlobalBounds().left + ESPACE,
								  rectStats[j*nbRectStats + 6].getGlobalBounds().top - rectStats[j*nbRectStats + 1].getGlobalBounds().height);
		textStats[j*nbtextStats + 1].setPosition( rectStats[j*nbRectStats + 1].getGlobalBounds().left + rectStats[j*nbRectStats + 1].getGlobalBounds().width/2 - textStats[j*nbtextStats + 1].getGlobalBounds().width/2
								, rectStats[j*nbRectStats + 1].getGlobalBounds().top + rectStats[j*nbRectStats + 1].getGlobalBounds().height/2 - textStats[j*nbtextStats + 1].getGlobalBounds().height/2);
		textStats[j*nbtextStats + 6].setPosition( rectStats[j*nbRectStats + 1].getGlobalBounds().left + rectStats[j*nbRectStats + 1].getGlobalBounds().width/2 - textStats[j*nbtextStats + 6].getGlobalBounds().width/2
								, rectStats[j*nbRectStats + 1].getGlobalBounds().top - ESPACE);
		for(int i = 2 ; i <= 5 ; i++){
			rectStats[j*nbRectStats + i].setPosition( rectStats[j*nbRectStats + i - 1].getGlobalBounds().left + rectStats[j*nbRectStats + i - 1].getGlobalBounds().width + ESPACE*2
									, rectStats[j*nbRectStats + 6].getGlobalBounds().top - rectStats[j*nbRectStats + i].getGlobalBounds().height );
			textStats[j*nbtextStats + i].setPosition( rectStats[j*nbRectStats + i].getGlobalBounds().left + rectStats[j*nbRectStats + i].getGlobalBounds().width/2 - textStats[j*nbtextStats + i].getGlobalBounds().width/2
									, rectStats[j*nbRectStats + i].getGlobalBounds().top + rectStats[j*nbRectStats + i].getGlobalBounds().height/2 - textStats[j*nbtextStats + i].getGlobalBounds().height/2);
			textStats[j*nbtextStats + i + 5].setPosition( rectStats[j*nbRectStats + i].getGlobalBounds().left + rectStats[j*nbRectStats + i].getGlobalBounds().width/2 - textStats[j*nbtextStats + i + 5].getGlobalBounds().width/2
										, rectStats[j*nbRectStats + i].getGlobalBounds().top - ESPACE);
		}
		iteh++;
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
										   ,_mapCurrent._origYmap - j*64*_mapCurrent._zoom - _mapCurrent._zoom*64);
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
	int i = 0, j = 0;
	if(fenetreActive == 1){

	} else if(fenetreActive == 2){

	} else if(fenetreActive == 3){
		for(j = 0 ; j < 3 ; j++){
			for(i = 0 ; i < nbRectStats*3 ; i++) {
				game->get_myWindow()->draw(rectStats[i]);
			}
			game->get_myWindow()->draw(spritePersoActuel[j]);
			for(i = 0 ; i < nbtextStats*3 ; i++) {
				game->get_myWindow()->draw(textStats[i]);
			}
		}

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
	game->get_myWindow()->draw(namePersoActif);
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
	game->get_myWindow()->draw(WeaponActif) ;
	game->get_myWindow()->draw(textAmmunation) ;

	for(Sprite g : boutonMenu) game->get_myWindow()->draw(g);
}

void Partie::DrawMap(IHMmanager* game){

	RectangleShape r(Vector2f(_mapCurrent.get_sizeX()*64*_mapCurrent._zoom,_mapCurrent.get_sizeY()*_mapCurrent._zoom*64));
	r.setPosition(_mapCurrent._origXmap, _mapCurrent._origYmap - _mapCurrent.get_sizeY()*_mapCurrent._zoom*64);
	r.setOutlineThickness(2.0);
	r.setOutlineColor(Color::Magenta);
	r.setFillColor(Color(0,0,0,0));
	game->get_myWindow()->draw(r);

	int i,j;
	list<RectangleShape>::iterator itelistSquareMap = _mapCurrent._listSquareMap.begin();
	for(i = 0 ; i <_mapCurrent.get_sizeX() ; i++){
		for(j = 0 ; j < _mapCurrent.get_sizeY() ; j++){
			game->get_myWindow()->draw((*itelistSquareMap));
			itelistSquareMap++;
		}
	}
	Sprite tpsSprite;
	//list<Personnage*>::iterator ite_l = _team_hero.begin();
	if (_mapCurrent.get_dangerZone()==0)
	{
		_ite_h = _tank_hero.begin() ;
		(*_ite_h).set_sprite(t);
		tpsSprite = (*_ite_h).get_sprite();
		tpsSprite.setScale(_mapCurrent._zoom, _mapCurrent._zoom);
		tpsSprite.setPosition(_mapCurrent._origXmap + 64*(_mapCurrent._zoom)*(*_ite_h).get_x()
							, _mapCurrent._origYmap - _mapCurrent._zoom*64 - 64*(_mapCurrent._zoom)*(*_ite_h).get_y() );
		game->get_myWindow()->draw(tpsSprite);
		Text nom((*_ite_h).get_name(), font, _mapCurrent._zoom*8);
		nom.setPosition(tpsSprite.getGlobalBounds().left, tpsSprite.getGlobalBounds().top);
		game->get_myWindow()->draw(nom);
	}else{
		for(_ite_h = _tank_hero.begin() ; _ite_h != _tank_hero.end() ; _ite_h++){
			(*_ite_h).set_sprite(t);
			tpsSprite = (*_ite_h).get_sprite();
			tpsSprite.setScale(_mapCurrent._zoom, _mapCurrent._zoom);
			tpsSprite.setPosition(_mapCurrent._origXmap + 64*(_mapCurrent._zoom)*(*_ite_h).get_x()
								, _mapCurrent._origYmap - _mapCurrent._zoom*64 - 64*(_mapCurrent._zoom)*(*_ite_h).get_y() );
			game->get_myWindow()->draw(tpsSprite);
			Text nom((*_ite_h).get_name(), font, _mapCurrent._zoom*8);
			nom.setPosition(tpsSprite.getGlobalBounds().left+tpsSprite.getGlobalBounds().width/2 -nom.getGlobalBounds().width/2, tpsSprite.getGlobalBounds().top);
			nom.setFillColor(Color::Yellow);
			game->get_myWindow()->draw(nom);
		}
	}
	for(list<Ennemi*>::iterator te = _team_ennemi.begin(); te!=_team_ennemi.end(); te++){
		//(*te)->display_info();
		(*te)->set_sprite(t);
		tpsSprite = (*te)->get_sprite();
		tpsSprite.setScale(_mapCurrent._zoom, _mapCurrent._zoom);
		tpsSprite.setPosition(_mapCurrent._origXmap + 64*(_mapCurrent._zoom)*(*te)->get_x()
							, _mapCurrent._origYmap - _mapCurrent._zoom*64 - 64*(_mapCurrent._zoom)*(*te)->get_y() );
		Text Pv("",font,_mapCurrent._zoom*8);
		stringstream s[2];
		s[0] << (*te)->get_pvCurrent();
		s[1] << (*te)->get_pvMax();
		Pv.setString( s[0].str() + "/" + s[1].str());
		Pv.setPosition(tpsSprite.getGlobalBounds().left+tpsSprite.getGlobalBounds().width/2 -Pv.getGlobalBounds().width/2, tpsSprite.getGlobalBounds().top);
		Pv.setFillColor(Color::Red);
		game->get_myWindow()->draw(tpsSprite);
		game->get_myWindow()->draw(Pv);
	}

	for(_ite_o = _tank_obstacle.begin(); _ite_o != _tank_obstacle.end(); _ite_o++)
	{
		Text obs("obstacle", font, _mapCurrent._zoom*8);
		obs.setPosition(_mapCurrent._origXmap+(*_ite_o).get_x()*64*_mapCurrent._zoom,
				_mapCurrent._origYmap- _mapCurrent._zoom*64 -(*_ite_o).get_y()*64*_mapCurrent._zoom);
		game->get_myWindow()->draw(obs);
	}

	for(_ite_p = _tank_portail.begin(); _ite_p != _tank_portail.end(); _ite_p++)
	{
		if((*_ite_p).get_nameNextMap().size()==2)
		{
			Text por("portail", font, _mapCurrent._zoom*8);
			por.setPosition(_mapCurrent._origXmap+(*_ite_p).get_x()*64*_mapCurrent._zoom,
					_mapCurrent._origYmap - _mapCurrent._zoom*64-(*_ite_p).get_y()*64*_mapCurrent._zoom);
			por.setFillColor(Color::Red);
			game->get_myWindow()->draw(por);
		}else{
			Text por("portail", font, _mapCurrent._zoom*8);
			por.setPosition(_mapCurrent._origXmap+(*_ite_p).get_x()*64*_mapCurrent._zoom,
					_mapCurrent._origYmap - _mapCurrent._zoom*64-(*_ite_p).get_y()*64*_mapCurrent._zoom);
			game->get_myWindow()->draw(por);
		}

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
	// ajout des héros sur la carte
	if (_mapCurrent.get_dangerZone()==0)
	{
		_ite_h = _tank_hero.begin();
		_mapCurrent.addItem((*_ite_h));
		(*_ite_h).display_info();
	}else{
		for(_ite_h = _tank_hero.begin(); _ite_h!=_tank_hero.end(); _ite_h++){
			_mapCurrent.addItem((*_ite_h));
		}
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
		_team_ennemi.push_back( &(*_ite_e) );
	}
	// initialisation de la team de héros sur la carte actuel
	_team_hero.clear();
	for(_ite_h = _tank_hero.begin() ; _ite_h != _tank_hero.end() ; _ite_h++){
		_team_hero.push_back( &(*_ite_h) );
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
			//this->fightMode();
			//isDangerZone = false;
			cout << "gain de niveau " << endl;
		} else {										// mode Exploration
			cout << " RAS " << endl;
			//this->explorationMode();
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
	cout << " on veux charger cette map " << p.get_nameNextMap() << endl;
	premiereApparition = true;
	_mapCurrent.removeAllItem();							// on retire tous le monde de la carte sans toucher au conteneur
	Fichier pathMap("src\\World.txt",0);					// chargement de la prochaine map
	//cout << "chargement de la map" << endl;
	pathMap.loadMap(p.get_nameNextMap(), _mapCurrent, _tank_ennemi, _tank_hero, _tank_obstacle, _tank_portail);


	//_mapCurrent.display();

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

	//_mapCurrent.display();
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
	if (_mapCurrent.get_dangerZone()==0)
	{
		_ite_h = _tank_hero.begin();
		_mapCurrent.addItem((*_ite_h));
	}else{
		for(_ite_h = _tank_hero.begin(); _ite_h!=_tank_hero.end(); _ite_h++){
			_mapCurrent.addItem((*_ite_h));
		}
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


// le destructeur
Partie::~Partie() {
	cout << " - Partie detruite " << endl;
}

