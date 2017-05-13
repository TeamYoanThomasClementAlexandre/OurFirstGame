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

int InteractionBDD::requeteParCol(string joueur, string nomTable, string nomCol) {
	/*
	---------joueur -> nom du joueur connecté
	---------nomTable -> "Personnages" ou "Equipements" ou " Personnages et Equipements"
	---------nomCol -> "force" ou "vie" ou "déplacement"
	*/
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	unsigned int nbr_champs = 0;
	int i;
	string requete;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{
		/*
		-----------------------------------------------------------------------------
		|			DANS LE CAS OU ON VEUX LES STATS GLOABAUX                        |
		-----------------------------------------------------------------------------
		*/
		if (nomCol == "personnage et equipements") {
			requete = "SELECT Personnages." + nomCol + " FROM " ";";
			mysql_query(&mysql, requete.c_str());
			result = mysql_store_result(&mysql);
			nbr_champs = mysql_num_fields(result);
			while (row = mysql_fetch_row(result)) {
				for (i = 0; i < nbr_champs; i++) { // parcourt toutes les colonnes de la table
					printf(" %s", row[i]);
				}
				printf("\n");
			}
			mysql_free_result(result); // libère la requete pour reuse result
		}
		else {
			requete = "SELECT " + nomCol + " FROM compte;";
			mysql_query(&mysql, requete.c_str());
			result = mysql_store_result(&mysql);
			nbr_champs = mysql_num_fields(result);
			printf("%d", nbr_champs);
			while (row = mysql_fetch_row(result)) {
				for (i = 0; i < nbr_champs; i++) { // parcourt toutes les colonnes de la table
					printf(" %s", row[i]);
				}
				printf("\n");
			}
			mysql_free_result(result); // libère la requete pour reuse result
		}
	}
	else {
		printf("erreur de connexion");
	}
	mysql_close(&mysql); // ferme la connexion à la BD
	return 1;
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
	int idEquipement = 0;


	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{

		requeteString = "SELECT idCarac0,idEquipement,idEquipement2,idEquipement3 from Personnages where loginUser='" + joueur + "' AND typePersonnage='" + classe + "';";
		mysql_query(&mysql, requeteString.c_str());

		result = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(result)) {
			nbr_champs = mysql_num_fields(result);
			for (i = 0; i < nbr_champs; i++) {
				if (i == 0) {
					// on est à carac0 nouvelle requete
					sprintf(requeteInt, "Select degat,vie,mouvement,armure from Carac where idCarac=%d", std::stoi(row[i]));
					mysql_query(&mysql, requeteInt);
					result2 = mysql_store_result(&mysql);
					while (row2 = mysql_fetch_row(result2)) {
						nbr_champs2 = mysql_num_fields(result2);
						for (n = 0; n < nbr_champs2; n++) {
							tableauCarac[n] = std::stoi(row2[n]);
						}
					}
					mysql_free_result(result2);
				}
				else {
					// on est aux idEquipement
					if (row[i] != NULL) {// il a un equipement
						printf("il y a un equipement");
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

	char requeteInt[200];
	string requeteString;
	int refEquipement = -1;
	unsigned int nbr_champs = 0;
	unsigned int nbr_champs2 = 0;
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
	*/

	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{
		requeteString = "Select refIdEquipement from Possede where refLogin='" + joueur + "';";
		mysql_query(&mysql, requeteString.c_str());

		result = mysql_store_result(&mysql);
		row = mysql_fetch_row(result);
		if (row[0] != NULL) {
			refEquipement = std::stoi(row[0]);
			printf("loooool %d\n", refEquipement);
		}
		mysql_free_result(result);


		if (refEquipement != -1) {
			sprintf(requeteInt, "Select typeEquipement,nomEquipement,url,idCarac0 from Equipements where idEquipement=%d", refEquipement);
			mysql_query(&mysql, requeteInt);

			result = mysql_store_result(&mysql);
			nbr_champs = mysql_num_fields(result);
			n = 0;
			/* ici on remplit l'indie 0 et 1*/
			while (row = mysql_fetch_row(result)) {//toutes les lignes
				tableauCarac.push_back(vector<string>(7));
				if (row[0] == NULL) {
					// le compte ne possède pas d'équipements
				}
				else {
					for (i = 0; i < nbr_champs; i++) {// toutes les cols
						printf("%s\n", row[i]);
						tableauCarac[n][i] = row[i];
						if (i == 3) {
							sprintf(requeteInt, "Select degat,vie,armure,mouvement from Carac where idCarac=%d", std::stoi(row[i]));
							mysql_query(&mysql, requeteInt);

							result2 = mysql_store_result(&mysql);
							nbr_champs2 = mysql_num_fields(result2);
							row2 = mysql_fetch_row(result2);
							for (z = 0; z < nbr_champs2; z++) {
								printf("%s\n", row2[z]);
								tableauCarac[n][z + 3] = row2[z];
							}
							mysql_free_result(result2);
						}
					}
				}
				n++;
			}
			mysql_free_result(result);
		}
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
		printf("%s\n", joueur2.c_str());
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
					printf("il y a un equipement");
					sprintf(requeteInt, "Select typeEquipement,nomEquipement,url,idCarac0 from Equipements where idEquipement=%d", std::stoi(row[i]));
					mysql_query(&mysql, requeteInt);
					result2 = mysql_store_result(&mysql);
					while (row2 = mysql_fetch_row(result2)) {
						nbr_champs2= mysql_num_fields(result2);
						for (n = 0; n < nbr_champs2; n++) {
							if (n == 3) {// on a recup idCarac0
								// on recupere force vie .... nouvelle requete
								sprintf(requeteInt, "Select degat,vie,mouvement,armure from Carac where idCarac=%d", std::stoi(row2[n]));
								mysql_query(&mysql, requeteInt);
								result3 = mysql_store_result(&mysql);
								while (row3 = mysql_fetch_row(result3)) {
									nbr_champs3= mysql_num_fields(result3);
									for (z = 0; z < nbr_champs3; z++) {
										printf("=>%d\n", z);
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
	char requeteInt[300];

	unsigned int nbr_champs = 0;
	int i;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{
		requeteString = "select idEquipement from Personnages where typePersonnage='" + classe + "' and loginUser='" + joueur + "';";
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
