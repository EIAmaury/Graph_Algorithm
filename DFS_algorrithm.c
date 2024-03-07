#include <stdlib.h>
#include <stdio.h>

typedef struct {
int nb_sommets;
int **matrice_adjacence;
}Graphe;
void lecture_graph(Graphe *graphe,const char* graph_fic_nom){
FILE* fp;
fp=fopen(graph_fic_nom,"r");

if(fp!=NULL){
int nb_arcs,nb_sommets;
fscanf(fp,"%d %d",&nb_sommets,&nb_arcs);
graphe->nb_sommets=nb_sommets;
graphe->matrice_adjacence=(int**)malloc((graphe->nb_sommets)*sizeof(int *));
for(int i=0;i<graphe->nb_sommets;i++){
graphe->matrice_adjacence[i]=(int*)malloc((graphe->nb_sommets)*sizeof(int));
}
//Initialisation de la matrice
for (int i = 0; i < graphe->nb_sommets; i++)
			for (int j = 0; j < graphe->nb_sommets; j++)
				graphe->matrice_adjacence[i][j] = 0;
//décalage de chaque arc car pas de sommets 0
for(int i=0;i<nb_arcs;i++){
int u,v;
fscanf(fp,"%d %d",&u,&v);
graphe->matrice_adjacence[u-1][v-1]=1;
}
fclose(fp);
}
else
printf("fichier vide");
}
void affichage_graphe(Graphe *graphe){
for (int i = 0; i < graphe->nb_sommets; i++)
{
			for (int j = 0; j < graphe->nb_sommets; j++)
				printf("%d ",graphe->matrice_adjacence[i][j]);
			printf("\n");
}
}
//un tableau comme pointeur
void visiter(Graphe* graphe,int sommet, int* tabmarque){
printf("Je visite le sommet %d\n",sommet+1);
tabmarque[sommet]=1;
for(int i=0;i<graphe->nb_sommets;i++){
if (graphe->matrice_adjacence[sommet][i]!=0){
if (tabmarque[i]!=1){
visiter(graphe,i,tabmarque);
}
}
}
}
void profondeur(Graphe *graphe,int sommet_source){
int* tabmarque=(int*)malloc((graphe->nb_sommets)*sizeof(int));
for(int i=0;i<graphe->nb_sommets;i++)
{
 tabmarque[i]=0;
}
visiter(graphe,sommet_source,tabmarque);
}
void main(){
 const char* graph_fic_nom = "graph_10_13.txt";
 Graphe graphe;
 lecture_graph(&graphe,graph_fic_nom);
 affichage_graphe(&graphe);
 profondeur(&graphe,7);
}
