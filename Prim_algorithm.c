#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct _sommet {
	int		isucceseur;
	int pondération;
	struct	_sommet* successeur;
} Sommet;

typedef struct {
	int		nb_sommets;
	Sommet** liste_successeurs;
} Graphe;

typedef struct _cell {
	int id; 
	int pondération;
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
int nb_arcs,nb_sommets,u,v,pondération;
fscanf(fp,"%d %d",&nb_sommets,&nb_arcs);
graphe->nb_sommets=nb_sommets+1;
graphe->liste_successeurs=(Sommet ** )malloc(graphe->nb_sommets*sizeof(Sommet *));
for (int i =0;i<graphe->nb_sommets;i++){
graphe->liste_successeurs[i]=NULL;
}
for(int i=0;i<nb_arcs;i++){
fscanf(fp,"%d %d %d",&u,&v,&pondération);
Sommet* s = (Sommet*) malloc(sizeof(Sommet)); 
s->isucceseur=v;
s->pondération=pondération;
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
			printf("(S:%d P:%d), ", courant->isucceseur,courant->pondération);
			courant = courant->successeur;
		} 
		printf("\n");
	}
}
int est_present(File *pF, int id_cell) {
    cell *courant = pF->tete;
    while (courant != NULL) {
        // Si l'ID de l'élément correspond à l'ID recherché, retourner vrai
        if (courant->id == id_cell) {
            return 1; // Vrai, l'élément est présent
        }
        courant = courant->suivant;
    }
    // Si l'élément n'est pas trouvé dans la liste, retourner faux
    return 0; // Faux, l'élément n'est pas présent
}
void enfiler(int sommet_source,int id_cell,File *pF,Graphe* graphe) {
    // Vérifier si l'élément est déjà présent dans la liste
    if (!est_present(pF, id_cell)) {
        // Allouer de la mémoire pour le nouvel élément
        cell* pelem = (cell*) malloc(sizeof(cell));
        
        // Initialiser les valeurs de l'élément
        pelem->id = id_cell;
        
        Sommet* courant=graphe->liste_successeurs[sommet_source];
        while(courant!=NULL){
        if(courant->isucceseur==id_cell){
        pelem->pondération=courant->pondération;
        }
        courant=courant->successeur;
        }
 if (pF->tete == NULL || pelem->pondération < pF->tete->pondération) {
            pelem->suivant = pF->tete;
            pF->tete = pelem;
        } else {
            // Sinon, parcourir la liste jusqu'à trouver l'endroit où insérer le nouvel élément
            cell* precedent = pF->tete;
            cell* courant = pF->tete->suivant;
            while (courant != NULL && courant->pondération < pelem->pondération) {
                precedent = courant;
                courant = courant->suivant;
            }
            // Insérer le nouvel élément après le nœud précédent
            pelem->suivant = courant;
            precedent->suivant = pelem;
        }
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
int pondération=pf->tete->pondération;

pf->tete = pf->tete->suivant;
return id;
}
}
void enfiler_source(Graphe *graphe,int sommet_source,File*pf){
        // Allouer de la mémoire pour le nouvel élément
        cell* pelem = (cell*) malloc(sizeof(cell));
        // Initialiser les valeurs de l'élément
        pelem->id = sommet_source;
	pelem->suivant = pf->tete;
            pf->tete = pelem;
}
void Prim(Graphe *graphe,int sommet_source,File *pf){
int* sommet_pondé=(int *)malloc(graphe->nb_sommets*sizeof(int));
int* pred=(int *)malloc(graphe->nb_sommets*sizeof(int));
for(int i=0;i<graphe->nb_sommets;i++){
sommet_pondé[i]=10000;
pred[i]=0;
}
// On ajoute directement les voisisns du sommet _source et le sommet_source
enfiler_source(graphe,sommet_source,pf);
while(!est_vide(pf)){
int sommet_out = defiler(pf);
sommet_pondé[sommet_out]=0;
Sommet* courant = graphe->liste_successeurs[sommet_out];
		while (courant != NULL) 
		{
			if ((courant->pondération + sommet_pondé[sommet_out])<sommet_pondé[courant->isucceseur]){
			enfiler(sommet_out,courant->isucceseur,pf,graphe);
			pred[courant->isucceseur]=courant->pondération;
			}
			courant=courant->successeur;
}
}
int poids=0;
for(int i=0;i<graphe->nb_sommets;i++){
poids+=pred[i];
printf("le poids du sommet  %d est de %d\n",i,pred[i]);
}
printf("le poids minimal du graph est %d\n",poids);
}
int main(){
const char* grapheFileName = "graph_10_13_weighted.txt";
Graphe graphe;
File file;
lecture_graph(&graphe, grapheFileName);
affichage_graphe_liste_adjacence(&graphe);
printf("PRIm Algorithm\n");
Prim(&graphe,8,&file);
}
