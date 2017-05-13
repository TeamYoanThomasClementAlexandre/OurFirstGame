#pragma once
#include "..//Fichiers header/ControlSouris.h"


ControlSouris::ControlSouris()
{
	
}

void ControlSouris::gererChoix(GestionTroupes *troupes, sf::RenderWindow &fen) {
	sf::Vector2i mouse = sf::Mouse::getPosition(fen);
	sf::Vector2f mouse_world = fen.mapPixelToCoords(mouse);
	troupes->onMouse(mouse_world.x, mouse_world.y);	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		troupes->setSelected(mouse_world.x, mouse_world.y);	
	}
}

void ControlSouris::gererInventaire(Inventaire *inventaire, sf::RenderWindow &fen) {
	sf::Vector2i mouse = sf::Mouse::getPosition(fen);
	sf::Vector2f mouse_world = fen.mapPixelToCoords(mouse);
	inventaire->onMouse(mouse_world.x, mouse_world.y);
}

ControlSouris::~ControlSouris() {

}