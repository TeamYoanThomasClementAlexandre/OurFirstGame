#include "..\Fichiers header\FenetreYoan.h"
/*Fenetre* game = new Fenetre();
	Carte* map=game->load();
	game->idle(map);*/
#include <SFML\Window\Event.hpp>

#include <iostream>

#include "..\Fichiers header\Carte.h"
#include "..\Fichiers header\Case.h"
#include "..\Fichiers header\Terrain.h"
#include "..\Fichiers header\Fichier.h"

#define MAXI 16 //1280 1024
#define MAXJ 34

#define TAILLESPRITE_X 78
#define TAILLESPRITE_Y 45

#define TAILLEMENU_X 960

#define TAILLEDEBASEY 540
#define TAILLEMENU_Y 150


#define ECRAN_BAS (6 * 45) // decalage pour le menu du bas

using namespace std;
using namespace sf;

FenetreYoan::FenetreYoan(sf::Vector2u dimension,Personnage* p)
{
	this->create(VideoMode(dimension.x, dimension.y), "Ages of Strategies");
	this->dimension_x = dimension.x;
	this->dimension_y = dimension.y;
	this->max_x = (dimension.x / TAILLESPRITE_X)-1;
	this->max_y = ((dimension.y - ECRAN_BAS)/ TAILLESPRITE_Y)*2;

	if (this->max_x > MAXI) {
		this->max_x = MAXI;
	}
	if (this->max_y > MAXJ) {
		this->max_y = MAXJ;
	}

	this->scaleMenuBasX = (double)this->dimension_x / TAILLEMENU_X;
	this->scaleMenuBasY= ((double)this->dimension_y/(TAILLEDEBASEY/ TAILLEMENU_Y))/TAILLEMENU_Y;

	/*
	Personnage* p1 = new Personnage("archer");
	Personnage* p2 = new Personnage("archer");
	Personnage* p3 = new Personnage("archer");
	Personnage* p4 = new Personnage("archer");

	Personnage* p = new Personnage[4]; 
	p[0] = *p1;
	p[1] = *p2;
	p[2] = *p3;
	p[3] = *p4;*/

	this->personnages = p;
	//this->personnages = new Personnage[4];
	//this->personnages = personnagesConstr;
	//printf("%f,%f", scaleMenuBasX, scaleMenuBasY);
}

FenetreYoan::~FenetreYoan()
{
}

void FenetreYoan::load() {
	// 1) Chargement des resources (texture -> sprite)
	// 2) Chargement des fichiers de "niveau"



	// Todo : Recuperer tableau a 1 dimensions contenant les lettres => NOP!
	Fichier* pFichier = new Fichier();
	string textureId[MAXJ][MAXI];
	pFichier->read("../Fichiers externe/maps/map.txt", textureId);

	//
	Texture* pPlaineTexture = new Texture();
	Texture* pEauTexture = new Texture();
	Texture* pDesertTexture = new Texture();

	Texture* pPlaineTextureMin = new Texture();
	Texture* pEauTextureMin = new Texture();
	Texture* pDesertTextureMin = new Texture();

	const char* szResourcePlaine = "../Fichiers externe/img/plaine.png";
	if (!pPlaineTexture->loadFromFile(szResourcePlaine)) {
		printf("Error load sprite %s", szResourcePlaine);
	}
	const char* szResourceEau = "../Fichiers externe/img/eau.png";
	if (!pEauTexture->loadFromFile(szResourceEau)) {
		printf("Error load sprite %s", szResourceEau);
	}
	const char* szResourceDesert = "../Fichiers externe/img/desert.png";
	if (!pDesertTexture->loadFromFile(szResourceDesert)) {
		printf("Error load sprite %s", szResourceDesert);
	}
	/*  */
	const char* szResourcePlaineMin = "../Fichiers externe/img/plaine_min.png";
	if (!pPlaineTextureMin->loadFromFile(szResourcePlaineMin)) {
		printf("Error load sprite %s", szResourcePlaineMin);
	}
	const char* szResourceEauMin = "../Fichiers externe/img/eau_min.png";
	if (!pEauTextureMin->loadFromFile(szResourceEauMin)) {
		printf("Error load sprite %s", szResourceEauMin);
	}
	const char* szResourceDesertMin = "../Fichiers externe/img/desert_min.png";
	if (!pDesertTextureMin->loadFromFile(szResourceDesertMin)) {
		printf("Error load sprite %s", szResourceDesertMin);
	}

	Case*** pTableau = new Case**[this->max_y];
	Carte* pMap = new Carte();
	string s;
	for (int j = 0; j < this->max_y; j++) {
		pTableau[j] = new Case*[this->max_y];

		for (int i = 0; i < this->max_x; i++) {

			Case* pCase=NULL;
			s= textureId[j][i];
			if (s=="plaine") {

				if (i == 0 && j % 2 == 0 || j == this->max_y -1 || i == this->max_x-1) {
					Sprite *plaine = new Sprite(*pPlaineTexture);
					pCase = new Case(*plaine);
				}
				else {
					
					Sprite *plaineMin = new Sprite(*pPlaineTextureMin);
					pCase = new Case(*plaineMin);
				}
				
			}
			if (s == "eau") {
				if (i == 0 && j % 2 == 0 || j == this->max_y - 1 || i == this->max_x - 1) {
					Sprite *eau = new Sprite(*pEauTexture);
					pCase = new Case(*eau);
				}
				else {
					Sprite *EauMin = new Sprite(*pEauTextureMin);
					pCase = new Case(*EauMin);
				}
			}
				
			
			if (s=="desert") {
				if (i == 0 && j % 2 == 0 || j == this->max_y - 1 || i== this->max_x - 1) {
					
					Sprite *desert = new Sprite(*pDesertTexture);
				pCase = new Case(*desert);
				}
				else {
					Sprite *DesertMin = new Sprite(*pDesertTextureMin);
					pCase = new Case(*DesertMin);
				}
			

				}


			pTableau[j][i] = pCase;
		}
	}

	pMap->caseJeu = pTableau;
	this->map = pMap;

	// Chargement des resources
	
}

