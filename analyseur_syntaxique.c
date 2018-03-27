#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboles.h"
#include "util.h"
#include "analyseur_syntaxique.h"
#include "premiers.h"
#include "suivants.h"
#include "affiche_arbre_abstrait.h"

int yylex(void);
extern char *yytext;
FILE *yyin;

n_prog* programme ()
{
	ouverture(__FUNCTION__);
	if ((est_premier(uniteCourante, _optDecVariables_) == 1) || (est_premier(uniteCourante, _listeDecFonctions_) == 1))
	{
		n_l_dec *$1 = optDecVariables ();
		n_l_dec *$2 = listeDecFonctions ();
		fermeture(__FUNCTION__);

		n_prog* $$ = cree_n_prog ($1, $2);
		
		affiche_n_prog($$);
		return $$;
	}

	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : FONCTION, NOMBRE ou FIN attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_l_dec* optDecVariables ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _listeDecVariables_) == 1)
	{
		n_l_dec* $1 = listeDecVariables ();
		affichage(POINT_VIRGULE, &uniteCourante); // Consome ';'
		fermeture(__FUNCTION__);

		return $1;
	}
	
	else if (est_suivant(uniteCourante, _optDecVariables_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return NULL;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s %s\nErreur de syntaxe : FONCTION, NOMBRE ou '{' attendu.\n", yytext, valeur);
		exit (-1);
	}
	
}

