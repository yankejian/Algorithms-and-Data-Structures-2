/*
*    nome: Clévio Orlando de Oliveira Junior
*    RA: 120734
*    turma: IB
*    algoritmo: heap sort
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

int find_max(int *array, int size, int pos)
{
    // Note que aqui trabalhamos apenas com indices
    int next_right, next_left, max;

    max = pos;
    next_left = 2 * pos + 1;
    next_right = 2 * pos + 2;
    
    if (next_left < size && array[next_left] > array[max])
        max = next_left;
    if (next_right < size && array[next_right] > array[max])
        max = next_right;

    return max;
}


void build_heap(int *array, int size, int pos)
{
    int max;
    max = find_max(array, size, pos);

    if (max != pos) {
        swap(array, pos, max);
        build_heap(array, size, max);
    }

}

void rearrange_heap(int *array, int size)
{
    int i;

    for (i = size / 2 - 1; i >= 0; i--)
        build_heap(array, size, i);
}

void heap_sort(int *array, int size)
{
    int i;

    print_array(array, size);
    build_heap(array, size, 0);
    rearrange_heap(array, size);
    print_array(array, size);

    for (i = size - 1; i > 0; i--) {
        swap(array, 0, i);
        build_heap(array, i, 0);
        
        print_array(array, size);
    }
}

int main()
{
    int size, *array;
    scanf("%d", &size);
    
    array = malloc(size * sizeof(int));
    read_array(array, size);

    heap_sort(array, size);
    free(array);
    return 0;
}