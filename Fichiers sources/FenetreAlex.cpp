#pragma once
#include "..\Fichiers header\FenetreAlex.h"

FenetreAlex::FenetreAlex(int** carac, vector<vector<vector<string>>>* equipPerso, vector<vector<string>> itemInvent) {
	this->carac = carac;
	this->control = new ControlSouris();
	this->troupes = new GestionTroupes(WIDTH, HEIGHT);
	troupes->setCarac(this->carac);
	troupes->setEquipement(equipPerso);
	Inventaire* a=*troupes->getInventaire();
	a->setItems(itemInvent);
	a->update(0);
	this->create(sf::VideoMode(WIDTH, HEIGHT), "GAME");
}
	void FenetreAlex::game() {		
		
		sf::Event event;
		while (this->isOpen())
		{
			while (this->pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					this->close();
				}
			}			
			this->gestionTroupes();
			this->display();
			this->clear(sf::Color(157, 217, 234, 0));
			
			
		}
	}

void FenetreAlex ::gestionTroupes() {
	control->gererChoix(troupes, *this);
	control->gererInventaire(*troupes->getInventaire(),*this);	
	troupes->draw(*this);
}

FenetreAlex::~FenetreAlex() {

}

