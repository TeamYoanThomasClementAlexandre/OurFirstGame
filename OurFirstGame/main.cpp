#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

int main()
{
	// check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;

	bool choixcavalier = false;

	int indicex = -1; // indice case viser par souris en X
	int indicey = -1; // indice case viser par souris en Y
	int oldvaluex = -1; //anciene valeur de l'indice de la souris en X
	int oldvaluey = -1; //anciene valeur de l'indice de la souris en Y
	sf::Vector2i taille;

	/* creation rectangle surlignement */
	sf::RectangleShape rectangle2(sf::Vector2f(50, 50));
	rectangle2.setFillColor(sf::Color::Green);
	
	/* creation rectangle surlignement */
	sf::RectangleShape rectangle3(sf::Vector2f(50, 50));
	rectangle3.setFillColor(sf::Color::Blue);
	rectangle3.setOutlineThickness(1);
	rectangle3.setOutlineColor(sf::Color::Black);
	
	/* creation rectangle blanc */
	sf::RectangleShape rectangleblanc(sf::Vector2f(800, 100));
	rectangleblanc.setFillColor(sf::Color::White);
	rectangleblanc.setPosition(0, 800);

	/* creation rectangle jaune cavalier */
	sf::RectangleShape rectangleUnite(sf::Vector2f(50, 50));
	rectangleUnite.setFillColor(sf::Color::Yellow);
	rectangleUnite.setOutlineThickness(1);
	rectangleUnite.setOutlineColor(sf::Color::Black);

	/* creation du cavalier */
	sf::Texture testons;
	sf::Sprite sprite1; // c'est le carré de jeu
	sf::RectangleShape rectanglechevalier(sf::Vector2f(50, 50));// designe le carré joué en local

	if (!testons.loadFromFile("D:\\Documents\\Visual Studio 2015\\Projects\\OurFirstGame\\Ressource\\Cuirassier.jpg")) {
		return EXIT_FAILURE;
	}
	sprite1.setTexture(testons);
	rectanglechevalier.setPosition(50, 850);
	rectanglechevalier.setTexture(&testons); // enregistre la vue (texture)
	/* creation fenetre */
	sf::RenderWindow window(sf::VideoMode(800, 900), "Age of strategies");
	window.setPosition(sf::Vector2i(0,0));


	// Boucle infini du Jeu
	while (window.isOpen())
	{

	   window.draw(rectangleblanc);
	
		window.draw(rectanglechevalier);

		
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		for (int i = 0; i < 800; i = i + 50) {
			for (int j = 0; j <= 800; j = j + 50)
			{
				sf::RectangleShape rectangle(sf::Vector2f(50, 50));

				rectangle.setFillColor(sf::Color::Blue);
				rectangle.setOutlineThickness(1);
				rectangle.setOutlineColor(sf::Color::Black);
				rectangle.setPosition(i, j);
				window.draw(rectangle);
			}
		}

	
		oldvaluey = indicey;
		oldvaluex = indicex;
		while(indicex == oldvaluex && indicey == oldvaluey) {
			taille = sf::Mouse::getPosition(window);
			indicex = (int)taille.x / 50;
			indicey = (int)taille.y / 50;
			int realX = indicex * 50;
			int realY = indicey * 50;

			if (realY > 800) {

				indicey = oldvaluey;
				indicex = oldvaluex;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (realX>=50 && realX<=100 && realY>=800 && realY<=850))
				{
					std::cout << "Click icone cavalier" << std::endl;
					choixcavalier = true; //switch mode placement chevalier
				}
			}
			else {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && choixcavalier == true) {
					rectangleUnite.setPosition(realX, realY);
					window.draw(rectangleUnite);
					choixcavalier = false; // switch mode deplacement
				}
			}
			rectangle2.setPosition(realX, realY);
		}

		window.draw(rectangle2);
		rectangle3.setPosition(oldvaluex * 50, oldvaluey * 50);
		window.draw(rectangle3);
		window.display();

	}

	return 0;
}