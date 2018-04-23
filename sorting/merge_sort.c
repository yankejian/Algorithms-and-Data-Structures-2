/*
*    nome: Clévio Orlando de Oliveira Junior
*    RA: 120734
*    turma: IB
*    algoritmo: merge sort
*    ms = merge sort
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

void copy_array(int *array_from, int *array_to, int from, int size)
{
    int i;
    
    for (i = 0; i < size; i++)
        array_to[i] = array_from[from + i];
}

void ms_merge(int *array, int left, int right, int half)
{
    int left_size, right_size, *left_temp, *right_temp;
    int i, j, k;

    left_size = (half - left) + 1;
    right_size = right - half;
    i = 0;
    j = 0;
    k = left;

    left_temp = malloc(left_size * sizeof(int));
    right_temp = malloc(right_size * sizeof(int));

    copy_array(array, left_temp, left, left_size);
    copy_array(array, right_temp, half + 1, right_size);

    while (i < left_size && j < right_size) {
        if (left_temp[i] < right_temp[j]) {
            array[k] = left_temp[i];
            i++;
        } else {
            array[k] = right_temp[j];
            j++;
        }

        k++;
    }

    while (i < left_size) {
        array[k] = left_temp[i];
        i++;
        k++;
    }

    while (j < right_size) {
        array[k] = right_temp[j];
        j++;
        k++;
    }

    free(left_temp);
    free(right_temp);
}

void ms_sort(int *array, int left, int right, int size)
{
    int half;

    if (left < right) {
        half = (left + right) / 2;

        ms_sort(array, left, half, size);
        ms_sort(array, half + 1, right, size);

        ms_merge(array, left, right, half);

        if (half != left && half != right)
            print_array(array, size);
    }
}

int main()
{
    int size, *array;
    scanf("%d", &size);
    
    array = malloc(size * sizeof(int));
    read_array(array, size);
    print_array(array, size);

    ms_sort(array, 0, size - 1, size);
    free(array);
    return 0;
}