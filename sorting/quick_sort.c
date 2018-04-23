/*
*    nome: Clévio Orlando de Oliveira Junior
*    RA: 120734
*    turma: IB
*    algoritmo: quick sort
*    observacao: entenda qs no codigo por Quick Sort,
*    esta foi a forma que achei adequada para organizar.
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
    printf("\n");
}

void swap(int *array, int pos1, int pos2)
{
    int tmp;

    tmp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = tmp;
}

int qs_partition(int *array, int left, int right)
{
    int pivot, i, j;
    pivot = array[right];
    i = left - 1;

    for (j = left; j < right; j++)
        if (array[j] <= pivot) {
            i++;
            swap(array, i, j);
        }

    i++;
    swap(array, i, right);
    return i;
}

void qs_sort(int *array, int left, int right, int size)
{
    int current;
    if (left < right) { // condicao de parada
        current = qs_partition(array, left, right);
        
        if (right != size - 1)
            print_array(array, size);

        qs_sort(array, left, current - 1, size);
        qs_sort(array, current + 1, right, size);
    } 
}

int main()
{
    int size, *array;
    scanf("%d", &size);
    
    array = malloc(size * sizeof(int));
    read_array(array, size);
    print_array(array, size);

    qs_sort(array, 0, size - 1, size);
    free(array);
    return 0;
}