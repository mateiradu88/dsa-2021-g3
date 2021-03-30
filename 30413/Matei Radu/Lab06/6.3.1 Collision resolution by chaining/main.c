#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
I have decided to implement a hash function using
a rolling polynomial hash (because I have masochistic tendencies)

I decided to use this function because it provides a reasonable
hash that has (probably, as far as I know) evenly distributed
values, reducing probable chain length for inputs

In the final version I plan to use about 2 MB of memory to store
the table (8 byte pointer on 64bit systems), however I will use a
lot less for testing to make sure chaining works

Wish me luck! ^^

PS: It was easier than I imagined, works like a charm

*/
#define M 524288 // 2^19
#define P 257  //prime very close to 256 for ascii encoding
#define STR_LEN 51  //50 + null char

typedef struct command
{
    char verb;
    char noun[STR_LEN];
} command;

typedef struct node
{
    char key[STR_LEN];
    struct node *next;
} NodeT;

long long int rolling_poly_hash(char string[])
{
    /*
    Initially implemented this iteratively.
    But then I got it into my head that it
    was more elegant this way.
    */
    if(string[0]==0)
        return 0;
    return ((rolling_poly_hash(string+1)+string[0])*P)%M;
}

NodeT *insertNodeFront(char key[], NodeT* list)
{
    NodeT *nodeToInsert = (NodeT *)malloc(sizeof(NodeT));
    if (nodeToInsert == NULL)
    {
        return NULL;
    }
    strcpy(nodeToInsert->key, key);
    nodeToInsert->next = list;
    return nodeToInsert;
}

void printTable(NodeT *hashTable[],FILE* fw) {
    for(int i=0;i<M;i++){
        fprintf(fw,"%d: ",i);
        NodeT *current_list;
        current_list = hashTable[i];
        while(current_list!=NULL){
            fprintf(fw,"%s, ", current_list->key);
            current_list = current_list ->next;
        }
        fprintf(fw,"\n");
    }
}

NodeT *find(char key[], NodeT* list) {
    if(list==NULL)
        return NULL;
    if(strcmp(list->key, key)!= 0){
        return find(key, list->next);
    }
    else{
        return list;
    }
}

NodeT *deleteByKey(char key[], NodeT* list) {
    NodeT *nodeToDelete = find(key, list);
    if (nodeToDelete == NULL) {
        printf("%s not in table!\n", key);
    }
    else {
        if(strcmp(nodeToDelete->key, list->key) == 0){
            free(nodeToDelete);
            return list->next;
        }
        while(list->next!=NULL){
            if(strcmp(nodeToDelete->key, list->next->key) == 0){
                list->next = list->next->next;
                free(nodeToDelete);
                return list;
            }
            else{
                list = list->next;
            }
        }
    }
}

command readCommand(FILE *fr)
{
    command inputCommand;
    char buffer[STR_LEN+1];
    if(fgets(buffer,STR_LEN+1,fr)!= NULL){
        inputCommand.verb = buffer[0];
        if(buffer[1]!=0){
            strcpy(inputCommand.noun,buffer+1);
        }
        else{
            inputCommand.noun[0] = 0;
        }
        return inputCommand;
    }
    else{
        inputCommand.noun[0]='X';
        inputCommand.verb='X';
    }
}

int main(int argc, char **argv)
{
    command input;
    NodeT *UserTable[M];
    FILE* fr;
    FILE* fw;
    fr=fopen(argv[1], "r");
    fw=fopen(argv[2], "w");
    for (int i = 0; i < M; i++)
        UserTable[i] = NULL;
    while(input.verb!='X'&&input.noun[0]!='X')
    {
        input = readCommand(fr);
        switch(input.verb)
        {
        case 'i':
            UserTable[rolling_poly_hash(input.noun)] = insertNodeFront(input.noun, UserTable[rolling_poly_hash(input.noun)]);
            break;
        case 'd':
            UserTable[rolling_poly_hash(input.noun)] = deleteByKey(input.noun,UserTable[rolling_poly_hash(input.noun)]);
            break;
        case 'f':
            if(find(input.noun,UserTable[rolling_poly_hash(input.noun)])!=NULL){
                fprintf(fw,"yes\n");
            }
            else{
                fprintf(fw,"no\n");
            }
            break;
        case 'l':
            printTable(UserTable,fw);
            break;
        default:
            printf("Illegal command\n");

        }
    }
    return 0;
}
