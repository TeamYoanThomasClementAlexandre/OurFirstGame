#include "..\Fichiers header\FenetreYoan.h"
#include <SFML\Window\Event.hpp>

#include <iostream>

#include "..\Fichiers header\Carte.h"
#include "..\Fichiers header\Case.h"
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

FenetreYoan::FenetreYoan(sf::Vector2u dimension,Joueur* playerss)
{
	// ini case map cliqued
	Vector2u *vec1 = new Vector2u();
	vec1->x = 0;
	vec1->x = 0;
	this->map_clicked_ij = *vec1;

	// ini tableau de coordonné de surbrillance pour se deplacer + tab info
	int**tabCostt = new int*[8];
	for (int i = 0; i < 8; i++) {
		int* tab = new int[10];
		tabCostt[i] = tab;
		for (int j = 0; j < 10; j++) {
			tabCostt[i][j] = 100 ;
		}
		
	}
	this->tabCost = tabCostt;
	Vector2u** vecc = new Vector2u*[8];
	for (int i = 0; i < 8; i++) {
		Vector2u* vec = new Vector2u[10];
		vecc[i] = vec;
		for (int j = 0; j < 10; j++) {
			vecc[i][j].x = 100;
			vecc[i][j].y = 100;
		}

	}
	this->tabDeplacement = vecc;


	this->setFramerateLimit(30); // limit framerate
	// ini brouillard placement
	this->brouillard_de_guerre = true;

	//ini compte a rebour nbr tour
	this->nbr_tour = 0;
	// ini text
	sf::Font *font= new Font();
	if (!font->loadFromFile("../Fichiers externe/arial.ttf"))
	{
		printf("Error load text :%s", font);
	}
	//
	sf::Text* tablo_texte= new sf::Text[5];
	this->tablo_text = tablo_texte;
	for (int i = 0; i < 5; i++) {
		tablo_text[i].setCharacterSize(20);
		tablo_text[i].setFont(*font);
		tablo_text[i].setString("");
	}

	// DEBUG
	sf::RenderWindow *window = new RenderWindow(sf::VideoMode(960, 540), "Debug Window", sf::Style::Titlebar);
	this->debug = window;
	this->debug->setPosition(sf::Vector2i(0, 0));
	//

	// choix joueur aleatoirement  // FIX EN FONCTION DE LA VITESSE DATTAQUE DES DEUX JOUEUR
	srand(time(NULL));
	this->joueur= rand() % 2;
	//

	// parametrage fenetre de jeu
	this->create(VideoMode(dimension.x, dimension.y), "Ages of Strategies",sf::Style::Titlebar);
	this->setFramerateLimit(60); // limité a 60fps
	this->setPosition(sf::Vector2i(960, 0));
	this->dimension_x = dimension.x;
	this->dimension_y = dimension.y;
	this->max_x = (dimension.x / TAILLESPRITE_X)-1;
	this->max_y = ((dimension.y - ECRAN_BAS)/ TAILLESPRITE_Y)*2;
	//
	// variable pour multi resolution 
	if (this->max_x > MAXI) {
		this->max_x = MAXI;
	}
	if (this->max_y > MAXJ) {
		this->max_y = MAXJ;
	}

	this->scaleMenuBasX = (double)this->dimension_x / TAILLEMENU_X;
	this->scaleMenuBasY= ((double)this->dimension_y/(TAILLEDEBASEY/ TAILLEMENU_Y))/TAILLEMENU_Y;
	//

	// Initialisation des Joueurs
	this->players= playerss;
	Personnage* p_good = new Personnage[4];
	Personnage* p_good2 = new Personnage[4];
	for (int i = 0; i < 4; i++) {
		Personnage *p = new Personnage("constr");
		p_good[i] = *p;
		p_good2[i] = *p;
	}
	this->players[0].p_placer = p_good;
	this->players[1].p_placer = p_good2;

	//Initialisation de la map virtuel
		std::map<char*, sf::Vector2u*,char_cmp> *dicoo = new std::map<char*, sf::Vector2u*,char_cmp>;
		std::map<char*, Personnage*, char_cmp> *dicooIJ = new std::map<char*, Personnage*, char_cmp>;
		BlendModee *bmm = new BlendModee(dicoo, dicooIJ);
		this->bm = *bmm;

		//Initialisation des personnages 
		Sprite* sPerso = new Sprite[4];
		this->sPersonnage = sPerso;

}
Sprite FenetreYoan::getSpritebyname(std::string str) {

	if (str == "archer") {
		return this->sPersonnage[0];
	}
	else if (str == "epeiste") {
		return this->sPersonnage[1];
	}
	else if (str == "lancier") {
		return this->sPersonnage[3];
	}
	else if (str == "paladin") {
		return this->sPersonnage[2];
	}

}
bool FenetreYoan::verifContrainte(sf::Vector2u *vec, char* s) {
	
	if (vec == NULL) {
		Personnage* perso = (*(this->bm.dicoPersonnagesIJ))[s];
		if (perso != NULL) {
			this->tablo_text[1].setString("Action Impossible, Unité déjà présente !");
		}
		else {
			this->tablo_text[1].setString("Action Impossible, Hors map !");
		}
		this->clear(Color(100, 100, 100));
		this->render();
		return false;
	}

	if (this->joueur == 0 && vec->x > 4) {
		this->tablo_text[1].setString("Action Impossible, Spawn ennemi !");
		this->clear(Color(100, 100, 100));
		this->render();
		return false;
	}
	if (this->joueur == 1 && vec->x < 6) {
		this->tablo_text[1].setString("Action Impossible, Spawn ennemi !");
		this->clear(Color(100, 100, 100));
		this->render();
		return false;
	}

		if (this->map->caseJeu[vec->y][vec->x]->who != -1) {
			this->tablo_text[1].setString("Action Impossible,Unité déjà présente!");
			this->clear(Color(100, 100, 100));
			this->render();
			return false;
		}
		std::string str = this->map->caseJeu[vec->y][vec->x]->types;
		if (str == "eau") {
			this->tablo_text[1].setString("Action Impossible, Case eau selectionné !");
			this->clear(Color(100, 100, 100));
			this->render();
			return false;
		
	}
	
	return true;
}

