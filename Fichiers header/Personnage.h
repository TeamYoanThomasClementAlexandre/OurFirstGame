#ifndef __PERSONNAGE_H__
#define __PERSONNAGE_H__

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Window\VideoMode.hpp>


using namespace std;
using namespace sf;
class Personnage 
{
private:
	

public:
	// ajouter un id;
	Personnage(std::string type);
	std::string afficher();
	Personnage();
	char* id;
	void setCarac();
	int vie;
	int range;
	int degat;
	int armure;
	int deplacement;
	int deplacementRestante;
	int vieRestante;
	std::string type;
	sf::Vector2i position;
	sf::Vector2i appartenance;


};

#endif
