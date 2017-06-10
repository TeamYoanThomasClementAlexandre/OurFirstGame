#pragma once
#include "..\Fichiers header\CaracEquip.h"

CaracEquip *CaracEquip::view = NULL;

CaracEquip::CaracEquip(float width,float height) {
	this->setFillColor(sf::Color(20, 182, 227,200));
	this->setSize(sf::Vector2f(width, height));
	this->setOutlineThickness(-1);
	this->setOutlineColor(sf::Color(0, 0, 0, 50));
	this->tailleAttributs = 15.f*((width + height) / (240.f + 240.f));
	police.loadFromFile("../Fichiers externe/arial_black.ttf");
	description[0] = sf::Text("Type:",police,tailleAttributs);
	description[1] = sf::Text("Degats:", police, tailleAttributs);
	description[2] = sf::Text("Vie:", police, tailleAttributs);
	description[3] = sf::Text("Armure:", police, tailleAttributs);
	description[4] = sf::Text("Deplacement:", police, tailleAttributs*0.8);
	attributs[0] = sf::Text("", police, tailleAttributs);
	attributs[1] = sf::Text("", police, tailleAttributs);
	attributs[2] = sf::Text("", police, tailleAttributs);
	attributs[3] = sf::Text("", police, tailleAttributs);
	attributs[4] = sf::Text("", police, tailleAttributs);
	attributs[5] = sf::Text("", police, tailleAttributs);
}

CaracEquip* CaracEquip::ini(float width, float height)
{
	if (view == NULL)
		view = new CaracEquip(width,height);
	return view;
}

void CaracEquip::setAttributs(std::string* carac) {
	this->attributs[0].setString(carac[1]);
	this->attributs[1].setString(carac[0]);
	this->attributs[2].setString(carac[2]);
	this->attributs[3].setString(carac[3]);
	this->attributs[4].setString(carac[4]);
	this->attributs[5].setString(carac[5]);
}

void CaracEquip::draw(sf::RenderWindow &fen) {
	if (this->attributs[0].getString() != "") {
		attributs[0].setPosition(this->getPosition().x + (this->getGlobalBounds().width - attributs[0].getGlobalBounds().width) / 2, this->getPosition().y + this->getGlobalBounds().height*0.05);
		for (int i = 0; i < 5; i++) {
			description[i].setPosition(this->getPosition().x + 0.05*this->getGlobalBounds().width, this->getPosition().y + 0.2*this->getGlobalBounds().height + i*0.15*this->getGlobalBounds().height);
			attributs[i + 1].setPosition(description[4].getGlobalBounds().left + 1.05f*description[4].getGlobalBounds().width, description[i].getGlobalBounds().top - description[i].getGlobalBounds().height / 4.f);
		}
		fen.draw(*this);
		for (int i = 0; i < 5; i++)
			fen.draw(description[i]);
		for (int i = 0; i < 6; i++)
			fen.draw(attributs[i]);
	}
}

CaracEquip::~CaracEquip() {
	view = NULL ;
}
