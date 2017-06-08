#include "..\Fichiers header\InteractionBDD.h"

InteractionBDD *InteractionBDD::bdd = NULL;

InteractionBDD * InteractionBDD::Ini()
{
	if (bdd == NULL)
		bdd = new InteractionBDD();
	return bdd;
}

InteractionBDD::InteractionBDD()
{
}

InteractionBDD::~InteractionBDD()
{
}

int InteractionBDD::requeteParCol(string joueur, string nomTable, string nomCol, string classe) {
	/*
	---------joueur -> nom du joueur connecté
	---------nomTable -> "Personnages" ou "Equipements" ou " Personnages et Equipements"
	---------nomCol -> "force" ou "vie" ou "déplacement" ou "niveau"
	---------nomClasse -> " Archer" etc
	*/
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	unsigned int nbr_champs = 0;
	int i;
	int champsAreturn = 0;
	string requete;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{
		requete = "SELECT " + nomCol + " FROM Personnages where loginUser='"+ joueur +"' and  typePersonnage='" + classe + "';";
		mysql_query(&mysql, requete.c_str());
		result = mysql_store_result(&mysql);
		row = mysql_fetch_row(result); // on a le resultat enq uestion
		champsAreturn = std::stoi(row[0]);
		mysql_free_result(result); // libère la requete pour reuse result
	}
	else {
		printf("erreur de connexion");
	}
	mysql_close(&mysql); // ferme la connexion à la BD
	return champsAreturn;
}

int* InteractionBDD::getCarac(string joueur, string classe) {
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;

	MYSQL_RES *result2 = NULL;
	MYSQL_ROW row2;

	string requeteString;
	char requeteInt[200];

	int *tableauCarac = new int[4];// va contenir force,vie,armure,déplacement


	unsigned int nbr_champs = 0;
	unsigned int nbr_champs2 = 0;
	int i;
	int n;
	int levelPersonnage = 0;
	int idEquipement = 0;


	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{

		requeteString = "SELECT level,idCarac0,idEquipement,idEquipement2,idEquipement3 from Personnages where loginUser='" + joueur + "' AND typePersonnage='" + classe + "';";
		mysql_query(&mysql, requeteString.c_str());

		result = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(result)) {
			nbr_champs = mysql_num_fields(result);
			for (i = 0; i < nbr_champs; i++) {
				if (i == 0) {
					levelPersonnage = std::stoi(row[i]);
				}
				else if (i == 1) {
					// on est à carac0 nouvelle requete
					sprintf(requeteInt, "Select degat,vie,mouvement,armure from Carac where idCarac=%d", std::stoi(row[i]));
					mysql_query(&mysql, requeteInt);
					result2 = mysql_store_result(&mysql);
					while (row2 = mysql_fetch_row(result2)) {
						nbr_champs2 = mysql_num_fields(result2);
						for (n = 0; n < nbr_champs2; n++) {
							if (n < 2)
								tableauCarac[n] = std::stoi(row2[n]) + (levelPersonnage * 5);// on le fait que pr dgt et vie
							else {
								tableauCarac[n] = std::stoi(row2[n]);
							}
						}
					}
					mysql_free_result(result2);
				}
				else {
					// on est aux idEquipement
					if (row[i] != NULL) {// il a un equipement
						sprintf(requeteInt, "Select idCarac0 from Equipements where idEquipement=%d", std::stoi(row[i]));
						mysql_query(&mysql, requeteInt);
						result2 = mysql_store_result(&mysql);
						row2 = mysql_fetch_row(result2);
						idEquipement = std::stoi(row2[0]);//on stock l'idCarac
						mysql_free_result(result2);// on libère l'ancier resultat et on recommence

						sprintf(requeteInt, "Select degat,vie,mouvement,armure from Carac where idCarac=%d", idEquipement);
						mysql_query(&mysql, requeteInt);
						result2 = mysql_store_result(&mysql);
						while (row2 = mysql_fetch_row(result2)) {
							nbr_champs2 = mysql_num_fields(result2);
							for (n = 0; n < nbr_champs2; n++) {
								tableauCarac[n] = tableauCarac[n] + std::stoi(row2[n]);
							}
						}
						mysql_free_result(result2);// on libère l'ancier resultat et on recommence
					}
				}
			}
		}
		mysql_free_result(result);// on libère l'ancier resultat et on recommence
	}
	else {
		printf("erreur de connexion");
	}
	mysql_close(&mysql); // ferme la connexion à la BD
	return tableauCarac;
}

