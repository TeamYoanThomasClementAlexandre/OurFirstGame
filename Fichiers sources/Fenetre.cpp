
#include "..\\Fichiers header\Fenetre.h"
#include "..\\Fichiers header\RectanglePerso.h"
#include "..\\Fichiers header\fonctionCalc.h"
#include"..\\Fichiers header\FenetreYoan.h"
#include "..\\Fichiers header\Personnage.h"
#include "..//Fichiers header/FenetreAlex.h"

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

Fenetre::Fenetre(int tailleFenetreAccueilX0,int tailleFenetreAccueilY0,string joueur0)
{
	this->tailleFenetreAccueilX = tailleFenetreAccueilX0;
	this->tailleFenetreAccueilY = tailleFenetreAccueilY0;
	this->joueur1 = joueur0;
	this->create(VideoMode(tailleFenetreAccueilX, tailleFenetreAccueilY), "Menu d'acceuil", sf::Style::Close);
	this->affichageMenu();
}

Fenetre::~Fenetre()
{
}

std::string Fenetre::adversaireEnter() {
	sf::Vector2i mouse;
	sf::Vector2f mouse_world;
	std::string joueur2="votre nom ici";
	std::string annulation = "null";
	sf::Text joueur2Affichage;
	sf::Text joueur1Affichage;
	sf::Text player1;
	sf::Text player2;
	sf::Text versus;
	sf::Text valider;
	sf::Text annuler;
	sf::Event event;
	sf::Font font;
	sf::RenderWindow window(sf::VideoMode(tailleFenetreAccueilX, tailleFenetreAccueilY), "Sélection du deuxième compte");
	sf::Color bleuClair = sf::Color(155, 216, 234);
	sf::Color bleuFonce = sf::Color(18, 154, 214);
	sf::RectangleShape terrainComplet(sf::Vector2f(tailleFenetreAccueilX, tailleFenetreAccueilY));
	RectanglePerso rectGauche = RectanglePerso(tailleFenetreAccueilX / 12, tailleFenetreAccueilY / 2.4, tailleFenetreAccueilX / 3.5, 40);
	rectGauche.jeuRectangle(sf::Color::White);
	RectanglePerso rectDroit = RectanglePerso(tailleFenetreAccueilX / 1.75, tailleFenetreAccueilY / 2.4, tailleFenetreAccueilX / 3.5, 40);
	rectDroit.jeuRectangle(sf::Color::White);
	RectanglePerso rectValider = RectanglePerso(tailleFenetreAccueilX / 8,tailleFenetreAccueilY-tailleFenetreAccueilY/5 ,200,50);
	RectanglePerso rectAnnuler = RectanglePerso(tailleFenetreAccueilX / 2 + tailleFenetreAccueilX / 7, tailleFenetreAccueilY-tailleFenetreAccueilY / 5,200,50);
	rectValider.dessinRectangle(bleuClair);
	rectAnnuler.dessinRectangle(bleuClair);
	terrainComplet.setFillColor(bleuClair);
	window.setPosition(sf::Vector2i(0, 0));

	font.loadFromFile("..//Fichiers externe/arial.ttf");


	player2.setStyle(sf::Text::Bold);
	player2.setCharacterSize(24);
	player2.setPosition(tailleFenetreAccueilX/2+tailleFenetreAccueilX/6,tailleFenetreAccueilY/3);
	player2.setFont(font);
	player2.setString("Player 2");

	player1.setFont(font);
	player1.setStyle(sf::Text::Bold);
	player1.setCharacterSize(24);
	player1.setPosition(tailleFenetreAccueilX / 6,tailleFenetreAccueilY / 3);
	player1.setString("Player 1");

	versus.setStyle(sf::Text::Bold);
	versus.setCharacterSize(100);
	versus.setPosition(((rectDroit.getPosition().x - (rectGauche.getPosition().x + rectGauche.getSize().x) - 100) / 3)+ rectGauche.getPosition().x + rectGauche.getSize().x, tailleFenetreAccueilY / 3-24);
	versus.setFont(font);
	versus.setString("VS");

	joueur2Affichage.setStyle(sf::Text::Bold);
	joueur2Affichage.setCharacterSize(20);
	joueur2Affichage.setPosition(rectDroit.getPosition().x+10, rectDroit.getPosition().y+10);
	joueur2Affichage.setFont(font);
	joueur2Affichage.setFillColor(sf::Color::Black);

	joueur1Affichage.setFont(font);
	joueur1Affichage.setStyle(sf::Text::Bold);
	joueur1Affichage.setCharacterSize(20);
	joueur1Affichage.setPosition(rectGauche.getPosition().x+10, rectGauche.getPosition().y+10);
	joueur1Affichage.setString(joueur1);
	joueur1Affichage.setFillColor(sf::Color::Black);
	/* definition de la policde d'affichage des joueurs */

	valider.setFont(font);
	valider.setStyle(sf::Text::Bold);
	valider.setCharacterSize(20);
	valider.setPosition(rectValider.getPosition().x+65,rectValider.getPosition().y+12);
	valider.setString("Valider");

	annuler.setFont(font);
	annuler.setStyle(sf::Text::Bold);
	annuler.setCharacterSize(20);
	annuler.setPosition(rectAnnuler.getPosition().x + 65, rectAnnuler.getPosition().y + 12);
	annuler.setString("Annuler");


	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered) 
			{ 
				if (event.text.unicode == 8 || (event.text.unicode >47 && event.text.unicode <154)) 
					// 13 touche entrée
					// 8 touche effacer
					if (event.text.unicode == 8) {
						joueur2 = joueur2.substr(0, joueur2.length() - 1);
					}
					else {
						joueur2=joueur2+ static_cast<char>(event.text.unicode);
					}
					 
			}
			if (event.type == sf::Event::MouseMoved) {
				//resolution[i].setOutlineThickness(3.0);
				//resolution[i].setOutlineColor(sf::Color::Black);
			}
			else {
				//resolution[i].setOutlineThickness(1.0);
				//resolution[i].setOutlineColor(color);
			}
			if (event.mouseButton.button == sf::Mouse::Left) {
				mouse = sf::Mouse::getPosition(window);
				mouse_world = window.mapPixelToCoords(mouse);
				if (rectValider.getGlobalBounds().contains(mouse_world)) {
					if (verifNom(joueur2Affichage.getString())) {
						printf("%s",joueur2Affichage.getString());
						return joueur2Affichage.getString();
					}
					else
						joueur2 = "compte inexistant";
				}
				if (rectAnnuler.getGlobalBounds().contains(mouse_world)) {
					return annulation;
				}
			}
		}
		joueur2Affichage.setString(joueur2);
		window.clear();
		
		window.draw(terrainComplet);
		window.draw(rectGauche);
		window.draw(rectDroit);
		window.draw(versus);
		window.draw(joueur2Affichage);
		window.draw(joueur1Affichage);
		window.draw(player1);
		window.draw(player2);
		window.draw(rectAnnuler);
		window.draw(rectValider);
		window.draw(valider);
		window.draw(annuler);
		window.setSize(sf::Vector2u(this->getSize().x, this->getSize().y));
		window.display();
	}

	return joueur2;
}
sf::Vector2u Fenetre::newScreen() {
	std::vector<RectanglePerso>resolution;
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
		resolution.push_back(RectanglePerso(50, 50+i*125, 200.0f, 75.0f));//carré de redimensionnemt
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
	std::string joueur2s;
	std::vector<RectanglePerso>choixJeu;
	sf::Color bleuFonce = sf::Color(0, 163, 253);
	sf::Color bleuClair = sf::Color(155, 216, 234);
	sf::Color blanc = sf::Color(255, 255, 255);
	sf::Event event;
	sf::Texture testons;
	sf::Sprite sprite1; // c'est le carré de d'option image
	sf::Texture titre;
	sf::Sprite sprite2;// image du titre
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
	if (!titre.loadFromFile("..//Fichiers externe//titre.png"))
		return exit(0);

	/* l'image n'est pas redimensionné en fonction de fonction de la taille de la fenetre !!*/
	sprite2.setTexture(titre);
	
	sprite2.setScale(this->getSize().x/1920.f,this->getSize().y/1080.f);
	sprite2.setPosition((this->getSize().x - sprite2.getGlobalBounds().width) / 2, 10);
	titre.setSmooth(true);
	sprite1.setTexture(testons);
	sprite1.setTextureRect(sf::IntRect(930, 0, 30, 30));
	sprite1.setPosition(tailleFenetreAccueilX - 40, 0);
	terrainComplet.setFillColor(bleuClair);
	choixJeu.push_back(RectanglePerso(124, 210, 243.0f, 48.0f));//jouer en local
	choixJeu.push_back(RectanglePerso(124, 300, 243.0f, 48.0f));//deuxième
	choixJeu.push_back(RectanglePerso(124, 390, 243.0f, 48.0f));//troisième
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
						//on lance joué en local
						joueur2s=this->adversaireEnter();
						if (joueur2s != "null") {
							//FenetreYoan* game = new FenetreYoan(taille); // donner ici les coordonnées
							//Carte* map = game->load();
							//game->idle(map);
							this->close();
							String map_taille = "petite";

							// RECUPERATION DANS LA BASE DE DONNEE ICI
							PersonnageYoan* pj1 = new PersonnageYoan[4];
							PersonnageYoan* p1 = new PersonnageYoan("Archer");
							PersonnageYoan* p2 = new PersonnageYoan("Paladin");
							PersonnageYoan* p3 = new PersonnageYoan("Epeiste");
							PersonnageYoan* p4 = new PersonnageYoan("Lancier");

							pj1[0] = *p1;
							pj1[1] = *p2;
							pj1[2] = *p3;
							pj1[3] = *p4;

							PersonnageYoan* pj2 = new PersonnageYoan[4];
							PersonnageYoan* p10 = new PersonnageYoan("Archer");
							PersonnageYoan* p20 = new PersonnageYoan("Paladin");
							PersonnageYoan* p30 = new PersonnageYoan("Epeiste");
							PersonnageYoan* p40 = new PersonnageYoan("Lancier");

							InteractionBDD* bdd = InteractionBDD::Ini();
							
							pj2[0] = *p10;
							pj2[1] = *p20;
							pj2[2] = *p30;
							pj2[3] = *p40;
							
						
								for (int i = 0; i < 4; i++) {

									int lvl=bdd->requeteParCol(this->joueur1, "Personnages", "level", pj1[i].type);
									pj1[i].level = lvl;
									string url = bdd->getUrl(this->joueur1, pj1[i].type);
									pj1[i].arme = url.c_str();
								}

								for (int i = 0; i < 4; i++) {
									int lvl = bdd->requeteParCol(joueur2s, "Personnages", "level", pj1[i].type);
									pj2[i].level = lvl;
									string url = bdd->getUrl(joueur2s, pj2[i].type);
									pj2[i].arme = url.c_str();
								}
							



							JoueurYoan * players = new JoueurYoan[2];
							JoueurYoan *joueur1 = new JoueurYoan();
							JoueurYoan *joueur2 = new JoueurYoan();
							joueur1->pseudo = this->joueur1;
							joueur2->pseudo = joueur2s;
							joueur1->p = pj1;
							joueur2->p = pj2;
							players[0] = *joueur1;
							players[1] = *joueur2;

							FenetreYoan* game = new FenetreYoan(taille, players);
							game->load();
							game->idle();
						}
					}
					if (i == 1) {}
					if (i == 2) {

						InteractionBDD* bdd = InteractionBDD::Ini();

						vector<vector<vector<string>>>* equipPerso = new vector<vector<vector<string>>>[4];
						vector<vector<string>> itemInvent = bdd->getEquipement("dragodia");
						equipPerso[0].push_back(bdd->getEquipementEquiped(this->joueur1, "Archer"));
						equipPerso[1].push_back(bdd->getEquipementEquiped(this->joueur1, "Epeiste"));
						equipPerso[2].push_back(bdd->getEquipementEquiped(this->joueur1, "Lancier"));
						equipPerso[3].push_back(bdd->getEquipementEquiped(this->joueur1, "Paladin"));
						int* carac[4];
						carac[0] = bdd->getCarac(this->joueur1, "Archer");
						carac[1] = bdd->getCarac(this->joueur1, "Epeiste");
						carac[2] = bdd->getCarac(this->joueur1, "Lancier");
						carac[3] = bdd->getCarac(this->joueur1, "Paladin");
						FenetreAlex *fenetreAlex = new FenetreAlex(carac, equipPerso, itemInvent);
						fenetreAlex->game();

					}
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
		this->draw(sprite2);// nameGame
		this->display();
	}

}


