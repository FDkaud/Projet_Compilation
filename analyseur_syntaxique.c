#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboles.h"
#include "util.h"
#include "analyseur_syntaxique.h"
#include "premiers.h"
#include "suivants.h"


int yylex(void);
extern char *yytext;
FILE *yyin;


void programme ()
{
	ouverture(__FUNCTION__);
	if ((est_premier(uniteCourante, _optDecVariables_) == 1) || (est_premier(uniteCourante, _listeDecFonctions_) == 1))//( remplaceuniteCourante == NOMBRE)
	{
		optDecVariables ();
		listeDecFonctions ();
		fermeture(__FUNCTION__);
		return;
	}
	
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s,%s\n Erreur: FONCTION, NOMBRE ou FIN demandes\n", yytext, valeur);
		exit (-1);
	}
}

void optDecVariables ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _listeDecVariables_) == 1)//( remplace uniteCourante == NOMBRE)
	{
		listeDecVariables ();
		affichage(POINT_VIRGULE, &uniteCourante);  // Consome ';' remplace // uniteCourante = yylex();
		fermeture(__FUNCTION__);
		return;
	}
	
	else if (est_suivant(uniteCourante, _optDecVariables_) == 1)
	{
		// si on a  Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur FONCTION, NOMBRE ou '{' demandes\n", yytext, valeur);
		exit (-1);
	}
	
}

void listeDecVariables ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _declarationVariable_) == 1)
	{
		declarationVariable ();
		listeDecVariablesBis ();
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s,%s\n Erreur NOMBRE demande\n", yytext, valeur);
		exit (-1);
	}
}

void listeDecVariablesBis ()
{
	ouverture(__FUNCTION__);	
	
	if (uniteCourante == VIRGULE)
	{
		affichage(VIRGULE, &uniteCourante); // Consome ','
		declarationVariable ();
		listeDecVariablesBis ();
		fermeture(__FUNCTION__);
		return;
	}
	
		// Epsilon
	
	else if (est_suivant(uniteCourante, _listeDecVariablesBis_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\n Erreur : ';', ',' ou '(' demandes \n", yytext, valeur);
		exit (-1);
	}
}

void declarationVariable ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ENTIER)
	{
		affichage(ENTIER, &uniteCourante); // Consome entier
		// Verifier si id_var present?
		affichage(ID_VAR, &uniteCourante);  // Consome id_var
		
		optTailleTableau ();
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : NOMBRE demande.\n", yytext, valeur);
		exit (-1);
	}
}

void optTailleTableau ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == CROCHET_OUVRANT)
	{ 
		affichage(CROCHET_OUVRANT, &uniteCourante); // Consome '['
		affichage(NOMBRE, &uniteCourante); // Consome nombre
		affichage(CROCHET_FERMANT, &uniteCourante);  // Consome ']'
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_suivant(uniteCourante, _optTailleTableau_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : ';', ',' ou '(' demande.\n", yytext, valeur);
		exit (-1);
	}
}


void declarationFonction ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ID_FCT)
	{
		affichage(ID_FCT, &uniteCourante);  // Consome idf
		listeParam ();
		optDecVariables ();
		instructionBloc ();
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s,%s\nErreur : ';', ',' ou '(' demande\n", yytext, valeur);
		exit (-1);
	}
}

void listeDecFonctions ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _declarationFonction_) == 1)
	{
		declarationFonction ();
		listeDecFonctions ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_suivant(uniteCourante, _listeDecFonctions_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s,%s\n Erreur : ';', ',' ou '(' demande \n", yytext, valeur);
		exit (-1);
	}
}

void listeParam ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == PARENTHESE_OUVRANTE)
	{
		affichage(PARENTHESE_OUVRANTE, &uniteCourante);  // Consome '('
		optListeDecVariables();
		affichage(PARENTHESE_FERMANTE, &uniteCourante);  // Consome ')'
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : ';', ',' ou '(' demande.\n", yytext, valeur);
		exit (-1);
	}
}

void optListeDecVariables ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _listeDecVariables_) == 1)   // si l'unite courrante es t sur entier
	{
		listeDecVariables ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_suivant(uniteCourante, _optListeDecVariables_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s,%s\n Erreur: ';', ',' ou '(' demande\n", yytext, valeur);
		exit (-1);
	}
}
void instruction ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _instructionAffect_) == 1)
	{
		instructionAffect ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_premier(uniteCourante, _instructionBloc_) == 1)
	{
		instructionBloc ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_premier(uniteCourante, _instructionSi_) == 1)
	{
		instructionSi ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_premier(uniteCourante, _instructionTantque_) == 1)
	{
		instructionTantque ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_premier(uniteCourante, _instructionAppel_) == 1)
	{
		instructionAppel ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_premier(uniteCourante, _instructionRetour_) == 1)
	{
		instructionRetour ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_premier(uniteCourante, _instructionEcriture_) == 1)
	{
		instructionEcriture ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_premier(uniteCourante, _instructionVide_) == 1)
	{
		instructionVide ();
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : instruction demandee.\n", yytext, valeur);
		exit (-1);
	}
}

