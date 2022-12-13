#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include <gtk/gtk.h>
enum
{
	EID_E,
	ENB_H,
	EMUNI,
	EJOUR,
	EMOIS,
	EANNEE,
	ETOUR,
	COLUMNS,
};


void ajout_election(election e,int tour)
{ 
    FILE *f=NULL;
	if (tour ==1)
	strcpy(e.tour,"1er_tour");
	if(tour==2)
	strcpy(e.tour,"2eme_tour");
    f=fopen("election.txt","a+");
    if(f!=NULL)
    { 
        
        fprintf(f,"%s %s %s %d %d %d %s\n",e.id_e,e.nb_h,e.muni,e.jour,e.mois,e.annee,e.tour);
        fclose(f);
    }
    }
void supprimer_election( char id[20])
{

    FILE *f=NULL;
    FILE *tmp=NULL;
    election e ;
    f=fopen("election.txt","r");
    tmp=fopen("tmp.txt","w");
	
    if(f!=NULL)
    {
        while(fscanf(f,"%s %s %s %d %d %d %s \n",e.id_e,e.nb_h,e.muni,&e.jour,&e.mois,&e.annee,e.tour)!=EOF)
        {
            if(strcmp(e.id_e ,  id)!=0)
            {
         fprintf(tmp,"%s %s %s %d %d %d %s\n",e.id_e,e.nb_h,e.muni,e.jour,e.mois,e.annee,e.tour);
            }

        }
        fclose(f);
        fclose(tmp);
        remove("election.txt");
        rename("tmp.txt","election.txt");

}
}

/*int chercher_election()
{
    election *p;
    FILE *f=NULL;
    election e;
    int teste;
    char id[20];
    f=fopen("election.txt","r");
    teste=0;
      printf("Donner l'identifiant :");scanf("%s",id);	
    if(f!=NULL)
    {
        while(fscanf(f,"%s %d %s %s  \n",e.id_e,&e.nb_h,e.muni,e.tour )!=EOF)
        {
            if(strcmp(e.id_e, id)==0)
            {
                *p=e;
                teste=1;
                break;
            }
	    else 
		 printf("not founded");


        }
        
    }
fclose(f);
    
    return(teste);
}

/*void modifer_election()
{
    
}*/
void afficher_election(GtkWidget *liste)
{

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	char id_e[20];
	//date date;
	char nb_h[20];
	char muni[20];
	char tour[20];
	char jour[20];
	char mois[20];
	char annee[20];
	store=NULL;
	FILE  *f;
	
	store = gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer,"text",EID_E,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("NB des habitant", renderer,"text",ENB_H,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Municipalite", renderer,"text",EMUNI,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jours", renderer,"text",EJOUR,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois", renderer,"text",EMOIS,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Annee", renderer,"text",EANNEE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Tour", renderer,"text",ETOUR,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
	store = gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

	f=fopen("election.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f = fopen("election.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s %s \n",id_e,nb_h,muni,jour,mois,annee,tour)!=EOF)
		{
		
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,EID_E,id_e,ENB_H,nb_h,EMUNI,muni,EJOUR,jour,EMOIS,mois,EANNEE,annee,ETOUR,tour,-1);
			
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);
	}  
	}


}
      





void afficher_chercher(GtkWidget *liste)
{

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	char id_e[20];
	//date date;
	char nb_h[20];
	char muni[20];
	char tour[20];
	char jour[20];
	char mois[20];
	char annee[20];
	store=NULL;
	FILE  *tmp1;
	
	store = gtk_tree_view_get_model(liste);
	if(store==NULL)
	{
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer,"text",EID_E,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("NB des habitant", renderer,"text",ENB_H,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Municipalite", renderer,"text",EMUNI,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jours", renderer,"text",EJOUR,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois", renderer,"text",EMOIS,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Annee", renderer,"text",EANNEE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Tour", renderer,"text",ETOUR,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
	store = gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

	tmp1=fopen("tmp1.txt","r");
	if(tmp1==NULL)
	{
		return;
	}
	else
	{
		tmp1= fopen("tmp1.txt","a+");
		while(fscanf(tmp1,"%s %s %s %s %s %s %s \n",id_e,nb_h,muni,jour,mois,annee,tour)!=EOF)
		{
		
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,EID_E,id_e,ENB_H,nb_h,EMUNI,muni,EJOUR,jour,EMOIS,mois,EANNEE,annee,ETOUR,tour,-1);
			
		}
		fclose(tmp1);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);
	}  
	}


}




void chercher_election(char ID[20] , int choix )
{
	
    FILE *f=NULL;
    FILE *tmp1=NULL;
   election e  ;
    f=fopen("election.txt","r");
    tmp1=fopen("tmp1.txt","w");
    if(f!=NULL)
    {
        while(fscanf(f,"%s %s %s %d %d %d %s \n",e.id_e,e.nb_h,e.muni,&e.jour,&e.mois,&e.annee,e.tour)!=EOF)
        {
	if (choix==1)
            if(strcmp(e.id_e ,  ID)==0)
            {
              fprintf(tmp1,"%s %s %s %d %d %d %s\n",e.id_e,e.nb_h,e.muni,e.jour,e.mois,e.annee,e.tour);;
            }
	if (choix==2)
            if(strcmp(e.muni ,  ID)==0)
            {
              fprintf(tmp1,"%s %s %s %d %d %d %s\n",e.id_e,e.nb_h,e.muni,e.jour,e.mois,e.annee,e.tour);;
            }
	if (choix==3)
            if(strcmp(e.tour,  ID)==0)
            {
              fprintf(tmp1,"%s %s %s %d %d %d %s\n",e.id_e,e.nb_h,e.muni,e.jour,e.mois,e.annee,e.tour);;
            }

        }
        fclose(f);
        fclose(tmp1);
}}
