/*
    nome: Clévio Orlando de Oliveira Junior
    RA: 120734
    turma: IB
    algoritmo: insert sort
*/

#include <stdlib.h>
#include <stdio.h>

void read_array(int *array, int size)
{
    int i;

    for (i = 0; i < size; i++)
        scanf("%d", &array[i]);
}

void print_array(int *array, int size)
{
    int i;
    printf("%d", array[0]);
    for (i = 1; i < size; i++)
        printf(" %d", array[i]);
}

void insert_sort(int *array, int size)
{
    int tmp, i, j;

    for (i = 1; i < size; i++) {
        tmp = array[i];
        j = i;
        while(j > 0 && tmp < array[j - 1]) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = tmp;
        
        print_array(array, size);
        printf("\n");
    }
}

int main()
{
    int size, *array;
    scanf("%d", &size);

    array = malloc(size * sizeof(int));
    read_array(array, size);

    insert_sort(array, size);
    free(array);
    return 0;
}
