#ifndef __FENETREYOAN_H__
#define __FENETREYOAN_H__

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\VideoMode.hpp>
#include <SFML/Graphics.hpp>
#include "Carte.h"
#include "..\\Fichiers header\Personnage.h"


class FenetreYoan : public sf::RenderWindow
{
private:
	std::string titre;
	sf::VideoMode Mode;
	int max_x; // nombre max de case en x
	int max_y; //nombre max de case en y
	int dimension_x;// dimmension fenetre x
	int dimension_y;// dimmension fenetre y
	double scaleMenuBasX;
	double scaleMenuBasY;
	Carte* map;
	Personnage* personnages;

	// TODO : faire un gestionnaire des resources
	sf::Sprite sprite;

public:
	FenetreYoan(sf::Vector2u dimension,Personnage* personnages);
	~FenetreYoan();

	// Chargement des resources
	void load();

	// Boucle d'oisiveté
	void idle();

	// Fonction de rendu
	void render();
};

#endif
