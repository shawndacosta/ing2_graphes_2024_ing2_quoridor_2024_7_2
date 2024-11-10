#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition des structures pour les nœuds, arêtes et graphes
typedef struct Node {
    char name[50];  // Nom de l'espèce ou de la ressource
    int trophicLevel;  // Niveau trophique
} Node;

typedef struct Edge {
    int from;  // Indice de l'espèce source
    int to;    // Indice de l'espèce cible
    float weight;  // Poids de l'interaction (quantité de biomasse)
} Edge;

typedef struct Graph {
    Node *nodes;
    Edge *edges;
    int nodeCount;
    int edgeCount;
} Graph;

// Fonction pour créer un graphe
Graph* createGraph(int maxNodes, int maxEdges) {
    Graph* g = malloc(sizeof(Graph));
    g->nodes = malloc(maxNodes * sizeof(Node));
    g->edges = malloc(maxEdges * sizeof(Edge));
    g->nodeCount = 0;
    g->edgeCount = 0;
    return g;
}

// Fonction pour ajouter un nœud
void addNode(Graph* g, const char* name, int trophicLevel) {
    Node n;
    strcpy(n.name, name);
    n.trophicLevel = trophicLevel;
    g->nodes[g->nodeCount++] = n;
}

// Fonction pour ajouter une arête
void addEdge(Graph* g, int from, int to, float weight) {
    Edge e = {from, to, weight};
    g->edges[g->edgeCount++] = e;
}

// Fonction pour charger un graphe à partir d'un fichier
void loadGraphFromFile(Graph* g, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur ouverture fichier");
        return;
    }

    int n, e;
    fscanf(file, "%d %d", &n, &e);  // Nombre de nœuds et d'arêtes
    for (int i = 0; i < n; i++) {
        char name[50];
        int level;
        fscanf(file, "%s %d", name, &level);
        addNode(g, name, level);
    }
    for (int i = 0; i < e; i++) {
        int from, to;
        float weight;
        fscanf(file, "%d %d %f", &from, &to, &weight);
        addEdge(g, from, to, weight);
    }
    fclose(file);
}

// Fonction pour afficher le graphe
void displayGraph(Graph* g) {
    printf("Noeuds:\n");
    for (int i = 0; i < g->nodeCount; i++) {
        printf("%d: %s (Niveau trophique %d)\n", i, g->nodes[i].name, g->nodes[i].trophicLevel);
    }

    printf("Aretes:\n");
    for (int i = 0; i < g->edgeCount; i++) {
        printf("%s -> %s (poids: %.2f)\n",
               g->nodes[g->edges[i].from].name,
               g->nodes[g->edges[i].to].name,
               g->edges[i].weight);
    }
}

// Programme principal pour tester
int main() {
    Graph* g = createGraph(100, 100);  // Capacité maximale de 100 nœuds et 100 arêtes

    char filename[100];
    printf("Entrez le nom du fichier texte a ouvrir : ");
    scanf("%s", filename);

    // Chargement des données depuis un fichier
    loadGraphFromFile(g, filename);

    // Affichage du graphe
    displayGraph(g);

    // Libération de la mémoire
    free(g->nodes);
    free(g->edges);
    free(g);

    return 0;
}
