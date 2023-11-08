
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "util.h"
#include "heap.h"
#include "main.h"
#include "stack.h"
#include "graph.h"

int lastSrc = -1;
int lastDest = -1;

int main(int argc, char **argv){
    FILE *fp;
    ELEMENT *element = NULL;
    HEAP *heap = NULL;
    LISTSTACK *liststack = NULL;
    VERTEX *vertex = NULL;
    NODE *node = NULL;
    COLOR *color = NULL;
    int flag;

    int key;
    int returnV;
    char Word[100];

     if (argc > 3) {
        flag = atoi(argv[3]);
        if (flag < 1 || flag > 2) { 
            fprintf(stderr, "Error: invalid flag value\n");
            return 1;  
        }
     }
     

    fp = NULL;

    fp = fopen(argv[1], "r");

    if (!fp){
        fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
        exit(0);
    }



    int n, m;  // number of vertices and edges
    pVERTEX* V = NULL;  // array of pointers to VERTEX
    pNODE* ADJ = NULL;  // array of adjacency lists

    fscanf(fp, "%d %d", &n, &m);

    // Allocate memory for V and ADJ
V = (pVERTEX*) malloc((n + 1) * sizeof(pVERTEX));
ADJ = (pNODE*) malloc((n + 1) * sizeof(pNODE));

if (V == NULL) {
    fprintf(stderr, "Error: Memory allocation failed for V\n");
    // Handle the error or exit
}

    // Initialize all pointers in V and ADJ to NULL
    for (int i = 1; i <= n; i++) {
        V[i] = (pVERTEX) malloc(sizeof(VERTEX));
        V[i]->position = i;
        ADJ[i] = NULL;
    }

    

    // Read edges and populate the adjacency lists
    for (int i = 1; i <= m; i++) {
        int edgeIndex, u, v;
        double w;

        fscanf(fp, "%d %d %d %lf", &edgeIndex, &u, &v, &w);

    if (u < 1 || u > n || v < 1 || v > n) {
        fprintf(stderr, "Error: Edge with invalid vertices\n");
        // Handle error or exit
    }

         insertIntoAdjacencyList(ADJ, u, v, w, edgeIndex, flag);
    
    // Assuming the argv[2] holds the graph type
    if (strcmp(argv[2], "UndirectedGraph") == 0) {
        insertIntoAdjacencyList(ADJ, v, u, w, edgeIndex, flag);
    }
}

    fclose(fp);
    
    while(1) {

        returnV = nextInstruction(Word, &key);

        if (returnV == 0){
            fprintf(stderr, "Invalid instruction: %s\n", Word);
            continue;
        }

        if(strcmp(Word, "Stop")==0){
            exit(0);
        }

        if (strcmp(Word, "PrintADJ") == 0) {
            PrintADJ(ADJ, n);
            continue;
        }

        if(strcmp(Word, "SinglePair") == 0){
            int src, dest;
            fscanf(stdin, "%d %d", &src, &dest); // Read source and destination
            dijkstra(V, ADJ, n, src, dest); // Apply Dijkstra's algorithm
            lastSrc = src;
            lastDest = dest;
            continue;
        }

        if(strcmp(Word, "SingleSource")==0){
            continue;
        }

        if(strcmp(Word, "PrintLength")==0){
            continue;
        }

        if(strcmp(Word, "PrintPath") == 0){
            int s, t;
            fscanf(stdin, "%d %d", &s, &t); // Read s and t;
            if (s == lastSrc && t == lastDest) {
                printPath(V, s, t); // Print the path if valid
    }    else {
            printf("Invalid request\n");
    }
            continue;
        }




    }
    
    
    return 0;    
    // TODO: Don't forget to free the dynamically allocated memory before program exit
}
