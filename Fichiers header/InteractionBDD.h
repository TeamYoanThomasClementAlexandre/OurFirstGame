#ifndef __INTERACTIONBDD_H__
#define __INTERACTIONBDD_H__

#include <winsock.h>
#include<vector>
#include <mysql/mysql.h>
#include <stdio.h>
#include <string>
using namespace std;


class InteractionBDD
{
private:
	InteractionBDD();
	~InteractionBDD();
	MYSQL mysql;
	static InteractionBDD *bdd;
	
public:
	

	static InteractionBDD* Ini();
	int requeteParCol(string joueur,string nomTable,string nomCol);
	int* getCarac(string joueur, string classe);
	vector<vector<string>> getEquipement(string joueur);
	vector<vector <string>> InteractionBDD::getEquipementEquiped(string joueur, string classe);
	bool exist(string joueur2);
	string getUrl(string joueur, string classe);
};

#endif

