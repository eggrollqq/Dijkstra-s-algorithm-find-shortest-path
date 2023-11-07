
#include <stdio.h>
#include <string.h>
#include "util.h"

int nextInstruction(char *Word, int *Key)
{
    int  returnV;
    
    fscanf(stdin, "%s", Word);
    

    if (strcmp(Word, "Stop")==0)    return 1;
    if (strcmp(Word, "PrintADJ")==0)    return 1;
    if (strcmp(Word, "SinglePair")==0)   return 1;
    if (strcmp(Word, "SingleSource")==0)  return 1;
    if (strcmp(Word, "PrintLength") == 0)   return 1;
    if (strcmp(Word, "PrintPath")==0) return 1;
        
    
    return 0;
}