void instructionAffect ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _var_) == 1)
	{
		var ();
		affichage(EGAL, &uniteCourante); // Consome '='
		expression ();
		affichage(POINT_VIRGULE, &uniteCourante); // Consome ';'
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : var demandee.\n", yytext, valeur);
		exit (-1);
	}
}

void instructionBloc ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ACCOLADE_OUVRANTE)
	{
		affichage(ACCOLADE_OUVRANTE, &uniteCourante);  // Consome '{'
		listeInstructions ();
		affichage(ACCOLADE_FERMANTE, &uniteCourante); // Consome '}'
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : { demandee.\n", yytext, valeur);
		exit (-1);
	}
}

void listeInstructions ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _instruction_) == 1)
	{
		instruction ();
		listeInstructions ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_suivant(uniteCourante, _listeInstructions_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : liste d'instructions ou rien demande.\n", yytext, valeur);
		exit (-1);
	}
}
void instructionSi ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == SI)
	{
		affichage(SI, &uniteCourante); // Consome 'si'
		expression ();
		affichage(ALORS, &uniteCourante);  // Consome 'alr'
		instructionBloc ();
		optSinon ();
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : si demande.\n", yytext, valeur);
		exit (-1);
	}
}
void optSinon ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == SINON)
	{
		affichage(SINON, &uniteCourante);// Consome 'sin'
		instructionBloc ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_suivant(uniteCourante, _optSinon_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : sinon ou rien demande.\n", yytext, valeur);
		exit (-1);
	}
}
void instructionTantque ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == TANTQUE)
	{
		affichage(TANTQUE, &uniteCourante); // Consome 'tq'
		expression ();
		affichage(FAIRE, &uniteCourante);  // Consome 'fr'
		instructionBloc ();
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : tant que demande.\n", yytext, valeur);
		exit (-1);
	}
}
void instructionAppel ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _appelFct_) == 1)
	{
		appelFct ();
		affichage(POINT_VIRGULE, &uniteCourante); // Consome ';'
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : appel de fonction demandee.\n", yytext, valeur);
		exit (-1);
	}

}
void instructionRetour ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == RETOUR)
	{
		affichage(RETOUR, &uniteCourante); // Consome 'ret'
		expression ();
		affichage(POINT_VIRGULE, &uniteCourante); // Consome ';'
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : retour demande.\n", yytext, valeur);
		exit (-1);
	}
}
void instructionEcriture ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ECRIRE)
	{
		affichage(ECRIRE, &uniteCourante);  // Consome 'ecr'
		affichage(PARENTHESE_OUVRANTE, &uniteCourante);  // Consome '('
		expression ();
		affichage(PARENTHESE_FERMANTE, &uniteCourante);  // Consome ')'
		affichage(POINT_VIRGULE, &uniteCourante); // Consome ';'
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : ecrire demande.\n", yytext, valeur);
		exit (-1);
	}
}
void instructionVide ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == POINT_VIRGULE)
	{
		affichage(POINT_VIRGULE, &uniteCourante);  // Consome ';'
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : ; demande.\n", yytext, valeur);
		exit (-1);
	}
}
void expression ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _conjonction_) == 1)
	{
		conjonction ();
		expressionBis ();
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : expression demandee.\n", yytext, valeur);
		exit (-1);
	}
}
void expressionBis ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == OU)
	{
		affichage(OU, &uniteCourante);  // Consome '|'
		conjonction ();
		expressionBis ();
	}else if (uniteCourante == INTERROGATION)
	{
			affichage(INTERROGATION, &uniteCourante);
			expression();
			affichage(DEUXPOINTS, &uniteCourante);
			expression();
	}else if (est_suivant(uniteCourante, _expressionBis_) == 1)
	{ //epsilon
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : expression(bis) demande.\n", yytext, valeur);
		exit (-1);
	}
	fermeture(__FUNCTION__);
}
void conjonction ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _comparaison_) == 1)
	{
		comparaison ();
		conjonctionBis ();
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : conjonction demandee.\n", yytext, valeur);
		exit (-1);
	}
}
void conjonctionBis ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ET)
	{
		affichage(ET, &uniteCourante);  // Consome '&'
		negation ();
		conjonctionBis ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_suivant(uniteCourante, _conjonctionBis_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : expression(bis) demande.\n", yytext, valeur);
		exit (-1);
	}
}
void negation ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == NON)
	{
		affichage(NON, &uniteCourante);  // Consome '!'
		comparaison ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_premier(uniteCourante, _facteur_) == 1)
	{
		facteur ();
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : negation demande.\n", yytext, valeur);
		exit (-1);
	}
}
void comparaison ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _expArith_) == 1)
	{
		expArith();
		comparaisonBis ();
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : comparaison demandee.\n", yytext, valeur);
		exit (-1);
	}
}
void comparaisonBis ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == EGAL)
	{
		affichage(EGAL, &uniteCourante);  // Consome '='
		expArith ();
		comparaisonBis ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (uniteCourante == INFERIEUR)
	{
		affichage(INFERIEUR, &uniteCourante);  // Consome '<'
		expArith ();
		comparaisonBis ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_suivant(uniteCourante, _comparaisonBis_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : comparaison(bis) demande.\n", yytext, valeur);
		exit (-1);
	}
}
void expArith()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _terme_) == 1)
	{
		terme ();
		expArithBis ();
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : expArith demandee.\n", yytext, valeur);
		exit (-1);
	}
}
void expArithBis()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == PLUS)
	{
		affichage(PLUS, &uniteCourante);
		terme();
		expArithBis();
		fermeture(__FUNCTION__);	
		return;
	}
	if (uniteCourante == MOINS)
	{
		affichage(MOINS, &uniteCourante); 
		terme();
		expArithBis();
		fermeture(__FUNCTION__);	
		return;
	}
	else if (est_suivant(uniteCourante, _expArithBis_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : expArith(bis) demande.\n", yytext, valeur);
		exit (-1);
	}
}
void terme()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _negation_) == 1)
	{
		negation ();
		termeBis ();
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : terme demande.\n", yytext, valeur);
		exit (-1);
	}
}
void termeBis()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == FOIS)
	{
		affichage(FOIS, &uniteCourante); 
		negation();
		termeBis ();
		fermeture(__FUNCTION__);	
		return;
	}
	if (uniteCourante == DIVISE)
	{
		affichage(DIVISE, &uniteCourante); 
		negation();
		termeBis ();
		fermeture(__FUNCTION__);	
		return;
	}
	else if (est_suivant(uniteCourante, _termeBis_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\n Erreur : terme(bis) demande\n", yytext, valeur);
		exit (-1);
	}
}

