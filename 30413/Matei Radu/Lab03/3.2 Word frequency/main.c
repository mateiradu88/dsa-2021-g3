#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node2Way{
    char word[50]; //key
    int occurances;
    struct Node2Way *next;
    struct Node2Way *prev;
}Node2Way;

typedef struct DLList{
    int count;
    Node2Way *first;
    Node2Way *last;
}DLList;

Node2Way *New_Node(char word[]){
    Node2Way *node_add = (Node2Way *)malloc(sizeof(Node2Way));
    if(node_add){
        strcpy(node_add -> word, word);
        node_add -> occurances = 1;
        node_add -> next = node_add -> prev = NULL;
    }
    return node_add;
}

DLList *New_DLL(){
    DLList *listPtr = (DLList*)malloc(sizeof(DLList));
    if (listPtr){
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}
int isEmpty(DLList *listPtr)
{
    if(listPtr -> count == 0)
        return 1;
    return 0;
}
int Compare_Nodes(Node2Way *node1,Node2Way *node2){
    return strcmp(node1->word,node2->word);
}



int Insert_In_Place(DLList *listPtr, Node2Way *node){

    if (listPtr){ // the list is non null
        if (isEmpty(listPtr)){
        // p will be the sole node in the list
            listPtr->first = listPtr->last = node;
            node->prev = node->next = NULL; // p is the first and single node
        }
        else{
            Node2Way *current_node = listPtr->first;
            int i=0;
            while(Compare_Nodes(node, current_node)>0 && current_node->next!=NULL){
                current_node = current_node->next;
                i++;
            }
            printf("debug: %s %s %d\n",current_node->word,node->word,i);
            if(Compare_Nodes(node, current_node)<0){
                if (current_node->prev == NULL)
                    listPtr->first = node;
                node->prev =  current_node->prev;
                node->next = current_node;
                current_node->prev = node;
                node->prev->next = node;
            }
            if(Compare_Nodes(node, current_node)==0){
                current_node->occurances++;
            }
            if(Compare_Nodes(node, current_node)>0){
                if (current_node->next == NULL)
                    listPtr->last = node;
                node->prev =  current_node;
                node->next = current_node->next;
                current_node->next = node;
            }
        }
        listPtr->count++;
        return 1; // success
    }
    return 0; // failure

}

void print_ascending(DLList *listPtr, FILE* fw){
    Node2Way *p;
    for(p=listPtr->first; p!=NULL; p=p->next)
        fprintf(fw,"%s:%d\n",p->word,p->occurances);

}

void print_descending(DLList *listPtr, FILE* fw){
    Node2Way *p;
    for(p=listPtr->last; p!=NULL; p=p->prev)
        fprintf(fw,"%s:%d\n",p->word,p->occurances);

}

int main(int argc, char* argv[]){

    FILE *fr, *fw;
    fr = fopen(argv[1], "r");
    fw = fopen(argv[2], "w");
    DLList *Word_List = New_DLL();
    char buffer[50];
    while(fscanf(fr,"%s",buffer)!=EOF){
        Insert_In_Place(Word_List,New_Node(buffer));
    }
    print_ascending(Word_List,fw);
    print_descending(Word_List,fw);

    return 0;
}
