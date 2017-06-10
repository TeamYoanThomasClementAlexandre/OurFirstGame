#pragma once
#include "..\Fichiers header\FenetreAlex.h"

FenetreAlex::FenetreAlex(int** carac, vector<vector<vector<string>>>* equipPerso, vector<vector<string>> itemInvent,int lvlClasse[4], int expClasse[4],float width,float height,string joueur) {
	this->carac = carac;
	this->control = new ControlSouris();
	this->troupes = new GestionTroupes(width, height);
	troupes->setCarac(this->carac);
	troupes->setEquipement(equipPerso);
	troupes->setLvlClasses(lvlClasse);
	troupes->setExpClasses(expClasse);
	Inventaire* a=*troupes->getInventaire();
	a->setItems(itemInvent);
	a->update(0);
	this->create(sf::VideoMode(width, height), "Ages of Strategies", sf::Style::Titlebar);
	this->setPosition(sf::Vector2i(0, 0));
	this->joueur = joueur;
}
	void FenetreAlex::game() {		
		
		sf::Event event;
		while (this->isOpen())
		{
			while (this->pollEvent(event))
			{
				if (!control->gererChoix(troupes, *this, event,this->joueur)) {
					delete(this);
					return;				
				}
				
				control->gererInventaire(*troupes->getInventaire(), troupes, *this, event);
			}
			troupes->draw(*this);
			this->display();
			this->clear(sf::Color(157, 217, 234, 0));	

		}
	}

	


FenetreAlex::~FenetreAlex() {
	delete(this->control);
	delete(this->troupes);
	delete(CaracEquip::ini(240.f, 240.f));

}

