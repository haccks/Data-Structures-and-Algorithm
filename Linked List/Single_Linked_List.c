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
void DeleteFront_SL(struct Node ** );
void DeleteEnd_SL(struct Node * );
void DeleteAny_SL(struct Node **, int );

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
		printf("5. Delete node from beginning\n");
		printf("6. Delete node from end\n");
		printf("7. Delete node from any position\n");
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
			case 5: DeleteFront_SL(&list); 	break;

			case 6: DeleteEnd_SL(list); 	break;

			case 7: printf("Enter a key data of the node which is to be deleted: ");
					scanf("%d", &key);
					DeleteAny_SL(&list, key);
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
		printf("Memory underflow: Insertion is not possible\n");
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
		printf("Memory is insufficient: Insertion is not possible\n");
		return;
	}

	while(list->next != NULL)
		list = list->next;

	new->data =  val;
	list->next = new;
	new->next = NULL;
}

void InsertAny_SL(struct Node *list, int val, int key)
{
	struct Node *new = malloc(sizeof(struct Node));

	if(new == NULL)
	{
		printf("Memory is insufficient: Insertion is not possible\n");
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

void DeleteFront_SL(struct Node **list)
{
	struct Node *ptr = *list;

	if(ptr == NULL)
	{
		printf("The list is empty: No deletion\n");
		return;
	}

	*list = (*list)->next;
	//ptr->next = NULL;
	free(ptr);
}

void DeleteEnd_SL(struct Node *list)
{
	struct Node *prev = NULL;
	if(list == NULL)
	{
		printf("The list is empty: No deletion\n");
		return;
	}

	while(list->next != NULL)
	{
		prev = list;
		list = list->next;
	}
	if(prev != NULL)
		prev->next = NULL;
	free(list);
}

void DeleteAny_SL(struct Node **list, int key)
{
	struct Node *prev = NULL;
	struct  Node *cur = *list;
	if(*list == NULL)
	{
		printf("The list is empty: No deletion\n");
		return;
	}

	while(cur != NULL && cur->data != key)
	{
		prev = cur;
		cur = cur->next;
	}

	if(cur == NULL)
	{
		printf("Node with key does not exist\n");
		return;
	}
	else if(prev == NULL)
		*list = (*list)->next;
	else
		prev->next = cur->next;
	free(cur);
}
