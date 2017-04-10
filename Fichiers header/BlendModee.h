#ifndef __BLENDMODEE_H__
#define __BLENDMODEE_H__

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\VideoMode.hpp>
#include <SFML\Graphics\Image.hpp>
#include <SFML/Graphics.hpp>
#include <SFML\Graphics\Color.hpp>

struct char_cmp
{
	bool operator () (const char *a, const char *b) const { return strcmp(a, b)<0; }
};

class BlendModee
{
public:
	BlendModee();
	BlendModee(std::map<char*, sf::Vector2u*,char_cmp>* dico, std::map<char*, sf::Vector2u*, char_cmp>* dicoIJ, std::map<char*, sf::Vector2u*, char_cmp>* dicoXY);
	~BlendModee();
	//sf::RenderWindow *debug;
	sf::Image image;
	std::map<char*, sf::Vector2u*,char_cmp>* dico;

	std::map<char*, sf::Vector2u*, char_cmp>* dicoPersonnagesIJ;
	std::map<char*, sf::Vector2u*, char_cmp>* dicoPersonnagesXY;
private:

	
};

#endif

