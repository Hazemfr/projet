#ifndef FONCTIONS_H_
#define FONCTIONS_H_
#include <string.h>
#include <gtk/gtk.h>
typedef struct 
{
	int jour
	int mois
	int annee
}date;
typedef struct
{
	char id_election[20];
	date date;
	int nb_habitant[20];
	char municipalite[20];
	char tour[20]
}election;

	void  ajout_election(election e);
	void supprimer_election();
	void modifier_election();
	int chercher_election( );
	void afficher_election(GtkWidget *liste);
#endif
