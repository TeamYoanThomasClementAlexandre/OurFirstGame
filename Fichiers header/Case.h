#ifndef __CASE_H__
#define __CASE_H__

#include <SFML/Graphics.hpp>
#include "Terrain.h"

class Case
{
private:
	

public:	
	Case(sf::Sprite s,int pmCostc);
	static std::string getRealString(char c);
	~Case();
	int who;
	int pmCost;
	std::string types;
	sf::Sprite sprite;
	sf::Texture texture;

};

#endif  
