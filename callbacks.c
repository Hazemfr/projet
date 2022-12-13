#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "fonctions.h"
#include "bv.h"
#include "utilisateur.h"

int tour=1;
int ET=1;
int role=1;
int sexe=1;
int choix;
int choix1;
void
on_creer_clicked                       (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_ajout;
GtkWidget *fenetre_afficher;


fenetre_afficher = lookup_widget(objet,"afficher_elections");
gtk_widget_hide(fenetre_afficher);
fenetre_ajout=lookup_widget(objet,"gestion_elections");
fenetre_ajout=create_gestion_elections();
gtk_widget_show(fenetre_ajout);




}






void
on_annuler_clicked                     (GtkButton       *objet,
                                        gpointer         user_data)
{
	char id[20];
	GtkWidget *donnee,*affichage,*treeview1;
	donnee = lookup_widget(objet,"entry_ID");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(donnee)));
	supprimer_election(id);
	affichage = lookup_widget(objet,"afficher_elections");
	gtk_widget_destroy(affichage);
	affichage = create_afficher_elections();
	gtk_widget_show(affichage);
	treeview1=lookup_widget(affichage,"treeview1");
	afficher_election(treeview1);
	

}


void
on_modifier_clicked                    (GtkButton       *objet,
                                        gpointer         user_data)
{ 	
	GtkWidget *entry_ID;
	GtkWidget *entry_id,*combo_nb_h,*muni,*jour,*mois,*annee,*tour1,*tour2;
	GtkWidget *fenetre_ajout, *fenetre_afficher, *treeview1, *donnee;
	election e;	
	char id[20];
	FILE *f=NULL;
	int i,j;
	f=fopen("election.txt","r");


	donnee = lookup_widget(objet,"entry_ID");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(donnee)));


	fenetre_afficher = lookup_widget(objet,"afficher_elections");
	
	fenetre_ajout=lookup_widget(objet,"gestion_election");
	
	fenetre_ajout=create_gestion_elections();
	gtk_widget_show(fenetre_ajout);
	
	
	if(f!=NULL)
	{
		while(fscanf(f,"%s %s %s %d %d %d %s \n",e.id_e,e.nb_h,e.muni,&e.jour,&e.mois,&e.annee,e.tour)!=EOF);
		{
			if(strcmp(e.id_e,id)==0)
			{

			entry_id= lookup_widget(fenetre_ajout,"entry_id");
			muni= lookup_widget(fenetre_ajout,"entry_muni");
			annee = lookup_widget(fenetre_ajout,"spinbutton_annee");
			jour = lookup_widget(fenetre_ajout,"spinbutton_jour");
			mois = lookup_widget(fenetre_ajout,"spinbutton_mois");
			combo_nb_h = lookup_widget(fenetre_ajout,"combo_nb_h");
			tour2 = lookup_widget(fenetre_ajout,"2eme_tour");
			tour1 = lookup_widget(fenetre_ajout,"radiobutton1");



				if(strcmp(e.tour,"1er_tour")==0)
				{	gtk_toggle_button_set_active(GTK_RADIO_BUTTON(tour1),TRUE);}
				else
					{gtk_toggle_button_set_active(GTK_RADIO_BUTTON(tour2),TRUE);}
				if(strcmp(e.nb_h,"1000-5000")==0)
				{	j=0;}
		else if (strcmp(e.nb_h,"5000-10000")==0)
					{j=1;}
		else if (strcmp(e.nb_h,"10000-50000")==0)
					{j=2;}
		else if (strcmp(e.nb_h,"50000-100000")==0)
					{j=3;}
		else 
		{j=4;}
				
				
				gtk_combo_box_set_active(GTK_COMBO_BOX(combo_nb_h),j);
				gtk_entry_set_text(GTK_ENTRY(entry_id),e.id_e);
				gtk_entry_set_text(GTK_ENTRY(muni),e.muni);
				gtk_spin_button_set_value(jour,e.jour);
				gtk_spin_button_set_value(mois,e.mois);
				gtk_spin_button_set_value(annee,e.annee);
				
			}
		}
	}
	fclose(f);
	supprimer_election(id);
	gtk_widget_hide(fenetre_afficher);

}

void
on_retour_clicked                      (GtkButton       *objet,
                                        gpointer         user_data)
{
	
	FILE *tmp1=NULL;
 
	
	char id[20];
	GtkWidget *donnee,*affichage,*treeview1;
	donnee = lookup_widget(objet,"entry_ID");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(donnee)));
	chercher_election(id,choix);
	affichage = lookup_widget(objet,"afficher_elections");
	gtk_widget_destroy(affichage);
	affichage = create_afficher_elections();
	gtk_widget_show(affichage);
	treeview1=lookup_widget(affichage,"treeview1");
	afficher_chercher(treeview1);
	remove("tmp1.txt");
}


