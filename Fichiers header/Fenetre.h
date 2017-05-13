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

	sf::Vector2u newScreen();
	std::string adversaireEnter();

public:
	Fenetre(int tailleFenetreAccueilX, int tailleFenetreAccueilY,string joueur0);
	~Fenetre();
	void affichageMenu();
	

};

#endif
