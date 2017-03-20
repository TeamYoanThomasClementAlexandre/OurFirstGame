#ifndef __FENETREYOAN_H__
#define __FENETREYOAN_H__

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\VideoMode.hpp>
#include <SFML/Graphics.hpp>
#include "Carte.h"


class FenetreYoan : public sf::RenderWindow
{
private:
	std::string titre;
	sf::VideoMode Mode;

	// TODO : faire un gestionnaire des resources
	sf::Sprite sprite;

public:
	FenetreYoan();
	~FenetreYoan();

	// Chargement des resources
	Carte* load();

	// Boucle d'oisiveté
	void idle(Carte* map);

	// Fonction de rendu
	void render(Carte* map);
};

#endif