void
on_confirmer_clicked                   (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *entry_id,*combo_nb_h,*label,*muni,*jour,*mois,*annee;
election e ;
GtkWidget *fenetre_ajout;
fenetre_ajout = lookup_widget(objet,"gestion_elections");

 entry_id= lookup_widget(objet,"entry_id");
muni= lookup_widget(objet,"entry_muni");
annee = lookup_widget(objet,"spinbutton_annee");
jour = lookup_widget(objet,"spinbutton_jour");
mois = lookup_widget(objet,"spinbutton_mois");
combo_nb_h = lookup_widget(objet,"combo_nb_h");
label = lookup_widget(objet,"reponse1");

strcpy(e.id_e,gtk_entry_get_text(GTK_ENTRY(entry_id)));
strcpy(e.muni,gtk_entry_get_text(GTK_ENTRY(muni)));
strcpy(e.nb_h,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_nb_h)));
e.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
e.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
e.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));



ajout_election( e,tour);
gtk_label_set_text(GTK_LABEL(label),"election est bien ajouté .");
}


void
on_consulter_clicked                   (GtkButton       *objet,
                                        gpointer         user_data)
{
election e;
GtkWidget *fenetre_ajout;
GtkWidget *fenetre_afficher;
GtkWidget *treeview1;

fenetre_ajout = lookup_widget(objet,"gestion_elections");
gtk_widget_hide(fenetre_ajout);
fenetre_afficher=lookup_widget(objet,"afficher_elections");
fenetre_afficher=create_afficher_elections();

gtk_widget_show(fenetre_afficher);

treeview1=lookup_widget(fenetre_afficher,"treeview1");
afficher_election(treeview1); 


}


void
on_radiobutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	tour=1;
}


void
on_radiobutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_button_ajouter_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_2eme_tour_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	tour=2;
}


void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
	gchar* id_e;
	gchar* nb_h;
	gchar* muni;
	gchar* tour;
	gchar* jour;
	gchar* mois;
	gchar* annee;
	election e;
	
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model,&iter,path))
	{
		gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id_e,1,&nb_h,2,&muni,3,&jour,4,&mois,5,&annee,6,&tour, -1);
		strcpy(e.id_e,id_e);
		strcpy(e.nb_h,nb_h);
		strcpy(e.muni,muni);
		e.jour=atoi(jour);
		e.mois=atoi(mois);
		e.annee=atoi(annee);
		strcpy(e.tour,tour);
		afficher_election(treeview);
}
}


void
on_ID_toggled                          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	choix=1;
}


void
on_muni_toggled                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	choix=2;
}


void
on_annee_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	choix=3;
}

/////////////////////////////////////Hazem////////////////////////////////////////////////////////

void
on_button_ajouterbv_clicked            (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *entry_num,*entry_id_ag,*label,*cap,*nb_o,*adress;
bureau bv;
GtkWidget *fenetre_ajout;
fenetre_ajout = lookup_widget(objet,"ajouter_bv");

entry_num= lookup_widget(objet,"entry_num");
entry_id_ag= lookup_widget(objet,"entry_idbv");
cap= lookup_widget(objet,"spinbutton_cap");
nb_o = lookup_widget(objet,"combobox_nb_o");
adress = lookup_widget(objet,"combobox_adresse");
//label = lookup_widget(objet,"reponse1");

strcpy(bv.numero,gtk_entry_get_text(GTK_ENTRY(entry_num)));
strcpy(bv.id,gtk_entry_get_text(GTK_ENTRY(entry_id_ag)));
strcpy(bv.nombredobservateur ,gtk_combo_box_get_active_text(GTK_COMBO_BOX(nb_o)));
strcpy(bv.adresse,gtk_combo_box_get_active_text(GTK_COMBO_BOX(adress)));
bv.capacite=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(cap));

ajouter( ET , bv );
}


void
on_consulter_bv_clicked                (GtkButton       *objet,
                                        gpointer         user_data)
{
bureau bv;
GtkWidget *fenetre_ajout;
GtkWidget *fenetre_afficher;
GtkWidget *treeview;

fenetre_ajout = lookup_widget(objet,"ajouter_bv");

gtk_widget_hide(fenetre_ajout);
fenetre_afficher=lookup_widget(objet,"afficher_bv");
fenetre_afficher=create_afficher_bv();

gtk_widget_show(fenetre_afficher);

treeview=lookup_widget(fenetre_afficher,"treeview");
afficherbv(treeview);

}