void facteur()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == PARENTHESE_OUVRANTE)
	{
		affichage(PARENTHESE_OUVRANTE, &uniteCourante);
		expression ();
		if (uniteCourante == PARENTHESE_FERMANTE)
			affichage(PARENTHESE_FERMANTE, &uniteCourante); 
		else
		{
			nom_token( uniteCourante, nom, valeur );
			printf("%s (%s)\nErreur : ')' demande.\n", yytext, valeur);
			exit (-1);
		}
		fermeture(__FUNCTION__);	
		return;
	}
	else if (uniteCourante == NOMBRE)
	{
		affichage(NOMBRE, &uniteCourante);
		fermeture(__FUNCTION__);	
		return;
	}
	else if (est_premier(uniteCourante, _appelFct_) == 1)
	{
		appelFct ();
		fermeture(__FUNCTION__);	
		return;
	}
	else if (est_premier(uniteCourante, _var_) == 1)
	{
		var ();
		fermeture(__FUNCTION__);	
		return;
	}
	else if (uniteCourante == LIRE)
	{
		affichage(LIRE, &uniteCourante); // uniteCourante = yylex();
		if (uniteCourante == PARENTHESE_OUVRANTE)
		{
			affichage(PARENTHESE_OUVRANTE, &uniteCourante); // uniteCourante = yylex();
			affichage(PARENTHESE_FERMANTE, &uniteCourante); // uniteCourante = yylex();
			fermeture(__FUNCTION__);	
			return;
		}
		else
		{
			nom_token( uniteCourante, nom, valeur );
			printf("%s (%s)\nErreur : '(' demande.\n", yytext, valeur);
			exit (-1);
		}
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : facteur demande.\n", yytext, valeur);
		exit (-1);
	}
}

void var ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ID_VAR)
	{
		affichage(ID_VAR, &uniteCourante); // uniteCourante = yylex();
		optIndice();
		fermeture(__FUNCTION__);	
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : terme(bis) demande.\n", yytext, valeur);
		exit (-1);
	}
}
void optIndice ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == CROCHET_OUVRANT)
	{
		affichage(CROCHET_OUVRANT, &uniteCourante); 
		expression ();
		affichage(CROCHET_FERMANT, &uniteCourante); 
		fermeture(__FUNCTION__);	
		return;
	}
	else if (est_suivant(uniteCourante, _optIndice_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s,%s\n Erreur : optIndice demande.\n", yytext, valeur);
		exit (-1);
	}
}
void appelFct ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ID_FCT)
	{
		affichage(ID_FCT, &uniteCourante);
		affichage(PARENTHESE_OUVRANTE, &uniteCourante);
		listeExpressions ();
		affichage(PARENTHESE_FERMANTE, &uniteCourante);
		fermeture(__FUNCTION__);	
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur : appelFct demande.\n", yytext, valeur);
		exit (-1);
	}
}
void listeExpressions ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _expression_) == 1)
	{
		expression ();
		listeExpressionsBis ();
		fermeture(__FUNCTION__);
		return;
	}
	else if (est_suivant(uniteCourante, _listeExpressions_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s,%s\n Erreur : listeExpressions demande.\n", yytext, valeur);
		exit (-1);
	}
}
void listeExpressionsBis ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == VIRGULE)
	{
		affichage(VIRGULE, &uniteCourante);
		expression ();
		listeExpressionsBis ();
		fermeture(__FUNCTION__);	
		return;
	}
	else if (est_suivant(uniteCourante, _listeExpressionsBis_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\n Erreur:listeExpressionsBis demande.\n", yytext, valeur);
		exit (-1);
	}
}

