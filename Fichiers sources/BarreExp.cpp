#pragma once
#include "..//Fichiers header/BarreExp.h"

BarreExp::BarreExp(float width,float height, float posX, float posY) {
	this->setPosition(posX,posY);
	this->setFillColor(sf::Color(0,0,0,0));
	this->setSize(sf::Vector2f(width, height));
	this->setOutlineThickness(-1);
	this->setOutlineColor(sf::Color(0, 0, 0, 255));
	police.loadFromFile("arial_black.ttf");
	pourcentageT = sf::Text("0%", police, 15);	
	pourcentageT.setPosition((width - pourcentageT.getGlobalBounds().width) / 2+posX, (height - pourcentageT.getGlobalBounds().height) / 2+posY- pourcentageT.getGlobalBounds().height/4);
	level = sf::Text("Niveau 1", police, 20);
	level.setPosition((width - level.getGlobalBounds().width) / 2 + posX, height+posY+0.1*height);

}

void BarreExp::setExp(int exp) {
	pourcentageT.setString(std::to_string(exp)+"%");
	int taille=pourcentageT.getCharacterSize();
	pourcentageT.setCharacterSize(15);
	pourcentageT.setPosition(pourcentageT.getPosition().x,pourcentageT.getPosition().y + (taille - pourcentageT.getCharacterSize())/2);	
	rectExp.setSize(sf::Vector2f(this->getGlobalBounds().width*exp /100-2, this->getGlobalBounds().height-2));
	rectExp.setPosition(this->getGlobalBounds().left+1, this->getGlobalBounds().top+1);
	rectExp.setFillColor(sf::Color::Green);

}

void BarreExp::setLvl(int lvl) {
	level.setString("Niveau " + std::to_string(lvl));
}
void BarreExp::draw(sf::RenderWindow &fen) {
	fen.draw(*this);
	fen.draw(rectExp);
	fen.draw(pourcentageT);
	fen.draw(level);
}

BarreExp::~BarreExp() {
}
