#pragma once
#include "..//Fichiers header/ControlSouris.h"
#include <math.h> 


ControlSouris::ControlSouris()
{
}

int ControlSouris::gererChoix(GestionTroupes *troupes, sf::RenderWindow &fen, sf::Event evenement) {
	int quitter = 1;
	sf::Vector2i mouse = sf::Mouse::getPosition(fen); 
	sf::Vector2f mouse_world = fen.mapPixelToCoords(mouse);
	bool isOnCase=troupes->onMouse(mouse_world.x, mouse_world.y);
	if (evenement.type == sf::Event::MouseButtonReleased ) {
			quitter=troupes->setSelected(mouse_world.x, mouse_world.y);
	}
	if (evenement.type == sf::Event::MouseButtonReleased) {
		if (isOnCase ) {
			troupes->delEquipementSelected();
		}
	}
	return quitter;
}

void ControlSouris::gererInventaire(Inventaire *inventaire,GestionTroupes *troupes, sf::RenderWindow &fen, sf::Event evenement) {
	sf::Vector2i mouse = sf::Mouse::getPosition(fen);
	sf::Vector2f mouse_world = fen.mapPixelToCoords(mouse);
	bool isOnCase= inventaire->onMouse(mouse_world.x, mouse_world.y);
	if (evenement.type == sf::Event::MouseButtonReleased) {
		if (isOnCase && !inventaire->getCaseOnMouse()->isEmpty()) {
			troupes->setEquipementSelected(inventaire->getCaseOnMouse());
		}
	}
}

ControlSouris::~ControlSouris() {

}