// AJOUTEZ CES DEUX FONCTIONS À util.c ET RAJOUTEZ LEURS PROTOTYPES À util.h

// À rajouter dans util.h
void affiche_feuille(int uc, int trace_xml);
void consommer( int c, int *uc, int trace_xml );

// À rajouter dans util.c
/*******************************************************************************
 * Affiche une élément XML correspondant à une unité lexicale de code uc. Pour
 * cela, utilise la fonction affiche_element ci-dessus, avec le nom de l'élément
 * comme balise et sa valeur comme texte. Si la valeur de trace_xml est zéro, 
 * rien ne sera affiché (permet de désactiver l'affichage de l'arbre syntaxique)
 ******************************************************************************/
void affiche_feuille(int uc, int trace_xml) {
  char nom[100], valeur[100];
  nom_token( uc, nom, valeur );
  affiche_element( nom, valeur, trace_xml );
}


/*******************************************************************************
 * Fonction utile pour faire avancer la tête de lecture quand un symbole 
 * terminal c dans une règle de production de la grammaire se retrouve sous la
 * tête de lecture uc. Attention, uc est un pointeur vers l'unité courante de
 * votre analyseur. Il peut être modifié avec un appel à yylex si la fonction
 * réussit la reconnaissance du symbole (c-à-d si *uc == c). Dans ce cas, la 
 * fonction affichera aussi l'élément XML feuille correspondant au terminal 
 * reconnu. En cas d'échec, affiche un message d'erreur informatif. Si la valeur 
 * de trace_xml est zéro, rien ne sera affiché (permet de désactiver l'affichage 
 * de l'arbre syntaxique)
 ******************************************************************************/
void consommer( int c, int *uc, int trace_xml ) {
  if( *uc == c ){
    affiche_feuille(*uc, trace_xml);
    *uc = yylex(); /* consommer le caractère */
  }
  else { /* Message d'erreur attendu/trouvé */
    char nomC[100], valeurC[100], 
         nomUC[100], valeurUC[100], messageErreur[250];  
    nom_token( c, nomC, valeurC );
    nom_token( *uc, nomUC, valeurUC );    
    sprintf( messageErreur, "%s '%s' attendu, %s '%s' trouvé", 
             nomC, valeurC, nomUC, valeurUC );
    erreur( messageErreur );
  }
}
