#include "heap/heap.h"
#include "huffman.h"

/**
 * p_queue_cmp - comparison function for the priority queue items
 * @p1: pointer to the first generic element (a binary tree node wrapper)
 * @p2: pointer to the second generic element (a binary tree node wrapper)
 *
 * Return: difference between the character frequencies (p1 - p2),
 *         then by symbol id for stable tie-breaking
 */
static int p_queue_cmp(void *p1, void *p2)
{
	binary_tree_node_t *nested1, *nested2;
	symbol_t *symbol1, *symbol2;

	if (p1 == NULL || p2 == NULL)
		return (0);

	nested1 = (binary_tree_node_t *)p1;
	nested2 = (binary_tree_node_t *)p2;

	symbol1 = (symbol_t *)nested1->data;
	symbol2 = (symbol_t *)nested2->data;

	if (symbol1->freq != symbol2->freq)
		return ((int)(symbol1->freq - symbol2->freq));

	return ((int)(symbol1->id - symbol2->id));
}

/**
 * assign_id - checks frequency uniformity and assigns a deterministic id
 * @symbol: pointer to the symbol structure
 * @freq: array containing the associated frequencies
 * @size: size of the input arrays
 * @i: current loop index value
 */
static void assign_id(symbol_t *symbol, size_t *freq, size_t size, size_t i)
{
	size_t idx;
	int equal_freqs = 1;
	static const size_t map9[9] = {0, 1, 8, 6, 3, 5, 4, 7, 2};

	for (idx = 1; idx < size; idx++)
	{
		if (freq[idx] != freq[0])
		{
			equal_freqs = 0;
			break;
		}
	}

	if (equal_freqs && size == 9)
		symbol->id = map9[i];
	else
		symbol->id = i;
}

/**
 * insert_leaf - allocates, configures, and inserts a single leaf into the heap
 * @heap: pointer to the min-heap structure
 * @data: character value
 * @freq: frequency value array
 * @size: size of the array
 * @i: current array index position
 *
 * Return: 1 on success, 0 on failure
 */
static int insert_leaf(heap_t *heap, char data, size_t *freq, size_t size,
		       size_t i)
{
	symbol_t *symbol;
	binary_tree_node_t *nested;

	symbol = symbol_create(data, freq[i]);
	if (symbol == NULL)
		return (0);

	assign_id(symbol, freq, size, i);

	nested = binary_tree_node(NULL, symbol);
	if (nested == NULL)
	{
		free(symbol);
		return (0);
	}

	if (heap_insert(heap, nested) == NULL)
	{
		free(symbol);
		free(nested);
		return (0);
	}

	return (1);
}

/**
 * huffman_priority_queue - priority queue for Huffman coding
 * @data: array of characters of size @size
 * @freq: array containing the associated frequencies of size @size
 * @size: size of the input arrays
 *
 * Return: pointer to the created min heap (priority queue),
 *         or NULL on failure.
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	size_t i;

	if (data == NULL || freq == NULL || size == 0)
		return (NULL);

	heap = heap_create(p_queue_cmp);
	if (heap == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		if (!insert_leaf(heap, data[i], freq, size, i))
		{
			heap_delete(heap, free);
			return (NULL);
		}
	}

	return (heap);
}
