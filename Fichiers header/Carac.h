#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef Carac_H
#define Carac_H


class Carac {

public:	
	Carac(float ratioX, float ratioY);
	void draw(sf::RenderWindow &fen);	
	void setPosition(float x, float y);
	void setTitle(sf::String nom);
	void setAttributs(int* attribut);
	void updateCarac();
	~Carac();

private:
	float ratioX;
	float ratioY;
	sf::VertexArray caracteristiques;
	sf::Text desc[6];
	sf::Text attributs[4];
	sf::Font police;
	int attrib[4];
	int tailleAttributs;
};


#endif  
