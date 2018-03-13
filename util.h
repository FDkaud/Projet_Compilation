#ifndef __UTIL__
#define __UTIL__



FILE* vue;


#define NO_DISPLAY  0
#define XML_DISPLAY 1

#define STD_OUT  0



int mode_aff; //mode affichage
int trace_xml;
int type_aff; // type d'aff








char *duplique_chaine(char *s);
void warning(char *message);
void erreur(char *message);
void warning_1s(char *message, char *s);
void erreur_1s(char *message, char *s);
void affiche_balise_ouvrante(const char *fct_, int trace_xml);
void affiche_balise_fermante(const char *fct_, int trace_xml);
void affiche_element(char *fct_, char *texte_, int trace_xml);
void affiche_texte(char *texte_, int trace_xml);
void test_yylex_internal(FILE *yyin);
void nom_token( int token, char *nom, char *valeur );
void affiche_feuille(int uc, int trace_xml);
void consommer( int c, int *uc, int trace_xml );
void ouverture(const char* Display);
void fermeture(const char* Display);
void affichage(int c, int* uc);

#endif
