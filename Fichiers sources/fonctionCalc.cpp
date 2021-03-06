#include "..\\Fichiers header\fonctionCalc.h"
#include "..\\Fichiers header\InteractionBDD.h"
#include <SFML/Graphics.hpp>


sf::RectangleShape calcRedimension(sf::RectangleShape temp, sf::Vector2u tailleFenetre, int tailleDepartFenetreX, int tailleDepartFenetreY) {
	sf::Vector2f position;
	position = temp.getPosition();
	temp.setPosition((tailleFenetre.x / (tailleDepartFenetreX / (float)position.x)), (tailleFenetre.y / (tailleDepartFenetreY / (float)position.y)));
	position = temp.getSize();
	temp.setSize(sf::Vector2f(tailleFenetre.x / (tailleDepartFenetreX / position.x), tailleFenetre.y/ (tailleDepartFenetreY / position.y)));

	return temp;
}
bool verifNom(string joueur2) {
	InteractionBDD* interaction = InteractionBDD::Ini();
	if (interaction->exist(joueur2))
		return true;
	else
		return false;
}
