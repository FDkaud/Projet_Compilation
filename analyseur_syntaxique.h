
#ifndef H_ANALYSEUR_SYNTAXIQUE
#define H_ANALYSEUR_SYNTAXIQUE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboles.h"
#include "util.h"
#include "premiers.h"
#include "syntabs.h"


char nom[100];
char valeur[100]; 
int uniteCourante;

n_instr *instructionAffect(void);
n_instr *instructionBloc(void);
n_instr *instructionSi(void);
n_instr *instructionTantque(void);
n_instr *instructionAppel(void);
n_instr *instructionEcriture(void);
n_instr *instructionVide(void);
void declarationVariable(void);
void listeDecVariables(void);
void optDecVariables(void);
void programme(void);
void listeDecVariablesBis(void);
void optTailleTableau(void);
void declarationFonctions(void);
void listeDecFonctions(void);
void listeParam(void);
void optListeDecVariables(void);
void instruction(void);
void instructionAffect(void);
void instructionBloc(void);
void listeInstructions(void);
void instructionSi(void);
void optSinon(void);
void instructionTantque(void);
void instructionAppel(void);
void instructionRetour(void);
void instructionEcriture(void);
void instructionVide(void);
void expressionBis(void);
void conjonction(void);
void conjonctionBis(void);
void expression(void);
void comparaison(void);
void comparaisonBis(void);
void expArith(void);
void expArithBis(void);
void terme(void);
void termeBis(void);
void negation(void);
void facteur(void);
void var(void);
void optIndice(void);
void appelFct(void);
void listeExpressionsBis(void);
void listeExpressions(void);



#endif
