
#include "..\Fichiers header\GestionTroupes.h"

GestionTroupes::GestionTroupes(float width,float height)	{
	textureChoix[0].loadFromFile("../Fichiers externe/img/equip/choix_archer.png");
	textureChoix[1].loadFromFile("../Fichiers externe/img/equip/choix_epeiste.png");
	textureChoix[2].loadFromFile("../Fichiers externe/img/equip/choix_lancier.png");
	textureChoix[3].loadFromFile("../Fichiers externe/img/equip/choix_paladin.png");
	textureChoix[4].loadFromFile("../Fichiers externe/img/equip/choix_archer2.png");
	textureChoix[5].loadFromFile("../Fichiers externe/img/equip/choix_epeiste2.png");
	textureChoix[6].loadFromFile("../Fichiers externe/img/equip/choix_lancier2.png");
	textureChoix[7].loadFromFile("../Fichiers externe/img/equip/choix_paladin2.png");
	texturePerso.loadFromFile("../Fichiers externe/img/equip/personnage.png");
	textLogo.loadFromFile("../Fichiers externe/img/Age_of_Strategy.png");
	textLogo.setSmooth(true);
	float ratioX = width / 1920.f;
	float ratioY =  height / 1080.f;
	logo.setTexture(textLogo);
	logo.setScale(ratioX, ratioY);
	logo.setPosition((width - logo.getGlobalBounds().width) / 2.f, 40.f);
	for (int i = 0; i < 8; i++) {
		textureChoix[i].setSmooth(true);
	}
	choixSelected = 0;
	for (int i = 0; i < 4; i++) {
		if (i == choixSelected)
			choix[i].setTexture(textureChoix[i+4]);
		else
			choix[i].setTexture(textureChoix[i]);	
		choix[i].setScale(ratioX, ratioY);
		choix[i].setPosition((textureChoix[i].getSize().x *(float)i)*ratioX + ((float)i*10.f + 30.f)*ratioX, 275.f*ratioY);
	}
	texturePerso.setSmooth(true);
	persoChoix.setTexture(texturePerso);
	persoChoix.setScale(ratioX, ratioY);
	persoChoix.setPosition(1330.f*ratioX, 100.f*ratioY);
	//inventaire
	inventaire = new Inventaire(ratioX, ratioY);
	
	//caracteristiques
	caracteristique = new Carac(ratioX, ratioY);
	caracteristique->setPosition(choix[0].getPosition().x, 425.f);
	viewCarac=CaracEquip::ini(240.f*ratioX, 240.f*ratioY);
	affichageView = false;

	//equipements
	
	equip[0] = new CaseEquip(85 * ratioX, 85 * ratioY,persoChoix.getGlobalBounds().left+0.02f*persoChoix.getGlobalBounds().width, persoChoix.getGlobalBounds().top+ persoChoix.getGlobalBounds().height*0.38f);
	equip[1] = new CaseEquip(85 * ratioX, 85 * ratioY, persoChoix.getGlobalBounds().left + 0.42f*persoChoix.getGlobalBounds().width, persoChoix.getGlobalBounds().top + persoChoix.getGlobalBounds().height *0.25f);
	equip[2] = new CaseEquip(85 * ratioX, 85 * ratioY, persoChoix.getGlobalBounds().left + 0.98f*persoChoix.getGlobalBounds().width- 85 * ratioX, persoChoix.getGlobalBounds().top + persoChoix.getGlobalBounds().height *0.38f);
	for (int i = 0; i < 3; i++) {
		//1:Arme 2:Armure 3:Bijoux		
		equip[i]->setFillColor(sf::Color(20, 182, 227, 150));
	}
	
	//experience
	exp = new BarreExp(500 * ratioX, 20 * ratioY, 1350*ratioX, 550 * ratioY);
	exp->setExp(55);
	exp->setLvl(2);

}

