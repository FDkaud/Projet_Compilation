#include "analyseur_syntaxique.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboles.h"
#include "util.h"
#include "premiers.h"
#include "suivants.h"

FILE *yyin;
int yylex(void);
extern char *yytext;
FILE *yyin;


int main (int argc, char **argv)
{	 
	type_aff = STD_OUT;
	mode_aff = NO_DISPLAY;
	trace_xml = 0;
	vue = stdout;
	
	if (argc < 2)
	{
		
		return 0;
	}

	int i = 1;

	if (argc > 2)
		if (strcmp(argv[i],"-s") == 0)
		{
			trace_xml = 1;
			mode_aff = XML_DISPLAY;
			i++;
		}

	yyin = fopen(argv[i], "r");
	
	if(yyin == NULL)
	{
		fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", argv[i]);
		exit(1);
	}

	
	if (argc > 2)
	{
		for (; i < argc ; i++)
		{
			if (strcmp(argv[i], "-f") == 0)
			{
				i++;
				vue = fopen(argv[i], "w+");
				if (vue == NULL)
				{
					fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", argv[i]);
					exit(1);
				}
				//printf("Stockage dans %s\n", argv[i]);
			}
			
		}
	}
	
	initialise_premiers();
	initialise_suivants();

	uniteCourante = yylex();
	programme();
	
	if (uniteCourante == FIN)
	{
		
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		//printf("%s (%s)\n Erreur de syntaxe : symbolme  FIN attendu.\n", yytext, valeur);
	}

	if (vue != stdout)
		fclose(vue);
	
	return !(uniteCourante == FIN);
}
