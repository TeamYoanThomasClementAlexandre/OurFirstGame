#include"..\\Fichiers header\Rectangle.h"
#include <iostream>


Rectangle::Rectangle(int posX0, int posY0, float tailleX0, float tailleY0)
{
	this->posX = posX0;
	this->posY = posY0;
	this->tailleX = tailleX0;
	this->tailleY = tailleY0;
}

Rectangle::Rectangle()
{
}
Rectangle::~Rectangle()
{
}

void Rectangle::dessinRectangle(sf::Color couleur) {
	sf::Color blanc = sf::Color(255, 255, 255);


	this->setPosition(posX, posY);
	this->setSize(sf::Vector2f(tailleX, tailleY));
	this->setOutlineThickness(2.0);
	this->setOutlineColor(blanc);
	this->setFillColor(couleur);
}
void Rectangle::jeuRectangle(sf::Color couleur2) {
	this->setPosition(posX, posY);
	this->setSize(sf::Vector2f(tailleX, tailleY));
	this->setFillColor(couleur2);

}
int Rectangle::getPositionX() {
	return posX;
}
int Rectangle::getTailleX() {
	return tailleX;
}