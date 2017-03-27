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
	std::string type;
	int vie;
	int range;
	int degat;
	int armure;
	int deplacement;
	int deplacementRestante;
	int vieRestante;
	Personnage(std::string type);
	Personnage();
	void setCarac();



};

#endif
