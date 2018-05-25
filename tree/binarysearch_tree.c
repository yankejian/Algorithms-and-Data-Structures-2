#include <stdlib.h>
#include <stdio.h>

struct node {
    int key;
    struct node *left;
    struct node *right;
};

struct node *tree_init()
{
    return NULL;
}

void tree_free(struct node *node)
{
    if (node != NULL) {
        tree_free(node->left);
        tree_free(node->right);
        free(node);
    }
}

struct node *tree_new(int key)
{
    struct node *new;
    new = malloc(sizeof(struct node));

    new->key = key;
    new->left = new->right = NULL;

    return new;
}

struct node *tree_smallest(struct node* node)
{
    struct node* current;
    current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

struct node *tree_insert(int key)
{
    return tree_new(key);

}

struct node *tree_remove(struct node *node)
{
    if (node->left == NULL) {
        struct node *tmp;
        tmp = node->right;

        free(node);
        return tmp;
    } else if (node->right == NULL) {
        struct node *tmp;
        tmp = node->left;

        free(node);
        return tmp;
    }

    struct node *tmp;
    tmp = tree_smallest(node->right);
    node->key = tmp->key;
    node->right = tree_remove(node->right);

    return node;
}

struct node *tree_search(struct node *node, int key)
{
    struct node *a;

    if (node == NULL)
        return tree_insert(key);

    else if (node->key == key)
        return tree_remove(node);

    else if (key < node->key)
        node->left = tree_search(node->left, key);

    else if (key > node->key)
        node->right = tree_search(node->right, key);

    // para os valores anteriores nao se perderem.
    return node;
}

void tree_inorder(struct node *node)
{
    if (node != NULL) {
        tree_inorder(node->left);
        printf("%d ", node->key);
        tree_inorder(node->right);
    }
}

void tree_preorder(struct node *node)
{
    if (node != NULL) {
        printf("%d ", node->key);
        tree_preorder(node->left);
        tree_preorder(node->right);
    }
}

void tree_postorder(struct node *node)
{
    if (node != NULL) {
        tree_postorder(node->left);
        tree_postorder(node->right);
        printf("%d ", node->key);
    }
}

struct node *tree_load()
{
    struct node *tree;
    int value, to_remove;
    tree = tree_init();

    scanf("%d", &value);
    if (value >= 0)
        tree = tree_search(tree, value);

    while(value >= 0) {
        scanf("%d", &value);
        if (value >= 0)
            tree_search(tree, value);
    }

    scanf("%d", &to_remove);
    tree_search(tree, to_remove);

    return tree;
}

int main()
{
    struct node *tree;
    tree = tree_load();

    tree_preorder(tree);
    printf("\n");
    tree_inorder(tree);
    printf("\n");
    tree_postorder(tree);

    tree_free(tree);
    return 0;
}
