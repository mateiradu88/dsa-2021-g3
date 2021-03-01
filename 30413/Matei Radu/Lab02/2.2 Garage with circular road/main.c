#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int car_id;
    struct node *next;
} NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} ListT;

typedef struct
{
    char verb;
    int noun;
    int end;
} Command;

int isEmpty(ListT *listPtr)
{
    if(listPtr -> count == 0)
        return 1;
    return 0;
}

ListT *createEmptySLL()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if (listPtr)
    {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

NodeT *createSLLNode(int car_id)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        p->car_id = car_id;
        p->next = NULL;
    }
    return p;
}
int insertAtFront(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        p->next = listPtr->first;
        if (isEmpty(listPtr))
        {
            listPtr->last = p;
        }
        listPtr->first = p;
        listPtr->count++;
        return 1;
    }
    return 0;
}
int insertAtRear(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        if (isEmpty(listPtr))
        {
            listPtr->first = p;
        }
        else
        {
            listPtr->last->next = p;
        }
        listPtr->last = p;
        listPtr->count++;
        return 1;
    }
    return 0;
}

NodeT *find(ListT *listPtr, int given_car_id)
{
    NodeT *p;
    p = listPtr->first;
    while ( p != NULL )
        if ( p->car_id == given_car_id )
        {
            return p;
        }
        else
            p = p->next;
    return NULL;
}
NodeT *deleteLast(ListT *listPtr)
{
    NodeT *q, *q1;
    q1 = NULL;
    q = listPtr->first;
    if ( q != NULL )
    {
        while ( q != listPtr->last )
        {
            q1 = q;
            q = q->next;
        }
        if ( q == listPtr->first )
        {
            listPtr->first = listPtr->last = NULL;
        }
        else
        {
            q1->next = NULL;
            listPtr->last = q1;
        }
    }
    return q;
}


void printList( ListT *list, FILE *fw)
{
    NodeT *current_node;
    current_node = list -> first;
    if(current_node == NULL)
    {
        fprintf(fw,"none\n");
        return;
    }
    while(current_node != NULL)
    {
        fprintf(fw,"%d ", current_node -> car_id);
        current_node = current_node -> next;
    }
    fprintf(fw,"\n");
    return;
}

int deleteByCarId(ListT *listPtr, int givenId)
{
    NodeT *q, *q1;
    q1 = NULL;
    q = listPtr -> first;
    while ( q != NULL )
    {
        if ( q->car_id == givenId )
            break;
        q1 = q;
        q = q->next;
    }
    if ( q != NULL )
    {
        if ( q == listPtr->first )
        {
            listPtr->first = listPtr->first->next;
            free( q );
            if ( listPtr->first == NULL )
                listPtr->last = NULL;
        }
        else
        {
            q1->next = q->next;
            if ( q == listPtr->last )
                listPtr->last = q1;
            free( q );
        }
        return 1;
    }
    return 0;
}

Command readCommand( FILE *fp)
{
    char verb;
    char unparsed_noun;
    int noun;
    Command read_command;
    if(fscanf(fp,"%c",&verb)!=EOF){
        read_command.end =0;
        if(verb!='S'&& verb!='s')
        {
            fscanf(fp,"(%d)",&noun);
            read_command.verb = verb;
            read_command.noun = noun;
            return read_command;
        }
        else
        {
            fscanf(fp,"(%c)",&unparsed_noun);
            read_command.verb = verb;
            read_command.noun = (int)(unparsed_noun);
            return read_command;
        }
    }
    else
    {
        read_command.end = 1;
    }
    return read_command;
}

int main(int argc, char* argv[])
{
    FILE *fr, *fw;
    ListT *garage;
    ListT *road;
    NodeT *current_car_garage;
    Command current_command; //command structure containing verb and noun (function and attribute)
    garage = createEmptySLL();
    road = createEmptySLL();
    fr= fopen(argv[1],"r"); // file pointer definition with files from CL
    fw= fopen(argv[2],"w"); // file pointer definition with files from CL
    current_command.end=0;  // set EOF flag of the command to 0
    while(!current_command.end) //while command not EOF
    {
        current_command = readCommand(fr); //read command from file
        /*this section acts according to the verb input*/
        if(current_command.verb == 'R'|| current_command.verb == 'r') //R verb
        {
            insertAtRear(road,createSLLNode(current_command.noun));
        }
        if(current_command.verb == 'E'|| current_command.verb == 'e') //E verb
        {
            if(!find(road, current_command.noun))
            {
                fprintf(fw,"error: %d not on road!\n",current_command.noun); //throws error if cannot apply verb
            }
            else
            {
                if(road->first->car_id!=current_command.noun)
                {
                    fprintf(fw,"error: %d not at road exit!\n",current_command.noun);
                }
                else{
                    insertAtRear(garage,createSLLNode(current_command.noun));
                    deleteLast(road);
                }
            }
        }
        if(current_command.verb == 'X'|| current_command.verb == 'x') //X verb
        {
            if(find(garage,current_command.noun))
            {
                if(garage -> first -> car_id == current_command.noun)
                {
                    deleteByCarId(garage, current_command.noun);
                    insertAtFront(road,createSLLNode(current_command.noun));
                }
                else
                {
                    fprintf(fw,"error: %d not at exit!\n",current_command.noun); //throws error if cannot apply verb
                }
            }
            else fprintf(fw,"error: %d not in garage!\n",current_command.noun);
        }
        if(current_command.verb == 'S'|| current_command.verb == 's') //S verb
        {
            if(((char)current_command.noun )== 'R'|| (char)current_command.noun == 'r') //S verb with R noun prints road
            {
                fprintf(fw,"R: ");
                printList(road,fw);
            }
            if((char)current_command.noun == 'G'|| (char)current_command.noun == 'g') //S verb with G noun prints road
            {
                fprintf(fw,"G: ");
                printList(garage,fw);
            }
        }
    }

    return 0;
}




















