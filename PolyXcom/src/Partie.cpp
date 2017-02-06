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

static int PXL_PV;			// taille d'un point de PV/PA en pxl dans la barre de PV/PA
static int ESPACE;			// espacemment entre les boutons
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

static RectangleShape rectInvent; // Element du menu Inventaire
static Text textInvent[7];
static Sprite spriteInvent[4];

static RectangleShape menuCarte; 				// Element du menu Carte
static Sprite spriteWorld;
static Text namePersoActuel;

static const int nbRectStats = 11;				// Element du menu Stats
static const int nbtextStats = 16;
static RectangleShape rectStats[nbRectStats];
static Text textStats[nbtextStats];
static Sprite spritePersoActuel;

static RectangleShape menuQuitter;				// Element du menu Quitter
static RectangleShape boutonOui;
static RectangleShape boutonNon;
static Text textMenuQuitter;
static Text textOui;
static Text textNon;

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
	InitMenuInvent();
	InitMenuCarte();
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

void Partie::InitMenuStats(){
	// Init Fenetre Stats
	 rectStats[0].setFillColor(unSelected);
	 // Nom du Personnage
	 textStats[0] = Text("none",font,20);
	 textStats[0].setFillColor(Color::White);

	 // Representation des Stats
	 for(int i = 1 ; i <= 5 ; i++){
	 	rectStats[i] = RectangleShape(Vector2f(150,PXL_PV));
	 	rectStats[i].setFillColor(Color(0,100,255));
	 	textStats[i] = Text("...",font,20);
	 	textStats[i+5] = Text("...",font,20);
	 }
	 rectStats[6] = RectangleShape(Vector2f( 5*(rectStats[1].getSize().x) + ESPACE*5 + 20,
	 										1));
	 rectStats[7] = RectangleShape(Vector2f( 1, PXL_PV*5 + 20 + 20 ));
	 rectStats[6].setFillColor(Color::White);
	 rectStats[7].setFillColor(Color::White);
}

void Partie::InitMenuInvent(){
	rectInvent.setFillColor(unSelected);
	textInvent[0] = Text("...",font,20); textInvent[0].setFillColor(Color::White);
	textInvent[1] = Text("Arme",font,20); textInvent[1].setFillColor(Color::White);
	textInvent[2] = Text("Medkit",font,20); textInvent[2].setFillColor(Color::White);
	textInvent[3] = Text("Grenade",font,20); textInvent[3].setFillColor(Color::White);
	textInvent[4] = Text("x..",font,20); textInvent[4].setFillColor(Color::White);
	textInvent[5] = Text("x..",font,20); textInvent[5].setFillColor(Color::White);
	textInvent[6] = Text("x..",font,20); textInvent[6].setFillColor(Color::White);
	spriteInvent[1].setTexture(t); spriteInvent[1].setTextureRect(IntRect(131,391,32,32));
	spriteInvent[2].setTexture(t); spriteInvent[2].setTextureRect(IntRect(164,391,32,32));
	spriteInvent[3].setTexture(t); spriteInvent[3].setTextureRect(IntRect(197,391,32,32));
}

