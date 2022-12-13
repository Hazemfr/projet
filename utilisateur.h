#ifndef UTILISATEUR_H_
#define UTILISATEUR_H_
#include <string.h>
#include <gtk/gtk.h>

typedef struct
{
    char cin[20];
    char mdp[20];
   char role[20];
    char nom[20];
    char prenom[20];
     char sexe[20];
    int jour;
    int mois;
    int annee;
    char vote[20];
    char nb_v[20];
} utilisateur;

void  ajout_utilisateur(utilisateur u , int type , int role);
void supprimer_utilisateur(char log[20]);
void modifer_utilisateur(char log[20] , utilisateur t2 , int type);
void affchercher_utilisateur(GtkWidget *liste);
//int chercher_utilisateur( );
void afficher_utilisateur(GtkWidget *liste);
void chercher_utilisateur(char log[20]);
int NbrElec(char *filename);
int  agemoyen(char * filename);
#endif
