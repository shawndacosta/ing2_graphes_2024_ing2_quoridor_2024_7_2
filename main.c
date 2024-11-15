#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100
#define MAX_EDGES 500

typedef struct Node {
    int id;
    char label[50];
    char trophicLevel[10];
    char category[20];
} Node;

typedef struct Edge {
    int source;
    int target;
    float weight;
    char type[20];
} Edge;

typedef struct Graph {
    Node nodes[MAX_NODES];
    Edge edges[MAX_EDGES];
    int nodeCount;
    int edgeCount;
} Graph;

// Fonction pour charger un reseau depuis un fichier
void loadGraphFromFile(Graph *g, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d", &g->nodeCount, &g->edgeCount);
    for (int i = 0; i < g->nodeCount; i++) {
        fscanf(file, "%d %s %s %s", &g->nodes[i].id, g->nodes[i].label, g->nodes[i].trophicLevel, g->nodes[i].category);
    }

    for (int i = 0; i < g->edgeCount; i++) {
        fscanf(file, "%d %d %f %s", &g->edges[i].source, &g->edges[i].target, &g->edges[i].weight, g->edges[i].type);
    }

    fclose(file);
}

// Fonction pour afficher un reseau en console
void displayGraph(Graph *g) {
    printf("Liste des sommets :\n");
    for (int i = 0; i < g->nodeCount; i++) {
        printf("Id: %d, Etiquette: %s, Niveau Trophique: %s, Categorie: %s\n", g->nodes[i].id, g->nodes[i].label, g->nodes[i].trophicLevel, g->nodes[i].category);
    }

    printf("\nListe des aretes :\n");
    for (int i = 0; i < g->edgeCount; i++) {
        printf("Source: %d, Cible: %d, Poids: %.1f, Type: %s\n", g->edges[i].source, g->edges[i].target, g->edges[i].weight, g->edges[i].type);
    }

    printf("\nSuccesseurs et predecesseurs :\n");
    for (int i = 0; i < g->nodeCount; i++) {
        printf("\nSommet %s:\n", g->nodes[i].label);

        printf("Successeurs ---> ");
        int hasSuccessor = 0;
        for (int j = 0; j < g->edgeCount; j++) {
            if (g->edges[j].source == g->nodes[i].id) {
                printf("|%s|\t ", g->nodes[g->edges[j].target - 1].label);
                hasSuccessor = 1;
            }
        }
        if (!hasSuccessor) printf("AUCUN");

        printf("\nPredecesseurs ---> ");
        int hasPredecessor = 0;
        for (int j = 0; j < g->edgeCount; j++) {
            if (g->edges[j].target == g->nodes[i].id) {
                printf(" |%s|\t", g->nodes[g->edges[j].source - 1].label);
                hasPredecessor = 1;
            }
        }
        if (!hasPredecessor) printf("AUCUN");

        printf("\n");
    }
}

// Fonction pour trouver les producteurs primaires
void findPrimaryProducers(Graph *g) {
    printf("\nProducteurs primaires:\n");
    for (int i = 0; i < g->nodeCount; i++) {
        int hasPredecessor = 0;
        for (int j = 0; j < g->edgeCount; j++) {
            if (g->edges[j].target == g->nodes[i].id) {
                hasPredecessor = 1;
                break;
            }
        }
        if (!hasPredecessor) {
            printf("%s\n", g->nodes[i].label);
        }
    }
}

// Fonction pour trouver les predateurs finaux
void findTopPredators(Graph *g) {
    printf("\nPredateurs finaux:\n");
    for (int i = 0; i < g->nodeCount; i++) {
        int hasSuccessor = 0;
        for (int j = 0; j < g->edgeCount; j++) {
            if (g->edges[j].source == g->nodes[i].id) {
                hasSuccessor = 1;
                break;
            }
        }
        if (!hasSuccessor) {
            printf("%s\n", g->nodes[i].label);
        }
    }
}

// Fonction pour calculer les degres de chaque sommet
void calculateDegrees(Graph *g) {
    printf("\nDegres des sommets :\n");
    for (int i = 0; i < g->nodeCount; i++) {
        int inDegree = 0, outDegree = 0;
        for (int j = 0; j < g->edgeCount; j++) {
            if (g->edges[j].target == g->nodes[i].id) inDegree++;
            if (g->edges[j].source == g->nodes[i].id) outDegree++;
        }
        printf("%s:\n Degre entrant = %d et Degre sortant = %d\n \n", g->nodes[i].label, inDegree, outDegree);
    }
}

int main() {
    Graph g;
    char filename[100];

    printf("Entrez le nom du fichier contenant le reseau trophique : ");
    scanf("%s", filename);

    loadGraphFromFile(&g, filename);
    displayGraph(&g);
    findPrimaryProducers(&g);
    findTopPredators(&g);
    calculateDegrees(&g);

    return 0;
}