void GestionTroupes::setSelected(float x,float y) {
	for (int i = 0; i < 4; i++) {
		float height= choix[i].getGlobalBounds().height;
		float left = choix[i].getGlobalBounds().left;
		float top = choix[i].getGlobalBounds().top;
		float width = choix[i].getGlobalBounds().width;
		if (x <= (left + width) && x >= left && y >= top && y <= (top + height)) {
			if (i != choixSelected) {
				//enlever ancien
				choix[choixSelected].setTexture(textureChoix[choixSelected], true);
				//nouveau
				choix[i].setTexture(textureChoix[i+4],true);

				if (i == 0) {
					caracteristique->setTitle("Caractéristiques de l'archer");
					caracteristique->setAttributs(this->carac[0]);
				}
				if (i == 1) {
					caracteristique->setTitle("Caractéristiques de l'epeiste");
					caracteristique->setAttributs(this->carac[1]);
				}
				if (i == 2) {
					caracteristique->setTitle("Caractéristiques du lancier");
					caracteristique->setAttributs(this->carac[2]);
				}
				if (i == 3) {
					caracteristique->setTitle("Caractéristiques du paladin");
					caracteristique->setAttributs(this->carac[3]);
				}
				choixSelected = i;
				this->updateItems(choixSelected);
				inventaire->update(choixSelected);
			}
		}
	}
}

void GestionTroupes::onMouse(float x, float y) {
	//choix classes
	for (int i = 0; i < 4; i++) {
		float height = choix[i].getGlobalBounds().height;
		float left = choix[i].getGlobalBounds().left;
		float top = choix[i].getGlobalBounds().top;
		float width = choix[i].getGlobalBounds().width;
		if (x <= (left + width) && x >= left && y >= top && y <= (top + height)) {
			if (i != choixSelected) {
				choix[i].setTexture(textureChoix[i + 4], true);
			}
		}
		else if (i != choixSelected) {
			choix[i].setTexture(textureChoix[i], true);
		}
	}

	//equipements	
	int verif = false;
	for (int i = 0; i < 3; i++) {
		float height = equip[i]->getGlobalBounds().height;
		float left = equip[i]->getGlobalBounds().left;
		float top = equip[i]->getGlobalBounds().top;
		float width = equip[i]->getGlobalBounds().width;
		if (x <= (left + width) && x >= left && y >= top && y <= (top + height)) {
			verif = true;
			equip[i]->setFillColor(sf::Color(242, 146, 22, 150));
			viewCarac->setPosition(equip[i]->getPosition().x - 3 * equip[i]->getGlobalBounds().width, equip[i]->getPosition().y - 2 * equip[i]->getGlobalBounds().height);
			viewCarac->setAttributs(equip[i]->getCarac());
		}
		else {
			equip[i]->setFillColor(sf::Color(20, 182, 227,150));
		}
	}
	affichageView = verif;
}

void GestionTroupes::setCarac(int** carac) {
	this->carac = carac;
	caracteristique->setAttributs(carac[0]);
}

void GestionTroupes::setEquipement(std::vector<std::vector<std::vector<std::string>>>* equipPerso) {
	this->equipPerso = equipPerso;
	this->updateItems(0);
}

void GestionTroupes::updateItems(int choixClasse) {
	for (int i = 0; i < 3; i++) {
		equip[i]->clean();
	}
	std::string carac[6];
	for (int i = 0; i < equipPerso[choixClasse].size(); i++) {
		for (int i2 = 0; i2 < equipPerso[choixClasse][0].size();i2++) {
			carac[0] = equipPerso[choixClasse][0][i2][0];
			carac[1] = equipPerso[choixClasse][0][i2][1];
			carac[2] = equipPerso[choixClasse][0][i2][3];
			carac[3] = equipPerso[choixClasse][0][i2][4];
			carac[4] = equipPerso[choixClasse][0][i2][5];
			carac[5] = equipPerso[choixClasse][0][i2][6];
			if (carac[0] == "armure")
				equip[1]->setEquipement(equipPerso[choixClasse][0][i2][2],carac);
			else if (carac[0] == "arc" || carac[0] == "epee" || carac[0] == "lance" || carac[0] == "marteau")
				equip[0]->setEquipement(equipPerso[choixClasse][0][i2][2], carac);
			else 
				equip[2]->setEquipement(equipPerso[choixClasse][0][i2][2], carac);
			
			
		}
	}
}

void GestionTroupes::draw(sf::RenderWindow &fen) {
	fen.draw(persoChoix);
	for (int i = 0; i < 3; i++) {
		equip[i]->draw(fen);
	}
	fen.draw(logo);
	for (int i = 0; i < 4; i++) {
		fen.draw(choix[i]);
	}	
	caracteristique->draw(fen);
	exp->draw(fen);
	inventaire->draw(fen);
	if (affichageView)
		viewCarac->draw(fen);
	
	
}

Inventaire** GestionTroupes::getInventaire() {
	return &this->inventaire;
}
GestionTroupes::~GestionTroupes() {
	
}
