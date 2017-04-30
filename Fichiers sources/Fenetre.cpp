#include "..\\Fichiers header\Fenetre.h"
#include "..\\Fichiers header\Rectangle.h"
#include "..\\Fichiers header\fonctionCalc.h"
#include"..\\Fichiers header\FenetreYoan.h"
#include <SFML\Window\Event.hpp>
#include <iostream>
#include "..\\Fichiers header\Personnage.h"

#define option_x 930
#define option_y 0

#define widthh 243.0f
#define heightt 48.0f


/* carré de resolution*/
#define width_fen_resolution 310
#define height_fen_resolution 400
#define pos_depart_resolution 50
#define pos_x_text 105
#define pos_y_text 80
/* fin carré résolution*/


/*Define des positions de base des rectangles pour evitez les valeurs magique*/
#define allPosX 124
#define rectanglePosY 210
#define rectangle2PosY 300
#define rectangle3PosY 390
/* fin*/

using namespace std;
using namespace sf;

Fenetre::Fenetre(int tailleFenetreAccueilX0,int tailleFenetreAccueilY0)
{
	this->tailleFenetreAccueilX = tailleFenetreAccueilX0;
	this->tailleFenetreAccueilY = tailleFenetreAccueilY0;
	this->create(VideoMode(tailleFenetreAccueilX, tailleFenetreAccueilY), "Menu d'acceuil", sf::Style::Close);
	this->affichageMenu();
}

Fenetre::~Fenetre()
{
}

sf::Vector2u Fenetre::newScreen() {
	std::vector<Rectangle>resolution;
	sf::Event event;
	sf::RenderWindow window(sf::VideoMode(width_fen_resolution, height_fen_resolution), "Changement de résolution");
	window.setPosition(sf::Vector2i(this->getSize().x - width_fen_resolution, 30));
	sf::Sprite sprite1;
	sf::Texture testons;
	int i;
	sf::Vector2u dimension;
	sf::Color color(255, 255, 255);
	sf::Color colorBleu(0, 162, 232);
	sf::FloatRect rect_resolution_bound[3];
	sf::Font font;
	font.loadFromFile("..//Fichiers externe/arial.ttf");
	sf::Text textResolution[3];
	

	for (i = 0; i < 3; i++) {
		resolution.push_back(Rectangle(50, 50+i*125, 200.0f, 75.0f));//carré de redimensionnemt
		textResolution[i].setFont(font);
		textResolution[i].setCharacterSize(16);
		textResolution[i].setPosition(pos_x_text, pos_y_text + i * 125);
	}
	textResolution[0].setString("960 x 540");
	textResolution[1].setString("1280 x 720");
	textResolution[2].setString("Ecran complet");
	for (i = 0; i < 3; i++)
	{
		resolution[i].dessinRectangle(colorBleu);
	}
	for (i = 0; i < 3; i++)
		rect_resolution_bound[i] = resolution[i].getGlobalBounds();
	if (!testons.loadFromFile("..//Fichiers externe//choixResolution.bmp"))
		exit(0);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				return this->getSize();
			}
			if (event.type == sf::Event::MouseMoved) {
				for (i = 0; i < 3; i++) {
					if (rect_resolution_bound[i].contains(event.mouseMove.x, event.mouseMove.y)) {
						resolution[i].setOutlineThickness(3.0);
						resolution[i].setOutlineColor(sf::Color::Black);
					}
					else {
						resolution[i].setOutlineThickness(1.0);
						resolution[i].setOutlineColor(color);
					}
				}
			}
			if (event.mouseButton.button == sf::Mouse::Left) {
				for (i = 0; i < 3; i++) {
					if (rect_resolution_bound[i].contains(event.mouseButton.x, event.mouseButton.y)) {
						if (i == 0) {
							dimension.x = 960;
							dimension.y = 540;
							resolution.pop_back();
							resolution.pop_back();
							resolution.pop_back();
							return dimension;
						}
						if (i == 1) {
							dimension.x = 1280;
							dimension.y = 600;
							resolution.pop_back();
							resolution.pop_back();
							resolution.pop_back();
							return dimension;
						}
						else {
							dimension.x = sf::VideoMode::getDesktopMode().width;
							dimension.y = sf::VideoMode::getDesktopMode().height - 30;
							resolution.pop_back();
							resolution.pop_back();
							resolution.pop_back();
							return dimension;
						}
					}
				}
			}
		}
		sprite1.setTexture(testons);
		window.draw(sprite1);
		for (i = 0; i < 3; i++) {
			window.draw(resolution[i]);
			window.draw(textResolution[i]);
		}
		window.display();
	}
}