vector<vector <string>> InteractionBDD::getEquipement(string joueur) {
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;

	MYSQL_RES *result2 = NULL;
	MYSQL_ROW row2;

	MYSQL_RES *result3 = NULL;
	MYSQL_ROW row3;

	char requeteInt[200];
	string requeteString;
	int refEquipement = -1;
	unsigned int nbr_champs = 0;
	unsigned int nbr_champs2 = 0;
	int i;
	int n=0;
	int z;
	int y;
	vector<vector<string>> tableauCarac(0, vector<string>(7));
	/* 0         -> nom
	   1         -> lien image
	   2         -> type Equipement
	   3         -> Force
	   4         -> Vie
	   5         -> Armure
	   6         -> Deplacement
	*/

	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{
		requeteString = "Select refIdEquipement from Possede where refLogin='" + joueur + "';";
		mysql_query(&mysql, requeteString.c_str());

		result = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(result)) {
			if (row[0] != NULL) {
				//refEquipement = std::stoi(row[y]);
				//printf("loooool %d\n", refEquipement);



				if (std::stoi(row[0]) != -1) {
					sprintf(requeteInt, "Select typeEquipement,nomEquipement,url,idCarac0 from Equipements where idEquipement=%d", std::stoi(row[0]));
					mysql_query(&mysql, requeteInt);

					result3 = mysql_store_result(&mysql);
					nbr_champs = mysql_num_fields(result3);
					
					/* ici on remplit l'indie 0 et 1*/
					while (row3 = mysql_fetch_row(result3)) {//toutes les lignes
						tableauCarac.push_back(vector<string>(7));
						if (row3[0] == NULL) {
							// le compte ne possède pas d'équipements
						}
						else {
							for (i = 0; i < nbr_champs; i++) {// toutes les cols
								tableauCarac[n][i] = row3[i];
								if (i == 3) {
									sprintf(requeteInt, "Select degat,vie,armure,mouvement from Carac where idCarac=%d", std::stoi(row3[i]));
									mysql_query(&mysql, requeteInt);

									result2 = mysql_store_result(&mysql);
									nbr_champs2 = mysql_num_fields(result2);
									row2 = mysql_fetch_row(result2);
									for (z = 0; z < nbr_champs2; z++) {
										tableauCarac[n][z + 3] = row2[z];
									}
									mysql_free_result(result2);
									
								}
								
							}
							
						}
						n++;
					}
					mysql_free_result(result3);
				}
			}
			//tableauCarac.push_back(vector<string>(1));
		}
		mysql_free_result(result);
	}
	else {
		printf("Problème de connexion");
	}
	mysql_close(&mysql); // ferme la connexion à la BD
	return tableauCarac;
}

bool InteractionBDD::exist(string joueur2) {
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	string requeteString;
	unsigned int nbr_champs = 0;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{
		requeteString = "Select compte.login from compte where compte.login='" + joueur2 + "';";
		mysql_query(&mysql, requeteString.c_str());

		result = mysql_store_result(&mysql);
		if (result->row_count == 0) {
			mysql_free_result(result);
			mysql_close(&mysql); // ferme la connexion à la BD

			return false;
		}
		else {
			mysql_free_result(result);
			mysql_close(&mysql); // ferme la connexion à la BD

			return true;
		}
	}
	else {
		printf("erreur de connexion à la BD");
	}
}

vector<vector <string>> InteractionBDD::getEquipementEquiped(string joueur, string classe) {
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;

	MYSQL_RES *result2 = NULL;
	MYSQL_ROW row2;

	MYSQL_RES *result3 = NULL;
	MYSQL_ROW row3;

	char requeteInt[200];
	string requeteString;
	int idEquipement = 0;
	unsigned int nbr_champs = 0;
	unsigned int nbr_champs2 = 0;
	unsigned int nbr_champs3 = 0;
	int nbr_ligne = 0;
	int i;
	int n;
	int z;
	vector<vector<string>> tableauCarac(0, vector<string>(7));
	/* 0         -> nom
	1         -> lien image
	2         -> type Equipement
	3         -> Force
	4         -> Vie
	5         -> Armure
	6         -> Deplacement

	a changé toi meme !
	*/

	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{
		requeteString = "SELECT idEquipement,idEquipement2,idEquipement3 from Personnages where loginUser='" + joueur + "' AND typePersonnage='" + classe + "';";
		mysql_query(&mysql, requeteString.c_str());

		result = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(result)) {
			nbr_champs = mysql_num_fields(result);
			for (i = 0; i < nbr_champs; i++) {
				// on est aux idEquipement
				if (row[i] != NULL) {// il a un equipement
					tableauCarac.push_back(vector<string>(7)); // on ajoute une ligne à notre tableau dynamique !!
					sprintf(requeteInt, "Select typeEquipement,nomEquipement,url,idCarac0 from Equipements where idEquipement=%d", std::stoi(row[i]));
					mysql_query(&mysql, requeteInt);
					result2 = mysql_store_result(&mysql);
					while (row2 = mysql_fetch_row(result2)) {
						nbr_champs2 = mysql_num_fields(result2);
						for (n = 0; n < nbr_champs2; n++) {
							if (n == 3) {// on a recup idCarac0
								// on recupere force vie .... nouvelle requete
								sprintf(requeteInt, "Select degat,vie,mouvement,armure from Carac where idCarac=%d", std::stoi(row2[n]));
								mysql_query(&mysql, requeteInt);
								result3 = mysql_store_result(&mysql);
								while (row3 = mysql_fetch_row(result3)) {
									nbr_champs3 = mysql_num_fields(result3);
									for (z = 0; z < nbr_champs3; z++) {
										tableauCarac[nbr_ligne][z + 3] = row3[z];
									}
								}
								mysql_free_result(result3);

							}
							else {
								tableauCarac[nbr_ligne][n] = row2[n];// i n'est pas une source sure
							}
						}
					}
					mysql_free_result(result2);// on libère l'ancier resultat et on recommence
					nbr_ligne++;
				}
			}
		}
		mysql_free_result(result);// on libère l'ancier resultat et on recommence
	}
	else {
		printf("Problème de connexion");
	}
	mysql_close(&mysql); // ferme la connexion à la BD
	return tableauCarac;
}


