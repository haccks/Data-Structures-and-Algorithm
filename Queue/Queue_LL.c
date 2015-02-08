#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    struct Node *LLink;
	int item;
	struct Node *RLink;
};

struct Queue{
    struct Node *front;
    struct Node *rear;
    struct Node *data_list;
};

struct Queue *InitializeQueue(void);
void Enqueue(struct Queue *, int );
int Dequeue(struct Queue *);
void PrintQueue(struct Queue *);

int main(void)
{
    int op, item;
    struct Queue *Q = InitializeQueue();
   // printf("%d", (int)sizeof(struct Queue));
    while(1)
    {
        printf("\n__________________________________________________________________\n");
        printf("Select an operation:\n");
		printf("\t1. Enqueue\n");
		printf("\t2. Dequeue\n");
		printf("\t3. Print Queue\n");
		printf("\t4. To exit\n");
        printf("__________________________________________________________________\n\n");
		scanf("%d", &op);

        switch(op)
		{
		    case 1: printf("Enter an item to be inserted: ");
                    scanf("%d", &item);
                    Enqueue(Q, item);
                    break;
            case 2: item = Dequeue(Q);
                    if(item != -1)
                        printf("Deleted item is: %d", item);
                    break;
            case 3: PrintQueue(Q);
                    break;
            case 4: free(Q);
                    exit(0);
            default: printf("Wrong Choice!\n\n");
		}
    }
}

struct Queue *InitializeQueue(void)
{
    struct Queue *Q = malloc(sizeof(struct Queue));

    if(Q == NULL)
    {
        printf("Insufficient Memory\n");
        exit(0);
    }
    Q->data_list = Q->front = Q->rear = NULL;

    return Q;
}

/*void Enqueue(struct Queue *Q, int item)
{
    struct Node *new = malloc(sizeof(struct Node));

    if(new == NULL)
    {
        printf("Insufficient Memory. No insertion\n");
        exit(0);
    }

    /// If first node is created then rear will point to it.
    if(Q->data_list == NULL)
        Q->rear = new;
//    /// otherwise
//    else
//    while((*Q)->rear->RLink != NULL)
//        (*Q)->rear = (*Q)->rear->RLink;

    /// Insert in front of list.
    new->item = item;
    new->RLink = Q->data_list;
    new->LLink = NULL;
    if(Q->data_list != NULL)
        Q->data_list->LLink = new;
    Q->data_list = new;
    Q->front = Q->data_list;
}*/

/// Insert at the end of the list.
void Enqueue(struct Queue *Q, int item)
{
    struct Node *new = malloc(sizeof(struct Node));

    if(new == NULL)
    {
        printf("Insufficient Memory. No insertion\n");
        exit(0);
    }

    new->item = item;
    new->RLink = NULL;
    /// If first node is created then front and rear pointer will point to it.
    if(Q->data_list == NULL)
    {
        Q->data_list = Q->front = Q->rear = new;
        new->LLink = NULL;
    }
    else
    {
        new->LLink = Q->rear;
        Q->rear->RLink = new;
        Q->rear = Q->rear->RLink;
    }
}

/// from front of the list.
int Dequeue(struct Queue *Q)
{
    if(Q->front == NULL)
    {
        printf("Queue is empty. No deletion");
        free(Q->rear);
        Q->rear = Q->front;
        return -1;
    }

    int item = Q->front->item;
    struct Node *ptr = Q->front;

    Q->data_list = Q->front = Q->front->RLink;
    if(Q->front != NULL)
    {
        Q->front->LLink = NULL;
    }
    ///If there is only node then set rear pointer to NULL.
    else
        Q->rear = Q->rear->RLink;
    free(ptr);
    return item;
}

void PrintQueue(struct Queue *Q)
{
    struct Node *ptr = Q->rear;
    if(ptr == NULL)
    {
        printf("Queue is empty\n");
        return;
    }
    printf("Rear-> ");
    while(ptr != NULL)
    {
        printf("%d ", ptr->item);
        ptr = ptr->LLink;
    }
    printf("<-Front\n");
}
