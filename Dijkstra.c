#include<stdlib.h>
#include<stdio.h>
#include <stdbool.h>
typedef struct 
{
	int   nb_sommets;
	int nb_arcs;
	int** matrice_adjacence;
} Graphe;

typedef struct Noeud
{
 int info;
 struct Noeud *suiv;
}Noeud;
//pour gérer la tete je la mets dans une strucuture
typedef struct 
{
 Noeud *tete;
}Liste;


void ajoute_arete(Graphe* graphe, int sommet1, int sommet2){
    graphe->matrice_adjacence[sommet1][sommet2]=1;
}

void printf_graph(Graphe *graphe)
{
	for (int i = 0; i < graphe->nb_sommets; i++) 
	{
		for (int j = 0; j < graphe->nb_sommets; j++)
			printf("%d ", graphe->matrice_adjacence[i][j]); 
		printf("\n" ); 
	}
	}
void cree_graph(Graphe *graphe, const char* grapheFileName) //passage de la structure à l'aide d'un pointeur
{
     	FILE *fp;
	fp = fopen(grapheFileName, "r");
	
	if (fp != NULL) {

		int nb_sommets, nb_arcs,u,v,pondération;

		fscanf(fp, "%d %d", &nb_sommets, &nb_arcs);
		graphe->nb_sommets=nb_sommets+1;
		graphe->nb_arcs=nb_arcs;
//Initialisation de la matrice
graphe->matrice_adjacence = (int**) malloc((graphe->nb_sommets)*sizeof(int*));

	for (int i = 0; i < (graphe->nb_sommets); i++) 
	{			
		graphe->matrice_adjacence[i] = (int*) malloc((graphe->nb_sommets)*sizeof(int)); 
		for (int j = 0; j < (graphe->nb_sommets); j++)
			graphe->matrice_adjacence[i][j] = 0; 
	}
 for (int i = 0; i < graphe->nb_arcs; i++)
 {
		fscanf(fp, "%d %d %d", &u, &v,&pondération);
	graphe->matrice_adjacence[u][v] = pondération;
}
}
else printf("fichier introuvable");
}
//Algorithme 2 lié à une file
void init_marques(Graphe *graphe,int marques_1[])
 {
	for (int i=0; i<graphe->nb_sommets; i++) 
	{
		marques_1[i] = 0;}
 
}
void créer_file(int marques_1[],int sommet_source,Noeud *noeud,Liste *liste)
{
 Noeud *nouveau;
 nouveau=(Noeud*)malloc(sizeof(Noeud));
 nouveau->info=sommet_source;
 nouveau->suiv=liste->tete;
 liste->tete=nouveau;
}
void enfiler(int sommet,Noeud *noeud,Liste *liste)
{
 printf("Je visite le sommet %d \n",sommet);
 Noeud *nouveau;
 nouveau=(Noeud*)malloc(sizeof(Noeud));

    if (liste->tete == NULL) {
        // Si la liste est vide, le nouveau nœud devient la tête de liste
         liste->tete = nouveau;
         nouveau->info=sommet;
         nouveau->suiv=NULL;
    } else {
        Noeud *courant = liste->tete;
        while (courant->suiv !=NULL) {
            courant = courant->suiv;
        }
        courant->suiv = NULL;
        courant->info=sommet;
    }
}
void marquer(int sommet,int marques_1[])
{
marques_1[sommet]=1;
}

int défiler(Noeud *noeud,Liste *liste)// je dois enlevre le preimer élément
{
int valeurSupprimee = liste->tete->info;
if (liste->tete==NULL)
{
 printf("liste vide\n");
}
 liste->tete=noeud->suiv;
 
 return valeurSupprimee;
}

    

void parcours(Graphe *graphe,int sommet_source,Liste *liste,Noeud *noeud)
{
   int file[graphe->nb_sommets];
   int s;
   int marques_1[graphe->nb_sommets];
   init_marques(graphe,marques_1);
   créer_file(marques_1,sommet_source,noeud,liste);
   marquer(sommet_source,marques_1);
   printf("Je visite en premier le sommet %d\n",sommet_source);
 while(liste->tete!=NULL)
 {
  s=défiler(noeud,liste);
 for (int i=0;i<(graphe->nb_sommets);i++)
{
 if (graphe->matrice_adjacence[s][i]!=0)
 {
 
   if (marques_1[i]!=1)
   {
    enfiler(i,noeud,liste);
    marquer(i,marques_1);
   }
 }
}
}
printf("Tous les sommets on été parcourus\n");
printf("Fin du parcours\n");
}

void Dijkstra(Graphe* graphe,int sommet_source,Liste *liste,Noeud *noeud)
{
int* pondération = (int*) malloc((graphe->nb_sommets)*sizeof(int));
 for(int i=0;i<graphe->nb_sommets;i++)
 {
  pondération[i]=1000000;
 }
 int s;
 int marques_1[graphe->nb_sommets];
 init_marques(graphe,marques_1);
 créer_file(marques_1,sommet_source,noeud,liste);
 marquer(sommet_source,marques_1);
 pondération[sommet_source]=0;
 printf("Je visite en premier le sommet %d\n",sommet_source);
  while(liste->tete!=NULL)
 {
  s=défiler(noeud,liste);
   for (int i=0;i<(graphe->nb_sommets);i++)
{
 if (graphe->matrice_adjacence[s][i]!=0)
 {
   if ((pondération[s]+graphe->matrice_adjacence[s][i])<pondération[i])
   {
    pondération[i]=pondération[s]+graphe->matrice_adjacence[s][i];
    printf("la pondération du sommet %d devient %d\n",i,pondération[i]);
   }
   if (marques_1[i]!=1)
 {
  enfiler(i,noeud,liste);
  marques_1[i]=1;
 }
}
}
}
  for(int i=0;i<graphe->nb_sommets;i++)
 {
  printf("la plus petite distance entre le sommet de départ %d et le sommet %d est %d\n",sommet_source,i,pondération[i]);
 }
}


int main()
{
    const char* graphFileName = "graph_10_13.txt";
    Graphe graphe;
    Liste liste;
    Noeud noeud;
    liste.tete=NULL;
    	FILE *fp;
	fp = fopen(graphFileName, "r");
	
	if (fp != NULL) {
		int nb_sommets, nb_arcs;
		fscanf(fp, "%d %d", &nb_sommets, &nb_arcs);
		graphe.nb_sommets=nb_sommets+1;
		graphe.nb_arcs=nb_arcs;
		}
    cree_graph(&graphe,graphFileName);
    printf_graph(&graphe);
    //parcours(&graphe,5,&liste,&noeud);
    Dijkstra(&graphe,5,&liste,&noeud);
    return 0;
}