string InteractionBDD::getUrl(string joueur, string classe) {
	string url;


	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	MYSQL_RES *result2 = NULL;
	MYSQL_ROW row2;

	string requeteString;
	char requeteInt[200];

	unsigned int nbr_champs = 0;
	int i;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{
		requeteString = "select idEquipement from Personnages where typePersonnage='" + classe + "' and	loginUser='" + joueur + "';";
		mysql_query(&mysql, requeteString.c_str());
		result = mysql_store_result(&mysql);
		row = mysql_fetch_row(result); // on a l'id de l'equipement en question

		sprintf(requeteInt, "select url from Equipements where idEquipement=%d;", std::stoi(row[0]));
		mysql_query(&mysql, requeteInt);
		result2 = mysql_store_result(&mysql);
		row2 = mysql_fetch_row(result2); // on a recupéré l'url
		url = row2[0];
		mysql_free_result(result);
		mysql_free_result(result2);
	}
	else {
		printf("erreur de connexion");
	}
	mysql_close(&mysql); // ferme la connexion à la BD

	return url;
}

void InteractionBDD::setEquipementOnChar(string nomEquipement, string typeEquipement, string joueur, string classe) {
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;

	string requeteString;
	char requeteInt[200];

	int i;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{
		requeteString = "select idEquipement from Equipements where nomEquipement='" + nomEquipement + "';";
		mysql_query(&mysql, requeteString.c_str());
		result = mysql_store_result(&mysql);
		row = mysql_fetch_row(result); // on a l'id de l'equipement en question
		if (typeEquipement == "armure") {
			sprintf(requeteInt, "Update Personnages set idEquipement2=%d where loginUser='%s' and typePersonnage='%s'", std::stoi(row[0]), joueur.c_str(), classe.c_str());
		}
		else if (typeEquipement == "autre") {
			sprintf(requeteInt, "Update Personnages set idEquipement3=%d where loginUser='%s' and typePersonnage='%s'", std::stoi(row[0]), joueur.c_str(), classe.c_str());
		}
		else {
			sprintf(requeteInt, "Update Personnages set idEquipement=%d where loginUser='%s' and typePersonnage='%s'", std::stoi(row[0]), joueur.c_str(), classe.c_str());
		}
		mysql_query(&mysql, requeteInt);
		mysql_free_result(result);

	}
	else {
		printf("erreur de connexion");
	}
	mysql_close(&mysql); // ferme la connexion à la BD
}

void InteractionBDD::setXP(int nombre, string joueur, string classe) {
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;

	string requeteString;
	char requeteInt[200];

	int i;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{
		sprintf(requeteInt, "Update Personnages set experience=%d where loginUser='%s' and typePersonnage='%s'", nombre, joueur.c_str(), classe.c_str());
		mysql_query(&mysql, requeteInt);

	}
	else {
		printf("erreur de connexion");
	}
	mysql_close(&mysql); // ferme la connexion à la BD
}


string* InteractionBDD::dropEquipement(string joueur) {
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	MYSQL_RES *result2 = NULL;
	MYSQL_ROW row2;

	string requeteString;
	char requeteInt[200];

	string* armeDropped=new string[3];
	unsigned int nbr_champs = 0;
	int nbrAlea=0;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL) {
		requeteString = "select MAX(idEquipement) from Equipements;";
		mysql_query(&mysql, requeteString.c_str());
		result = mysql_store_result(&mysql);
		row = mysql_fetch_row(result); // on a le nbr max d'equipements
		nbrAlea = rand() % stoi(row[0]) + 1;// on a un nbr d'equipement aléa il faut regarder son ratio pour le drop
		mysql_free_result(result);

		sprintf(requeteInt, "select txDrop,typeEquipement,nomEquipement,url from Equipements where idEquipement=%d;", nbrAlea);
		mysql_query(&mysql, requeteInt);
		result2= mysql_store_result(&mysql);
		row2 = mysql_fetch_row(result2); // on a les infos sur l'equipement en question
		if (rand() % 100 + 1 < stoi(row2[0])) {// si txDrop =80 et le rand est 81 on gagne pas l'item
			// on est dans le cas ou on a gagné l'item
			armeDropped[0] = row2[1];
			armeDropped[1] = row2[2];
			armeDropped[2] = row2[3];
		}
		else {
			armeDropped[0] = "null";
			armeDropped[1] = "null";
			armeDropped[2] = "null";
		}
	}
	else {
		printf("erreur de connexion");
	}
	mysql_close(&mysql); // ferme la connexion à la BD
	return armeDropped;
}

