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
void insert(struct Tree *, int, int);
void delete(struct Tree *, int);

int main(void)
{
    int op, l, key, item;
    struct Tree *T = InitializeTree();


    while(1)
    {
        printf("\n__________________________________________________________________\n");
        printf("Select an operation:\n");
		printf("\t1. Build Binary Tree\n");
		printf("\t2. Default Binary Tree (assumed to be of size 5)\n");
		printf("\t3. print Tree\n");
		printf("\t4. Search an item in tree\n");
		printf("\t5. Insert a node from tree\n");
		printf("\t6. Delete a node from tree\n");
		printf("\t7. To exit\n");
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
            case 5: printf("Enter an item to be inserted: ");
                    scanf("%d", &item);
                    printf("Enter a key after which item is inserted: ");
                     scanf("%d", &key);
                    insert(T, key, item);
                    break;
            case 6: printf("Enter an item of the node to identify node for deletion: ");
                    scanf("%d", &item);
                    delete(T, item);
                    break;
            case 7: free(T);
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

/// Its in fact preorder traversal. Root is processed before visiting any child.
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

void insert(struct Tree *T, int key, int item)
{
    int l = search(T, key, 0);
    char opn;

    if(l == 0)
    {
        printf("Search is unsuccessful. No insertion\n");
        return;
    }

    if(T->data[2*l+1] == -1 || T->data[2*l+2] == -1)
    {
        printf("Press L or R to insert in left or right respectively: ");
        scanf(" %c", &opn);

        if(opn == 'l' || opn == 'L')
        {
            if(T->data[2*l+1] == -1)
                T->data[2*l+1] = item;
            else
                printf("Insertion is not possible in left\n");
        }
        else if(opn == 'r' || opn == 'R')
        {
            if(T->data[2*l+2] == -1)
                T->data[2*l+2] = item;
            else
                printf("Insertion is not possible in right\n");
        }
    }
    else
        printf("Item can't be inserted as a leaf node\n");
}

void delete(struct Tree *T, int item)
{
    int l = search(T, item, 0);

    if(l == -1)
    {
        printf("Node does not exist. No deletion\n");
        return;
    }

    if(2*l+1 >= T->size || (T->data[2*l+1] == -1 && T->data[2*l+2] == -1))
        T->data[l] = -1;
    else
        printf("The node containing %d is not a leaf node\n", item);
}