void FenetreYoan::controleur_placement(Event event) {

		if (event.mouseButton.button == sf::Mouse::Left) //
		{
			Color c;
			if (event.mouseButton.x != NULL && event.mouseButton.y != NULL) {
				c = this->bm.image.getPixel(event.mouseButton.x, 540 - event.mouseButton.y);
			}
			
			char* s = new char[10];
			memset(s, 0, 10);
			sprintf_s(s, 10, "%00d%00d%00d\0",c.r, c.g, c.b);
			sf::Vector2u* vec = (*(this->bm.dico))[s];
			
			if (this->players[this->joueur].selected != -1 && this->verifContrainte(vec,s) ) {
				this->tablo_text[1].setString("");
			//	printf("joueur %d personnage %d sur la case (%d,%d)", this->joueur, this->players[this->joueur].selected, vec->y, vec->x);
				this->players[this->joueur].p_placer[this->players[this->joueur].personnage_placer] = this->players[this->joueur].p[this->players[this->joueur].selected]; //placer le personnage dans le tab de perso placer;
				this->map->caseJeu[vec->y][vec->x]->who = this->joueur;
				this->players[this->joueur].p_placer[this->players[this->joueur].personnage_placer].position.x = vec->x;
				this->players[this->joueur].p_placer[this->players[this->joueur].personnage_placer].position.y = vec->y;
				this->players[this->joueur].p_placer[this->players[this->joueur].personnage_placer].appartenance.x = this->joueur;
				this->players[this->joueur].p_placer[this->players[this->joueur].personnage_placer].appartenance.y = this->players[this->joueur].personnage_placer;

				this->players[this->joueur].personnage_placer++;
			}
			this->players[this->joueur].selected = -1;
			this->clear(Color(100, 100, 100));
			this->render();

		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			//printf("%d , %d\n", event.mouseButton.x, event.mouseButton.y);
			if (event.mouseButton.x > 7 && event.mouseButton.x < 714 && event.mouseButton.y >= 370 && event.mouseButton.y<400) {
				this->players[this->joueur].selected = 0;
			}
			else if (event.mouseButton.x > 7 && event.mouseButton.x < 714 && event.mouseButton.y >= 400 && event.mouseButton.y < 430) {
				this->players[this->joueur].selected = 1;
			}
			else if (event.mouseButton.x > 7 && event.mouseButton.x < 714 && event.mouseButton.y >= 430 && event.mouseButton.y < 460) {
				this->players[this->joueur].selected = 2;
			}
			else if (event.mouseButton.x > 7 && event.mouseButton.x < 714 && event.mouseButton.y >= 460 && event.mouseButton.y < 490) {
				this->players[this->joueur].selected = 3;
			}
			/*
			else {
			sur une case ou il y a un personnage alors ça le retire 
			}
			*/
			this->clear(Color(100, 100, 100));
			this->render();
			}
	
	
}



FenetreYoan::~FenetreYoan()
{
}

