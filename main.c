#include <stdio.h>
#include <stdlib.h>

void generateNodesFile() {
    FILE *file = fopen("nodes.csv", "w");
    if (file == NULL) {
        perror("Erreur lors de la création du fichier nodes.csv");
        exit(EXIT_FAILURE);
    }
    // En-tête du fichier des nœuds
    fprintf(file, "Id,Label,TrophicLevel,Category\n");
    // Données des nœuds
    fprintf(file, "1,Mûres,PL,Producer\n");
    fprintf(file, "2,Glands,PL,Producer\n");
    fprintf(file, "3,Herbes,PL,Producer\n");
    fprintf(file, "4,Feuilles Vertes,PL,Producer\n");
    fprintf(file, "5,Litière,1,Resource\n");
    fprintf(file, "6,Chenille,CI,Consumer\n");
    fprintf(file, "7,Campagnol,CI,Consumer\n");
    fprintf(file, "8,Collembole,CI,Consumer\n");
    fprintf(file, "9,Gamaside,CII,Consumer\n");
    fprintf(file, "10,Mésange,CII,Consumer\n");
    fprintf(file, "11,Renard,CIII,Consumer\n");
    fprintf(file, "12,Martre,CIII,Consumer\n");
    fprintf(file, "13,Décomposeurs,2,Decomposer\n");
    fclose(file);
}

void generateEdgesFile() {
    FILE *file = fopen("edges.csv", "w");
    if (file == NULL) {
        perror("Erreur lors de la creation du fichier edges.csv");
        exit(EXIT_FAILURE);
    }
    // En-tête du fichier des arêtes
    fprintf(file, "Source,Target,Weight,Type\n");
    // Données des arêtes
    fprintf(file, "1,6,1,Trophic\n");
    fprintf(file, "2,7,1,Trophic\n");
    fprintf(file, "3,6,1,Trophic\n");
    fprintf(file, "4,6,1,Trophic\n");
    fprintf(file, "5,8,1,Trophic\n");
    fprintf(file, "5,9,1,Trophic\n");
    fprintf(file, "5,13,1,Decomposition\n");
    fprintf(file, "6,10,1,Trophic\n");
    fprintf(file, "7,11,1,Trophic\n");
    fprintf(file, "10,12,1,Trophic\n");
    fprintf(file, "7,11,1,Trophic\n");
    fprintf(file, "9,12,1,Trophic\n");
    fclose(file);
}

int main() {
    generateNodesFile();
    generateEdgesFile();
    printf("Fichiers nodes.csv et edges.csv produits avec succès !\n");
    return 0;
}
