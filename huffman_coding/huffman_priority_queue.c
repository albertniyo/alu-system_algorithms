#include "heap/heap.h"
#include "huffman.h"

/**
 * p_queue_cmp - comparison function for the priority queue items
 * @p1: pointer to the first generic element (a binary tree node wrapper)
 * @p2: pointer to the second generic element (a binary tree node wrapper)
 *
 * Return: difference between the character frequencies (p1 - p2)
 */
static int p_queue_cmp(void *p1, void *p2)
{
	binary_tree_node_t *nested1;
	binary_tree_node_t *nested2;
	symbol_t *symbol1;
	symbol_t *symbol2;

	if (p1 == NULL || p2 == NULL)
		return (0);

	nested1 = (binary_tree_node_t *)p1;
	nested2 = (binary_tree_node_t *)p2;

	symbol1 = (symbol_t *)nested1->data;
	symbol2 = (symbol_t *)nested2->data;

	return ((int)(symbol1->freq - symbol2->freq));
}

/**
 * huffman_priority_queue - priority queue for Huffman coding
 * @data: array of characters of size @size
 * @freq: rray containing the associated frequencies of size @size
 * @size: size of the input arrays
 *
 * Return: pointer to the created min heap (priority queue),
 *         or NULL on failure.
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	symbol_t *symbol;
	binary_tree_node_t *nested;
	size_t i;

	if (data == NULL || freq == NULL || size == 0)
		return (NULL);

	heap = heap_create(p_queue_cmp);
	if (heap == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (symbol == NULL)
		{
			heap_delete(heap, free);
			return (NULL);
		}

		nested = binary_tree_node(NULL, symbol);
		if (nested == NULL)
		{
			free(symbol);
			heap_delete(heap, free);
			return (NULL);
		}

		if (heap_insert(heap, nested) == NULL)
		{
			free(symbol);
			free(nested);
			heap_delete(heap, free);
			return (NULL);
		}
	}

	return (heap);
}