void FenetreYoan::load() {
	//initialisation des autres sprites utiles

	Sprite* tabSprite = new Sprite[10];
	this->autre = tabSprite;
	Texture* pFindutourTexture = new Texture();

	const char* szResourceFindutour = "../Fichiers externe/img/findutour.png";
	if (!pFindutourTexture->loadFromFile(szResourceFindutour)) {
		printf("Error load sprite %s", szResourceFindutour);
	}
	Sprite *findutour = new Sprite(*pFindutourTexture);
	this->autre[0] = *findutour;

	// recuperation map

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
					pCase = new Case(*plaine,1);
					pCase->texture = *pPlaineTexture;
				}
				else {
					
					Sprite *plaineMin = new Sprite(*pPlaineTextureMin);
					pCase = new Case(*plaineMin,1);
					pCase->texture = *pPlaineTextureMin;
				}
			
			}
			if (s == "eau") {
				if (i == 0 && j % 2 == 0 || j == this->max_y - 1 || i == this->max_x - 1) {
					Sprite *eau = new Sprite(*pEauTexture);
					pCase = new Case(*eau,100);
					pCase->texture = *pEauTexture;
				}
				else {
					Sprite *EauMin = new Sprite(*pEauTextureMin);
					pCase = new Case(*EauMin,100);
					pCase->texture = *pPlaineTextureMin;
				}
			}
				
			
			if (s=="desert") {
				if (i == 0 && j % 2 == 0 || j == this->max_y - 1 || i== this->max_x - 1) {
					
					Sprite *desert = new Sprite(*pDesertTexture);
				pCase = new Case(*desert,2);
				pCase->texture = *pDesertTexture;
				}
				else {
					Sprite *DesertMin = new Sprite(*pDesertTextureMin);
					pCase = new Case(*DesertMin,2);
					pCase->texture = *pDesertTextureMin;
				}
			

				}
			pCase->types = s;

			pTableau[j][i] = pCase;
		}
	}

	pMap->caseJeu = pTableau;
	this->map = pMap;



	// Chargement des resources PERSONNAGES
	Texture* pArcherTexture = new Texture();
	Texture* pEpeisteTexture = new Texture();
	Texture* pPaladinTexture = new Texture();
	Texture* pLancierTexture = new Texture();

	const char* szResourceArcher = "../Fichiers externe/img/archer.png";
	if (!pArcherTexture->loadFromFile(szResourceArcher)) {
		printf("Error load sprite %s", szResourceArcher);
	}
	const char* szResourceEpeiste = "../Fichiers externe/img/epeiste.jpg";
	if (!pEpeisteTexture->loadFromFile(szResourceEpeiste)) {
		printf("Error load sprite %s", szResourceEpeiste);
	}
	const char* szResourcePaladin = "../Fichiers externe/img/paladin.jpg";
	if (!pPaladinTexture->loadFromFile(szResourcePaladin)) {
		printf("Error load sprite %s", szResourcePaladin);
	}
	const char* szResourceLancier = "../Fichiers externe/img/lancier.jpg";
	if (!pLancierTexture->loadFromFile(szResourceLancier)) {
		printf("Error load sprite %s", szResourceLancier);
	}
	Sprite *sArcher = new Sprite(*pArcherTexture);
	Sprite *sEpeiste = new Sprite(*pEpeisteTexture);
	Sprite *sPaladin = new Sprite(*pPaladinTexture);
	Sprite *sLancier = new Sprite(*pLancierTexture);

	this->sPersonnage[0] = *sArcher;
	this->sPersonnage[1] = *sEpeiste;
	this->sPersonnage[2] = *sPaladin;
	this->sPersonnage[3] = *sLancier;
}

void FenetreYoan::idle() {	
	this->PlacementPersonnage();
	this->joueur = (this->joueur == 0) ? 1 : 0;
	this->PlacementPersonnage();
	this->nbr_tour++;
	this->players[0].selected = -1;
	this->players[1].selected = -1;
	while (1) {
		this->joueur = (this->joueur == 0) ? 1 : 0;

		for (int i = 0; i < 4; i++) {
			this->players[this->joueur].p_placer[i].deplacementRestante = this->players[this->joueur].p_placer[i].deplacement; // reinitialisation pm des persos du joueur
		}

		this->Game();

		this->joueur = (this->joueur == 0) ? 1 : 0;

		for (int i = 0; i < 4; i++) {
			this->players[this->joueur].p_placer[i].deplacementRestante = this->players[this->joueur].p_placer[i].deplacement; // reinitialisation pm des persos du joueur
		}

		this->Game();
		if (this->isWin()) {
			printf("Un joueur à gagné");
			return;
		}
		this->nbr_tour++;


	}

	/* game ( methode ou on verifie click et recupere i,j =>
	si c'est une unité =>
	- on afficher dans le carre le sprite de l'unité + sur quelle case elle est
	- on affiche les deplacement possible autour d'elle si il lui reste des pm ;
	- on surligne en bas sur l'unité

	si cest la case =>
	- on affiche la case dans le carre
	- si auparavant on a cliquer sur une unité elle se deplacera 
	*/
}

void FenetreYoan::PlacementPersonnage() {
	this->clear(Color(100, 100, 100));
	this->render();
	//Personnage** persos = new Personnage*[2]; // tableau de perso a remplir 
	while (1) {

		while (this->pollEvent(this->event))
		{
			this->controleur_placement(this->event);
		}

		if (this->players[this->joueur].personnage_placer == 4) {
			printf("Joueur %d, a terminer de placer !", this->joueur + 1);
			return;
		}
	}

	return;
}

void FenetreYoan::Game() {
	this->map_clicked = false;
	this->findutour = false;
	this->clear(Color(50, 50, 50));
	this->renderView();
	while (1) {
		while (this->pollEvent(this->event))
		{
			this->controleur_game(this->event);
		}

		if (this->findutour) {
			printf("Fin du tour de joueur %d !\n", this->joueur);
			this->findutour = false;
			return;
		}
	}
}