void FenetreYoan::idle() {
	Event event;
	this->clear(Color(100, 100, 100));
	this->render();
	while (this->isOpen())
	{
		while (this->pollEvent(event))
		{
			// on regarde le type de l'évènement...
			switch (event.type)
			{

			case  Event::Closed:
			this->close();
				break;
				// fenêtre fermée

				break;
			case sf::Event::Resized:

				this->dimension_x = this->getSize().x;
				this->dimension_y = this->getSize().y;
				//Sprite.Resize(60, 100);

				// touche pressée
			case sf::Event::MouseButtonPressed: 

				if (!event.mouseButton.button == sf::Mouse::Right)
				{
					/*if (map->caseJeu[11][0]->sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					printf("yu");
					}*/
					
					sf::Vector2u vec;
					this->map;
					vec=this->map->getCasebyCoord(event.mouseButton.x, event.mouseButton.y, this->max_x - 1, this->max_y - 1,this->dimension_x,this->dimension_y);
					this->map->caseJeu[vec.y][vec.x];
				}
				if (!event.mouseButton.button == sf::Mouse::Left)
				{

				}
					break;

				// on ne traite pas les autres types d'évènements
			default:
				break;
			}
			this->clear(Color(100,100,100));
			this->render();
		}
		
	}
}

void FenetreYoan::render() {

	Image * img;

	float offsetX = 0; //25;
	float offsetY = 0; //25;

	const float tileWidth = 78.0;
	const float tileWidth2 = tileWidth / 2.0;
	const float tileHeight = 23.0;
	
	// rendu case de la map 

	for (int j = 0; j <this->max_y; j++) {
		float offsetPosX = j % 2 == 0 ? offsetX : offsetX + tileWidth2;
		float offsetPosY = offsetY;
		
		for (int i = 0; i < this->max_x; i++) {
			this->map->caseJeu[j][i]->sprite.setPosition(offsetPosX + i * tileWidth, offsetPosY + j * tileHeight);
			this->map->caseJeu[j][i]->who = 0;
			this->draw(this->map->caseJeu[j][i]->sprite);
			

		}
	}
	// rendu du menu du bas
	Texture* pMenuBas = new Texture();
	const char* szResourceMenuBas = "../Fichiers externe/img/menu_bas.png";
	if (!pMenuBas->loadFromFile(szResourceMenuBas)) {
		printf("Error load sprite %s", szResourceMenuBas);
	}

	Sprite *sMenuBas = new Sprite(*pMenuBas);
	sMenuBas->setPosition(0,360);
	this->draw(*sMenuBas);
	sMenuBas->scale(this->scaleMenuBasX, this->scaleMenuBasY);

	// rendu du text
	sf::Font font;
	if (!font.loadFromFile("../Fichiers externe/arial.ttf"))
	{
		printf("Error load text :%s", font);
	}
	for (int i = 0; i < 4; i++) {
		sf::Text type;
		type.setFont(font);
		type.setCharacterSize(15);
		type.setString(this->personnages[i].type);
		type.setPosition(20, 375 + (i * 30));
		sf::Text pv;
		pv.setFont(font);
		pv.setCharacterSize(12);
		pv.setString(std::to_string(this->personnages[i].vieRestante) + "/" + std::to_string(this->personnages[i].vie));
		pv.setPosition(125, 375 + (i * 30));
		sf::Text pm;
		pm.setFont(font);
		pm.setCharacterSize(15);
		pm.setString(std::to_string(this->personnages[i].deplacementRestante) + "/" + std::to_string(this->personnages[i].deplacement));
		pm.setPosition(220, 375 + (i * 30));
		sf::Text degat;
		degat.setFont(font);
		degat.setCharacterSize(15);
		degat.setString(std::to_string(this->personnages[i].degat));
		degat.setPosition(300, 375 + (i * 30));
		sf::Text armor;
		armor.setFont(font);
		armor.setCharacterSize(15);
		armor.setString(std::to_string(this->personnages[i].armure));
		armor.setPosition(400, 375 + (i * 30));
		sf::Text range;
		range.setFont(font);
		range.setCharacterSize(15);
		range.setString(std::to_string(this->personnages[i].range));
		range.setPosition(550, 375 + (i * 30));

		

		
		std::string s = this->personnages[i].afficher();
		
		//	text.setColor(sf::Color::Red);
		this->draw(type);
		this->draw(pv);
		this->draw(pm);
		this->draw(degat);
		this->draw(armor);
		this->draw(range);
		
	}
	sf::Text name;
	name.setFont(font);
	name.setCharacterSize(15);
	name.setString("Joueur 1");
	name.setPosition(10, 520);
	this->draw(name);

	this->display();
}
