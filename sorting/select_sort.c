/*
    nome: Clévio Orlando de Oliveira Junior
    RA: 120734
    turma: IB
    algoritmo: select sort
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

void select_sort(int *array, int size)
{
    int i, j, tmp, index;

    for (i = 0; i < size - 1; i++) {
        for (j = i, index = i; j < size; j++)
            if (array[j] < array[index])
                index = j;

        tmp = array[i];
        array[i] = array[index];
        array[index] = tmp;

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

    select_sort(array, size);
    free(array);
    return 0;
}
