#pragma once
#include "..//Fichiers header/Inventaire.h"

Inventaire::Inventaire(float ratioX, float ratioY) {
	this->ratioX = ratioX;
	this->ratioY = ratioY;
	this->viewC = false;
	inventaire = sf::VertexArray(sf::Quads, 4);
	inventaire[0].color = sf::Color(18, 154, 214);
	inventaire[1].color = sf::Color(24, 230, 249);
	inventaire[2].color = sf::Color(24, 230, 249);
	inventaire[3].color = sf::Color(18, 154, 214);
	inventaire[0].position = sf::Vector2f(850.f*ratioX, 625.f*ratioY);
	inventaire[1].position = sf::Vector2f(1890.f*ratioX, 625.f*ratioY);
	inventaire[2].position = sf::Vector2f(1890.f*ratioX, 1025.f*ratioY);
	inventaire[3].position = sf::Vector2f(850.f*ratioX, 1025.f*ratioY);

	for (int l = 0; l < Largeur; l++) {
		for (int c = 0; c < Hauteur; c++) {
			cases[l][c] = new CaseEquip(ratioX*80.f, ratioY*80.f, inventaire[0].position.x + 80.f*(float)l*ratioX, inventaire[0].position.y + c*80.f*ratioY);
		}		
	}	
	viewCarac = CaracEquip::ini(240.f*ratioX, 240.f*ratioY);

}



void Inventaire::update(int classe) {	
	for (int l = 0; l < Largeur; l++) {
		for (int c = 0; c < Hauteur; c++) {
			cases[l][c]->clean();
		}
	}
	std::string carac[6];
	int ligne=0, colonne=0,nb=0;
	for (int i = 0; i < itemInvent.size(); i++) {		
		carac[0] = itemInvent[i][0];
		carac[1] = itemInvent[i][1];
		carac[2] = itemInvent[i][3];
		carac[3] = itemInvent[i][4];
		carac[4] = itemInvent[i][5];
		carac[5] = itemInvent[i][6];
		if (carac[0] != "" ) {
			
			if (classe == 0 && carac[0] != "epee" && carac[0] != "lance" && carac[0] != "marteau") {
				cases[ligne][colonne]->setEquipement(itemInvent[i][2], carac);
				nb++;
				colonne++;
			}
			else if (classe == 1 && carac[0] != "arc" && carac[0] != "lance" && carac[0] != "marteau") {
				cases[ligne][colonne]->setEquipement(itemInvent[i][2], carac);
				nb++;
				colonne++;
			}
			else if (classe == 2 && carac[0] != "epee" && carac[0] != "arc" && carac[0] != "marteau") {
				cases[ligne][colonne]->setEquipement(itemInvent[i][2], carac);
				nb++;
				colonne++;
			}
			else if (classe == 3 && carac[0] != "epee" && carac[0] != "lance" && carac[0] != "arc") {
				cases[ligne][colonne]->setEquipement(itemInvent[i][2], carac);
				nb++;
				colonne++;
			}		
		}
		if (colonne == this->Largeur)
			ligne++;
	}
	std::cout << "il y a " << nb << "item" << std::endl;
}

void Inventaire::setItems(std::vector<std::vector<std::string>> itemInvent) {
	this->itemInvent = itemInvent;
}

void Inventaire::setPosition(float x, float y) {
	inventaire[0].position = sf::Vector2f(x*ratioX, y*ratioY);
	inventaire[1].position = sf::Vector2f((x+1040)*ratioX,y);
	inventaire[2].position = sf::Vector2f((x + 1040)*ratioX,(y+400)*ratioY);
	inventaire[3].position = sf::Vector2f(x*ratioX, (y + 400)*ratioY);
	for (int l = 0; l < Largeur; l++) {
		for (int c = 0; c < Hauteur; c++) {
			cases[l][c] = new CaseEquip(ratioX*80.f, ratioY*80.f, inventaire[0].position.x + 80.f*(float)l*ratioX, inventaire[0].position.y + c*80.f*ratioY);
		}
	}
}

void Inventaire::addItem(std::string* carac) {
	bool verif = false;
	for (int i = 0; i < itemInvent.size(); i++) {
		if (itemInvent[i][0] == "") {
			verif = true;
			for (int i2 = 0; i2 < 7; i2++)
				itemInvent[i][i2] = carac[i2];
			break;
		}
	}
	if (!verif) {
		std::vector<std::string> caracTemp;
		for (int i2 = 0; i2 < 7; i2++)
			caracTemp.push_back(carac[i2]);
		itemInvent.push_back(caracTemp);
	}

}

bool Inventaire::onMouse(float x,float y) {
	float height, left, top, width;
	bool verif=false;
	for (int l = 0; l < Largeur; l++) {
		for (int c = 0; c < Hauteur; c++) {
			height = cases[l][c]->getGlobalBounds().height;
			left = cases[l][c]->getGlobalBounds().left;
			top = cases[l][c]->getGlobalBounds().top;
			width = cases[l][c]->getGlobalBounds().width;
			if (x <= (left + width) && x >= left && y >= top && y <= (top + height)) {
				cases[l][c]->setFillColor(sf::Color(242, 146, 22, 255));
				viewCarac->setPosition(cases[l][c]->getPosition().x- 3.f*cases[l][c]->getGlobalBounds().width, cases[l][c]->getPosition().y- 2* cases[l][c]->getGlobalBounds().height);
				viewCarac->setAttributs(cases[l][c]->getCarac());
				verif = true;
				this->caseOnMouse = cases[l][c];
				
			}
			else {
				cases[l][c]->setFillColor(sf::Color(0, 0, 0, 0));
			}
		}		
	}	

	this->viewC = verif;
	return verif;
}

CaseEquip* Inventaire::getCaseOnMouse() {
	return caseOnMouse;
}
void Inventaire::draw(sf::RenderWindow &fen) {
	fen.draw(inventaire);
	for (int l = 0; l < Largeur; l++) {
		for (int c = 0; c < Hauteur; c++) {
			cases[l][c]->draw(fen);
		}
	}
	
	if(this->viewC)
		viewCarac->draw(fen);
}

void Inventaire::retirerItem(std::string nomItem) {

	for (int i = 0; i < itemInvent.size(); i++) {
		if (itemInvent[i][1] == nomItem) {
			for (int i2 = 0; i2 < 7; i2++) 
				itemInvent[i][i2] = "";		
			break;
		}
	}
}

Inventaire::~Inventaire() {
}