void FenetreYoan::controleur_game(Event event)
{
	if (event.mouseButton.button == sf::Mouse::Left) //
	{
		if (event.mouseButton.x > 870 && event.mouseButton.x < 960 && event.mouseButton.y >= 515 && event.mouseButton.y < 535) {
			this->findutour = true;
		}
		Color c;
		if (event.mouseButton.x != NULL && event.mouseButton.y != NULL) {
			c = this->bm.image.getPixel(event.mouseButton.x, 540 - event.mouseButton.y);

		}
		char* s = new char[10];
		memset(s, 0, 10);
		sprintf_s(s, 10, "%00d%00d%00d\0", c.r, c.g, c.b);
		sf::Vector2u* vec = (*(this->bm.dico))[s];
		Personnage* perso = (*(this->bm.dicoPersonnagesIJ))[s];
		if (vec != NULL) {
			if (this->players[this->joueur].selected != -1) {
				for (int l=0; l < 8; l++) {
					for (int k=0; k < 10; k++) { // mettre -1 dans une ancinne case
						if (this->tabDeplacement[l][k].x == vec->x && this->tabDeplacement[l][k].y == vec->y) {
							if (this->players[this->joueur].p_placer[this->players[this->joueur].selected].deplacementRestante != 0) {

								int bigx = this->players[this->joueur].p_placer[this->players[this->joueur].selected].position.x;
								int bigy = this->players[this->joueur].p_placer[this->players[this->joueur].selected].position.y;
								this->map->caseJeu[bigy][bigx]->who = -1; // permet de vider l'ancienne case

								this->players[this->joueur].p_placer[this->players[this->joueur].selected].position.x = vec->x;
								this->players[this->joueur].p_placer[this->players[this->joueur].selected].position.y = vec->y;
								//savoir de combien de case il c'est deplacer ,metre dans x;
								int x = this->tabCost[l][k];
								this->players[this->joueur].p_placer[this->players[this->joueur].selected].deplacementRestante = this->players[this->joueur].p_placer[this->players[this->joueur].selected].deplacementRestante - x;
								this->map->caseJeu[vec->y][vec->x]->who = this->joueur;
								}
							}
						}
					}
				}
			else {

				this->players[this->joueur].selected = -1;
				this->map_clicked = true;
				this->map_clicked_ij.x = vec->x;
				this->map_clicked_ij.y = vec->y;
			}
		}
		else if (perso != NULL) {
			if (perso->appartenance.x == this->joueur) {
				this->players[this->joueur].selected = perso->appartenance.y;
				Vector2u v;
				v.x = perso->position.x;
				v.y = perso->position.y;

				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 10; j++) {
						this->tabDeplacement[i][j].x = 100;
						this->tabDeplacement[i][j].y = 100;
					}

				}
				//printf("position perso (%d,%d)\n", v.x, v.y);
				this->map->getCasesForDeplacementRecursifNord(this->tabDeplacement[0], this->tabCost[0], v, perso->deplacementRestante, perso->deplacementRestante, 0);
				this->map->getCasesForDeplacementRecursifSud(this->tabDeplacement[1], this->tabCost[1], v, perso->deplacementRestante, perso->deplacementRestante, 0);
				this->map->getCasesForDeplacementRecursifEst(this->tabDeplacement[2], this->tabCost[2], v, perso->deplacementRestante, perso->deplacementRestante, 0);
				this->map->getCasesForDeplacementRecursifOuest(this->tabDeplacement[3], this->tabCost[3], v, perso->deplacementRestante, perso->deplacementRestante, 0);

				this->map->getCasesForDeplacementRecursifNordOuest(this->tabDeplacement[4], this->tabCost[4], v, perso->deplacementRestante, perso->deplacementRestante, 0);
				this->map->getCasesForDeplacementRecursifNordEst(this->tabDeplacement[5], this->tabCost[5], v, perso->deplacementRestante, perso->deplacementRestante, 0);
				this->map->getCasesForDeplacementRecursifSudOuest(this->tabDeplacement[6], this->tabCost[6], v, perso->deplacementRestante, perso->deplacementRestante, 0);
				this->map->getCasesForDeplacementRecursifSudEst(this->tabDeplacement[7], this->tabCost[7], v, perso->deplacementRestante, perso->deplacementRestante, 0);

			}
		}
		else if (vec == NULL  && perso == NULL) {
			this->map_clicked = false;
			//printf("ni perso ni map\n");
			this->players[this->joueur].selected = -1;
		}
	}
	if (event.mouseButton.button == sf::Mouse::Right) //
	{
		
	}

	this->clear(Color(50, 50, 50));
	this->renderView();
}

bool FenetreYoan::isWin()
{
	return false;
}

void FenetreYoan::player_choice() {
	if (this->players[this->joueur].selected != -1) {
		sf::CircleShape shape(8);
		shape.setFillColor(sf::Color(74, 167, 250));
		// définit un contour orange de  10 pixels d'épaisseur
		shape.setOutlineThickness(1);
		shape.setOutlineColor(sf::Color(250, 150, 100));
		shape.setPosition(650, 377+ this->players[this->joueur].selected*30);
		this->draw(shape);
	}
}


