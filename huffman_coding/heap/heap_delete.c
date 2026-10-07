#include "heap.h"

/**
 * free_tree_nodes - recursively frees tree nodes using a post-order traversal
 * @node: pointer to the current binary tree node
 * @free_data: pointer to the function used to free the node data layer
 */
static void free_tree_nodes(binary_tree_node_t *node,
			    void (*free_data)(void *))
{
	if (node == NULL)
		return;

	free_tree_nodes(node->left, free_data);
	free_tree_nodes(node->right, free_data);

	if (free_data != NULL && node->data != NULL)
	{
		free_data(node->data);
	}

	free(node);
}

/**
 * heap_delete - deallocates a tree-structured Min Binary Heap
 * @heap: pointer to the heap structural tracking shell
 * @free_data: pointer to a callback function used to clear custom nested data
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (heap == NULL)
		return;

	free_tree_nodes(heap->root, free_data);

	free(heap);
}
