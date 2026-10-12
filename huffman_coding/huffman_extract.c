#include "huffman.h"

/**
 * huffman_extract - extracts the root node from priority queue
 * @heap: pointer to the heap struct used as the priority queue
 *
 * Return: pointer to the extracted btree node,
 *         or NULL on failure
 */
binary_tree_node_t *huffman_extract(heap_t *heap)
{
	binary_tree_node_t *extracted_node;

	if (heap == NULL || heap->root == NULL || heap->size == 0)
		return (NULL);

	extracted_node = (binary_tree_node_t *)heap_extract(heap);

	return (extracted_node);
}