void FenetreYoan::render() {
	
	/* SHADER */
	sf::Shader shader;

	/* if transparence return transparence else return color param*/

	const std::string fragmentShader = \
		"uniform sampler2D texture;" \
		"uniform vec3 color;" \
		"void main()" \
		"{" \
		" vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);" \
		"if(pixel.a!=0.0) { gl_FragColor = vec4(color.rgb, 1.0);  return ;  } " \
		"gl_FragColor = pixel;" \
		"}";

	// load only the fragment shader

	if (!shader.loadFromMemory(fragmentShader, sf::Shader::Fragment))
	{
		// error...
	}
	shader.setUniform("texture", sf::Shader::CurrentTexture);

	//

	// RENDU SPRITE MENU HAUT

	float offsetX = 0; //25;
	float offsetY = 0; //25;

	const float tileWidth = 78.0;
	const float tileWidth2 = tileWidth / 2.0;
	const float tileHeight = 23.0;
	
	// rendu case de la map 
	sf::RenderTexture renderTexture;
	if (!renderTexture.create(960, 540))
	{
		// erreur...
	}
	renderTexture.clear();
	

	for (int j = 0; j < this->max_y; j++) {
		float offsetPosX = j % 2 == 0 ? offsetX : offsetX + tileWidth2;
		float offsetPosY = offsetY;

		for (int i = 0; i < this->max_x; i++) {
			this->map->caseJeu[j][i]->sprite.setPosition(offsetPosX + i * tileWidth, offsetPosY + j * tileHeight);
			
				if (this->joueur == 0 && i > 4) {
					this->map->caseJeu[j][i]->sprite.setColor(Color::Black);
				}
				else if(this->joueur == 0 && i < 5) {
					this->map->caseJeu[j][i]->sprite.setColor(Color::White);
				}
				if (this->joueur == 1 && i < 6) {
					this->map->caseJeu[j][i]->sprite.setColor(Color::Black);
				}
				else if (this->joueur == 1 && i > 5) {
					this->map->caseJeu[j][i]->sprite.setColor(Color::White);
				}

			
			Sprite* a = &this->map->caseJeu[j][i]->sprite;
		
			unsigned int r = i*23;
			unsigned int g = j*12;
			unsigned int b = 100;
			
				char* s = new char[10];
				memset(s, 0, 10);
				sprintf_s(s,10,"%00u%00u%00u\0", r, g, b);
				Vector2u *v = new Vector2u();
				v->x = i;
				v->y = j;
				
				this->bm.dico->insert(std::pair<char*, sf::Vector2u*>(s,v));

			float fr =(float)r / 255.0;
			float fg = (float)g / 255.0;
			float fb = (float)b / 255.0;
			shader.setUniform("color", Glsl::Vec3(fr, fg, fb));
			RenderStates rs(&shader);
			renderTexture.draw(*a, rs); // rendu dans une texture shader
			this->draw(*a); // rendu dans une fenetre
		

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

	this->player_choice();

	// affichage des perso des joueurs
	//for(int j = 0;j<2;j++) {
		for (int i = 0; i < 4; i++) {

			// initialisation du cercle des joueur
			sf::CircleShape cerclejoueur(10);
			if (this->joueur == 1) {
				cerclejoueur.setFillColor(sf::Color(255, 0, 0, 0));
				cerclejoueur.setOutlineThickness(2);
				cerclejoueur.setOutlineColor(sf::Color(255, 0, 0));
			}
			else {
				cerclejoueur.setFillColor(sf::Color(0, 0, 255, 0));
				cerclejoueur.setOutlineThickness(2);
				cerclejoueur.setOutlineColor(sf::Color(0, 0, 255));

			}
			

			char* s = new char[10];
			memset(s, 0, 10);
			sprintf_s(s, 10, "%00d%00d%00d\0", 0, 0, 0);

			int position_x_tmp = this->players[this->joueur].p_placer[i].position.x;
			if (position_x_tmp != -1) {
				std::string name = this->players[this->joueur].p_placer[i].type;
				sf::Shader shader2;
				Sprite spriteperso = getSpritebyname(name);

				unsigned int r = 10;
				unsigned int g = 63 * ( i+1);
				unsigned int b = this->joueur * (127+1);

				char* couleurname = new char[10];
				memset(couleurname, 0, 10);
				sprintf_s(couleurname, 10, "%00d%00d%00d\0", r, g, b);


				Vector2u *v = new Vector2u();
				v->x = this->players[this->joueur].p_placer[i].position.x;
				v->y = this->players[this->joueur].p_placer[i].position.y;
				Personnage * p_tmp = &(this->players[this->joueur].p_placer[i]);
				this->bm.dicoPersonnagesIJ->insert(std::pair<char*, Personnage*>(couleurname, p_tmp));

				//char* id = new char[10];
				//id = this->players[j].p_placer[i].id;
				//sf::Vector2u* res1 = (*.(this->bm.dicoPersonnagesIJ))[id];

				float offsetPosX = this->players[this->joueur].p_placer[i].position.x % 2 == 0 ? offsetX : offsetX + tileWidth2;
				
				float offsetPosY = offsetY;
				int decalage_y_cercle = 22;
				cerclejoueur.setPosition((this->players[this->joueur].p_placer[i].position.x * 80) + 27, decalage_y_cercle + this->players[this->joueur].p_placer[i].position.y * 45);
				spriteperso.setPosition((this->players[this->joueur].p_placer[i].position.x *80)+20, this->players[this->joueur].p_placer[i].position.y *45);
				if (this->players[this->joueur].p_placer[i].position.y % 2 == 1) {
					cerclejoueur.setPosition((this->players[this->joueur].p_placer[i].position.x * 80 + 67), decalage_y_cercle + this->players[this->joueur].p_placer[i].position.y * 45 / 2);
					spriteperso.setPosition((this->players[this->joueur].p_placer[i].position.x * 80+60), this->players[this->joueur].p_placer[i].position.y * 45/2);
				}
				if (this->players[this->joueur].p_placer[i].position.y % 2 == 0) {
					cerclejoueur.setPosition((this->players[this->joueur].p_placer[i].position.x * 80) + 27, decalage_y_cercle +(this->players[this->joueur].p_placer[i].position.y / 2) * 45);
					spriteperso.setPosition((this->players[this->joueur].p_placer[i].position.x * 80) + 20, (this->players[this->joueur].p_placer[i].position.y / 2) * 45);
				}

				float fr = (float)r / 255.0; // ici arriver a trouver les 3 r g b a partir du char;
				float fg = (float)g / 255.0;
				float fb = (float)b / 255.0;
				shader.setUniform("color", Glsl::Vec3(fr, fg, fb));
				RenderStates rs(&shader);

				
				this->draw(cerclejoueur);
				this->draw(spriteperso);
				renderTexture.draw(spriteperso, rs); // rendu dans une texture shader
		//	}
		}
	}


	this->renderTexte();

	//DEBUG	
	const sf::Texture& texture = renderTexture.getTexture();
	sf::Sprite sprite(texture);
	Image *image;
	this->debug->draw(sprite);
	this->debug->display();
	this->bm.image = texture.copyToImage();
	this->display();
	
}

void FenetreYoan::renderTexte() {
	// Quell joueur
	this->tablo_text[0].setString(this->players[this->joueur].pseudo);
	this->tablo_text[0].setPosition(10, 515);
	// erreur
	this->tablo_text[1].setPosition(100, 515);
	//info supp 
	this->tablo_text[2].setPosition(300, 515);
	//nbr tour
	this->tablo_text[3].setPosition(870, 5);
	this->tablo_text[3].setString("Tour :"+std::to_string(this->nbr_tour));

	for (int i = 0; i < 4; i++) {
		this->draw(this->tablo_text[i]);
	}
	
	// rendu des infos personnages
	sf::Font font;
	if (!font.loadFromFile("../Fichiers externe/arial.ttf"))
	{
		printf("Error load text :%s", font);
	}
	for (int i = 0; i < 4; i++) {
		sf::Text type;
		type.setFont(font);
		type.setCharacterSize(15);
		type.setString(this->players[this->joueur].p[i].type);
		type.setPosition(20, 375 + (i * 30));
		sf::Text pv;
		pv.setFont(font);
		pv.setCharacterSize(12);
		pv.setString(std::to_string(this->players[this->joueur].p[i].vieRestante) + "/" + std::to_string(this->players[this->joueur].p[i].vie));
		pv.setPosition(125, 375 + (i * 30));
		sf::Text pm;
		pm.setFont(font);
		pm.setCharacterSize(15);
		pm.setString(std::to_string(this->players[this->joueur].p[i].deplacementRestante) + "/" + std::to_string(this->players[this->joueur].p[i].deplacement));
		pm.setPosition(220, 375 + (i * 30));
		sf::Text degat;
		degat.setFont(font);
		degat.setCharacterSize(15);
		degat.setString(std::to_string(this->players[this->joueur].p[i].degat));
		degat.setPosition(300, 375 + (i * 30));
		sf::Text armor;
		armor.setFont(font);
		armor.setCharacterSize(15);
		armor.setString(std::to_string(this->players[this->joueur].p[i].armure));
		armor.setPosition(400, 375 + (i * 30));
		sf::Text range;
		range.setFont(font);
		range.setCharacterSize(15);
		range.setString(std::to_string(this->players[this->joueur].p[i].range));
		range.setPosition(550, 375 + (i * 30));

		//std::string s = this->personnagesJ1[i].afficher();

		//	text.setColor(sf::Color::Red);
		this->draw(type);
		this->draw(pv);
		this->draw(pm);
		this->draw(degat);
		this->draw(armor);
		this->draw(range);

	}
	//
}

void FenetreYoan::renderTexteView() {
	// Quell joueur
	this->tablo_text[0].setString(this->players[this->joueur].pseudo);
	this->tablo_text[0].setPosition(10, 515);
	// erreur
	this->tablo_text[1].setPosition(100, 515);
	//info supp 
	this->tablo_text[2].setPosition(300, 515);
	//nbr tour
	this->tablo_text[3].setPosition(870, 5);
	this->tablo_text[3].setString("Tour :" + std::to_string(this->nbr_tour));

	for (int i = 0; i < 4; i++) {
		this->draw(this->tablo_text[i]);
	}

	// rendu des infos personnages
	sf::Font font;
	if (!font.loadFromFile("../Fichiers externe/arial.ttf"))
	{
		printf("Error load text :%s", font);
	}
	for (int i = 0; i < 4; i++) {
		sf::Text type;
		type.setFont(font);
		type.setCharacterSize(15);
		type.setString(this->players[this->joueur].p_placer[i].type);
		type.setPosition(20, 375 + (i * 30));
		sf::Text pv;
		pv.setFont(font);
		pv.setCharacterSize(12);
		pv.setString(std::to_string(this->players[this->joueur].p_placer[i].vieRestante) + "/" + std::to_string(this->players[this->joueur].p_placer[i].vie));
		pv.setPosition(125, 375 + (i * 30));
		sf::Text pm;
		pm.setFont(font);
		pm.setCharacterSize(15);
		pm.setString(std::to_string(this->players[this->joueur].p_placer[i].deplacementRestante) + "/" + std::to_string(this->players[this->joueur].p_placer[i].deplacement));
		pm.setPosition(220, 375 + (i * 30));
		sf::Text degat;
		degat.setFont(font);
		degat.setCharacterSize(15);
		degat.setString(std::to_string(this->players[this->joueur].p_placer[i].degat));
		degat.setPosition(300, 375 + (i * 30));
		sf::Text armor;
		armor.setFont(font);
		armor.setCharacterSize(15);
		armor.setString(std::to_string(this->players[this->joueur].p_placer[i].armure));
		armor.setPosition(400, 375 + (i * 30));
		sf::Text range;
		range.setFont(font);
		range.setCharacterSize(15);
		range.setString(std::to_string(this->players[this->joueur].p_placer[i].range));
		range.setPosition(550, 375 + (i * 30));

		//std::string s = this->personnagesJ1[i].afficher();

		//	text.setColor(sf::Color::Red);
		this->draw(type);
		this->draw(pv);
		this->draw(pm);
		this->draw(degat);
		this->draw(armor);
		this->draw(range);

	}
	//
}

void FenetreYoan::renderView() {
	Color *c = new Color(231, 62, 1);
	/* SHADER */
	sf::Shader shader;

	/* if transparence return transparence else return color param*/

	const std::string fragmentShader = \
		"uniform sampler2D texture;" \
		"uniform vec3 color;" \
		"void main()" \
		"{" \
		" vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);" \
		"if(pixel.a!=0.0) { gl_FragColor = vec4(color.rgb, 1.0);  return ;  } " \
		"gl_FragColor = pixel;" \
		"}";

	// load only the fragment shader

	if (!shader.loadFromMemory(fragmentShader, sf::Shader::Fragment))
	{
		// error...
	}
	shader.setUniform("texture", sf::Shader::CurrentTexture);

	//

	// RENDU SPRITE MENU HAUT

	float offsetX = 0; //25;
	float offsetY = 0; //25;

	const float tileWidth = 78.0;
	const float tileWidth2 = tileWidth / 2.0;
	const float tileHeight = 23.0;

	// rendu case de la map 
	sf::RenderTexture renderTexture;
	if (!renderTexture.create(960, 540))
	{
		// erreur...
	}
	renderTexture.clear();


	for (int j = 0; j < this->max_y; j++) {
		float offsetPosX = j % 2 == 0 ? offsetX : offsetX + tileWidth2;
		float offsetPosY = offsetY;

		for (int i = 0; i < this->max_x; i++) {
			this->map->caseJeu[j][i]->sprite.setPosition(offsetPosX + i * tileWidth, offsetPosY + j * tileHeight);
			this->map->caseJeu[j][i]->sprite.setColor(Color::White);

			if (this->players[this->joueur].selected != -1) {
				int k = 0;
				int l = 0;
				for (int l=0; l < 8; l++) {
					for (int k=0; k < 10; k++) {
						if (this->tabDeplacement[l][k].x == i && this->tabDeplacement[l][k].y == j) {
							this->map->caseJeu[j][i]->sprite.setColor(*c);
							//printf("view = %d,%d\n", tabDeplacement[l][k].x, tabDeplacement[l][k].y);
						}
					}
				}
			}
			
			Sprite* a = &this->map->caseJeu[j][i]->sprite;

			unsigned int r = i * 23;
			unsigned int g = j * 12;
			unsigned int b = 100;

			char* s = new char[10];
			memset(s, 0, 10);
			sprintf_s(s, 10, "%00u%00u%00u\0", r, g, b);
			Vector2u *v = new Vector2u();
			v->x = i;
			v->y = j;

			this->bm.dico->insert(std::pair<char*, sf::Vector2u*>(s, v));

			float fr = (float)r / 255.0;
			float fg = (float)g / 255.0;
			float fb = (float)b / 255.0;
			shader.setUniform("color", Glsl::Vec3(fr, fg, fb));
			RenderStates rs(&shader);
			renderTexture.draw(*a, rs); // rendu dans une texture shader
			this->draw(*a); // rendu dans une fenetre


		}
	}



	// rendu du menu du bas
	Texture* pMenuBas = new Texture();
	const char* szResourceMenuBas = "../Fichiers externe/img/menu_bas.png";
	if (!pMenuBas->loadFromFile(szResourceMenuBas)) {
		printf("Error load sprite %s", szResourceMenuBas);
	}

	Sprite *sMenuBas = new Sprite(*pMenuBas);
	sMenuBas->setPosition(0, 360);
	this->draw(*sMenuBas);
	sMenuBas->scale(this->scaleMenuBasX, this->scaleMenuBasY);

	this->player_choice();

	// affichage des perso des joueurs
	for(int j = 0;j<2;j++) {
	for (int i = 0; i < 4; i++) {

		// initialisation du cercle des joueur
		sf::CircleShape cerclejoueur(10);
		if (j == 1) {
			cerclejoueur.setFillColor(sf::Color(255, 0, 0, 0));
			cerclejoueur.setOutlineThickness(2);
			cerclejoueur.setOutlineColor(sf::Color(255, 0, 0));
		}
		else {
			cerclejoueur.setFillColor(sf::Color(0, 0, 255, 0));
			cerclejoueur.setOutlineThickness(2);
			cerclejoueur.setOutlineColor(sf::Color(0, 0, 255));

		}


		char* s = new char[10];
		memset(s, 0, 10);
		sprintf_s(s, 10, "%00d%00d%00d\0", 0, 0, 0);

		int position_x_tmp = this->players[j].p_placer[i].position.x;
		if (position_x_tmp != -1) {
			std::string name = this->players[j].p_placer[i].type;
			sf::Shader shader2;
			Sprite spriteperso = getSpritebyname(name);

			unsigned int r = 10;
			unsigned int g = 63 * (i+ 1);
			unsigned int b = j * (127 + 1);

			char* couleurname = new char[10];
			memset(couleurname, 0, 10);
			sprintf_s(couleurname, 10, "%00d%00d%00d\0", r, g, b);


			Vector2u *v = new Vector2u();
			v->x = this->players[j].p_placer[i].position.x;
			v->y = this->players[j].p_placer[i].position.y;
			Personnage * p_tmp = &(this->players[j].p_placer[i]);
			this->bm.dicoPersonnagesIJ->insert(std::pair<char*, Personnage*>(couleurname, p_tmp));

			float offsetPosX = this->players[j].p_placer[i].position.x % 2 == 0 ? offsetX : offsetX + tileWidth2;

			float offsetPosY = offsetY;
			int decalage_y_cercle = 22;
			cerclejoueur.setPosition((this->players[j].p_placer[i].position.x * 80) + 27, decalage_y_cercle + this->players[j].p_placer[i].position.y * 45);
			spriteperso.setPosition((this->players[j].p_placer[i].position.x * 80) + 20, this->players[j].p_placer[i].position.y * 45);
			if (this->players[j].p_placer[i].position.y % 2 == 1) {
				cerclejoueur.setPosition((this->players[j].p_placer[i].position.x * 80 + 67), decalage_y_cercle + this->players[j].p_placer[i].position.y * 45 / 2);
				spriteperso.setPosition((this->players[j].p_placer[i].position.x * 80 + 60), this->players[j].p_placer[i].position.y * 45 / 2);
			}
			if (this->players[j].p_placer[i].position.y % 2 == 0) {
				cerclejoueur.setPosition((this->players[j].p_placer[i].position.x * 80) + 27, decalage_y_cercle + (this->players[j].p_placer[i].position.y / 2) * 45);
				spriteperso.setPosition((this->players[j].p_placer[i].position.x * 80) + 20, (this->players[j].p_placer[i].position.y / 2) * 45);
			}

			float fr = (float)r / 255.0; // ici arriver a trouver les 3 r g b a partir du char;
			float fg = (float)g / 255.0;
			float fb = (float)b / 255.0;
			shader.setUniform("color", Glsl::Vec3(fr, fg, fb));
			RenderStates rs(&shader);


			this->draw(cerclejoueur);
			this->draw(spriteperso);
			renderTexture.draw(spriteperso, rs); // rendu dans une texture shader
		}								 
		}
	}

	this->renderTexteView();
	this->autre[0].setPosition(870, 515);
	this->draw(autre[0]);

	if (this->map_clicked) {
		Case *c = this->map->caseJeu[this->map_clicked_ij.y][this->map_clicked_ij.x];
		Sprite *s = new Sprite(c->texture);
		s->setPosition(800, 380);

		this->tablo_text[4].setString(c->types);
		this->tablo_text[4].setPosition(800, 360);
		this->draw(this->tablo_text[4]);
		this->draw(*s);
	}

	//DEBUG	
	const sf::Texture& texture = renderTexture.getTexture();
	sf::Sprite sprite(texture);
	Image *image;
	this->debug->draw(sprite);
	this->debug->display();
	this->bm.image = texture.copyToImage();
	this->display();

}