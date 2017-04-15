#ifndef __FENETREYOAN_H__
#define __FENETREYOAN_H__

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\VideoMode.hpp>
#include <SFML/Graphics.hpp>
#include "Carte.h"
#include "..\\Fichiers header\Personnage.h"
#include "..\\Fichiers header\Joueur.h"
#include "..\\Fichiers header\BlendModee.h"



class FenetreYoan : public sf::RenderWindow
{
private:
	std::string titre;
	sf::VideoMode Mode;
	int max_x; // nombre max de case en x
	int max_y; //nombre max de case en y
	int dimension_x;// dimmension fenetre x
	int dimension_y;// dimmension fenetre y
	double scaleMenuBasX; // % menu bas x
	double scaleMenuBasY; // % menu haut y
	Carte* map; // map du jeu
	int joueur; // tour de quelle joueur
	Event event; // evenement
	Joueur* players; // tableau de joueur
	sf::RenderWindow *debug; // debug blendmode
	BlendModee bm; // blendmode 
	Sprite* sPersonnage; // contient les 4 sprites de personnages
	sf::Text* tablo_text; // contient les Texts de la vue
	int nbr_tour;
	bool findutour;
	bool brouillard_de_guerre;
	sf::Vector2u* tabDeplacement;
	bool map_clicked;
	Vector2u map_clicked_ij;

	// TODO : faire un gestionnaire des resources
	sf::Sprite sprite;
public:
	FenetreYoan(sf::Vector2u dimension, Joueur* players);
	~FenetreYoan();

	void controleur_placement(Event event);
	void controleur_game(Event event);


	
	bool verifContrainte(sf::Vector2u* vec,char* s); // verif contrainte de positionnement perso
	Sprite getSpritebyname(std::string str);

	void load(); // charge les sprites
	void idle(); // instructions principales
	void PlacementPersonnage(); // boucle de placement
	void Game(); // boucle de jeu
	bool isWin(); // c'est gagné ?

	void player_choice(); // affiche cercle de choix perso

	void render(); // affiche vue placement
	void renderView(); // affiche vue in game
	void renderTexte(); // affiche les textes
	void renderTexteView(); // affiche les textes
	Sprite* autre;
	
	
};

#endif
