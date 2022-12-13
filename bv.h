#ifndef function_H_
#define function_H_
#include <string.h>
#include <gtk/gtk.h>
typedef struct
{
char numero [20] ;
char id[20] ;
int capacite ;
char adresse [20];
char etat [20];
char nombredobservateur [20];
} bureau ;

void ajouter(int ET ,bureau bv);
void afficherbv (GtkWidget *liste);
void afficher_bv (GtkWidget *liste);
void supprimer_bv();
void chercher_bv();


#endif

