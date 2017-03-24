#ifndef __CASE_H__
#define __CASE_H__

#include <SFML/Graphics.hpp>
#include "Terrain.h"

class Case
{
private:
	

public:	Case(sf::Sprite s);
	~Case();
	int who;
	Terrain* terrain;
	sf::Sprite sprite;

};

#endif  
