#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node *next;
};

void InsertFront_SL(struct Node **, int );
void InsertEnd_SL(struct Node *, int );
void InsertAny_SL(struct Node *, int , int );
void print_SL(struct Node *);

int main(void)
{
	struct Node *list = NULL;
	
	while(1)
	{
		printf("Select an operation:\n");
		printf("1. Insert node at the beginning\n");
		printf("2. Insert node at the end\n");
		printf("3. Insert note at any position\n");
		printf("4. Print Linked list\n");
		
		printf("Press -1 to exit\n\n");
		
		int op, val, key;
		scanf("%d", &op);
	
		switch(op)
		{
			case 1: printf("Enter a data to be inserted: ");
					scanf("%d", &val);
			        InsertFront_SL(&list, val); 	
					break;
					
			case 2: printf("Enter a data to be inserted: ");
					scanf("%d", &val);
					InsertEnd_SL(list, val); 	
					break;
					
			case 3: printf("Enter a data to be inserted and a key data of the node after which it has to be inserted: ");
					scanf("%d %d", &val, &key);
					InsertAny_SL(list, val, key); 	
					break;
			case 4: printf("Linked list is: ");
					print_SL(list);
					break;
							
			case -1: exit(0);
			
			default: printf("Wrong choice");
		}
	}		
}

void InsertFront_SL(struct Node **list, int val)
{
	struct Node *new = malloc(sizeof(struct Node));
	
	if(new == NULL)
	{
		printf("Memory underflow: Insersion is not possible\n");
		return;
	}
		
	new->data =  val;
	new->next = *list;
	*list = new;	
}

void InsertEnd_SL(struct Node *list, int val)
{
	struct Node *new = malloc(sizeof(struct Node));
	
	if(new == NULL)
	{
		printf("Memory is insufficient: Insersion is not possible\n");
		return;
	}
	
	while(list)
		list = list->next;
	 	
	new->data =  val;
	list = new;
	new->next = NULL;
}
void InsertAny_SL(struct Node *list, int val, int key)
{
	struct Node *new = malloc(sizeof(struct Node));
	
	if(new == NULL)
	{
		printf("Memory is insufficient: Insersion is not possible\n");
		return;
	}
	
	while(list != NULL && list->data != key)
		list = list->next;
	if(list == NULL)
	{
		printf("%d is not available in the list\n", key);
		return;
	}	
	 	
	new->data =  val;
	new->next = list->next;
	list->next = new;
}

void print_SL(struct Node *list)
{
	while(list != NULL)
	{
		printf("%d ", list->data);
		list = list->next;
	}
	putchar('\n');
}