n_l_dec* listeDecVariables ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _declarationVariable_) == 1)
	{
		n_dec* $1 = declarationVariable ();
		n_l_dec* $2 = listeDecVariablesBis ();
		fermeture(__FUNCTION__);
		n_l_dec *$$ = cree_n_l_dec($1, $2);
		
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : NOMBRE attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_l_dec* listeDecVariablesBis ()
{
	ouverture(__FUNCTION__);	
	
	if (uniteCourante == VIRGULE)
	{
		affichage(VIRGULE, &uniteCourante);  // Consome ','
		n_dec* $1 = declarationVariable ();
		n_l_dec* $2 = listeDecVariablesBis ();
		fermeture(__FUNCTION__);

		n_l_dec *$$ = cree_n_l_dec($1, $2);
		
		return $$;
	}
	
	else if (est_suivant(uniteCourante, _listeDecVariablesBis_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return NULL;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : ';', ',' ou '(' attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_dec* declarationVariable ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ENTIER)
	{
		affichage(ENTIER, &uniteCourante);  // Consome entier
		
		nom_token( uniteCourante, nom, valeur ); // Verifier présence id_var
		char* $1 = malloc(sizeof(char)*100);
		strcpy($1, valeur);
		affichage(ID_VAR, &uniteCourante);  // Consome id_var
		
		int $2 = optTailleTableau ();
		fermeture(__FUNCTION__);

		n_dec *$$ = NULL;

		if ($2 > 0)
		{
			$$ = cree_n_dec_tab($1,$2);
			
		}
		else
		{			
			$$ = cree_n_dec_var($1);
			
		}
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : NOMBRE attendu.\n", yytext, valeur);
		exit (-1);
	}
}

int optTailleTableau ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == CROCHET_OUVRANT)
	{
		affichage(CROCHET_OUVRANT, &uniteCourante);  // Consome '['
		nom_token( uniteCourante, nom, valeur );
		affichage(NOMBRE, &uniteCourante);  // Consome nombre
		affichage(CROCHET_FERMANT, &uniteCourante); // Consome ']'
		fermeture(__FUNCTION__);
		
		return atoi(valeur);
	}
	else if (est_suivant(uniteCourante, _optTailleTableau_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return -1;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : ';', ',' ou '(' attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_l_dec* listeDecFonctions ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _declarationFonction_) == 1)
	{
		n_dec *$1 = declarationFonction ();
		n_l_dec *$2 = listeDecFonctions ();
		fermeture(__FUNCTION__);

		n_l_dec *$$ = cree_n_l_dec($1, $2);
		
		return $$;
	}
	else if (est_suivant(uniteCourante, _listeDecFonctions_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return NULL;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : ';', ',' ou '(' attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_dec* declarationFonction ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ID_FCT)
	{
		nom_token( uniteCourante, nom, valeur );
		char* $1 = malloc(sizeof(char)*100);
		strcpy($1, valeur);

		affichage(ID_FCT, &uniteCourante); // Consome idf
		
		

		n_l_dec *$2 = listeParam ();
		n_l_dec *$3 = optDecVariables ();
		n_instr *$4 = instructionBloc ();
		fermeture(__FUNCTION__);

		n_dec *$$ = cree_n_dec_fonc($1, $2, $3, $4);
		
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : ';', ',' ou '(' attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_l_dec * listeParam ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == PARENTHESE_OUVRANTE)
	{
		affichage(PARENTHESE_OUVRANTE, &uniteCourante); // Consome '('
		n_l_dec* $$ = optListeDecVariables();
		affichage(PARENTHESE_FERMANTE, &uniteCourante); // Consome ')'
		fermeture(__FUNCTION__);
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : ';', ',' ou '(' attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_l_dec* optListeDecVariables ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _listeDecVariables_) == 1)//(uniteCourante == ENTIER)
	{
		n_l_dec* $1 = listeDecVariables ();
		fermeture(__FUNCTION__);
		return $1;
	}
	else if (est_suivant(uniteCourante, _optListeDecVariables_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return NULL;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : ';', ',' ou '(' attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_instr * instruction ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _instructionAffect_) == 1)
	{
		n_instr *$$ = instructionAffect ();
		fermeture(__FUNCTION__);
		return $$;
	}
	else if (est_premier(uniteCourante, _instructionBloc_) == 1)
	{
		n_instr *$$ = instructionBloc ();
		fermeture(__FUNCTION__);
		return $$;
	}
	else if (est_premier(uniteCourante, _instructionSi_) == 1)
	{
		n_instr *$$ = instructionSi ();
		fermeture(__FUNCTION__);
		return $$;
	}
	else if (est_premier(uniteCourante, _instructionTantque_) == 1)
	{
		n_instr *$$ = instructionTantque ();
		fermeture(__FUNCTION__);
		return $$;
	}
	else if (est_premier(uniteCourante, _instructionAppel_) == 1)
	{
		n_instr *$$ = instructionAppel ();
		fermeture(__FUNCTION__);
		return $$;
	}
	else if (est_premier(uniteCourante, _instructionRetour_) == 1)
	{
		n_instr *$$ = instructionRetour ();
		fermeture(__FUNCTION__);
		return $$;
	}
	else if (est_premier(uniteCourante, _instructionEcriture_) == 1)
	{
		n_instr *$$ = instructionEcriture ();
		fermeture(__FUNCTION__);
		return $$;
	}
	else if (est_premier(uniteCourante, _instructionVide_) == 1)
	{
		n_instr *$$ = instructionVide ();
		fermeture(__FUNCTION__);
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : instruction attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_instr * instructionAffect ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _var_) == 1)
	{
		n_var *$1 = var ();
		affichage(EGAL, &uniteCourante); // uniteCourante = yylex(); // Consome '='
		n_exp *$2 = expression ();
		affichage(POINT_VIRGULE, &uniteCourante); // uniteCourante = yylex(); // Consome ';'
		fermeture(__FUNCTION__);

		n_instr *$$ = cree_n_instr_affect($1, $2);
		
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s %s\nErreur de syntaxe : var attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_instr * instructionBloc ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ACCOLADE_OUVRANTE)
	{
		affichage(ACCOLADE_OUVRANTE, &uniteCourante);  // Consome '{'
		n_l_instr *$1 = listeInstructions ();
		affichage(ACCOLADE_FERMANTE, &uniteCourante);  // Consome '}'
		fermeture(__FUNCTION__);

		n_instr *$$ = cree_n_instr_bloc($1);
		
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s %s\nErreur de syntaxe : { attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_l_instr * listeInstructions ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _instruction_) == 1)
	{
		n_instr *$1 = instruction ();
		n_l_instr *$2 = listeInstructions ($1);
		fermeture(__FUNCTION__);
		
		n_l_instr *$$ = cree_n_l_instr($1, $2);
		
		return $$;
	}
	else if (est_suivant(uniteCourante, _listeInstructions_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return NULL;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : liste d'instructions ou rien attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_instr * instructionSi ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == SI)
	{
		affichage(SI, &uniteCourante); // uniteCourante = yylex(); // Consome 'si'
		n_exp *$1 = expression ();
		affichage(ALORS, &uniteCourante); // uniteCourante = yylex(); // Consome 'alr'
		n_instr *$2 = instructionBloc ();
		n_instr *$3 = optSinon ();
		fermeture(__FUNCTION__);
		
		n_instr *$$ = cree_n_instr_si($1, $2, $3);
		
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : si attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_instr * optSinon ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == SINON)
	{
		affichage(SINON, &uniteCourante);  // Consome 'sin'
		n_instr * $1 = instructionBloc ();
		fermeture(__FUNCTION__);
		return $1;
	}
	else if (est_suivant(uniteCourante, _optSinon_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return NULL;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s %s\nErreur de syntaxe : sinon ou vide attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_instr * instructionTantque ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == TANTQUE)
	{
		affichage(TANTQUE, &uniteCourante);  // Consome 'tq'
		n_exp *$1 = expression ();
		affichage(FAIRE, &uniteCourante); // Consome 'fr'
		n_instr *$2 = instructionBloc ();
		fermeture(__FUNCTION__);
		
		n_instr *$$ = cree_n_instr_tantque($1, $2);
		
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s %s\nErreur de syntaxe : tant que attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_instr * instructionAppel ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _appelFct_) == 1)
	{
		n_appel *$1 = appelFct ();
		affichage(POINT_VIRGULE, &uniteCourante); // Consome ';'
		fermeture(__FUNCTION__);
		
		n_instr *$$ = cree_n_instr_appel($1);
		
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s %s\n Erreur de syntaxe : appel de fonction attendu.\n", yytext, valeur);
		exit (-1);
	}

}

n_instr * instructionRetour ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == RETOUR)
	{
		affichage(RETOUR, &uniteCourante);  // Consome 'ret'
		n_exp *$1 = expression ();
		affichage(POINT_VIRGULE, &uniteCourante);  // Consome ';'
		fermeture(__FUNCTION__);
		
		n_instr *$$ = cree_n_instr_retour($1);
		
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s %s\n Erreur de syntaxe : retour attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_instr * instructionEcriture ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ECRIRE)
	{
		affichage(ECRIRE, &uniteCourante); // Consome 'ecr'
		affichage(PARENTHESE_OUVRANTE, &uniteCourante); // Consome '('

		n_exp *$1 = expression ();
		affichage(PARENTHESE_FERMANTE, &uniteCourante); // Consome ')'
		affichage(POINT_VIRGULE, &uniteCourante); // Consome ';'
		fermeture(__FUNCTION__);
		
		n_instr *$$ = cree_n_instr_ecrire($1);
		
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s %s\n Erreur de syntaxe : instruction ecrire attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_instr * instructionVide ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == POINT_VIRGULE)
	{
		affichage(POINT_VIRGULE, &uniteCourante);  // Consome ';'
		fermeture(__FUNCTION__);

		n_instr *$$ = cree_n_instr_vide();
		
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : ; attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * expression ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _conjonction_) == 1)
	{
		n_exp *$1 = conjonction ();
		n_exp *$2 = expressionBis ($1);
			
		fermeture(__FUNCTION__);

	
		return $2;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s %s\n Erreur de syntaxe : expression attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * expressionBis (n_exp * herite)
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == OU)
	{
		affichage(OU, &uniteCourante);  // Consome '|'
		n_exp *$1 = conjonction ();
		n_exp *$2 = cree_n_exp_op(ou, herite, $1); 
		n_exp *$3 = expressionBis ($2);
			
		fermeture(__FUNCTION__);

	
		
		return $3;
	}
	
	else if (uniteCourante == INTERROGATION)
	{	
		affichage(INTERROGATION, &uniteCourante); 
		n_exp *$1 = expression();
		affichage(DEUXPOINTS, &uniteCourante);
		n_exp *$2 = expression();
		fermeture(__FUNCTION__);
		
		n_exp *$$ = cree_n_exp_op(et, $1, $2); 
		
		return $$;
	}
	else if (est_suivant(uniteCourante, _expressionBis_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return herite;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s %s\n Erreur de syntaxe : expression(bis) attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * conjonction ()
{
	ouverture(__FUNCTION__);
	if (est_premier(uniteCourante, _comparaison_) == 1)
	{	
		n_exp *$1 = comparaison ();
		n_exp *$2 = conjonctionBis ($1);
		fermeture(__FUNCTION__);
		
		
		
		return $2;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s %s\n Erreur de syntaxe : conjonction attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * conjonctionBis (n_exp *herite)
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ET)
	{
		affichage(ET, &uniteCourante); // Consome '&'
		n_exp *$1 = comparaison();
		n_exp *$2 = cree_n_exp_op(et, herite, $1); 
		n_exp *$3 = conjonctionBis ($2);
		fermeture(__FUNCTION__);
		
	
		
		return $3;
	}
	else if (est_suivant(uniteCourante, _conjonctionBis_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return herite;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : expression(bis) attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * negation ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == NON)
	{
		affichage(NON, &uniteCourante);  // Consome '!'
		n_exp *$1 = negation(); 
		fermeture(__FUNCTION__);

		n_exp *$$ = cree_n_exp_op(non, $1, NULL);
		
		return $$;
	}
	else if (est_premier(uniteCourante, _facteur_) == 1)
	{
		n_exp *$1 = facteur ();
		fermeture(__FUNCTION__);
		
		
		
		return $1;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : negation attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * comparaison ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _expArith_) == 1)
	{
		n_exp *$1 = expArith();
		n_exp *$2 = comparaisonBis ($1);
		fermeture(__FUNCTION__);
		
	
		
		return $2;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s %s\n Erreur de syntaxe : comparaison attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * comparaisonBis (n_exp *herite)
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == EGAL)
	{
		affichage(EGAL, &uniteCourante); // Consome '='
		n_exp *$1 = expArith();
		n_exp *$2 = cree_n_exp_op(egal, herite, $1); 
		n_exp *$3 = comparaisonBis ($2);
		fermeture(__FUNCTION__);
		
		
		
		return $3;
	}
	else if (uniteCourante == INFERIEUR)
	{
		affichage(INFERIEUR, &uniteCourante); // Consome '<'
		n_exp *$1 = expArith();
		n_exp *$2 = cree_n_exp_op(inferieur, herite, $1); 
		n_exp *$3 = comparaisonBis ($2);
		fermeture(__FUNCTION__);
		
		
		
		return $3;
	}
	else if (est_suivant(uniteCourante, _comparaisonBis_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return herite;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : comparaison(bis) attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * expArith()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _terme_) == 1)
	{
		n_exp *$1 = terme ();
		n_exp *$2 = expArithBis ($1);
		fermeture(__FUNCTION__);
		
		//n_exp *$$ = cree_n_exp_op(egal, $1, $2); // 	
		return $2;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : expArith attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * expArithBis(n_exp *herite)
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == PLUS)
	{
		affichage(PLUS, &uniteCourante); 
		n_exp *$1 = terme ();
		n_exp *$2 = cree_n_exp_op(plus, herite, $1); 
		n_exp *$3 = expArithBis ($2);
		fermeture(__FUNCTION__);
		
		//n_exp *$$ = cree_n_exp_op(egal, $1, $2); 
		
		return $3;
	}
	if (uniteCourante == MOINS)
	{
		affichage(MOINS, &uniteCourante); // uniteCourante = yylex();
		n_exp *$1 = terme ();
		n_exp *$2 = cree_n_exp_op(moins, herite, $1); 
		n_exp *$3 = expArithBis ($2);
		fermeture(__FUNCTION__);
		
		//n_exp *$$ = cree_n_exp_op(egal, $1, $2);
		
		return $3;
	}
	else if (est_suivant(uniteCourante, _expArithBis_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return herite;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : expArith(bis) attendue.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * terme()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _negation_) == 1)
	{
		n_exp *$1 = negation ();
		n_exp *$2 = termeBis ($1);
		fermeture(__FUNCTION__);
		
		//n_exp *$$ = cree_n_exp_op(egal, $1, $2); 
		
		return $2;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : terme attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * termeBis(n_exp *herite)
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == FOIS)
	{
		affichage(FOIS, &uniteCourante); 
		n_exp *$1 = negation ();
		n_exp *$2 = cree_n_exp_op(fois, herite, $1); 
		n_exp *$3 = termeBis ($2);
		fermeture(__FUNCTION__);
		
		//n_exp *$$ = cree_n_exp_op(egal, $1, $2); 
		
		return $3;
	}
	if (uniteCourante == DIVISE)
	{
		affichage(DIVISE, &uniteCourante); 
		n_exp *$1 = negation ();
		n_exp *$2 = cree_n_exp_op(divise, herite, $1); 
		n_exp *$3 = termeBis ($2);
		fermeture(__FUNCTION__);
		
		//n_exp *$$ = cree_n_exp_op(egal, $1, $2); 
		
		return $3;
	}
	else if (est_suivant(uniteCourante, _termeBis_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return herite;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : terme(bis) attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * facteur()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == PARENTHESE_OUVRANTE)
	{
		affichage(PARENTHESE_OUVRANTE, &uniteCourante);
		n_exp *$1 = expression ();
		if (uniteCourante == PARENTHESE_FERMANTE)
			affichage(PARENTHESE_FERMANTE, &uniteCourante); 
		else
		{
			nom_token( uniteCourante, nom, valeur );
			printf("%s (%s)\nErreur de syntaxe : ')' attendue.\n", yytext, valeur);
			exit (-1);
		}
		fermeture(__FUNCTION__);	
		return $1;
	}
	else if (uniteCourante == NOMBRE)
	{
		nom_token( uniteCourante, nom, valeur );
		int $1 = atoi(valeur);

		affichage(NOMBRE, &uniteCourante); 
		
		fermeture(__FUNCTION__);	
		n_exp *$$ = cree_n_exp_entier($1);
		
		return $$;
	}
	else if (est_premier(uniteCourante, _appelFct_) == 1)
	{
		n_appel *$1 = appelFct ();
		fermeture(__FUNCTION__);	
		return cree_n_exp_appel($1);
	}
	else if (est_premier(uniteCourante, _var_) == 1)
	{
		n_var *$1 = var ();
		fermeture(__FUNCTION__);	
		return cree_n_exp_var($1);
	}
	else if (uniteCourante == LIRE)
	{
		affichage(LIRE, &uniteCourante); 
		if (uniteCourante == PARENTHESE_OUVRANTE)
		{
			affichage(PARENTHESE_OUVRANTE, &uniteCourante); 
			affichage(PARENTHESE_FERMANTE, &uniteCourante);
			fermeture(__FUNCTION__);	

			n_exp *$$ = cree_n_exp_lire();
			return $$;
		}
		else
		{
			nom_token( uniteCourante, nom, valeur );
			printf("%s (%s)\nErreur de syntaxe : '(' attendue.\n", yytext, valeur);
			exit (-1);
		}
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : facteur attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_var * var ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ID_VAR)
	{
		nom_token( uniteCourante, nom, valeur );
		char* $1 = malloc(sizeof(char)*100);
		strcpy($1, valeur);
		affichage(ID_VAR, &uniteCourante); 

		n_exp *$2 = optIndice();

		fermeture(__FUNCTION__);	

		n_var *$$ = NULL;

		if ($2 < 0)
		{
			$$ = cree_n_var_indicee($1,$2);
			
		}
		else
		{			
			$$ = cree_n_var_simple($1);
			
		}

		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : terme(bis) attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_exp * optIndice ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == CROCHET_OUVRANT)
	{
		affichage(CROCHET_OUVRANT, &uniteCourante); 
		n_exp *$1 = expression ();
		affichage(CROCHET_FERMANT, &uniteCourante);
		fermeture(__FUNCTION__);	
		return $1;
	}
	else if (est_suivant(uniteCourante, _optIndice_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return NULL;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : optIndice attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_appel * appelFct ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == ID_FCT)
	{
		affichage(ID_FCT, &uniteCourante);
		affichage(PARENTHESE_OUVRANTE, &uniteCourante);
		nom_token( uniteCourante, nom, valeur );
		char* $1 = malloc(sizeof(char)*100);
		strcpy($1, valeur);
		n_l_exp *$2 = listeExpressions ();
		
		affichage(PARENTHESE_FERMANTE, &uniteCourante);
		fermeture(__FUNCTION__);	

		n_appel *$$ = cree_n_appel ($1, $2);
		return $$;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : appelFct attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_l_exp * listeExpressions ()
{
	ouverture(__FUNCTION__);	
	if (est_premier(uniteCourante, _expression_) == 1)
	{
		n_exp *$1 = expression ();
		n_l_exp *$2 = listeExpressionsBis ();
		fermeture(__FUNCTION__);

		n_l_exp *$$ = cree_n_l_exp($1, $2);
		
		return $$;
	}
	else if (est_suivant(uniteCourante, _listeExpressions_) == 1)
	{
		// Epsilon
		fermeture(__FUNCTION__);
		return NULL;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : listeExpressions attendu.\n", yytext, valeur);
		exit (-1);
	}
}

n_l_exp * listeExpressionsBis ()
{
	ouverture(__FUNCTION__);	
	if (uniteCourante == VIRGULE)
	{
		affichage(VIRGULE, &uniteCourante); 
		n_exp *$1 = expression ();
		n_l_exp *$2 = listeExpressionsBis ();
		fermeture(__FUNCTION__);

		n_l_exp *$$ = cree_n_l_exp($1, $2);
		
		return $$;
	}
	else if (est_suivant(uniteCourante, _listeExpressionsBis_) == 1)
	{
		
		fermeture(__FUNCTION__);
		return NULL;
	}
	else
	{
		nom_token( uniteCourante, nom, valeur );
		printf("%s (%s)\nErreur de syntaxe : listeExpressionsBis attendu.\n", yytext, valeur);
		exit (-1);
	}
}
