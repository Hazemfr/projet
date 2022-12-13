#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilisateur.h"
#include <gtk/gtk.h>




void  ajout_utilisateur(utilisateur u, int sexe ,int role )
{ 
   
    FILE *f=NULL;
    if (sexe==1)
    strcpy(u.sexe,"homme");
    if (sexe==2)
    strcpy(u.sexe,"femme");
   if (role==1)
    strcpy(u.role,"electeur");
    if (role==2)
    strcpy(u.role,"observateur");
    if (role==3)
    strcpy(u.role,"agent");
    
    f=fopen("utilisateur.txt","a+");
    if(f!=NULL)
    { 
        
        fprintf(f,"%s %s %s %s %s %d %d %d %s %s %s   \n",u.cin,u.nom,u.prenom,u.mdp,u.sexe,u.jour,u.mois,u.annee ,u.role, u.vote ,u.nb_v);
        fclose(f);
    }
    }

int NbrElec(char *filename){
int n=0;
FILE *f1=fopen(filename,"r");
utilisateur u;

int test;
    if(f1!=NULL){
while(fscanf(f1,"%s %s %s %s %s %d %d %d %s %s %s   \n",u.cin,u.nom,u.prenom,u.mdp,u.sexe,&u.jour,&u.mois,&u.annee ,u.role, u.vote ,u.nb_v)!=EOF)
{
test=strcmp(u.role,"electeur");
if(test==0)

n=n+1;
}
n=n-1;
    }
fclose(f1);
return n;

}
int agemoyen(char * filename )
{
  FILE * f = fopen (filename, "r");
int n=NbrElec(filename);
int s =0;
int age ;
utilisateur u;


while (fscanf (f,"%s %s %s %s %s %d %d %d %s %s %s   \n",u.cin,u.nom,u.prenom,u.mdp,u.sexe,&u.jour,&u.mois,&u.annee ,u.role, u.vote ,u.nb_v)!=EOF)
{
if (strcmp(u.role,"electeur")==0 ) { 

	
	age = 2022-u.annee ;
	s  = s + age ;

 	}
}
close(f);
int moyenage= s/n;
return moyenage ;  
}
