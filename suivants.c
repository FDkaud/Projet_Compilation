#include "symboles.h"
#include "suivants.h"

void initialise_suivants(void){
  int i,j;
  
  // Initialiser toutes les cases du tableau à 0
  for(i=0; i <= NB_NON_TERMINAUX; i++)
    for(j=0; j <= NB_TERMINAUX; j++)
      suivants[i][j] = 0;
      
  //PG
  suivants[_programme_][FIN] = 1;
  
  //ODV
  suivants[_optDecVariables_][ID_FCT] = 1;
  suivants[_optDecVariables_][ACCOLADE_OUVRANTE] = 1;
  suivants[_optDecVariables_][FIN] = 1;

  //LDV
  suivants[_listeDecVariables_][POINT_VIRGULE] = 1;
  suivants[_listeDecVariables_][PARENTHESE_FERMANTE] = 1;
  
  //LDVB
  suivants[_listeDecVariablesBis_][POINT_VIRGULE] = 1;
  suivants[_listeDecVariablesBis_][PARENTHESE_FERMANTE] = 1;

  //DV
  suivants[_declarationVariable_][POINT_VIRGULE] = 1;
  suivants[_declarationVariable_][PARENTHESE_FERMANTE] = 1;

  //OTT
  suivants[_optTailleTableau_][VIRGULE] = 1;
  suivants[_optTailleTableau_][POINT_VIRGULE] = 1;
  suivants[_optTailleTableau_][PARENTHESE_FERMANTE] = 1;

  //LDF
  suivants[_listeDecFonctions_][VIRGULE] = 1;
  suivants[_listeDecFonctions_][POINT_VIRGULE] = 1;
  suivants[_listeDecFonctions_][PARENTHESE_FERMANTE] = 1;

  //DF
  suivants[_declarationFonction_][FIN] = 1;

  //LP
  suivants[_listeParam_][ID_FCT] = 1;
  suivants[_listeParam_][FIN] = 1;

  //OLDV
  suivants[_optListeDecVariables_][ENTIER] = 1;
  suivants[_optListeDecVariables_][ACCOLADE_OUVRANTE] = 1;

  //I
  suivants[_instruction_][PARENTHESE_FERMANTE] = 1;

  //IAFF
  suivants[_instructionAffect_][ID_VAR] = 1;
  suivants[_instructionAffect_][SI] = 1;
  suivants[_instructionAffect_][TANTQUE] = 1;
  suivants[_instructionAffect_][RETOUR] = 1;
  suivants[_instructionAffect_][ECRIRE] = 1;
  suivants[_instructionAffect_][POINT_VIRGULE] = 1;
  suivants[_instructionAffect_][PARENTHESE_OUVRANTE] = 1;
  suivants[_instructionAffect_][PARENTHESE_FERMANTE] = 1;
  suivants[_instructionAffect_][ID_FCT] = 1;

  //IB
  suivants[_instructionBloc_][ID_VAR] = 1;
  suivants[_instructionBloc_][ID_FCT] = 1;
  suivants[_instructionBloc_][TANTQUE] = 1;
  suivants[_instructionBloc_][SI] = 1;
  suivants[_instructionBloc_][RETOUR] = 1;
  suivants[_instructionBloc_][ECRIRE] = 1;
  suivants[_instructionBloc_][POINT_VIRGULE] = 1;
  suivants[_instructionBloc_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionBloc_][ACCOLADE_FERMANTE] = 1;

  //LI
  suivants[_listeInstructions_][SINON] = 1;
  suivants[_listeInstructions_][ID_VAR] = 1;
  suivants[_listeInstructions_][ACCOLADE_OUVRANTE] = 1;
  suivants[_listeInstructions_][SI] = 1;
  suivants[_listeInstructions_][TANTQUE] = 1;
  suivants[_listeInstructions_][ID_FCT] = 1;
  suivants[_listeInstructions_][RETOUR] = 1;
  suivants[_listeInstructions_][ECRIRE] = 1;
  suivants[_listeInstructions_][POINT_VIRGULE] = 1;
  suivants[_listeInstructions_][ACCOLADE_FERMANTE] = 1;
  suivants[_listeInstructions_][FIN] = 1;
  
  //ISI
  suivants[_instructionSi_][ACCOLADE_FERMANTE] = 1;
  
  //OSINON
  suivants[_optSinon_][SI] = 1;
  suivants[_optSinon_][TANTQUE] = 1;
  suivants[_optSinon_][RETOUR] = 1;
  suivants[_optSinon_][ECRIRE] = 1;
  suivants[_optSinon_][POINT_VIRGULE] = 1;
  suivants[_optSinon_][ACCOLADE_OUVRANTE] = 1;
  suivants[_optSinon_][ACCOLADE_FERMANTE] = 1;
  suivants[_optSinon_][ID_VAR] = 1;
  suivants[_optSinon_][ID_FCT] = 1;

  //ITQ
  suivants[_instructionTantque_][SI] = 1;
  suivants[_instructionTantque_][TANTQUE] = 1;
  suivants[_instructionTantque_][RETOUR] = 1;
  suivants[_instructionTantque_][ECRIRE] = 1;
  suivants[_instructionTantque_][POINT_VIRGULE] = 1;
  suivants[_instructionTantque_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionTantque_][ACCOLADE_FERMANTE] = 1;
  suivants[_instructionTantque_][ID_VAR] = 1;
  suivants[_instructionTantque_][ID_FCT] = 1;

  //IAPP
  suivants[_instructionAppel_][SI] = 1;
  suivants[_instructionAppel_][TANTQUE] = 1;
  suivants[_instructionAppel_][RETOUR] = 1;
  suivants[_instructionAppel_][ECRIRE] = 1;
  suivants[_instructionAppel_][POINT_VIRGULE] = 1;
  suivants[_instructionAppel_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionAppel_][ACCOLADE_FERMANTE] = 1;
  suivants[_instructionAppel_][ID_VAR] = 1;
  suivants[_instructionAppel_][ID_FCT] = 1;

  //IRET
  suivants[_instructionRetour_][SI] = 1;
  suivants[_instructionRetour_][TANTQUE] = 1;
  suivants[_instructionRetour_][RETOUR] = 1;
  suivants[_instructionRetour_][ECRIRE] = 1;
  suivants[_instructionRetour_][POINT_VIRGULE] = 1;
  suivants[_instructionRetour_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionRetour_][ACCOLADE_FERMANTE] = 1;
  suivants[_instructionRetour_][ID_VAR] = 1;
  suivants[_instructionRetour_][ID_FCT] = 1;

  //IECR
  suivants[_instructionEcriture_][SI] = 1;
  suivants[_instructionEcriture_][TANTQUE] = 1;
  suivants[_instructionEcriture_][RETOUR] = 1;
  suivants[_instructionEcriture_][ECRIRE] = 1;
  suivants[_instructionEcriture_][POINT_VIRGULE] = 1;
  suivants[_instructionEcriture_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionEcriture_][ACCOLADE_FERMANTE] = 1;
  suivants[_instructionEcriture_][ID_VAR] = 1;
  suivants[_instructionEcriture_][ID_FCT] = 1;

  //IVIDE
  suivants[_instructionVide_][SI] = 1;
  suivants[_instructionVide_][TANTQUE] = 1;
  suivants[_instructionVide_][RETOUR] = 1;
  suivants[_instructionVide_][ECRIRE] = 1;
  suivants[_instructionVide_][POINT_VIRGULE] = 1;
  suivants[_instructionVide_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionVide_][ACCOLADE_FERMANTE] = 1;
  suivants[_instructionVide_][ID_VAR] = 1;
  suivants[_instructionVide_][ID_FCT] = 1;

  //EXP
  suivants[_expression_][ALORS] = 1;
  suivants[_expression_][FAIRE] = 1;
  suivants[_expression_][POINT_VIRGULE] = 1;
  suivants[_expression_][PARENTHESE_FERMANTE] = 1;
  suivants[_expression_][CROCHET_FERMANT] = 1;
  suivants[_expression_][VIRGULE] = 1;

  //EXPB
  suivants[_expressionBis_][ALORS] = 1;
  suivants[_expressionBis_][FAIRE] = 1;
  suivants[_expressionBis_][POINT_VIRGULE] = 1;
  suivants[_expressionBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_expressionBis_][CROCHET_FERMANT] = 1;
  suivants[_expressionBis_][VIRGULE] = 1;

  //CONJ
  suivants[_conjonction_][PARENTHESE_FERMANTE] = 1;
  suivants[_conjonction_][OU] = 1;

  //CONJB
  suivants[_conjonctionBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_conjonctionBis_][OU] = 1;

  //NEG
  suivants[_negation_][PARENTHESE_FERMANTE] = 1;
  suivants[_negation_][OU] = 1;
  suivants[_negation_][ET] = 1;

  //COMP
  suivants[_comparaison_][PARENTHESE_FERMANTE] = 1;
  suivants[_comparaison_][OU] = 1;
  suivants[_comparaison_][ET] = 1;

  //COMPB
  suivants[_comparaisonBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_comparaisonBis_][OU] = 1;
  suivants[_comparaisonBis_][ET] = 1;

  //E
  suivants[_expArith_][EGAL] = 1;
  suivants[_expArith_][INFERIEUR] = 1;
  suivants[_expArith_][ET] = 1;
  suivants[_expArith_][OU] = 1;
  suivants[_expArith_][PARENTHESE_FERMANTE] = 1;

  //EB
  suivants[_expArithBis_][EGAL] = 1;
  suivants[_expArithBis_][INFERIEUR] = 1;
  suivants[_expArithBis_][ET] = 1;
  suivants[_expArithBis_][OU] = 1;
  suivants[_expArith_][PARENTHESE_FERMANTE] = 1;

  //T
  suivants[_terme_][PLUS] = 1;
  suivants[_terme_][MOINS] = 1;
  suivants[_terme_][EGAL] = 1;
  suivants[_terme_][INFERIEUR] = 1;
  suivants[_terme_][ET] = 1;
  suivants[_terme_][OU] = 1;
  suivants[_terme_][PARENTHESE_FERMANTE] = 1;

  //TB
  suivants[_termeBis_][PLUS] = 1;
  suivants[_termeBis_][MOINS] = 1;
  suivants[_termeBis_][EGAL] = 1;
  suivants[_termeBis_][INFERIEUR] = 1;
  suivants[_termeBis_][ET] = 1;
  suivants[_termeBis_][OU] = 1;
  suivants[_termeBis_][PARENTHESE_FERMANTE] = 1;

  //F
  suivants[_facteur_][FOIS] = 1;
  suivants[_facteur_][DIVISE] = 1;
  suivants[_facteur_][PLUS] = 1;
  suivants[_facteur_][MOINS] = 1;
  suivants[_facteur_][EGAL] = 1;
  suivants[_facteur_][INFERIEUR] = 1;
  suivants[_facteur_][ET] = 1;
  suivants[_facteur_][OU] = 1;
  suivants[_facteur_][PARENTHESE_FERMANTE] = 1;

  //VAR
  suivants[_var_][FOIS] = 1;
  suivants[_var_][DIVISE] = 1;
  suivants[_var_][PLUS] = 1;
  suivants[_var_][MOINS] = 1;
  suivants[_var_][EGAL] = 1;
  suivants[_var_][INFERIEUR] = 1;
  suivants[_var_][ET] = 1;
  suivants[_var_][OU] = 1;
  suivants[_var_][PARENTHESE_FERMANTE] = 1;

  //OIND
  suivants[_optIndice_][FOIS] = 1;
  suivants[_optIndice_][DIVISE] = 1;
  suivants[_optIndice_][PLUS] = 1;
  suivants[_optIndice_][MOINS] = 1;
  suivants[_optIndice_][EGAL] = 1;
  suivants[_optIndice_][INFERIEUR] = 1;
  suivants[_optIndice_][ET] = 1;
  suivants[_optIndice_][OU] = 1;
  suivants[_optIndice_][PARENTHESE_FERMANTE] = 1;
  
  //APPF
  suivants[_appelFct_][POINT_VIRGULE] = 1;
  suivants[_appelFct_][FOIS] = 1;
  suivants[_appelFct_][DIVISE] = 1;
  suivants[_appelFct_][PLUS] = 1;
  suivants[_appelFct_][MOINS] = 1;
  suivants[_appelFct_][EGAL] = 1;
  suivants[_appelFct_][INFERIEUR] = 1;
  suivants[_appelFct_][ET] = 1;
  suivants[_appelFct_][OU] = 1;
  suivants[_appelFct_][PARENTHESE_FERMANTE] = 1;

  //LEXP
  suivants[_listeExpressions_][PARENTHESE_FERMANTE] = 1;

  //LEXPB
  suivants[_listeExpressionsBis_][PARENTHESE_FERMANTE] = 1;
  
}

int est_suivant(int terminal, int non_terminal)
{
  return suivants[non_terminal][terminal];
}