void Fenetre::affichageMenu() {
	std::vector<Rectangle>choixJeu;
	sf::Color bleuFonce = sf::Color(0, 163, 253);
	sf::Color bleuClair = sf::Color(155, 216, 234);
	sf::Color blanc = sf::Color(255, 255, 255);
	sf::Event event;
	sf::Texture testons;
	sf::Sprite sprite1; // c'est le carré de d'option image
	sf::Vector2u taille;
	sf::Vector2f test;
	
	static int choixPosX = 164;
	static int choixPosY = 220;
	static float option_width_height = 30.0f;

	this->setPosition(sf::Vector2i(0, 0));

	taille.x = tailleFenetreAccueilX;
	taille.y = tailleFenetreAccueilY;
	int oldTailleX = taille.x;
	int oldTailleY = taille.y;
	int i;


	//sf::RectangleShape rectangle[3];// tous les carré de choix
	sf::RectangleShape temp_rectangle[3];// EVITE QUE LES CARR2 PRENNENT le redimensionnement de la fenetre plus els coord
	sf::RectangleShape terrainComplet(sf::Vector2f(taille.x, taille.y));// designe le carré gérer mes troupes
	sf::RectangleShape option(sf::Vector2f(option_width_height, option_width_height));// designe le carré option
	sf::RectangleShape tempOption(sf::Vector2f(option_width_height, option_width_height));

	sf::FloatRect boundRectangle[3]; // coord physique des rectangles
	sf::FloatRect boundBonjour;
	sf::FloatRect boundOption;
	sf::FloatRect newbound;
	sf::Font font;
	font.loadFromFile("..//Fichiers externe/arial.ttf");
	sf::Text bonjour("Bonjour nom du joueur", font);
	sf::Text nameGame("My little World", font);
	sf::Text choix[3];



	if (!testons.loadFromFile("..//Fichiers externe//accueil.jpg"))
		return exit(0);

	/* l'image n'est pas redimensionné en fonction de fonction de la taille de la fenetre !!*/
	sprite1.setTexture(testons);
	sprite1.setTextureRect(sf::IntRect(930, 0, 30, 30));
	sprite1.setPosition(tailleFenetreAccueilX - 40, 0);
	terrainComplet.setFillColor(bleuClair);
	choixJeu.push_back(Rectangle(124, 210, 243.0f, 48.0f));//jouer en local
	choixJeu.push_back(Rectangle(124, 300, 243.0f, 48.0f));//deuxième
	choixJeu.push_back(Rectangle(124, 390, 243.0f, 48.0f));//troisième
	for (i = 0; i < 3; i++) {
		choixJeu[i].dessinRectangle(bleuClair);
		temp_rectangle[i] = choixJeu[i];
		boundRectangle[i] = temp_rectangle[i].getGlobalBounds();
		choix[i].setCharacterSize(20);
		choix[i].setPosition(choixPosX, choixPosY + i * 90);
		choix[i].setFont(font);
	}
	choix[0].setString("Jouer en local");
	choix[1].setString("Jouer en réseau");
	choix[2].setString("Afficher l'inventaire");
	option.setPosition(930, 0);
	tempOption.setPosition(930, 0);
	boundOption = option.getGlobalBounds();


	nameGame.setCharacterSize(30);
	nameGame.setPosition(tailleFenetreAccueilX / 2.5, tailleFenetreAccueilY*(1 / 3));
	nameGame.setStyle(sf::Text::Bold);
	bonjour.setCharacterSize(16);
	bonjour.setPosition(sf::Vector2f(170, 145));
	bonjour.setStyle(sf::Text::Bold);
	bonjour.setStyle(sf::Text::Underlined);
	int compteur = 0;

	while (this->isOpen())
	{
		while (this->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->close();
		}
		if (event.mouseButton.button == sf::Mouse::Left) {
			/* si un clique gauche de souris l'évènement se déclenche*/
			for (i = 0; i < 3; i++) {
				if (boundRectangle[i].contains(event.mouseButton.x, event.mouseButton.y)) {
					if (i == 0) {
						this->close();
						String map_taille = "petite";
						
						// RECUPERATION DANS LA BASE DE DONNEE ICI
						Personnage* pj1 = new Personnage[4];
						Personnage* p1 = new Personnage("archer");
						Personnage* p2 = new Personnage("paladin");
						Personnage* p3 = new Personnage("epeiste");
						Personnage* p4 = new Personnage("lancier");

						pj1[0] = *p1;
						pj1[1] = *p2;
						pj1[2] = *p3;
						pj1[3] = *p4;

						Personnage* pj2 = new Personnage[4];
						Personnage* p10 = new Personnage("archer");
						Personnage* p20 = new Personnage("paladin");
						Personnage* p30 = new Personnage("epeiste");
						Personnage* p40 = new Personnage("lancier");

						pj2[0] = *p10;
						pj2[1] = *p20;
						pj2[2] = *p30;
						pj2[3] = *p40;
						Joueur * players = new Joueur[2];
						Joueur *joueur1 = new Joueur();
						Joueur *joueur2 = new Joueur();
						joueur1->pseudo = "Yoan";
						joueur2->pseudo = "Yoan2";
						joueur1->p = pj1;
						joueur2->p = pj2;
						players[0] = *joueur1;
						players[1] = *joueur2;

						FenetreYoan* game = new FenetreYoan(taille,players); // donner ici les coordonnées
						game->load();
						game->idle();
					}
					if (i == 1) {}
					if (i == 2) {}
				}
			}
			if (boundOption.contains(event.mouseButton.x, event.mouseButton.y)) {
				taille = newScreen();
				this->clear();
				this->display();
				this->setSize(taille);
				//redéfinition des rectangle joué et affiché
				for (i = 0; i < 3; i++) {
					//temp_rectangle[i].setSize(sf::Vector2f(taille.x / (oldTailleX / widthh), taille.y / (oldTailleY / heightt)));
					temp_rectangle[i] = calcRedimension(choixJeu[i], taille, oldTailleX,oldTailleY);
					boundRectangle[i] = temp_rectangle[i].getGlobalBounds();
				}
				//redéfinition des paramètres 
				option = calcRedimension(tempOption, taille, oldTailleX, oldTailleY);
				boundOption = option.getGlobalBounds();
			}
		}

		this->clear();
		terrainComplet.setFillColor(bleuClair);
		this->draw(terrainComplet);
		for (i = 0; i < 3; i++) {
			this->draw(choixJeu[i]);
			this->draw(choix[i]);
		}
		//pas obligé de dessiner le rectangle, il est invisible ^^
		this->draw(sprite1);
		this->draw(bonjour);// on l'affiche après sprite 1 pour qu'on puisse le voir !!
		this->draw(nameGame);
		this->display();
	}

}


