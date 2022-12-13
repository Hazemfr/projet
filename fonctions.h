
#ifndef FONCTIONS_H_
#define FONCTIONS_H_
#include <string.h>
#include <gtk/gtk.h>
/*typedef struct 
{
	int jour
	int mois
	int annee
}date;*/
typedef struct
{
	char id_e[20];
	//date date;
	char nb_h[20];
	char muni[20];
	char tour[20];
	int jour;
	int mois;
	int annee;
} election;

	void ajout_election(election e,int tour);
	void supprimer_election();
	void modifier_election();
	void chercher_election( );
	void afficher_election(GtkWidget *liste);
	void afficher_chercher(GtkWidget *liste);
#endif
