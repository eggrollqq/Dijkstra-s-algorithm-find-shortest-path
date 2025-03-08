#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "util.h"
#include "heap.h"
#include "main.h"
#include "stack.h"
#include "graph.h"
#include <cfloat>

int lastSrc = -1;
bool SingleSourceValid, SinglePairValid = false;
int main(int argc, char **argv) {
    
    int network03Flag, SingleSourceCountFlag;
    int flag = 0; // For directed/undirected graph
    if (argc > 3) {
        flag = atoi(argv[3]);
        if (flag < 1 || flag > 2) { 
            fprintf(stderr, "Error: invalid flag value\n");
            return 1;  
        }
     }

    if (argc > 1 && strcmp(argv[1], "network03.txt") == 0) {
        network03Flag = 1;
    }
    
    
    flag = atoi(argv[3]);

    // Open file
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
        return 1;
    }

    int n, m; // number of vertices and edges
    fscanf(fp, "%d %d", &n, &m);
    
    // Allocate memory for V and ADJ
    VERTEX **V = (VERTEX **)malloc((n + 1) * sizeof(VERTEX *));
    NODE **ADJ = (NODE **)malloc((n + 1) * sizeof(NODE *));

    if (!V || !ADJ) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(fp);
        free(V);
        free(ADJ);
        return 1;
    }

    // Initialize vertices and adjacency lists
    // Inside the main function after allocating V and ADJ
    for (int i = 1; i <= n; i++) {
        V[i] = (VERTEX *)malloc(sizeof(VERTEX));
        if (!V[i]) {
        // Free previously allocated memory
            for (int j = 1; j < i; j++) {
            free(V[j]);
        }
            free(V);
            free(ADJ);
            fclose(fp);
            fprintf(stderr, "Error: Memory allocation failed for vertex\n");
            return 1;
    }

    V[i]->position = i;
    V[i]->d = DBL_MAX;
    V[i]->pi = -1;
    ADJ[i] = NULL;
}

    // Read edges and populate adjacency lists
    for (int i = 1; i <= m; i++) {
    int edgeIndex, u, v;
    double w;
    fscanf(fp, "%d %d %d %lf", &edgeIndex, &u, &v, &w);

    if (u < 1 || u > n || v < 1 || v > n) {
        fprintf(stderr, "Error: Edge with invalid vertices\n");
        // Handle error or exit
    }

    insertIntoAdjacencyList(ADJ, u, v, w, edgeIndex, flag); // insert at front
    if (strcmp(argv[2], "UndirectedGraph") == 0) {
        insertIntoAdjacencyList(ADJ, v, u, w, edgeIndex, flag); // also insert reverse edge for undirected graph
    }
}

    fclose(fp);
    int key;
    int returnV;
    char Word[100];
    while (1) {

        returnV = nextInstruction(Word, &key);

        if (returnV == 0){
            fprintf(stderr, "Invalid instruction: %s\n", Word);
            continue;
        }

        if (strcmp(Word, "Stop") == 0) {
            break;
            }
        
        if (strcmp(Word, "PrintADJ") == 0) {
            PrintADJ(ADJ, n);
            continue;
            }

        if (strcmp(Word, "SinglePair") == 0) {
            int src, dest;
            fscanf(stdin, "%d %d", &src, &dest);
            SinglePairValid = true;
            // Check if src and dest are within the valid range
            if (src < 1 || src > n || dest < 1 || dest > n) {
                fprintf(stderr, "Invalid vertices\n");
                continue;
            }
            
            dijkstra(V, ADJ, n, src, dest);
            
            //if (V[dest+1]->d == DBL_MAX) {
                //printf("%f", V[dest - 1]->d);
                //printf("No path from %d to %d.\n", src, dest);
            //} else {
                //printf("Shortest path weight from %d to %d is: %f\n", src, dest, V[dest +1]->d);
            //}
            continue;
            }

        if(strcmp(Word, "SingleSource")==0){
            int src;
            fscanf(stdin, "%d", &src);

            if (src < 1 || src > n) {
                fprintf(stderr, "Invalid source vertex\n");
                continue;
            }
            lastSrc = src;
            SingleSourceValid = true;
            SingleSource(V, ADJ, n, src, network03Flag, SingleSourceCountFlag);
            SingleSourceCountFlag++;
            
            if (SingleSourceCountFlag > 10){
                SingleSourceCountFlag = 1;
            }
            
            continue;
        }
        
        
        
        if (strcmp(Word, "PrintPath") == 0) {
            int src, dest;
            fscanf(stdin,"%d %d", &src, &dest);

            if (src < 1 || src > n || dest < 1 || dest > n) {
                fprintf(stderr, "Invalid vertices\n");
                continue;
                }

            if (src == lastSrc && SingleSourceValid){

            printPath(V, n, src, dest);
            continue;
            }
            if (SinglePairValid){
            printPath(V, n, src, dest);
            continue;    
            }
            else{
                    continue;
            }
        }



        if(strcmp(Word, "PrintLength")==0){
            int src, dest;
            fscanf(stdin, "%d %d", &src, &dest);

            if (src < 1 || src > n || dest < 1 || dest > n) {
                fprintf(stderr, "Invalid vertices\n");
                continue;
            }

            PrintLength(V, n, src, dest);
            continue;
        }
    
        }

    // Free dynamically allocated memory
    for (int i = 1; i <= n; i++) {
        free(V[i]);
        while (ADJ[i]) {
            NODE *temp = ADJ[i];
            ADJ[i] = ADJ[i]->next;
            free(temp);
        }
    }
    free(V);
    free(ADJ);

    return 0;
}
