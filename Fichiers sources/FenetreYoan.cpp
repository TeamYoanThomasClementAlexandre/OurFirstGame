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

#define MAXI 16
#define MAXJ 34

using namespace std;
using namespace sf;

FenetreYoan::FenetreYoan()
{
	this->create(VideoMode(1280, 1024), "Ages of Strategies");
}

FenetreYoan::~FenetreYoan()
{
}

Carte* FenetreYoan::load() {
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

	Case*** pTableau = new Case**[MAXJ];
	Carte* pMap = new Carte();
	string s;
	for (int j = 0; j < MAXJ; j++) {
		pTableau[j] = new Case*[MAXJ];

		for (int i = 0; i < MAXI; i++) {

			Case* pCase=NULL;
			s= textureId[j][i];
			if (s=="plaine") {

				if (i == 0 && j % 2 == 0 || j == MAXJ-1 || i == MAXI-1) {
					Sprite *plaine = new Sprite(*pPlaineTexture);
					pCase = new Case(*plaine);
				}
				else {
					
					Sprite *plaineMin = new Sprite(*pPlaineTextureMin);
					pCase = new Case(*plaineMin);
				}
				
			}
			if (s == "eau") {
				if (i == 0 && j % 2 == 0 || j == MAXJ - 1 || i == MAXI - 1) {
					Sprite *eau = new Sprite(*pEauTexture);
					pCase = new Case(*eau);
				}
				else {
					Sprite *EauMin = new Sprite(*pEauTextureMin);
					pCase = new Case(*EauMin);
				}
			}
				
			
			if (s=="desert") {
				if (i == 0 && j % 2 == 0 || j == MAXJ - 1 || i== MAXI - 1) {
					
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
	return pMap;
	// Chargement des resources
	
}

void FenetreYoan::idle(Carte* map) {
	Event event;

	while (this->isOpen())
	{
		while (this->pollEvent(event))
		{
			if (event.type == Event::Closed) {
				this->close();
			}
		}
		this->clear();
		this->render(map);
		this->display();

	}
}

void FenetreYoan::render(Carte* map) {
	float offsetX = 0; //25;
	float offsetY = 0; //25;

	const float tileWidth = 78.0;
	const float tileWidth2 = tileWidth / 2.0;
	const float tileHeight = 23.0;
	


	for (int j = 0; j < MAXJ; j++) {
		float offsetPosX = j % 2 == 0 ? offsetX : offsetX + tileWidth2;
		float offsetPosY = offsetY;
		
		for (int i = 0; i < MAXI; i++) {
			map->caseJeu[j][i]->sprite.setPosition(offsetPosX + i * tileWidth, offsetPosY + j * tileHeight);
			this->draw(map->caseJeu[j][i]->sprite);

		}
	}
}
