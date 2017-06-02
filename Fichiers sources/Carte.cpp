
#include "..\Fichiers header\Carte.h"

Carte::Carte()
{
		
}
		
Carte::~Carte()
{
}

void Carte::getCasesForDeplacementRecursifNord(sf::Vector2u * tab,int* tabCost,sf::Vector2u case_tmp,int mobi_tmp,int mobi_de_base,int indice) {
	// N 
	if (mobi_tmp == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if(case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y - 2);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y - 2);
		}
		
		int cost = 0;
		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		cost=this->caseJeu[tmp->y][tmp->x]->pmCost*2;
	
		mobi_tmp = mobi_tmp - cost;
		
		if (mobi_tmp < 0) {
			return;
		}
		if (this->caseJeu[tmp->y][tmp->x]->who == -1 && this->caseJeu[tmp->y][tmp->x]->types != "eau") {
			tab[indice] = *tmp;
			tabCost[indice] = mobi_de_base - mobi_tmp;
			indice++;
		}
		this->getCasesForDeplacementRecursifNord(tab, tabCost, *tmp, mobi_tmp, mobi_de_base,indice);
	}
}

void Carte::getCasesForDeplacementRecursifSud(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice) {
	// S
	if (mobi_tmp == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y + 2);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y + 2);
		}
		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		int cost = this->caseJeu[tmp->y][tmp->x]->pmCost * 2;

		mobi_tmp = mobi_tmp - cost;

		if (mobi_tmp < 0) {
			return;
		}
		if (this->caseJeu[tmp->y][tmp->x]->who == -1 && this->caseJeu[tmp->y][tmp->x]->types != "eau") {
			tab[indice] = *tmp;
			tabCost[indice] = mobi_de_base - mobi_tmp;
			indice++;
		}
		else {
			return;
		}
		this->getCasesForDeplacementRecursifSud(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);
		/*	this->getCasesForDeplacementRecursifNord(tab, tabCost, *tmp, mobi_tmp, mobi_de_base,indice);

		this->getCasesForDeplacementRecursifSud(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);
		this->getCasesForDeplacementRecursifEst(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);
		this->getCasesForDeplacementRecursifOuest(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);

		this->getCasesForDeplacementRecursifNordOuest(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);
		this->getCasesForDeplacementRecursifNordEst(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);
		this->getCasesForDeplacementRecursifSudOuest(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);
		this->getCasesForDeplacementRecursifSudEst(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);*/
	}
}

void Carte::getCasesForDeplacementRecursifEst(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice) {
	// E
	if (mobi_tmp == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x+1, case_tmp.y);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x+1, case_tmp.y);
		}

		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		int cost = this->caseJeu[tmp->y][tmp->x]->pmCost*2;

		mobi_tmp = mobi_tmp - cost;

		if (mobi_tmp < 0) {
			return;
		}
		if (this->caseJeu[tmp->y][tmp->x]->who == -1 && this->caseJeu[tmp->y][tmp->x]->types != "eau") {
			tab[indice] = *tmp;
			tabCost[indice] = mobi_de_base - mobi_tmp;
			indice++;
		}
		this->getCasesForDeplacementRecursifEst(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);
	}
}
void Carte::getCasesForDeplacementRecursifOuest(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice) {
	// C
	if (mobi_tmp == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x - 1, case_tmp.y);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x - 1, case_tmp.y);
		}
		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		int cost = this->caseJeu[tmp->y][tmp->x]->pmCost*2;

		mobi_tmp = mobi_tmp - cost;

		if (mobi_tmp < 0) {
			return;
		}
		if (this->caseJeu[tmp->y][tmp->x]->who == -1 && this->caseJeu[tmp->y][tmp->x]->types != "eau") {
			tab[indice] = *tmp;
			tabCost[indice] = mobi_de_base - mobi_tmp;
			indice++;
		}
		else {
			return;
		}
		this->getCasesForDeplacementRecursifOuest(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);
	}
}

