#pragma once
#include "PersonnageYoan.h"
#include <cstdlib>
#include <ctime> 
class Combat
{
private:
	bool coupCritique();
public:
	Combat();
	~Combat();
	void simulationCombat(PersonnageYoan* attaquant, PersonnageYoan* victime,Carte c);

};

