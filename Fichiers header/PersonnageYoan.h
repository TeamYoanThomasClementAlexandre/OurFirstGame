#ifndef __PERSONNAGEYOAN_H__
#define __PERSONNAGEYOAN_H__

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Window\VideoMode.hpp>
#include <SFML/Graphics.hpp>
#include "..\\Fichiers header\Carte.h"
#include "..\\Fichiers header\Personnage.h"

using namespace std;
using namespace sf;
class PersonnageYoan 
{
private:
	

public:
	// ajouter un id;
	~PersonnageYoan();
	PersonnageYoan(std::string type,Personnage tested);
	std::string afficher();
	PersonnageYoan();
	char* id;
	int* getNewCaracwithCase(Carte c);
	bool * isChangeCarac(Carte c);
	int getExperiencePersonnage(int nbr_tour,bool isWin);
	void setCarac();
	int vie;
	int range;
	int degat;
	int armure;
	int deplacement;
	int deplacementRestante;
	int vieRestante;
	int vitesse_dattaque;
	std::string type;
	sf::Vector2i position;
	sf::Vector2i appartenance;
	std::string arme;
	Sprite* sarme;
	bool isdead;
	int level;
	int nbr_tue;
	float gain_xp;

};

#endif
