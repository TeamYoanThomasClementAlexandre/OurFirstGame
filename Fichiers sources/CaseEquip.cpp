#pragma once
#include "..\Fichiers header\CaseEquip.h"

CaseEquip::CaseEquip(float width,float height, float posX, float posY) {
	this->cleanbool = true;
	this->setPosition(posX,posY);
	this->setFillColor(sf::Color(0,0,0,0));
	this->setSize(sf::Vector2f(width, height));
	this->setOutlineThickness(-1);
	this->setOutlineColor(sf::Color(0, 0, 0, 50));
}

void CaseEquip::setEquipement(std::string url,std::string* carac) {
	this->url = url;
	for (int i = 0; i < 6; i++)
		caracEquip[i] = carac[i];
	this->cleanbool =false;
	image.loadFromFile("../Fichiers externe/img/equip/"+this->url+ ".png");
	image.setSmooth(true);
	equipement.setTexture(image);
	equipement.setScale((this->getGlobalBounds().width / 80.f), (this->getGlobalBounds().height / 80.f));
	float x = (this->getGlobalBounds().width)/ 2.f - (equipement.getGlobalBounds().width / 2);
	float y = (this->getGlobalBounds().height) / 2.f - (equipement.getGlobalBounds().height / 2);
	equipement.setPosition(this->getGlobalBounds().left + x, this->getGlobalBounds().top + y);
}

std::string CaseEquip::getUrl() {
	return this->url;
}

void CaseEquip::clean() {
	for (int i = 0; i < 6; i++)
		caracEquip[i] = "";
	this->cleanbool = true;
	this->url = "";
}

std::string* CaseEquip::getCarac() {
	return this->caracEquip;
}

bool CaseEquip::isEmpty() {
	return this->cleanbool;
}
void CaseEquip::draw(sf::RenderWindow &fen) {
	fen.draw(*this);
	if(!this->cleanbool)
		fen.draw(equipement);
}

CaseEquip::~CaseEquip() {
}