void Partie::InitMenuCarte(){
	menuCarte.setFillColor(unSelected);
	namePersoActuel = Text("none",font,20);
	namePersoActuel.setFillColor(Color::White);
	spriteWorld.setTexture(t);
	spriteWorld.setTextureRect(IntRect(1,466,66,66));
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
	_mapCurrent.removeAllItem();// carte actuelle
	_tank_ennemi.clear();		// conteneurs pour
	_tank_hero.clear();			// le chargement a partir d'un fichier
	_tank_obstacle.clear();
	_tank_portail.clear();
	_tank_portail_close.clear();
	_team_hero.clear();			// equipe de heros
	_team_ennemi.clear();		// equipe de ennemi
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
									switchMap((*_ite_p),false);
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
									switchMap((*_ite_p),false);
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
									switchMap((*_ite_p),false);
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
									switchMap((*_ite_p),false);
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
									if(STATE_GRE==false)
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
														switchMap((*_ite_p),false);
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
									{//cas grenade
										cout<< "on y va!\n";
										if(_mapCurrent.moveIsPossible(xcase, ycase, 0))
										{
											cout<<"possible!";
											list<Hero*>::iterator ph;
											list<Ennemi*>::iterator pe;
											int xcompt;
											int ycompt;
											(*_ite_l)->set_paCurrent((*_ite_l)->get_paCurrent()-4);
											for(xcompt=xcase-(*_ite_l)->get_inv()->get_grenade()->get_range();xcompt<=xcase+(*_ite_l)->get_inv()->get_grenade()->get_range();xcompt++)
											{
												for(ycompt=ycase-(*_ite_l)->get_inv()->get_grenade()->get_range();ycompt<=ycase+(*_ite_l)->get_inv()->get_grenade()->get_range();ycompt++)
												{
													if( !((xcompt < 0) || (xcompt >= _mapCurrent.get_sizeX()) || (ycompt < 0) || (ycompt >= _mapCurrent.get_sizeY())))
													{
														cout<<"\n\tX= "<<xcompt<<" Y= "<<ycompt<<endl;
														/*
														if(_mapCurrent.get_IDin(xcompt, ycompt)==1)
														{
															cout<<"obs\n";
															for(_ite_o=_tank_obstacle.begin();_ite_o!=_tank_obstacle.end();_ite_o++)
															{
																if(((*_ite_o).get_x()==xcase)||((*_ite_o).get_y()==ycase))
																{
																	cout<<"Cet obstacle est modifié X= "<<(*_ite_o).get_x()<<" Y= "<<(*_ite_o).get_y()<<endl;
																	(*_ite_o).set_destructible();//degats sur les obstacles
																	(*_ite_o).display_info();
																}
															}
														}
														*/
														/*
														if(_mapCurrent.get_IDin(xcompt, ycompt)==2)
														{
															cout<<"hero\n";
															for(ph = _team_hero.begin() ; ph != _team_hero.end() ; ph++)
															{
																if((*ph)->get_x()==xcase||(*ph)->get_y()==ycase)
																{								//degats sur les heros
																	cout<<"Ce hero est touché X= "<<(*ph)->get_x()<<" Y= "<<(*ph)->get_y()<<endl;
																	(*ph)->set_pvCurrent((*ph)->get_pvCurrent()-(*_ite_l)->get_inv()->get_grenade()->get_dammage());
																	(*ph)->display_info();
																}
															}
														}
														*/
														if(_mapCurrent.get_IDin(xcompt, ycompt)==3)
														{
															cout << "en\n";
															for(pe = _team_ennemi.begin() ; pe != _team_ennemi.end() ; pe++)
															{
																if((*pe)->get_x()==xcase||(*pe)->get_y()==ycase)
																{								//degats sur les ennemis
																	cout<<"Cet ennemis est touché X= "<<(*pe)->get_x()<<" Y= "<<(*pe)->get_y()<<endl;
																	(*pe)->set_pvCurrent((*pe)->get_pvCurrent()-(*_ite_l)->get_inv()->get_grenade()->get_dammage());
																	if((*pe)->get_pvCurrent()<0)
																	{
																		(*pe)->set_pvCurrent(0);
																	}
																	(*pe)->display_info();
																}
															}
														}
														else if(_mapCurrent.get_IDin(xcompt, ycompt)==0)
														{
															cout << "ya rien en "<< xcompt<< " "<< ycompt<<endl;
														}
														else
														{
															cout<<"Pas traitéX= "<<xcompt<<" Y= "<<ycompt<<endl;
														}
													}
												}
											}
										}

										STATE_GRE=false;
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
										(*_ite_ee)->set_pvCurrent((*_ite_ee)->get_pvCurrent()-(*_ite_l)->get_strength()*(1+(crit<=(*_ite_l)->get_luck())));
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
	PXL_PV = 25*game->_scaleBouton;			// taille d'un point de PV/PA en pxl dans la barre de PV/PA
	ESPACE = 20*game->_scaleBouton;
	size_window_X = game->get_myWindow()->getSize().x;
	size_window_Y = game->get_myWindow()->getSize().y;
	size_Map_part_X = size_window_X - ESPACE*2 - boutonMenu[0].getGlobalBounds().width;
	size_Map_part_Y = size_window_Y - ESPACE*2 - boutonMenu[0].getGlobalBounds().height;

	UpdateMap(game);
	UpdateHUD(game);
	if(fenetreActive == 1){
		UpdateMenuInvent(game);
	} else if(fenetreActive == 2){
		UpdateMenuCarte(game);
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
				STATE_CC =false;
				STATE_TIR=false;
				STATE_GRE=false;
				_ite_h = _tank_hero.begin();
			} else {
				// mode combat
				cout << " Mode combat " << endl;
				STATE_CC =false;
				STATE_TIR=false;
				STATE_GRE=false;
			}
		} else {

		}
	}
}

