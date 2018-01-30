/*
 * Analyseur lexical du compilateur L en FLEX
 */
 
%{
#include "symboles.h"
%}
%option yylineno
%option nounput
%option noinput

/* Déclarations à compléter ... */


%%

";"	{return POINT_VIRGULE;}
"+"	{return PLUS;}
"-"	{return MOINS;}
"*"	{return FOIS;}
"/"	{return DIVISE;}
"("	{return PARENTHESE_OUVRANTE;}
")"	{return PARENTHESE_FERMANTE;}
"["	{return CROCHET_OUVRANT;}
"]"	{return CROCHET_FERMANT;}
"{"	{return ACCOLADE_OUVRANTE;}
"}"	{return ACCOLADE_OUVRANTE;}
"="	{return EGAL;}
"<"	{return INFERIEUR;}
"&" {return ET;}
"|"	{return OU;}
"!"	{return NON;}
","	{return VIRGULE;}
si	{return SI;}
alors	{return ALORS;}
sinon	{return SINON;}
tantque	{return TANTQUE;}
faire	{return FAIRE;}
entier	{return ENTIER;}
retour	{return RETOUR;}
lire	{return LIRE;}
ecrire	{return ECRIRE;}
$[a-zA-Z0-9]+	{return ID_VAR;}
[a-zA-Z]+	{return ID_FCT;}
[0-9]+	{return NOMBRE;}
[ \t]	;	/* pour ignorer les blancs*/
\n	;
.	return yytext[0];
<<EOF>>		{ return FIN;}  /* Fin de fichier */

%%
int yywrap(){
  return 1;
}

