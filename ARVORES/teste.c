#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Element maior a direita, elemento menor a esquerda
Node *insert(Node *root, int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));

    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    if (root == NULL)
    {
        root = temp;
    }
    else
    {
        Node *current = root;
        Node *parent = NULL;

        while (1)
        {
            parent = current;
            if (data < parent->data)
            {
                current = current->left;

                if (current == NULL)
                {
                    parent->left = temp;
                    return root;
                }
            }
            else
            {
                current = current->right;

                if (current == NULL)
                {
                    parent->right = temp;
                    return root;
                }
            }
        }
    }

    return root;
}

Node *search(Node *root, int data)
{
    Node *current = root;
    printf("\nVisitando elementos: ");

    while (current)
    {
        printf("%d ", current->data);

        if (data < current->data)
        {
            current = current->left;
        }
        else if (data > current->data)
        {
            current = current->right;
        }
        else
        {
            return current;
        }
    }
}

void inorder_traverssal(struct Node *root)
{
    if (root)
    {
        inorder_traverssal(root->left);
        printf("%d ", root->data);
        inorder_traverssal(root->right);
    }
}

int main()
{
    int i;
    int array[14];

    Node *root = NULL;

    printf("Inserindo: ");
    for (int i = 0; i < 14; i++)
    {
        array[i] = rand() % 101;
        root = insert(root, array[i]);
        printf("%d ", array[i]);
    }

    printf("\nTraverssia em ordem: ");
    inorder_traverssal(root);

    int info;
    printf("\nBuscar numero: ");
    scanf("%d", &info);

    Node *temp = search(root, info);
    if (temp)
    {
        printf("\n[%d] encontrado!\n", temp->data);
    }
    else
    {
        printf("\n[x] (%d) nao encontrado!\n", i);
    }

    printf("\n\n");
    return 0;
}
