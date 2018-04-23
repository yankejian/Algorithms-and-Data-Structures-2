/*
*    nome: Clévio Orlando de Oliveira Junior
*    RA: 120734
*    turma: IB
*    algoritmo: counting sort
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

int get_max(int *array, int size)
{
    int i, max;

    max = array[0];
    for (i = 1; i < size; i++)
        if (array[i] > max)
            max = array[i];

    return max;
}

int* get_occurrences(int *array, int size, int max)
{
    int *occurrences, i;

    occurrences = calloc(max, sizeof(int));
    for (i = 0; i < size; i++)
        occurrences[array[i]]++;
    
    return occurrences;
}

void sum_occurrences(int *array, int size)
{
    int i;

    for (i = 1; i < size; i++)
        array[i] += array[i - 1];
}

void counting_sort(int *array, int size)
{
    int max, *occurrences, *new_array, *tmp, i;

    max = get_max(array, size);
    occurrences = get_occurrences(array, size, max);
    new_array = malloc(size * sizeof(int));

    sum_occurrences(occurrences, max);
    for (i = 0; i < size; i++) {
        new_array[occurrences[array[i] - 1]--] = array[i]; 
        print_array(new_array, size);
    }
    
    tmp = array;
    array = new_array;

    free(tmp);
    free(new_array);
    free(occurrences);
}

int main()
{
    int size, *array;
    scanf("%d", &size);
    
    array = malloc(size * sizeof(int));
    read_array(array, size);
    print_array(array, size);

    counting_sort(array, size);
    free(array);
    return 0;
}