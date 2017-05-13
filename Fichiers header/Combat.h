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
	bool simulationCombat(PersonnageYoan* attaquant, PersonnageYoan* victime);

};

