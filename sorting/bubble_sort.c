/*
    nome: Clévio Orlando de Oliveira Junior
    RA: 120734
    turma: IB
    algoritmo: bubble sort
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

void bubble_sort(int *array, int size)
{
    int i, temp, j = size, sorted = 0;

    while (!sorted) {
        sorted = 1;

        for (i = 1; i < j; i++)
            if (array[i] < array[i - 1]) {
                temp = array[i];
                array[i] = array[i - 1];
                array[i - 1] = temp;

                sorted = 0;
            }

        j--;
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

    bubble_sort(array, size);
    free(array);
    return 0;
}