void
on_radiobutton_inac_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
 ET=1;

}


void
on_radiobutton_act_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
 ET=2;
}


void
on_treeview_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
	gchar* numero;
	gchar* id;
	gchar* capacite;
	gchar* nombredobservateur;
	gchar* adresse;
	gchar* etat;
	bureau bv;
	
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model,&iter,path))
	{
		gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,1,&numero,2,&capacite,3,&nombredobservateur,4,&adresse,5,&etat,-1);
		strcpy(bv.numero,numero);
		strcpy(bv.id,id);
		bv.capacite=atoi(capacite);
		strcpy(bv.nombredobservateur,nombredobservateur);
	        strcpy(bv.adresse,adresse);
		bv.capacite=atoi(capacite);
		strcpy(bv.etat,etat);
		afficherbv(treeview);
}
}


void
on_button_modifierbv_clicked           (GtkButton       *objet,
                                        gpointer         user_data)
{GtkWidget *entry_ID;
	GtkWidget *entry_num,*entry_id_ag,*label,*cap,*nb_o,*adress,*actif,*inactif;
	GtkWidget *fenetre_ajout, *fenetre_afficher, *treeview, *donnee;
	bureau bv;	
	char id[20];
	FILE *f=NULL;
	int i;
	int j;
	int o;
	f=fopen("bv.txt","r");


	donnee = lookup_widget(objet,"entry_id_bv");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(donnee)));


	fenetre_afficher = lookup_widget(objet,"afficher_bv");
	
	fenetre_ajout=lookup_widget(objet,"ajouter_bv");
	
	fenetre_ajout=create_ajouter_bv();
	gtk_widget_show(fenetre_ajout);
	
	
	if(f!=NULL)
	{
		while(fscanf(f,"%s %s %d %s %s %s  \n",bv.id,bv.numero,&bv.capacite,bv.nombredobservateur,bv.adresse,bv.etat)!=EOF);
		{
			if(strcmp(bv.id,id)==0)
			{
			entry_num= lookup_widget(fenetre_ajout,"entry_num");
			entry_id_ag= lookup_widget(fenetre_ajout,"entry_idbv");
			cap= lookup_widget(fenetre_ajout,"spinbutton_cap");
			nb_o = lookup_widget(fenetre_ajout,"combobox_nb_o");
			adress = lookup_widget(fenetre_ajout,"combobox_adresse");
			inactif = lookup_widget(fenetre_ajout,"radiobutton_inac");
			actif = lookup_widget(fenetre_ajout,"radiobutton_act");



			 	
			              if(strcmp(bv.etat,"inactif")==0)
{gtk_toggle_button_set_active(GTK_RADIO_BUTTON(inactif),TRUE);}
		                      else
{gtk_toggle_button_set_active(GTK_RADIO_BUTTON(actif),TRUE);}
                                
		
                                if(strcmp(bv.adresse,"tunis")==0)
				{j=0;}
           else if (strcmp(bv.adresse,"ariana")==0)
				{j=1;}
           else if (strcmp(bv.adresse,"manouba")==0)
				{j=2;}
           else if
                   (strcmp(bv.adresse,"nabeul")==0)
                                {j=3;}
           else 
	                        {j=4;}

                                
				
			  
			
		         if(strcmp(bv.nombredobservateur,"4")==0)
				{o=0;}
		else if (strcmp(bv.nombredobservateur,"8")==0)
					{o=1;}
		else if (strcmp(bv.nombredobservateur,"12")==0)
					{o=2;}

		else 
					{o=3;}
		
				
				gtk_combo_box_set_active(GTK_COMBO_BOX(nb_o),o);
				gtk_combo_box_set_active(GTK_COMBO_BOX(adress),j);
				gtk_entry_set_text(GTK_ENTRY(entry_id_ag),bv.id);
				gtk_spin_button_set_value(cap,bv.capacite);
				gtk_entry_set_text(GTK_ENTRY(entry_num),bv.numero);
                               
				
			}
		}
	}
	fclose(f);
	supprimer_bv(id);
	gtk_widget_hide(fenetre_afficher);

}




