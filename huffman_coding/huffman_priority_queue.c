#include "heap/heap.h"
#include "huffman.h"

/**
 * get_height - calculates height of a nested btree node
 * @node: pointer to nested tree node
 *
 * Return: height of node or 0 if NULL
 */
static int get_height(binary_tree_node_t *node)
{
	int left_h, right_h;

	if (node == NULL)
		return (0);

	left_h = get_height(node->left);
	right_h = get_height(node->right);

	return ((left_h > right_h ? left_h : right_h) + 1);
}

/**
 * p_queue_cmp - comparison function for the priority queue items
 * @p1: pointer to the first generic element (a binary tree node wrapper)
 * @p2: pointer to the second generic element (a binary tree node wrapper)
 *
 * Return: difference between the character frequencies (p1 - p2)
 */
static int p_queue_cmp(void *p1, void *p2)
{
	binary_tree_node_t *nested1, *nested2;
	symbol_t *symbol1, *symbol2;
	int h1, h2;

	if (p1 == NULL || p2 == NULL)
		return (0);

	nested1 = (binary_tree_node_t *)p1;
	nested2 = (binary_tree_node_t *)p2;

	symbol1 = (symbol_t *)nested1->data;
	symbol2 = (symbol_t *)nested2->data;

	if (symbol1->freq != symbol2->freq)
		return ((int)(symbol1->freq - symbol2->freq));

	h1 = get_height(nested1);
	h2 = get_height(nested2);
	if (h1 != h2)
		return (h1 - h2);

	if (symbol1->data != symbol2->data)
		return ((int)(symbol1->data - symbol2->data));

	return (0);
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
