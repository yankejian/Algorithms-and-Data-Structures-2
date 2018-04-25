/*
    * Nome: Clévio Orlando de Oliveira Junior
    * RA: 120.734
    * Turma: IB
    * Arvore: AVL

    * AVISO: A minha arvore de pesquisas binarias enviada no judge
    * está sem este cabeçalho, porém foi enviada no judge no prazo correto.
*/

#include <stdlib.h>
#include <stdio.h>

// estrutura criada para a arvore, que é um nó.
struct node {
    // arvore de pesquisa binaria
    int key;
    struct node *left;
    struct node *right;
    // arvore AVL
    int height;
};

// apenas uma função de utilidade para achar o maior entre 2 inteiros.
int max(int a, int b)
{
    return a > b ? a : b;
}

// inicializador, criador de nós, free
struct node *avl_init()
{
    return NULL;
}

struct node *avl_new(int key)
{
    struct node *new;
    new = malloc(sizeof(struct node));

    new->key = key;
    new->left = new->right = NULL;
    new->height = 0;
    return new;
}

void avl_free(struct node *node)
{
    if (node != NULL) {
        avl_free(node->left);
        avl_free(node->right);
        free(node);
    }
}

// getters da arvore
int avl_height(struct node *node)
{
    if (node == NULL)
        return -1;
    return node->height;
}

int avl_balance_factor(struct node *node)
{
    if (node == NULL)
        return 0;
    return avl_height(node->left) - avl_height(node->right); 
}

struct node *avl_smallest(struct node* node)
{
    struct node* current;
    current = node;
 
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

// funções de rotação e balanceamento
struct node *avl_left_rotate(struct node* a)
{
    struct node *b, *c;
    b = a->right;
    c = b->left;

    b->left = a;
    a->right = c;

    a->height = max(avl_height(a->left), avl_height(a->right)) + 1;
    b->height = max(avl_height(b->left), avl_height(b->right)) + 1;

    return b;
}

struct node *avl_right_rotate(struct node* b)
{
    struct node *a, *c;
    a = b->left;
    c = a->right;

    a->right = b;
    b->left = c;

    b->height = max(avl_height(b->left), avl_height(b->right)) + 1;
    a->height = max(avl_height(a->left), avl_height(a->right)) + 1;

    return a;
}

struct node *avl_balance(struct node* node)
{
    // vamos chamar balance factor de bf
    int node_bf, left_bf, right_bf;
    node_bf = avl_balance_factor(node);
    left_bf = avl_balance_factor(node->left);
    right_bf = avl_balance_factor(node->right);

    // LL
    if (node_bf > 1 && left_bf >= 0)
        return avl_right_rotate(node);
 
    // RR
    if (node_bf < -1 && right_bf <= 0)
        return avl_left_rotate(node);
 
    // LR
    if (node_bf > 1 && left_bf < 0) {
        node->left = avl_left_rotate(node->left);
        return avl_right_rotate(node);
    }
 
    // RL
    if (node_bf < -1 && right_bf > 0) {
        node->right = avl_right_rotate(node->right);
        return avl_left_rotate(node);
    }

    return node;
}

// pesquisa, inserção, remoção.
struct node *avl_search(struct node *node, int key)
{
    if (node == NULL || node->key == key)
        return node;

    if (node->key < key)
        return avl_search(node->right, key);

    return avl_search(node->left, key);
}

struct node *avl_insert(struct node *node, int key)
{
    int balance;

    if (node == NULL)
        return avl_new(key);
    if (key < node->key)
        node->left = avl_insert(node->left, key); 
    else if (key > node->key)
        node->right = avl_insert(node->right, key);
    else
        return node;
    
    node->height = max(avl_height(node->left), avl_height(node->right)) + 1;
    return avl_balance(node);
}

struct node *avl_delete(struct node *node, int key)
{
    if (node == NULL)
        return node;
    if (key < node->key)
        node->left = avl_delete(node->left, key); 
    else if (key > node->key)
        node->right = avl_delete(node->right, key);
    else {
        if (node->left == NULL || node->right == NULL) {
            struct node *tmp;
            tmp = node->left;
            if (tmp == NULL) tmp = node->right;

            // caso não tenha filhos
            if (tmp == NULL) {
                tmp = node;
                node = NULL;
            } else // caso tenha apenas um filho
                *node = *tmp;
            
            free(tmp);
        } else {
            struct node *tmp;
            tmp = avl_smallest(node->right);
            node->key = tmp->key;
            node->right = avl_delete(node->right, tmp->key);
        }
    }

    if (node == NULL)
        return node;

    node->height = max(avl_height(node->left), avl_height(node->right)) + 1;
    return avl_balance(node);
}

// apenas uma função para fatorar o main, e remover multiplas entradas da arvore.
void avl_delete_many(struct node **node, int **to_delete, int to_delete_size)
{
    int i;

    for (i = 0; i < to_delete_size; i++)
        *node = avl_delete(*node, (*to_delete)[i]);
}

// funções para carregamento de entrada e impressão.
int *avl_entries(int *size)
{
    int i, *entries, entries_size, value;
    i = 0;
    entries_size = 500;
    entries = malloc(entries_size * sizeof(int));

    scanf("%d", &value);
    if (value >= 0)
        entries[i++] = value;

    while(value >= 0) {
        if (i == entries_size) {
            entries_size += 500;
            entries = realloc(entries, entries_size * sizeof(int));
        }

        scanf("%d", &value);
        if (value >= 0)
            entries[i++] = value;
    }

    *size = i;
    return entries;
}

struct node *avl_load(int **to_delete, int *to_delete_size)
{
    struct node *avl;
    int size, *entries, i;
    avl = avl_init();

    entries = avl_entries(&size);
    if (size > 0)
        for (i = 0; i < size; i++)
            avl = avl_insert(avl, entries[i]);
    
    free(entries);
    *to_delete = avl_entries(to_delete_size);
    return avl;
}

void avl_preorder(struct node *node)
{
    if (node != NULL) {
        printf("%d ", node->key);
        avl_preorder(node->left);
        avl_preorder(node->right);
    }
}

int main() 
{
    struct node *avl;
    int *to_delete, to_delete_size;

    avl = avl_load(&to_delete, &to_delete_size);
    avl_preorder(avl);
    printf("\n%d\n", avl_height(avl));

    avl_delete_many(&avl, &to_delete, to_delete_size);
    avl_preorder(avl);
    printf("\n%d", avl_height(avl));

    avl_free(avl);
    free(to_delete);
    return 0;
}
