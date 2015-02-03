#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Queue{
    int QueueSize;
    int front;
    int rear;
    int data[];
};

struct Queue *InitializeQueue(void);
void Enqueue(struct Queue *, int );
int Dequeue(struct Queue *);
void PrintQueue(struct Queue *);

int main(void)
{
    int op, item;
    struct Queue *Q = InitializeQueue();


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
                        printf("The deleted item is: %d", item);
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
    int n;
    printf("Enter the size of queue: ");
    scanf("%d", &n);

    struct Queue *Q = malloc(sizeof(struct Queue) + n*sizeof(int));

    if(Q == NULL)
    {
        printf("Insufficient Memory\n");
        exit(0);
    }
    Q->QueueSize = n;
    Q->front = -1;
    Q->rear = -1;

    return Q;
}

void Enqueue(struct Queue *Q, int item)
{
    if(Q->rear == Q->QueueSize-1)
    {
        printf("Queue is full. No insertion.\n");
        return;
    }
    else if(Q->rear == -1 && Q->front == -1)
    {
        Q->front = 0;
    }

    Q->data[++Q->rear] = item;
}

int Dequeue(struct Queue *Q)
{
    int item;
    if(Q->front == -1)
    {
        printf("Queue is empty. No deletion\n");
        return -1;
    }

    item = Q->data[Q->front];
    if(Q->rear == Q->front)
    {
        Q->rear = -1;
        Q->front = -1;
    }
    else
        Q->front++;
    return item;
}

void PrintQueue(struct Queue *Q)
{
    if(Q->rear == -1 && Q->front == -1)
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Rear -> ");
    for(int i = Q->rear; i >= Q->front; i--)
        printf("%d ", Q->data[i]);
    printf("<-Front\n");
}
