#include"..\\Fichiers header\RectanglePerso.h"
#include <iostream>


RectanglePerso::RectanglePerso(int posX0, int posY0, float tailleX0, float tailleY0)
{
	this->posX = posX0;
	this->posY = posY0;
	this->tailleX = tailleX0;
	this->tailleY = tailleY0;
}

RectanglePerso::RectanglePerso()
{
}
RectanglePerso::~RectanglePerso()
{
}

void RectanglePerso::dessinRectangle(sf::Color couleur) {
	sf::Color blanc = sf::Color(255, 255, 255);


	this->setPosition(posX, posY);
	this->setSize(sf::Vector2f(tailleX, tailleY));
	this->setOutlineThickness(2.0);
	this->setOutlineColor(blanc);
	this->setFillColor(couleur);
}
void RectanglePerso::jeuRectangle(sf::Color couleur2) {
	this->setPosition(posX, posY);
	this->setSize(sf::Vector2f(tailleX, tailleY));
	this->setFillColor(couleur2);

}
int RectanglePerso::getPositionX() {
	return posX;
}
int RectanglePerso::getTailleX() {
	return tailleX;
}