void
on_button_annulerbv_clicked            (GtkButton       *objet,
                                        gpointer         user_data)
{ 	
	char id[20];
	GtkWidget *donnee,*affichage,*treeview;
	donnee = lookup_widget(objet,"entry_id_bv");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(donnee)));
	supprimer_bv(id);
	affichage = lookup_widget(objet,"afficher_bv");
	gtk_widget_destroy(affichage);
	affichage = create_afficher_bv();
	gtk_widget_show(affichage);
	treeview=lookup_widget(affichage,"treeview");
	afficherbv(treeview);

}


void
on_button_chercherbv_clicked           (GtkButton       *objet,
                                        gpointer         user_data)
{
	FILE *tmp=NULL;
	char id[20];
	GtkWidget *donnee,*affichage,*treeview;
	donnee = lookup_widget(objet,"entry_id_bv");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(donnee)));
	chercher_bv(id,choix1);
	affichage = lookup_widget(objet,"afficher_bv");
	gtk_widget_destroy(affichage);
	affichage = create_afficher_bv();
	gtk_widget_show(affichage);
	treeview=lookup_widget(affichage,"treeview");
	afficher_bv(treeview);
	remove("tmp.txt");
}



void
on_nb_toggled                          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	choix1=1;
}


void
on_id_toggled                          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	choix1=2;
}


void
on_etat_toggled                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	choix1=3;
}
void
on_button_cre__rbv_clicked             (GtkButton       *objet,
                                        gpointer         user_data)
{GtkWidget *fenetre_ajout;
GtkWidget *fenetre_afficher;


fenetre_afficher = lookup_widget(objet,"afficher_bv");
gtk_widget_hide(fenetre_afficher);
fenetre_ajout=lookup_widget(objet,"ajouter_bv");
fenetre_ajout=create_ajouter_bv();
gtk_widget_show(fenetre_ajout);

}





//////////////////////////////////////////////////////////////////////////nermine//////////////////////////////
void
on_button_ajout_ut_clicked             (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *entry_nom,*entry_prenom,*entry_cin,*entry_mdp,*entry_num,*combo_vote,*jour,*mois,*annee;
GtkWidget *fenetre_gestion;
fenetre_gestion = lookup_widget(objet,"gestion_utilisateur");

utilisateur u;


entry_nom=lookup_widget(objet,"entry_nom");
entry_prenom=lookup_widget(objet,"entry_prenom");
entry_cin=lookup_widget(objet,"entry_cin");
entry_mdp=lookup_widget(objet,"entry_mdp");
entry_num=lookup_widget(objet,"entry_num");

combo_vote=lookup_widget(objet,"combo_vote");
jour=lookup_widget(objet,"spinbutton_jour");
mois=lookup_widget(objet,"spinbutton_mois");
annee=lookup_widget(objet,"spinbutton_annee");



strcpy(u.nom,gtk_entry_get_text(GTK_ENTRY(entry_nom)));
strcpy(u.prenom,gtk_entry_get_text(GTK_ENTRY(entry_prenom)));
strcpy(u.cin,gtk_entry_get_text(GTK_ENTRY(entry_cin)));
strcpy(u.mdp,gtk_entry_get_text(GTK_ENTRY(entry_mdp)));
strcpy(u.nb_v,gtk_entry_get_text(GTK_ENTRY(entry_num)));
strcpy(u.vote,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_vote)));
u.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
u.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
u.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));


ajout_utilisateur(u, sexe , role);	




}


void
on_button_afficher_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_homme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
sexe=1;
}


void
on_femme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
sexe=2;
}


void
on_electeur_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
role=1;
}


void
on_observateur_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
role=2;
}


void
on_agent_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
role=3;
}



void
on_stat_clicked                        (GtkButton       *objet,
                                        gpointer         user_data)
{

GtkWidget *agebv;
GtkWidget *nb7;
GtkWidget *fenetre_ajout;
GtkWidget *fenetre_afficher;

fenetre_ajout = lookup_widget(objet,"afficher_bv");

gtk_widget_hide(fenetre_ajout);
fenetre_afficher=lookup_widget(objet,"statbv1");
fenetre_afficher=create_statbv1();
gtk_widget_show(fenetre_afficher);
agebv=lookup_widget(fenetre_afficher,"stat1");
nb7=lookup_widget(fenetre_afficher,"stat2");
char agstr[10];
char nbstr[10];

int a=agemoyen("utilisateur.txt");
sprintf(agstr,"%d",a);
strcat(agstr,"ans");
gtk_label_set_text(GTK_LABEL(agebv),agstr);
int b=NbrElec("utilisateur.txt");
sprintf(nbstr,"%d",b);
gtk_label_set_text(GTK_LABEL(nb7),nbstr);


}

