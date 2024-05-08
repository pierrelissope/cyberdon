/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** sprite_sorting
*/

#include "entity.h"

static void swap(linked_objects_t **array, int i, int j)
{
    linked_objects_t *temp = array[i];

    array[i] = array[j];
    array[j] = temp;
}

static int partition(linked_objects_t **array, int low, int high)
{
    float pivot = array[high]->bounds.top;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (array[j]->bounds.top == pivot && array[j]->priority) {
            continue;
        }
        if (array[j]->bounds.top <= pivot) {
            i++;
            swap(array, i, j);
            continue;
        }
    }
    swap(array, i + 1, high);
    return (i + 1);
}

void quicksort(linked_objects_t **array, int low, int high)
{
    int pi = 0;

    if (low < high) {
        pi = partition(array, low, high);
        quicksort(array, low, pi - 1);
        quicksort(array, pi + 1, high);
    }
}
