#include <winsock.h>
#include <mysql/mysql.h>
#include "..\\Fichiers header\Fenetre.h"
int main()
{
	/*MYSQL mysql;
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	unsigned int nbr_champs = 0;
	int i;

	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	if (mysql_real_connect(&mysql, "dwarves.iut-fbleau.fr", "barbier", "barbier", "barbier", 0, NULL, 0) != NULL)
	{
		mysql_query(&mysql, "SELECT passwd,user FROM compte");
		result = mysql_store_result(&mysql);
		nbr_champs= mysql_num_fields(result);
		while (row = mysql_fetch_row(result)){
			for (i = 0; i < nbr_champs; i++) {
				printf(" %s", row[i]);
			}
			printf("\n");
		}
		mysql_free_result(result);
		mysql_close(&mysql);
	}
	else
	{
		printf("non");
	}
	char * utilisateur;
	utilisateur = "clément";*/


	Fenetre test(960,540);
	return 0;
}