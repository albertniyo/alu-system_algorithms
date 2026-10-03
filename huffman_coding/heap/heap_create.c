#include "heap.h"

/**
 * heap_create - creates a Heap data structure
 * @data_cmp: pointer to a comparison function
 *
 * Return: pointer to the created heap_t structure, or NULL if it fails
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap;

	if (!data_cmp)
		return (NULL);

	heap = malloc(sizeof(*heap));
	if (!heap)
		return (NULL);

	heap->size = 0;
	heap->data_cmp = data_cmp;
	heap->root = NULL;

	return (heap);
}