void Carte::getCasesForDeplacementRecursifNordOuest(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice) {
	// NO
	if (mobi_tmp == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x - 1, case_tmp.y-1);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x , case_tmp.y-1);
		}
		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		int cost = this->caseJeu[tmp->y][tmp->x]->pmCost;

		mobi_tmp = mobi_tmp - cost;

		if (mobi_tmp < 0) {
			return;
		}
		if (this->caseJeu[tmp->y][tmp->x]->who == -1 && this->caseJeu[tmp->y][tmp->x]->types != "eau") {
			tab[indice] = *tmp;
			tabCost[indice] = mobi_de_base - mobi_tmp;
			indice++;
		}
		else {
			return;
		}
		this->getCasesForDeplacementRecursifNordOuest(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);
	}
}
void Carte::getCasesForDeplacementRecursifNordEst(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice) {
	// NE
	if (mobi_tmp == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y-1);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x + 1, case_tmp.y-1);
		}
		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		int cost = this->caseJeu[tmp->y][tmp->x]->pmCost;

		mobi_tmp = mobi_tmp - cost;

		if (mobi_tmp < 0) {
			return;
		}
		if (this->caseJeu[tmp->y][tmp->x]->who == -1 && this->caseJeu[tmp->y][tmp->x]->types != "eau") {
			tab[indice] = *tmp;
			tabCost[indice] = mobi_de_base - mobi_tmp;
			indice++;
		}
		else {
			return;
		}
		this->getCasesForDeplacementRecursifNordEst(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);
	}
}
void Carte::getCasesForDeplacementRecursifSudOuest(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice) {
	// SO
	if (mobi_tmp == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x - 1, case_tmp.y+1);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y+1);
		}
		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		int cost = this->caseJeu[tmp->y][tmp->x]->pmCost;

		mobi_tmp = mobi_tmp - cost;

		if (mobi_tmp < 0) {
			return;
		}
		if (this->caseJeu[tmp->y][tmp->x]->who == -1 && this->caseJeu[tmp->y][tmp->x]->types != "eau") {
			tab[indice] = *tmp;
			tabCost[indice] = mobi_de_base - mobi_tmp;
			indice++;
		}
		else {
			return;
		}
		this->getCasesForDeplacementRecursifSudOuest(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);
	}
}
void Carte::getCasesForDeplacementRecursifSudEst(sf::Vector2u * tab, int* tabCost, sf::Vector2u case_tmp, int mobi_tmp, int mobi_de_base, int indice) {
	// SE
	if (mobi_tmp == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x,  case_tmp.y+1);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x +1, case_tmp.y+1);
		}
		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		int cost = this->caseJeu[tmp->y][tmp->x]->pmCost;

		mobi_tmp = mobi_tmp - cost;

		if (mobi_tmp < 0) {
			return;
		}
		if (this->caseJeu[tmp->y][tmp->x]->who == -1 && this->caseJeu[tmp->y][tmp->x]->types != "eau") {
			tab[indice] = *tmp;
			tabCost[indice] = mobi_de_base - mobi_tmp;
			indice++;
		}
		else {
			return;
		}
		this->getCasesForDeplacementRecursifSudEst(tab, tabCost, *tmp, mobi_tmp, mobi_de_base, indice);
	}
}




void Carte::getCasesForCombatRecursifNord(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice) {
	if (range == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y - 2);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y - 2);
		}

		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		tab[indice] = *tmp;
		indice++;
		range--;
		
		this->getCasesForCombatRecursifNord(tab, *tmp, range, indice);
	}

}
void Carte::getCasesForCombatRecursifSud(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice) {
	if (range == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y + 2);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y + 2);
		}

		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		tab[indice] = *tmp;
		indice++;
		range--;

		this->getCasesForCombatRecursifSud(tab, *tmp, range, indice);
	}

}
void Carte::getCasesForCombatRecursifEst(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice) {
	if (range == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x + 1, case_tmp.y);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x + 1, case_tmp.y);
		}

		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		tab[indice] = *tmp;
		indice++;
		range--;

		this->getCasesForCombatRecursifEst(tab, *tmp, range, indice);
	}


}
void Carte::getCasesForCombatRecursifOuest(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice) {
	if (range == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x - 1, case_tmp.y);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x - 1, case_tmp.y);
		}

		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		tab[indice] = *tmp;
		indice++;
		range--;

		this->getCasesForCombatRecursifOuest(tab, *tmp, range, indice);
	}

}

void Carte::getCasesForCombatRecursifNordOuest(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice) {
	if (range == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x - 1, case_tmp.y - 1);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y - 1);
		}

		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		tab[indice] = *tmp;
		indice++;
		range--;

		this->getCasesForCombatRecursifNordOuest(tab, *tmp, range, indice);
	}

}
void Carte::getCasesForCombatRecursifNordEst(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice) {
	if (range == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y - 1);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x + 1, case_tmp.y - 1);
		}

		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		tab[indice] = *tmp;
		indice++;
		range--;

		this->getCasesForCombatRecursifNordEst(tab, *tmp, range, indice);
	}

}
void Carte::getCasesForCombatRecursifSudOuest(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice) {
	if (range == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x - 1, case_tmp.y + 1);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y + 1);
		}

		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		tab[indice] = *tmp;
		indice++;
		range--;

		this->getCasesForCombatRecursifSudOuest(tab, *tmp, range, indice);
	}

}
void Carte::getCasesForCombatRecursifSudEst(sf::Vector2u * tab, sf::Vector2u case_tmp, int range, int indice) {
	if (range == 0) {
		return;
	}
	else {
		sf::Vector2u *tmp = NULL;
		if (case_tmp.y % 2 == 0) {
			tmp = new sf::Vector2u(case_tmp.x, case_tmp.y + 1);
		}
		else {
			tmp = new sf::Vector2u(case_tmp.x + 1, case_tmp.y + 1);
		}

		if (tmp->y < 0 || tmp->y >11 || tmp->x <0 || tmp->x > 10) {
			return;
		}
		tab[indice] = *tmp;
		indice++;
		range--;

		this->getCasesForCombatRecursifSudEst(tab, *tmp, range, indice);
	}

}


			

