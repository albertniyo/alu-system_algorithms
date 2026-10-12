#include "huffman.h"

/**
 * huffman_extract_and_insert - extracts two lowest nodes and inserts their sum
 * @priority_queue: pointer to the min-heap representing the priority queue
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *parent_node;
	symbol_t *symbol1, *symbol2, *new_symbol;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	node1 = (binary_tree_node_t *)heap_extract(priority_queue);
	node2 = (binary_tree_node_t *)heap_extract(priority_queue);
	if (!node1 || !node2)
		return (0);

	symbol1 = (symbol_t *)node1->data;
	symbol2 = (symbol_t *)node2->data;

	new_symbol = symbol_create(-1, symbol1->freq + symbol2->freq);
	if (!new_symbol)
		return (0);

	parent_node = binary_tree_node(NULL, new_symbol);
	if (!parent_node)
	{
		free(new_symbol);
		return (0);
	}

	parent_node->left = node1;
	parent_node->right = node2;
	node1->parent = parent_node;
	node2->parent = parent_node;

	if (heap_insert(priority_queue, parent_node) == NULL)
	{
		free(new_symbol);
		free(parent_node);
		return (0);
	}

	return (1);
}
