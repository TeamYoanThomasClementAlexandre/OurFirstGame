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
	bool brouillard_de_guerre;

	// TODO : faire un gestionnaire des resources
	sf::Sprite sprite;
public:
	void controleur_placement(Event event);
	FenetreYoan(sf::Vector2u dimension,Joueur* players);
	~FenetreYoan();
	bool verifContrainte(int x,int y);
	Sprite getSpritebyname(std::string str);
	void Game();

	// Chargement des resources
	void load();
	
	void PlacementPersonnage();

	// Boucle d'oisiveté
	void idle();

	void player_choice();

	// Fonction de rendu
	void render();
	void renderView(); // affiche vue in game
	void renderTexte();
};

#endif
