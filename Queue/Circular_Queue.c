/***************************************************************************************
 * Queue_Array.c has one potential problem that the queue may not be full , still a    *
 * request for insertion operation may be denied. For example, let queue size of 5 and *
 * queue is full. Perform 2 or 3 deletion operation and then requesting an insertion   *
 * operation will be denied because the insertion pointer (or "rear") reaches the end  *
 * of the queue. This is simply a wastage of memory.                                   *
 *                                                                                     *
 * This problem can be overcome by improving Enqueue or Dequeue functions or using a   *
 * circular queue as follows:
 ***************************************************************************************/

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
void CircularEnqueue(struct Queue *, int );
int CircularDequeue(struct Queue *);
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
                    CircularEnqueue(Q, item);
                    break;
            case 2: item = CircularDequeue(Q);
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

/****************************************************************************************
 * Whenever the "rear" member gets to the end of the queue, test whether the "front" is *
 * 0 or not; if not, insert the elements so that they are wrapped from the beginning    *
 * and thus make room for a new item.                                                   *
 ****************************************************************************************/
void CircularEnqueue(struct Queue *Q, int item)
{
    /// Queue will be full, either when front is 0 and rear is at the end or rear is just
    /// one less than that of front. Condition "(Q->rear+1) % Q->QueueSize == Q->front"
    /// will check both possibilities.
    if((Q->rear+1) % Q->QueueSize == Q->front)
    {
        printf("Queue is full. No insertion.\n");
        return;
    }
    else if(Q->rear == -1 && Q->front == -1)
    {
        Q->front = 0;
    }
    /// Modulo operation is done for wraparound condition.
    Q->rear = (Q->rear+1) % Q->QueueSize;
    Q->data[Q->rear] = item;
}

int CircularDequeue(struct Queue *Q)
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
        /// Modulo operation is done for wraparound condition.
        Q->front = (Q->front+1) % Q->QueueSize;
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
    /// Before wrapping the inserted elements.
    if(Q->rear >= Q->front)
        for(int i = Q->rear; i >= Q->front; i--)
            printf("%d ", Q->data[i]);
    /// After wrapping is performed.
    else
    {
        /// Print elements till rear is 0.
        for(int i = Q->rear; i >= 0; i--)
            printf("%d ", Q->data[i]);
        /// Print elements from end of the queue till front is reached.
        for(int i = Q->QueueSize-1; i >= Q->front; i--)
            printf("%d ", Q->data[i]);
    }
    printf("<-Front\n");
}
