#pragma once
#include "..//Fichiers header/ControlSouris.h"
#include <math.h> 


ControlSouris::ControlSouris()
{
}

int ControlSouris::gererChoix(GestionTroupes *troupes, sf::RenderWindow &fen, sf::Event evenement,string joueur) {
	int action = 1;
	sf::Vector2i mouse = sf::Mouse::getPosition(fen); 
	sf::Vector2f mouse_world = fen.mapPixelToCoords(mouse);
	bool isOnCase=troupes->onMouse(mouse_world.x, mouse_world.y);
	if (evenement.type == sf::Event::MouseButtonReleased ) {
		action =troupes->setSelected(mouse_world.x, mouse_world.y);
	}
	if (action == 2 || action==0) {
		std::string** saveTab = troupes->getSaveTab();
		InteractionBDD* bdd = NULL;
		if (saveTab[0][0] != "" || saveTab[1][0] != "" || saveTab[2][0] != "" )
			bdd = InteractionBDD::Ini();
		if (saveTab[0][0] != "")
			bdd->setEquipementOnChar(saveTab[0][0], saveTab[0][1], joueur, saveTab[0][2]);
		if (saveTab[1][0] != "")
			bdd->setEquipementOnChar(saveTab[1][0], saveTab[1][1], joueur, saveTab[1][2]);
		if (saveTab[2][0] != "")
			bdd->setEquipementOnChar(saveTab[2][0], saveTab[2][1], joueur, saveTab[2][2]);
			
		
	}
	if (evenement.type == sf::Event::MouseButtonReleased) {
		if (isOnCase ) {
			troupes->delEquipementSelected();
		}
	}
	return action;
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