#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool IsEmpty(int );
int Pop_Array(int *, int * );
bool IsFull(int , int );
void Push_Array(int * , int * ,int ,  int);
void PrintStack_Array(int *, int);

int main(void)
{
    int TOP = -1;
    int SIZE, op, item;
    printf("Enter the size of stack: ");
    scanf("%d", &SIZE);
    int stack[SIZE];

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
                    Push_Array(&TOP, stack, item, SIZE);
                    break;

            case 2: item = Pop_Array(&TOP, stack);
                    if(item != -1)
                        printf("The poped item is: %d\n", item);
                    break;

            case 3: printf("The stack is: ");
                    PrintStack_Array(stack, TOP);
                    break;
            case -1: exit(0);
            default: printf("Wrong Choice!\n\n");
		}
    }
}

bool IsFull(int top, int size)
{
    return top >= size-1;
}

bool IsEmpty(int top)
{
    return top < 0;
}

void Push_Array(int *top, int *array, int item, int size)
{
    if(IsFull(*top, size))
    {
        printf("Stack is overflow\n");
        return;
    }
    else
    {
        array[++(*top)] = item;
    }
}

int Pop_Array(int *top, int *array)
{
    if(IsEmpty(*top))
    {
        printf("Stack is underflow\n");
        return -1;
    }
    else
    {
        return array[(*top)--];
    }
}

void PrintStack_Array(int *array, int top)
{
    for(int i = top; i >= 0; i--)
        printf("%d ", array[i]);
    printf("\n\n");
}
