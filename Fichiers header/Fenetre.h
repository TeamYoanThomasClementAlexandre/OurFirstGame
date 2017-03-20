#ifndef __FENETRE_H__
#define __FENETRE_H__

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Window\VideoMode.hpp>
#include "Rectangle.h"
using namespace std;
using namespace sf;
class Fenetre : public sf::RenderWindow
{
private:
	std::string titre;
	int tailleFenetreAccueilX;
	int tailleFenetreAccueilY;
	sf::VideoMode Mode;
	//std::vector<Rectangle>choixJeu;// tous les carré de choix

public:
	Fenetre(int tailleFenetreAccueilX, int tailleFenetreAccueilY);
	~Fenetre();
	void affichageMenu();
	sf::Vector2u newScreen();

};

#endif
