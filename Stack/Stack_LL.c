#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int item;
    struct Node *next;
};

int Pop_LL(struct Node ** );
void Push_LL(struct Node ** ,  int );
void PrintStack_LL(struct Node * );

int main(void)
{
    int op, item;
    struct Node *stack = NULL;

    while(1)
    {
        printf("Select an operation:\n");
		printf("1. Push an item to stack\n");
		printf("2. Pop an item from stack\n");
		printf("3. Print Stack\n");
		printf("Press -1 to exit\n\n");

		scanf("%d", &op);

		switch(op)
		{
		    case 1: printf("Enter an item to be pushed: ");
                    scanf("%d", &item);
                    Push_LL(&stack, item);
                    break;

            case 2: item = Pop_LL(&stack);
                    if(item != -1)
                        printf("The poped item is: %d\n", item);
                    break;

            case 3: printf("The stack is: ");
                    PrintStack_LL(stack);
                    break;
            case -1: exit(0);
            default: printf("Wrong Choice!\n\n");
		}
    }
}


void Push_LL(struct Node **stack,  int item)
{
    struct Node *new = malloc(sizeof(struct Node));

    if(new == NULL)
    {
        printf("Memory Insufficient\n");
        return;
    }
    else
    {
        new->item = item;
        new->next = *stack;
        *stack = new;
    }
}

int Pop_LL(struct Node **stack)
{
    struct Node *ptr = *stack;
    int item;
    if(*stack == NULL)
    {
        printf("Stack is underflow\n");
        return -1;
    }
    else
    {
        *stack = (*stack)->next;
        item =  ptr->item;
        free(ptr);
        return item;
    }
}

void PrintStack_LL(struct Node *stack)
{
    if(stack == NULL)
    {
        printf("Empty\n");
        return;
    }
    while(stack != NULL)
    {
        printf("%d ", stack->item);
        stack = stack->next;
    }
    printf("\n\n");
}
