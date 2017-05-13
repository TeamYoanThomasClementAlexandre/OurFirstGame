#pragma once
#include "..\Fichiers header\Carac.h"

Carac::Carac(float ratioX, float ratioY) {	
	this->ratioX = ratioX;
	this->ratioY = ratioY;
	caracteristiques = sf::VertexArray(sf::Quads, 4);
	caracteristiques[0].color = sf::Color(18, 154, 214);
	caracteristiques[1].color = sf::Color(24, 230, 249);
	caracteristiques[2].color = sf::Color(24, 230, 249);
	caracteristiques[3].color = sf::Color(18, 154, 214);
	caracteristiques[0].position = sf::Vector2f(30.f*ratioX, 400.f*ratioY);
	caracteristiques[1].position = sf::Vector2f(800.f*ratioX, 400.f*ratioY);
	caracteristiques[2].position = sf::Vector2f(800.f*ratioX, 1000.f*ratioY);
	caracteristiques[3].position = sf::Vector2f(30.f*ratioX, 1000.f*ratioY);
	police.loadFromFile("../Fichiers externe/arial_black.ttf");
	int tailleTitre = 30 * (ratioX+ratioY)/2;
	tailleAttributs = 28* (ratioX + ratioY) / 2;
	desc[0] = sf::Text("Caractéristiques de l'archer", police, tailleTitre);
	desc[0].setPosition(((caracteristiques[1].position.x - (desc[0].getGlobalBounds().width)))/2 + caracteristiques[0].position.x/2, ((caracteristiques[0].position.y) + (caracteristiques[1].position.y - caracteristiques[0].position.y))*ratioY);
	desc[1] = sf::Text("Dégats :", police, tailleAttributs);
	desc[2] = sf::Text("Vie :", police, tailleAttributs);
	desc[3] = sf::Text("Mouvement :", police, tailleAttributs);
	desc[4] = sf::Text("Armure :", police, tailleAttributs);
	for (int i = 1; i <= 4; i++) {
		desc[i].setPosition(caracteristiques[0].position.x+(caracteristiques[1].position.x- caracteristiques[0].position.x)*0.12f, (caracteristiques[0].position.y+ (caracteristiques[1].position.y - caracteristiques[0].position.y)*0.06f +100.f*(float)i)*ratioY);
	}	

}

void Carac::draw(sf::RenderWindow &fen) {
	fen.draw(caracteristiques);
	for (int i = 0; i < sizeof(desc) / sizeof(sf::Text); i++) 
		fen.draw(desc[i]);
	for(int i=0;i<sizeof(attributs)/sizeof(sf::Text);i++)		
		fen.draw(attributs[i]);	
}

void Carac::setAttributs(int* attribut) {
	for (int i = 0; i < 4; i++) {		
		this->attributs[i]= sf::Text(std::to_string(attribut[i]), police, tailleAttributs);
		this->attributs[i].setPosition(caracteristiques[1].position.x*0.75f, desc[i + 1].getPosition().y);
	}
}

void Carac::setPosition(float x, float y) {
	caracteristiques[0].position = sf::Vector2f(x*ratioX, y*ratioY);
	caracteristiques[1].position = sf::Vector2f((x+770.f)*ratioX, y*ratioY);
	caracteristiques[2].position = sf::Vector2f((x+770.f)*ratioX, (y+600)*ratioY);
	caracteristiques[3].position = sf::Vector2f(x*ratioX, (y + 600)*ratioY);
	desc[0].setPosition((caracteristiques[1].position.x - desc[0].getGlobalBounds().width + caracteristiques[0].position.x)/2.f, caracteristiques[0].position.y + (caracteristiques[2].position.y - caracteristiques[0].position.y)*0.05f);
	for (int i = 1; i <= 4; i++) {
		desc[i].setPosition(caracteristiques[0].position.x + (caracteristiques[1].position.x - caracteristiques[0].position.x)*0.15f, caracteristiques[0].position.y + (caracteristiques[2].position.y - caracteristiques[0].position.y)*0.15f + 90.f*(float)i*ratioY);
	}
}

void Carac::setTitle(sf::String nom) {
	desc[0].setString(nom);
}

Carac::~Carac() {
	
}
