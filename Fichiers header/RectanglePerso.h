#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <SFML\Graphics\RectangleShape.hpp>
class RectanglePerso : public sf::RectangleShape
{
private:
	std::string titre;
	float tailleX;
	float tailleY;
	int posX;
	int posY;

public:
	RectanglePerso(int posX0,int posY0, float tailleX0,float tailleY0);
	RectanglePerso();
	~RectanglePerso();
	void dessinRectangle(sf::Color couleur);
	void jeuRectangle(sf::Color couleur);
	int getPositionX();
	int getTailleX();
};

#endif