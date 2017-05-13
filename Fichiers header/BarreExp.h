
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef BARREEXP_H
#define BARREEXP_H

class BarreExp : public sf::RectangleShape {

public:	
	BarreExp(float width,float height,float posX, float posY);
	void draw(sf::RenderWindow &fen);
	void setExp(int exp);
	void setLvl(int lvl);
	~BarreExp();
	

private:
	sf::Font police;
	sf::Text pourcentageT;
	sf::Text level;
	sf::RectangleShape rectExp;
};


#endif  
