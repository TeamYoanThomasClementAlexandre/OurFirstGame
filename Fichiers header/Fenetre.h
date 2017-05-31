#ifndef __FENETRE_H__
#define __FENETRE_H__

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Window\VideoMode.hpp>
using namespace std;
using namespace sf;
class Fenetre : public sf::RenderWindow
{
private:
	std::string titre;
	std::string joueur1;
	int tailleFenetreAccueilX;
	int tailleFenetreAccueilY;
	sf::VideoMode Mode;
	sf::Vector2u taille;
	sf::Vector2u newScreen();
	

public:
	Fenetre(int tailleFenetreAccueilX, int tailleFenetreAccueilY,string joueur0);
	~Fenetre();
	int affichageMenu();
	std::string adversaireEnter();
	sf::Vector2u getTaille();
	

};

#endif
