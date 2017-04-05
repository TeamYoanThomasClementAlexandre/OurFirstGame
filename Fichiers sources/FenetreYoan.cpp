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

FenetreYoan::FenetreYoan(sf::Vector2u dimension,Joueur* playerss)
{
	// DEBUG
	sf::RenderWindow *window = new RenderWindow(sf::VideoMode(960, 540), "Debug Window", sf::Style::Titlebar);
	this->debug = window;
	this->debug->setPosition(sf::Vector2i(0, 0));
	//

	// choix joueur aleatoirement 
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
		this->selected.x = -1;
		this->selected.y = -1;

		/*struct char_cmp
		{
			bool operator () (const char *a, const char *b) const { return strcmp(a, b)<0; }
		};*/

		std::map<char*, sf::Vector2u*,char_cmp> *dicoo = new std::map<char*, sf::Vector2u*,char_cmp>;
		BlendModee *bmm = new BlendModee(dicoo);
		this->bm = *bmm;

}

void FenetreYoan::controleur_placement(Event event) {
	// on regarde le type de l'évènement...
	switch (event.type)
	{
	case Event::KeyPressed:
		return;
			break;
	case  Event::Closed:
		this->close();
		break;
	case sf::Event::Resized:
		this->dimension_x = this->getSize().x;
		this->dimension_y = this->getSize().y;
	case sf::Event::MouseButtonPressed:

		if (!event.mouseButton.button == sf::Mouse::Right) //
		{
			Color c=this->bm.image.getPixel(event.mouseButton.x, 540-event.mouseButton.y);
			char* s = new char[10];
			memset(s, 0, 10);
			sprintf_s(s, 10, "%00d%00d%00d\0",c.r, c.g, c.b);
			printf("ID : %s\n", s);


			sf::Vector2u* vec = (*(this->bm.dico))[s];
			if (vec != NULL) {
				printf("I,J : (%d , %d)\n", vec->y, vec->x);
			}
			
						
			//vec = this->map->getCasebyCoord(event.mouseButton.x, event.mouseButton.y, this->max_x - 1, this->max_y - 1, this->dimension_x, this->dimension_y);
			if (this->selected.x != -1) {
				printf("joueur %d personnage %d sur la case (%d,%d)", this->selected.x, this->selected.y + 1, vec->y, vec->x);
				this->players[this->joueur].personnage_placer++;
				this->players[this->joueur].p_placer[this->players[this->joueur].personnage_placer] = this->players[this->joueur].p[this->selected.y]; //placer le personnage dans le tab de perso placer;
				this->selected.x = -1;
				this->selected.y = -1;
			}

		}
		if (!event.mouseButton.button == sf::Mouse::Left)
		{
			printf("%d , %d\n", event.mouseButton.x, event.mouseButton.y);
			if (event.mouseButton.x > 7 && event.mouseButton.x < 714 && event.mouseButton.y >= 370 && event.mouseButton.y<400) {
				printf("perso 1\n");
				this->selected.x = this->joueur + 1;
				this->selected.y = 0;
			}
			else if (event.mouseButton.x > 7 && event.mouseButton.x < 714 && event.mouseButton.y >= 400 && event.mouseButton.y < 430) {
				this->selected.x = this->joueur + 1;
				this->selected.y = 1;
				printf("perso 2\n");
			}
			else if (event.mouseButton.x > 7 && event.mouseButton.x < 714 && event.mouseButton.y >= 430 && event.mouseButton.y < 460) {
				printf("perso 3\n");
				this->selected.x = this->joueur + 1;
				this->selected.y = 2;
			}
			else if (event.mouseButton.x > 7 && event.mouseButton.x < 714 && event.mouseButton.y >= 460 && event.mouseButton.y < 490) {
				printf("perso 4\n");
				this->selected.x = this->joueur + 1;
				this->selected.y = 3;
			}
			/*
			else {
			sur une case ou il y a un personnage alors ça le retire 
			}
			*/
		}
		break;
	default:
		break;
	}
	//this->clear(Color(100, 100, 100));
	//this->render(this->joueur);
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
// choix 1er joueur choisie

void FenetreYoan::PlacementPersonnage() {
	this->clear(Color(100, 100, 100));
	this->render(this->joueur);
	Personnage** persos = new Personnage*[2]; // tableau de perso a remplir 
	while (1) {

		while (this->pollEvent(this->event))
		{
			this->controleur_placement(this->event);
		}

		if (this->players[this->joueur].personnage_placer == 4) {
			printf("Joueur %d, a terminer de placer !",this->joueur+1);
			return;
		}
	}
	
	return;
}

void FenetreYoan::idle() {	
	this->PlacementPersonnage();
	this->joueur = (this->joueur == 0) ? 1 : 0;
	this->PlacementPersonnage();

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

void FenetreYoan::render(int quellejoueur) {
	
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
			this->map->caseJeu[j][i]->who = 0;

			Sprite* a = &this->map->caseJeu[j][i]->sprite;
			/*    */
			//float nombre = 0;
			//srand(time(NULL));
			//nombre = (float)rand() / (float)RAND_MAX;
			//printf("%f", nombre);
			unsigned int r = i*23;
			unsigned int g = j*12;
			unsigned int b = 100;
			
			//std::string a = std::to_string(r) + std::to_string(g) + std::to_string(b);
				//String *s = new String(std::to_string(r) + std::to_string(g) + std::to_string(b));
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
			//printf("(%f , %f , %f)\n", fr,fg,fb);
			if (i == 1 && j == 0) {
				printf("%s\n", s);

			}
			//shader.setUniform("color", Glsl::Vec3(0.1*i+(j*0.02), 0.02+(i*0.03)+(j*0.02), 0.2+(j*0.03)));
			shader.setUniform("color", Glsl::Vec3(fr, fg, fb));
			//Color *c = new Color(0.1*i + (j*0.02), 0.02 + (i*0.03) + (j*0.02), (j*0.02), 0.2 + (j*0.03));
			RenderStates rs(&shader);
			renderTexture.draw(*a, rs); // rendu dans une texture shader
			this->draw(*a); // rendu dans une fenetre
		

		}
	}
	//DEBUG
	const sf::Texture& texture = renderTexture.getTexture();
	sf::Sprite sprite(texture);
	Image *image;
	this->debug->draw(sprite);
	this->debug->display();
	this->bm.image=texture.copyToImage();


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
	sf::Text name;
	name.setFont(font);
	name.setCharacterSize(20);
	name.setString(this->players[this->joueur].pseudo);
	name.setPosition(10, 520);
	this->draw(name);
	this->display();
}
