#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//struct Node
//{
//    int data;
//    struct Node *lchild;
//    struct Node *rchild;
//};
//
//void build_tree(struct Node *);

struct Tree {
    int size;
    int data[];
};

struct Tree *InitializeTree(void);
void build_tree(struct Tree *, int);
void print_tree(struct Tree *);
int search(struct Tree *, int, int);

int main(void)
{
    int op, l, key;
    struct Tree *T = InitializeTree();


    while(1)
    {
        printf("\n__________________________________________________________________\n");
        printf("Select an operation:\n");
		printf("\t1. Build Binary Tree\n");
		printf("\t2. Default Binary Tree\n");
		printf("\t3. print Tree\n");
		printf("\t4. Search an item in tree\n");
		printf("\t5. To exit\n");
        printf("__________________________________________________________________\n\n");
		scanf("%d", &op);

        switch(op)
		{
		    case 1: build_tree(T, 0);
                    break;
            case 2: T->data[0] = 1;
                    T->data[1] = 2;
                    T->data[2] = 3;
                    T->data[4] = 5;
                    break;
            case 3: print_tree(T);
                    break;
            case 4: printf("Enter an item to be searched: ");
                    scanf("%d", &key);
                    l= search(T, key, 0);    // Start from root
                    if(l == -1)
                        printf("Item not found!\n");
                    else
                        printf("%d is found at node %d\n", key, l);
                    break;
            case 5: free(T);
                    exit(0);
            default: printf("Wrong Choice!\n\n");
		}
    }
}

struct Tree *InitializeTree(void)
{
    int n;
    printf("Enter the size of array: ");
    scanf("%d", &n);

    struct Tree *T = malloc(sizeof(struct Tree) + n*sizeof(int));

    if(T == NULL)
    {
        printf("Insufficient Memory\n");
        exit(0);
    }

    T->size = n;
    memset(T->data, -1, sizeof(int)*n);
    return T;
}

void build_tree(struct Tree *T, int I)
{
    if(I >= T->size)
    {
        printf("Out of space\n");
        return;
    }

    if(I != -1)
    {
        int item;
        char opn;

        printf("Enter an item to be inserted at node %d: ", I);
        scanf("%d", &item);

        T->data[I] = item;
        printf("Node %d has left sub-tree (y/n): ", I);
        scanf(" %c", &opn);

        if(opn == 'y' || opn == 'Y')
            build_tree(T, 2*I+1);
        else
            build_tree(T, -1);

        printf("Node %d has right sub-tree (y/n): ", I);
        scanf(" %c", &opn);

        if(opn == 'y' || opn == 'Y')
            build_tree(T, 2*I+2);
        else
            build_tree(T, -1);
    }

}

void print_tree(struct Tree *T)
{
    for(int i = 0; i < T->size; i++)
        printf("%3d", i);
    printf("\n");
    for(int i = 0; i < T->size; i++)
        printf("%3d", T->data[i]);
}

int search(struct Tree *T, int key, int I)
{
    if(T->data[I] != key)
    {
        if(2*I + 1 <= T->size)
        {
            int i = search(T, key, 2*I+1);
            if(i == -1)
                i = search(T, key, 2*I+2);
            return i;
        }
        else
            return -1;
    }

    return I;
}
