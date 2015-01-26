#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *LLink;
	int data;
	struct Node *RLink;
};

void InsertFront_DL(struct Node **, int );
void InsertEnd_DL(struct Node *, int );
void InsertAny_DL(struct Node *, int , int );
void print_DL(struct Node *);
void DeleteFront_DL(struct Node ** );
void DeleteEnd_DL(struct Node ** );
void DeleteAny_DL(struct Node **, int );

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
			        InsertFront_DL(&list, val);
					break;

			case 2: printf("Enter a data to be inserted: ");
					scanf("%d", &val);
					InsertEnd_DL(list, val);
					break;

			case 3: printf("Enter a data to be inserted and a key data of the node after which it has to be inserted: ");
					scanf("%d %d", &val, &key);
					InsertAny_DL(list, val, key);
					break;
			case 4: printf("Linked list is: ");
					print_DL(list);
					break;
			case 5: DeleteFront_DL(&list); 	break;

			case 6: DeleteEnd_DL(&list); 	break;

			case 7: printf("Enter a key data of the node which is to be deleted: ");
					scanf("%d", &key);
					DeleteAny_DL(&list, key);
					break;
			case -1: exit(0);

			default: printf("Wrong choice\n");
		}
	}
}

void InsertFront_DL(struct Node **list, int val)
{
    struct Node *new = malloc(sizeof(struct Node));

    if(new == NULL)
	{
		printf("Memory underflow: Insertion is not possible\n");
		return;
	}

	new->data =  val;
	new->RLink = *list;
	new->LLink = NULL;
	if(*list != NULL)
        (*list)->LLink = new;
	*list = new;
}

void InsertEnd_DL(struct Node *list, int val)
{
	struct Node *new = malloc(sizeof(struct Node));

	if(new == NULL)
	{
		printf("Memory is underflow: Insertion is not possible\n");
		return;
	}

    if(list != NULL)
        while(list->RLink != NULL)
            list = list->RLink;
    else
    {
        printf("Insertion failed. Insert in front first.\n\n");
        return;
    }
	new->data =  val;
	new->LLink = list;
	list->RLink = new;
	new->RLink = NULL;
}

void InsertAny_DL(struct Node *list, int val, int key)
{
	struct Node *new = malloc(sizeof(struct Node));

	if(new == NULL)
	{
		printf("Memory is insufficient: Insertion is not possible\n");
		return;
	}

	while(list != NULL && list->data != key)
		list = list->RLink;
	if(list == NULL)
	{
		printf("%d is not available in the list\n", key);
		return;
	}

	new->data =  val;
	new->RLink = list->RLink;
	if(list->RLink != NULL)
        list->RLink->LLink = new;
	new->LLink = list;
	list->RLink = new;

}

void print_DL(struct Node *list)
{
    if(list == NULL)
    {
        printf("Empty\n\n");
        return;
    }
	while(list != NULL)
	{
		printf("%d ", list->data);
		list = list->RLink;
	}
	printf("\n\n");
}


void DeleteFront_DL(struct Node **list)
{
	struct Node *ptr = *list;

	if(ptr == NULL)
	{
		printf("The list is empty: No deletion\n");
		return;
	}

	*list = (*list)->RLink;
	if(*list != NULL)
        (*list)->LLink = NULL;
	free(ptr);
}

void DeleteEnd_DL(struct Node **list)
{
	struct Node *temp = *list;
	if(*list == NULL)
 	{
		printf("The list is empty: No deletion\n");
		return;
	}

	while(temp->RLink != NULL)
	{
	    printf("%d\n", temp->data);
		temp = temp->RLink;
	}

	if(temp->LLink != NULL)
    {
        printf("%d\n", (temp->LLink)->data);
        (temp->LLink)->RLink = NULL;

    }
    else
        *list = NULL;
    free(temp);
}

void DeleteAny_DL(struct Node **list, int key)
{
	struct  Node *cur = *list;
	if(*list == NULL)
	{
		printf("The list is empty: No deletion\n");
		return;
	}

	while(cur != NULL && cur->data != key)
		cur = cur->RLink;

	if(cur == NULL)
	{
		printf("Node with key does not exist\n");
		return;
	}
	else if(cur->LLink == NULL)
    {
        *list = (*list)->RLink;
        (*list)->LLink = NULL;
    }
	else
    {
        cur->LLink->RLink = cur->RLink;
        if(cur->RLink != NULL)
            cur->RLink->LLink = cur->LLink;
    }

	free(cur);
}
