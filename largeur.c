#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _sommet {
	int		isucceseur;
	struct	_sommet* successeur;
} Sommet;

typedef struct {
	int		nb_sommets;
	Sommet** liste_successeurs;
} Graphe;

typedef struct _cell {
	int		id; 
	struct	_cell* suivant;
} cell;

typedef struct {
	cell* tete;
	cell* queue; 
} File;

void lecture_graph(Graphe *graphe,const char* graphFileName){
FILE *fp;
fp = fopen(graphFileName, "r");
if (fp!=NULL){
int nb_arcs,nb_sommets,u,v;
fscanf(fp,"%d %d",&nb_sommets,&nb_arcs);
graphe->nb_sommets=nb_sommets+1;
graphe->liste_successeurs=(Sommet ** )malloc(graphe->nb_sommets*sizeof(Sommet *));
for (int i =0;i<graphe->nb_sommets;i++){
graphe->liste_successeurs[i]=NULL;
}
for(int i=0;i<nb_arcs;i++){
fscanf(fp,"%d %d",&u,&v);
Sommet* s = (Sommet*) malloc(sizeof(Sommet)); 
s->isucceseur=v;
s->successeur=graphe->liste_successeurs[u];
graphe->liste_successeurs[u]=s; 

}
}
else
printf("fichier vide");
}
void affichage_graphe_liste_adjacence(Graphe* G) 
{	
	for(int i = 0; i < G->nb_sommets; i++) 
	{
		printf("Les voisins du sommet %d sont: ", i);

		Sommet* courant = G->liste_successeurs[i];

		while(courant != NULL)
		{
			printf("(%d), ", courant->isucceseur);
			courant = courant->successeur;
		} 
		printf("\n");
	}
}
void enfiler(int id_cell,File *pF) 
{
	cell* pelem = (cell*) malloc(sizeof(cell)); 

	pelem->id = id_cell;
	pelem->suivant = NULL; 
	 
	if (pF->tete == NULL) 
	{
		pF->tete = pF->queue = pelem; 
	}
	else 	{
	cell *courant = pF->tete;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        // Lier le nouveau nœud à la fin de la liste
        courant->suivant = pelem;
}
}
bool est_vide(File *pf){
if (pf->tete==NULL)
return true;
else
return false;
}

int defiler(File *pf){
if (pf->tete==NULL)
printf("liste vide");
else{
int id = pf->tete->id;
pf->tete = pf->tete->suivant;
return id;
}
}
File Initialiser() 
{
	File filevide;
	filevide.tete = NULL; 
	return filevide;
}
bool largeur(Graphe *graphe,int sommet_source,File *pf){
int* marques=(int *)malloc(graphe->nb_sommets*sizeof(int));
for(int i=0;i<graphe->nb_sommets;i++){
marques[i]=0;
}
enfiler(sommet_source,pf);
marques[sommet_source]=1;
printf(" (%d) ",sommet_source);
while(!est_vide(pf)){
int sommet_out = defiler(pf);

		Sommet* courant = graphe->liste_successeurs[sommet_out];
		while (courant != NULL) 
		{
			if (marques[courant->isucceseur] == 0)
			{
				if(marques[sommet_out]==1) marques[courant->isucceseur] = 2; 
				else marques[courant->isucceseur] = 1;  
				printf(" (%d) ", courant->isucceseur);			
				enfiler(courant->isucceseur,pf);	
			}
			else{
				if (marques[sommet_out] == marques[courant->isucceseur])
					return false;
			}
			courant = courant->successeur;
		}
}
}

int main(){
const char* grapheFileName = "graph_10_13.txt";
Graphe graphe;
File file;
lecture_graph(&graphe, grapheFileName);
affichage_graphe_liste_adjacence(&graphe);
	printf("\nParcours en largeur du graphe G a partir du sommet 9 : " );
	largeur(&graphe,8,&file);
}