void Partie::UpdateHUD(IHMmanager* game){
	// mis à jour des positions des boutons de l'interface
	PersoActif.setScale(game->_scaleBouton , game->_scaleBouton );


	PersoActif.setPosition( ESPACE, (game->get_myWindow()->getSize().y - ESPACE - PersoActif.getGlobalBounds().height));
	namePersoActif.setString((*_ite_l)->get_name());
	namePersoActif.setScale(game->_scaleBouton , game->_scaleBouton );
	namePersoActif.setPosition( PersoActif.getGlobalBounds().left + PersoActif.getGlobalBounds().width/2 - namePersoActif.getGlobalBounds().width/2 + 12*game->_scaleBouton
							  , PersoActif.getGlobalBounds().top - 10*game->_scaleBouton - namePersoActif.getGlobalBounds().height );

	ConteneurPVMAX.setSize(Vector2f( (*_ite_l)->get_pvMax() * PXL_PV  ,50));
	ConteneurPVMAX.setScale( game->_scaleBouton , game->_scaleBouton );
	ConteneurPVMAX.setPosition( PersoActif.getGlobalBounds().left + PersoActif.getGlobalBounds().width + ESPACE*2,
								PersoActif.getGlobalBounds().top + ConteneurPVMAX.getOutlineThickness());
	ConteneurPAMAX.setSize(Vector2f( (*_ite_l)->get_paMax() * PXL_PV  ,50));
	ConteneurPAMAX.setScale( game->_scaleBouton , game->_scaleBouton );
	ConteneurPAMAX.setPosition( PersoActif.getGlobalBounds().left + PersoActif.getGlobalBounds().width + ESPACE*2,
								PersoActif.getGlobalBounds().top + PersoActif.getGlobalBounds().height - ConteneurPAMAX.getGlobalBounds().height + ConteneurPAMAX.getOutlineThickness());

	ConteneurPV.setSize(Vector2f( ((*_ite_l)->get_pvCurrent() * PXL_PV - 8) ,42));
	ConteneurPA.setSize(Vector2f( ((*_ite_l)->get_paCurrent() * PXL_PV - 8) ,42));
	ConteneurPV.setScale( game->_scaleBouton , game->_scaleBouton );
	ConteneurPA.setScale( game->_scaleBouton , game->_scaleBouton );

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

	textPV.setScale( game->_scaleBouton , game->_scaleBouton);
	textPA.setScale( game->_scaleBouton , game->_scaleBouton);
	textAmmunation.setScale( game->_scaleBouton , game->_scaleBouton);

	ConteneurPV.setPosition( ConteneurPVMAX.getGlobalBounds().left + 8*game->_scaleBouton,
							 ConteneurPVMAX.getGlobalBounds().top + 8*game->_scaleBouton );
	ConteneurPA.setPosition( ConteneurPAMAX.getGlobalBounds().left + 8*game->_scaleBouton,
							 ConteneurPAMAX.getGlobalBounds().top + 8*game->_scaleBouton );

	textPV.setPosition(ConteneurPV.getGlobalBounds().left + 10,
			ConteneurPV.getGlobalBounds().top + ConteneurPV.getGlobalBounds().height/2 - textPV.getGlobalBounds().height/2 );
	textPA.setPosition(ConteneurPA.getGlobalBounds().left + 10,
			ConteneurPA.getGlobalBounds().top + ConteneurPA.getGlobalBounds().height/2 - textPA.getGlobalBounds().height/2 );

	boutonMenu[0].setScale(2 * game->_scaleBouton, 2 *game->_scaleBouton);
	boutonMenu[1].setScale(2 * game->_scaleBouton, 2 *game->_scaleBouton);
	boutonMenu[2].setScale(2 *game->_scaleBouton, 2 *game->_scaleBouton);
	boutonMenu[3].setScale(2 *game->_scaleBouton, 2 *game->_scaleBouton);

	boutonMenu[0].setPosition( (game->get_myWindow()->getSize().x - ESPACE - boutonMenu[0].getGlobalBounds().width),
			ESPACE );
	boutonMenu[1].setPosition( (game->get_myWindow()->getSize().x - ESPACE - boutonMenu[1].getGlobalBounds().width),
			boutonMenu[0].getGlobalBounds().top + boutonMenu[0].getGlobalBounds().height + 10 );
	boutonMenu[2].setPosition( (game->get_myWindow()->getSize().x - ESPACE - boutonMenu[2].getGlobalBounds().width),
			boutonMenu[1].getGlobalBounds().top + boutonMenu[1].getGlobalBounds().height + 10 );
	boutonMenu[3].setPosition( (game->get_myWindow()->getSize().x - ESPACE - boutonMenu[3].getGlobalBounds().width),
			boutonMenu[2].getGlobalBounds().top + boutonMenu[2].getGlobalBounds().height + 10 );

	boutonFinTour.setScale(2 * game->_scaleBouton, 2 *game->_scaleBouton);
	boutonChangerCompagnon.setScale(2 * game->_scaleBouton, 2 *game->_scaleBouton);
	boutonMedKit.setScale(2 * game->_scaleBouton, 2 *game->_scaleBouton);
	boutonGrenade.setScale(2 * game->_scaleBouton, 2 *game->_scaleBouton);
	boutonRecharger.setScale(2 * game->_scaleBouton, 2 *game->_scaleBouton);
	boutonTirer.setScale(2 * game->_scaleBouton, 2 *game->_scaleBouton);
	boutonCC.setScale(2 * game->_scaleBouton, 2 *game->_scaleBouton);
	WeaponActif.setScale(game->_scaleBouton, game->_scaleBouton);

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
		case 1 : boutonMenu[0].setTextureRect(IntRect(COLUNN1_PXL + 65 ,ROWPLAYERBUTTOM_PXL,64,64)); break;
		case 2 : boutonMenu[1].setTextureRect(IntRect(COLUNN2_PXL + 65 ,ROWPLAYERBUTTOM_PXL,64,64)); break;
		case 3 : boutonMenu[2].setTextureRect(IntRect(COLUNN3_PXL + 65 ,ROWPLAYERBUTTOM_PXL,64,64)); break;
		case 4 : boutonMenu[3].setTextureRect(IntRect(COLUNN4_PXL + 65 ,ROWPLAYERBUTTOM_PXL,64,64)); break;
		case 5 : boutonCC.setTextureRect(IntRect(COLUNN1_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		case 6 : boutonTirer.setTextureRect(IntRect(COLUNN2_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		case 7 : boutonRecharger.setTextureRect(IntRect(COLUNN3_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		case 8 : boutonGrenade.setTextureRect(IntRect(COLUNN4_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		case 9 : boutonMedKit.setTextureRect(IntRect(COLUNN5_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		case 10: boutonChangerCompagnon.setTextureRect(IntRect(COLUNN6_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		case 11: boutonFinTour.setTextureRect(IntRect(COLUNN7_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64)); break;
		default:
			switch(fenetreActive){
				case 1 : boutonMenu[0].setTextureRect(IntRect(COLUNN1_PXL + 65 ,ROWPLAYERBUTTOM_PXL,64,64)); break;
				case 2 : boutonMenu[1].setTextureRect(IntRect(COLUNN2_PXL + 65 ,ROWPLAYERBUTTOM_PXL,64,64)); break;
				case 3 : boutonMenu[2].setTextureRect(IntRect(COLUNN3_PXL + 65 ,ROWPLAYERBUTTOM_PXL,64,64)); break;
				case 4 : boutonMenu[3].setTextureRect(IntRect(COLUNN4_PXL + 65 ,ROWPLAYERBUTTOM_PXL,64,64)); break;
				default: break;
			}
			if(STATE_TIR == true){
				boutonTirer.setTextureRect(IntRect(COLUNN2_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64));
			} else if(STATE_CC == true){
				boutonCC.setTextureRect(IntRect(COLUNN1_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64));
			} else if(STATE_GRE == true){
				boutonGrenade.setTextureRect(IntRect(COLUNN4_PXL + 65 ,ROWFIGHTBUTTOM_PXL,64,64));
			}
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
				if(( STATE_CC==false) && (*_ite_l)->get_paCurrent()>=3 )
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
				if(( STATE_TIR==false) && ((*_ite_l)->get_paCurrent()>=4)
						&& (*_ite_l)->get_inv()->get_weapon_c()->get_munCurrent()>0)
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
				(*_ite_l)->set_paCurrent((*_ite_l)->get_paCurrent()-2);
			}
			Sleep(500);
			break;
		case 8:
			// afficher Grenade
			if ( _mapCurrent.get_dangerZone()==true)
			{
				if(( STATE_GRE==false) && ((*_ite_l)->get_paCurrent()>=4))
				{
					STATE_GRE=true;
					cout <<" get ready the boomsticks !"<<endl;
				}
				else
				{
					STATE_GRE=false;
					cout << "no fire works?"<< endl;
				}
			}
			Sleep(500);
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

			//cout << "actuellement avec ";
			//(*_ite_l)->display_info();
			if(_mapCurrent.get_dangerZone()==true)
			{
				if(	*(_ite_l)==_team_hero.back())
				{
					_ite_l=_team_hero.begin();
				}
				else
				{
					_ite_l++;
					cout<<"Cas2\n";
				}
			}
			//cout << "\n maintenant avec ";
			//(*_ite_l)->display_info();
			STATE_CC=false;
			STATE_TIR=false;
			STATE_GRE=false;
			Sleep(500);
			break;
		case 11:
		{
			if(_mapCurrent.get_dangerZone()==true)
			{
				// afficher Fin du Tour
				STATE_CC=false;
				STATE_TIR=false;
				cout << " Avant les modifs"<<endl;
				_mapCurrent.display();

				for (_ite_l=_team_hero.begin();_ite_l!=_team_hero.end();_ite_l++)
				{
					(*_ite_l)->set_paCurrent(0);
					if((*_ite_l)->get_pvCurrent()<=0)
					{
						_team_hero.remove((*_ite_l));
					}
				}
				for (_ite_ee=_team_ennemi.begin(); _ite_ee!=_team_ennemi.end();_ite_ee++)
				{
					if((*_ite_ee)->get_pvCurrent()<=0)
					{
						_team_ennemi.remove((*_ite_ee));
					}
				}

				if(_team_ennemi.size()==0)
				{
					cout << "WIIIIIIIIIIIIIIIIIIIIIIIn\n";
					for (_ite_l=_team_hero.begin();_ite_l!=_team_hero.end();_ite_l++)
					{
						(*_ite_l)->set_paCurrent((*_ite_l)->get_paMax());
						(*_ite_l)->get_inv()->get_weapon_c()->set_munCurrent(
								(*_ite_l)->get_inv()->get_weapon_c()->get_munMax());

					}
					// fermer portail
					switchMap(_tank_portail.front(),false);//todo portail ban
				}

				cout << " Apres les modifs"<<endl;
				_mapCurrent.display();

				for (_ite_ee=_team_ennemi.begin(); _ite_ee!=_team_ennemi.end();_ite_ee++)
				{
					cout << " je suis en "<< (*_ite_ee)->get_x()<< " / "<<(*_ite_ee)->get_y()<<endl;
					if((*_ite_ee)->get_inv()->get_weapon_c()->get_munCurrent()==0 && (*_ite_ee)->get_paCurrent()>=2)
					{
						(*_ite_ee)->get_inv()->get_weapon_c()->set_munCurrent(
								(*_ite_ee)->get_inv()->get_weapon_c()->get_munMax());
						cout<< "je recharge\n";
					}
					int cible=rand()%_team_hero.size();
					cout << " cible ="<< cible<< endl;
					list<Hero*>::iterator tmp= _team_hero.begin();
					/*
					for( tmp=_team_hero.begin();tmp!=_team_hero.end();tmp++)
					{
						(*tmp)->display_info();
					}
					*/
					while(cible!=0)
					{
						if(tmp==_team_hero.end())
						{
							tmp= _team_hero.begin();
							cout << " jour!";
						}
						tmp++;
						(*tmp)->display_info();
						cible--;
					}
					cout << "ma  cible est "<< cible;(*tmp)->display_info();
					if( ((*_ite_ee)->get_paCurrent()>=4)&&((*_ite_ee)->get_inv()->get_weapon_c()->get_munCurrent()>=1)
							&& (_mapCurrent.pathIsPossible((*_ite_ee)->get_x(), (*_ite_ee)->get_y(),
									(*tmp)->get_x(), (*tmp)->get_y())))
					{
						(*_ite_ee)->get_inv()->get_weapon_c()->set_munCurrent(
								(*_ite_ee)->get_inv()->get_weapon_c()->get_munCurrent()-1);
						(*_ite_ee)->set_paCurrent((*_ite_ee)->get_paCurrent());
						(*tmp)->set_pvCurrent((*tmp)->get_pvCurrent()-( ((*_ite_ee)->get_inv()->get_weapon_c()->get_degats()) *( (cible<=((*_ite_ee)->get_accuracy()+5)) * (1+(cible<=(*_ite_ee)->get_luck())) ) ));
						cout << " j'ai tire\n";
					}
					if((*_ite_ee)->get_paCurrent()>=1)
					{
						list<pair<int,int>> chemin = _mapCurrent.pathfinding((*_ite_ee)->get_x(),
								(*_ite_ee)->get_y(),(*tmp)->get_x(), (*tmp)->get_y());
						if(chemin.front().first!=-1)
						{
							/*
							list<pair<int,int>>::iterator tmpl=chemin.begin();
							while ( (*_ite_ee)->get_paCurrent()!=0 && tmpl!=chemin.end())
							{
								_mapCurrent.moveItemToWithMoveAnim((*_ite_ee)->get_x(), (*_ite_ee)->get_y(),(*tmpl).first, (*tmpl).second);
								cout<< "je bouge en "<< (*tmpl).first<<" "<<(*tmpl).second<<endl;
								(*_ite_ee)->set_paCurrent((*_ite_ee)->get_paCurrent()-1);
								tmpl++;
							}
							*/
							_mapCurrent.moveItemToWithMoveAnim((*_ite_ee)->get_x(), (*_ite_ee)->get_y(),(*tmp)->get_x(), (*tmp)->get_y());
							_mapCurrent.display();
						}
					}
				}

				for (_ite_l=_team_hero.begin();_ite_l!=_team_hero.end();_ite_l++)
				{
					(*_ite_l)->set_paCurrent((*_ite_l)->get_paMax());
					if((*_ite_l)->get_pvCurrent()<=0)
					{
						_team_hero.remove((*_ite_l));
					}
				}
				for (_ite_ee=_team_ennemi.begin(); _ite_ee!=_team_ennemi.end();_ite_ee++)
				{
					(*_ite_ee)->set_paCurrent((*_ite_ee)->get_paMax());
					if((*_ite_ee)->get_pvCurrent()<=0)
					{
						_team_ennemi.remove((*_ite_ee));
					}
				}
				if( _team_hero.size()==0)
				{
					cout <<" loooooooooooooose\n";
					game->PopState();
				}
				cout <<" size ennemi = "<< _team_ennemi.size()<<endl;
				cout <<" size hero = "<< _team_hero.size()<<endl;
				_ite_l=_team_hero.begin();
				cout<<"on y retourne!";
				Sleep(500);
			}
		}
		break;
		default:

			break;
		}
	}
}

void Partie::UpdateMenuCarte(IHMmanager* game){
	menuCarte.setSize(Vector2f(size_Map_part_X*0.80 , size_Map_part_Y*0.80));
	menuCarte.setScale(game->_scaleBouton, game->_scaleBouton);
	menuCarte.setPosition((game->get_myWindow()->getSize().x - ESPACE*2 - 96)/2 - menuCarte.getGlobalBounds().width/2
			            , (game->get_myWindow()->getSize().y - ESPACE*2 - 96)/2 - menuCarte.getGlobalBounds().height/2
	 	 	 	 	 	);
	spriteWorld.setScale(8*game->_scaleBouton, 8*game->_scaleBouton);
	spriteWorld.setPosition( menuCarte.getGlobalBounds().left + menuCarte.getGlobalBounds().width/2 - spriteWorld.getGlobalBounds().width/2
						   , menuCarte.getGlobalBounds().top + menuCarte.getGlobalBounds().height/2 - spriteWorld.getGlobalBounds().height/2
	 	 	 			  );
}

void Partie::UpdateMenuInvent(IHMmanager* game){
	rectInvent.setSize(Vector2f(size_Map_part_X*0.80*game->_scaleBouton , size_Map_part_Y*0.80*game->_scaleBouton));

	rectInvent.setPosition((game->get_myWindow()->getSize().x - ESPACE*2 - 96*game->_scaleBouton)/2 - rectInvent.getGlobalBounds().width/2
						 , (game->get_myWindow()->getSize().y - ESPACE*2 - 96*game->_scaleBouton)/2 - rectInvent.getGlobalBounds().height/2
						 );
	spriteInvent[0] = (*_ite_l)->_sprite;
	spriteInvent[0].setScale(3*game->_scaleBouton,3*game->_scaleBouton);
	spriteInvent[0].setPosition( rectInvent.getGlobalBounds().left + 10*game->_scaleBouton
						       , rectInvent.getGlobalBounds().top + (rectInvent.getGlobalBounds().height/2 - spriteInvent[0].getGlobalBounds().height/2 ));

	textInvent[0].setString((*_ite_l)->get_name());
	textInvent[0].setScale(game->_scaleBouton, game->_scaleBouton);

	textInvent[0].setPosition( spriteInvent[0].getGlobalBounds().left + spriteInvent[0].getGlobalBounds().width/2 - textInvent[0].getGlobalBounds().width/2
			                 , spriteInvent[0].getGlobalBounds().top - 10*game->_scaleBouton);

	spriteInvent[1].setScale(4*game->_scaleBouton,4*game->_scaleBouton);
	spriteInvent[2].setScale(4*game->_scaleBouton,4*game->_scaleBouton);
	spriteInvent[3].setScale(4*game->_scaleBouton,4*game->_scaleBouton);
	spriteInvent[1].setPosition( spriteInvent[0].getGlobalBounds().left + spriteInvent[0].getGlobalBounds().width + ESPACE*2
							   , rectInvent.getGlobalBounds().top + (rectInvent.getGlobalBounds().height/2 - spriteInvent[1].getGlobalBounds().height/2));
	spriteInvent[2].setPosition( spriteInvent[1].getGlobalBounds().left + spriteInvent[1].getGlobalBounds().width + ESPACE*2
							   , spriteInvent[1].getGlobalBounds().top);
	spriteInvent[3].setPosition( spriteInvent[2].getGlobalBounds().left + spriteInvent[2].getGlobalBounds().width + ESPACE*2
			   	   	   	   	   , spriteInvent[2].getGlobalBounds().top);

	textInvent[1].setScale(game->_scaleBouton, game->_scaleBouton);
	textInvent[2].setScale(game->_scaleBouton, game->_scaleBouton);
	textInvent[3].setScale(game->_scaleBouton, game->_scaleBouton);

	textInvent[1].setPosition( spriteInvent[1].getGlobalBounds().left ,
							   spriteInvent[1].getGlobalBounds().top - ESPACE*2 );
	textInvent[2].setPosition( spriteInvent[2].getGlobalBounds().left ,
							   spriteInvent[2].getGlobalBounds().top - ESPACE*2 );
	textInvent[3].setPosition( spriteInvent[3].getGlobalBounds().left ,
			                   spriteInvent[3].getGlobalBounds().top - ESPACE*2 );
	stringstream ss[4];
	ss[0] << (*_ite_l)->get_inv()->get_weapon_c()->get_munCurrent();
	ss[1] << (*_ite_l)->get_inv()->get_weapon_c()->get_munMax();
	ss[2] << (*_ite_l)->get_inv()->get_medkit()->get_uses();
	ss[3] << (*_ite_l)->get_inv()->get_grenade()->get_number();
	textInvent[4].setString( ss[0].str() + "/" + ss[1].str() + " mun");
	textInvent[5].setString( "x" + ss[2].str());
	textInvent[6].setString( "x" + ss[3].str());

	textInvent[4].setScale(game->_scaleBouton, game->_scaleBouton);
	textInvent[5].setScale(game->_scaleBouton, game->_scaleBouton);
	textInvent[6].setScale(game->_scaleBouton, game->_scaleBouton);

	textInvent[4].setPosition( spriteInvent[1].getGlobalBounds().left ,
				  	  	  	   spriteInvent[1].getGlobalBounds().top + spriteInvent[1].getGlobalBounds().height + ESPACE*2 );
	textInvent[5].setPosition( spriteInvent[2].getGlobalBounds().left ,
							   spriteInvent[2].getGlobalBounds().top + spriteInvent[2].getGlobalBounds().height + ESPACE*2 );
	textInvent[6].setPosition( spriteInvent[3].getGlobalBounds().left ,
							   spriteInvent[3].getGlobalBounds().top + spriteInvent[3].getGlobalBounds().height + ESPACE*2 );

}

void Partie::UpdateMenuStats(IHMmanager* game){
	rectStats[0].setSize(Vector2f(size_Map_part_X*0.80, size_Map_part_Y*0.80));
	rectStats[0].setPosition((game->get_myWindow()->getSize().x - ESPACE*2 - 96)/2 - rectStats[0].getGlobalBounds().width/2
						   , (game->get_myWindow()->getSize().y - ESPACE*2 - 96)/2 - rectStats[0].getGlobalBounds().height/2
							 );
	spritePersoActuel = (*_ite_l)->_sprite;
	spritePersoActuel.setScale(3*game->_scaleBouton, 3*game->_scaleBouton);
	spritePersoActuel.setPosition( rectStats[0].getGlobalBounds().left + 10
						         , rectStats[0].getGlobalBounds().top + (rectStats[0].getGlobalBounds().height/2 - spritePersoActuel.getGlobalBounds().height/2 ));

	textStats[0].setString((*_ite_l)->get_name());
	textStats[0].setScale(game->_scaleBouton, game->_scaleBouton);
	textStats[0].setPosition( spritePersoActuel.getGlobalBounds().left + spritePersoActuel.getGlobalBounds().width/2 - textStats[0].getGlobalBounds().width/2
	 					    , spritePersoActuel.getGlobalBounds().top - 10);

	rectStats[1].setSize(Vector2f( 150 * game->_scaleBouton, PXL_PV*((*_ite_l)->get_strength()) ));
	rectStats[2].setSize(Vector2f( 150 * game->_scaleBouton, PXL_PV*((*_ite_l)->get_accuracy()) ));
	rectStats[3].setSize(Vector2f( 150 * game->_scaleBouton, PXL_PV*((*_ite_l)->get_endurance()) ));
	rectStats[4].setSize(Vector2f( 150 * game->_scaleBouton, PXL_PV*((*_ite_l)->get_agility()) ));
	rectStats[5].setSize(Vector2f( 150 * game->_scaleBouton, PXL_PV*((*_ite_l)->get_luck()) ));

	// Axe des X
	rectStats[6] = RectangleShape(Vector2f( 5*(rectStats[1].getGlobalBounds().width) + PXL_PV*5 + ESPACE*7, 1));
	// Axe des Y
	rectStats[7] = RectangleShape(Vector2f( 1, PXL_PV*5 + ESPACE*2 ));

	rectStats[7].setPosition( spritePersoActuel.getGlobalBounds().left + spritePersoActuel.getGlobalBounds().width + ESPACE*2
							, rectStats[0].getGlobalBounds().top + (rectStats[0].getGlobalBounds().height/2 - rectStats[7].getGlobalBounds().height/2));
	rectStats[6].setPosition( rectStats[7].getGlobalBounds().left - ESPACE
	 						, rectStats[7].getGlobalBounds().top + rectStats[7].getGlobalBounds().height - ESPACE);

	stringstream ss;
	ss << (*_ite_l)->get_strength();
	textStats[1].setString( ss.str() ); textStats[6].setString( "Force" );
	ss.str(string()); ss << (*_ite_l)->get_accuracy();
	textStats[2].setString( ss.str() ); textStats[7].setString( "Precision" );
	ss.str(string()); ss << (*_ite_l)->get_endurance();
	textStats[3].setString( ss.str() ); textStats[8].setString( "Endurance" );
	ss.str(string()); ss << (*_ite_l)->get_agility();
	textStats[4].setString( ss.str() ); textStats[9].setString( "Agilité" );
	ss.str(string()); ss << (*_ite_l)->get_luck();
	textStats[5].setString( ss.str() ); textStats[10].setString( "Chance" );



	rectStats[1].setPosition( rectStats[7].getGlobalBounds().left + ESPACE,
							  rectStats[6].getGlobalBounds().top - rectStats[1].getGlobalBounds().height);
	textStats[1].setScale(game->_scaleBouton, game->_scaleBouton);
	textStats[1].setPosition( rectStats[1].getGlobalBounds().left + rectStats[1].getGlobalBounds().width/2 - textStats[1].getGlobalBounds().width/2
							, rectStats[1].getGlobalBounds().top + rectStats[1].getGlobalBounds().height/2 - textStats[1].getGlobalBounds().height/2);
	textStats[6].setScale(game->_scaleBouton, game->_scaleBouton);
	textStats[6].setPosition( rectStats[1].getGlobalBounds().left + rectStats[1].getGlobalBounds().width/2 - textStats[6].getGlobalBounds().width/2
							, rectStats[1].getGlobalBounds().top - ESPACE);
	for(int i = 2 ; i <= 5 ; i++){
		rectStats[i].setPosition( rectStats[i - 1].getGlobalBounds().left + rectStats[i - 1].getGlobalBounds().width + ESPACE*2
								, rectStats[6].getGlobalBounds().top - rectStats[i].getGlobalBounds().height );
		textStats[i].setScale(game->_scaleBouton, game->_scaleBouton);
		textStats[i].setPosition( rectStats[i].getGlobalBounds().left + rectStats[i].getGlobalBounds().width/2 - textStats[i].getGlobalBounds().width/2
								, rectStats[i].getGlobalBounds().top + rectStats[i].getGlobalBounds().height/2 - textStats[i].getGlobalBounds().height/2);
		textStats[i + 5].setScale(game->_scaleBouton, game->_scaleBouton);
		textStats[i + 5].setPosition( rectStats[i].getGlobalBounds().left + rectStats[i].getGlobalBounds().width/2 - textStats[i + 5].getGlobalBounds().width/2
	 								, rectStats[i].getGlobalBounds().top - ESPACE);
	}
}

void Partie::UpdateMenuQuitter(IHMmanager*game){
	textMenuQuitter.setScale(game->_scaleBouton, game->_scaleBouton);

	menuQuitter.setSize(Vector2f(textMenuQuitter.getGlobalBounds().width + ESPACE*2
							   , textMenuQuitter.getGlobalBounds().height + 100*game->_scaleBouton));
	boutonOui.setScale(game->_scaleBouton, game->_scaleBouton);
	boutonNon.setScale(game->_scaleBouton, game->_scaleBouton);
	textOui.setScale(game->_scaleBouton, game->_scaleBouton);
	textNon.setScale(game->_scaleBouton, game->_scaleBouton);

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
	int i = 0;
	if(fenetreActive == 1){
		game->get_myWindow()->draw(rectInvent);
		for(Text t : textInvent) game->get_myWindow()->draw(t);
		for(Sprite s : spriteInvent) game->get_myWindow()->draw(s);
	} else if(fenetreActive == 2){
		game->get_myWindow()->draw(menuCarte);
		game->get_myWindow()->draw(spriteWorld);
	} else if(fenetreActive == 3){
		for(i = 0 ; i < nbRectStats ; i++) {
			game->get_myWindow()->draw(rectStats[i]);
		}
		game->get_myWindow()->draw(spritePersoActuel);
		for(i = 0 ; i < nbtextStats ; i++) {
			game->get_myWindow()->draw(textStats[i]);
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
			if(_mapCurrent.get_IDin(i, j) == 1) (*itelistSquareMap).setFillColor(Color(128,128,128));
			if(_mapCurrent.get_IDin(i, j) == 4) (*itelistSquareMap).setFillColor(Color::Blue);
			game->get_myWindow()->draw((*itelistSquareMap));
			itelistSquareMap++;
		}
	}
	Sprite tpsSprite;
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
		for(list<Hero*>::iterator th = _team_hero.begin() ; th != _team_hero.end() ; th++){
			(*th)->set_sprite(t);
			tpsSprite = (*th)->get_sprite();
			tpsSprite.setScale(_mapCurrent._zoom, _mapCurrent._zoom);
			tpsSprite.setPosition(_mapCurrent._origXmap + 64*(_mapCurrent._zoom)*(*th)->get_x()
								, _mapCurrent._origYmap - _mapCurrent._zoom*64 - 64*(_mapCurrent._zoom)*(*th)->get_y() );
			game->get_myWindow()->draw(tpsSprite);
			Text nom((*th)->get_name(), font, _mapCurrent._zoom*8);
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



void Partie::savePartie(void){
	Fichier f("src\\Save.txt",1);
	f.updateSave( _mapCurrent.get_nameMap(),
				  _tank_hero,
				  _tank_portail_close);
}

/** La méthode switchMap permet de changer de carte actuel à partir des données fourni par le
  * portail p
  	  * @param p - portail où le joueur se situe qui engendre le changement de carte*/
void Partie::switchMap( Portail p , bool ban){
	cout << " on veux charger cette map " << p.get_nameNextMap() << endl;
	premiereApparition = true;
	_mapCurrent.removeAllItem();							// on retire tous le monde de la carte sans toucher au conteneur
	Fichier pathMap("src\\World.txt",0);					// chargement de la prochaine map
	//Fichier pathSave("src\\Save.txt",1);					// chargement de la Save
	//cout << "chargement de la map" << endl;
	pathMap.loadMap(p.get_nameNextMap(), _mapCurrent, _tank_ennemi, _tank_hero, _tank_obstacle, _tank_portail);


	//_mapCurrent.display();
	_mapCurrent.removeAllItem();
	// ajout des ennemis sur la carte
	for(_ite_e = _tank_ennemi.begin();_ite_e!=_tank_ennemi.end();_ite_e++){
		_mapCurrent.addItem((*_ite_e));
	}

	// ajout des obstacles sur la carte
	for(_ite_o=_tank_obstacle.begin();_ite_o!=_tank_obstacle.end();_ite_o++){
		_mapCurrent.addItem((*_ite_o));
	}
	// ajout des portail sur la carte
	for(_ite_p=_tank_portail.begin();_ite_p!=_tank_portail.end();_ite_p++)
	{
		/*//todo
		if(_tank_portail_close.size()!=0)
		{
			for(list<Portail>::iterator itep=_tank_portail_close.begin(); itep!=_tank_portail_close.end();itep++ )
			{
				if( !((*_ite_p).get_x()==(*itep).get_x() && ((*_ite_p).get_y()==(*itep).get_y())))
				{
					_mapCurrent.addItem((*_ite_p));
				}
				else
				{
					cout << " ce portail:";
					(*_ite_p).display();
					cout<<" est le meme que celui ci";
					(*itep).display();
				}
			}
		}
		else
		{
			_mapCurrent.addItem((*_ite_p));
		}
		*/
		//(*_ite_p).display();
		_mapCurrent.addItem((*_ite_p));
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
		/*
		if(ban==true)
		{
			list<Portail>::iterator tmpp;
			for(_ite_p=_tank_portail.begin();_ite_p!=_tank_portail.end();_ite_p++)
			{
				if(((*_ite_h).distance((*_ite_p)))==1)
				{
					_tank_portail_close.push_front((*_ite_p));
					tmpp==_ite_p;
					(*_ite_p).display();
					_mapCurrent.removeItem((*_ite_p));
				}
			}
			//_tank_portail.remove((*tmpp));
		}
		*/
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

	cout << "SAUVEGARDE ATTENTION " << endl;
	cout << "car : " << _mapCurrent.get_nameMap() << endl;
	if(_mapCurrent.get_nameMap() == "checkpoint"){
		cout << " ... sauvegarde en cours" << endl;
		savePartie();
	}

}



/** La méthode fightMode définit le mode combat du jeu
  * */
/*
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
				for(_ite=_team_hero.begin();_ite!=_team_hero.end();_ite++){
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
					cout<<"me deplacer"<<endl;
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
*/
/*
#define DEPLACER 1
#define TIRER 2
#define RECHARGER 3
#define CC 4
#define BONUS 5
#define CHANGER 6
*/
/** La méthode allieTour définit le tour de l'allié et indique si c'est la fin du tour
 	 * @param &endTour - adresse du booléen qui indique si c'est la fin du tour ou pas
 	 * */
/*
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
*/
/** La méthode main_switch invite le joueur à choisir une action à faire
 	 * @return elle retourne le choix saisit par le joueur
 	 * */
/*
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
*/
/** La méthode move_choice gère le déplacement du héros en action dans le tour.
 	 * @param withUsePA - boolean qui indique si le mouvement consomme des PA.
 	 * @return elle retourne -1 si on annule l'action
	 * 						  0 si le déplacement est impossible
	 * 						  1 si le déplacement a fonctionné
	 * 						  2 si le déplacement engendre un changement de carte
 	 * */
/*
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
*/
/** La méthode move_switch invite le joueur à choisir le déplacement à faire
 	 * @return elle retourne le choix saisit par le joueur
 	 * */
/*
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
*/
/** La méthode shoot_choice gère le système de tir à distance du héros en action dans le tour.
 	 * @return elle retourne "vrai" si il n'y a plus d'ennemis et "false" sinon
 	 * */
/*
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
*/
/** La méthode close_combat_choice gère le système de tir au càc du héros en action dans le tour.
 	 * @return elle retourne "vrai" si il n'y a plus d'ennemis et "false" sinon
 	 * */
/*
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
				return (false);
			}
		}
		return (false);
	}
	else
	{
		return (false);
	}
}
*/
/** La méthode end_team indique si la team à fini son tour
 	 * @return elle retourne "vrai" si c'est le cas et "false" sinon
 	 * */
/*
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
*/

// le destructeur
Partie::~Partie() {
	cout << " - Partie detruite " << endl;
}

