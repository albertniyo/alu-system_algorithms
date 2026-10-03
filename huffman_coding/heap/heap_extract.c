#include "heap.h"

/**
 * get_node_at - finds a node at a specific heap index position
 * @root: pointer to root node of the heap
 * @idx: size index of the target node
 *
 * Return: pointer to the targeted node
 */
binary_tree_node_t *get_node_at(binary_tree_node_t *root, size_t idx)
{
	size_t mask;

	mask = 1;
	while (mask <= idx)
		mask <<= 1;
	mask >>= 2;

	while (mask > 0)
	{
		if (idx & mask)
			root = root->right;
		else
			root = root->left;
		mask >>= 1;
	}
	return (root);
}

/**
 * shift_down - restores min-heap property from root downward
 * @heap: pointer to heap structure
 * @node: pointer to the node being shifted down
 */
void shift_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *smallest;
	void *temp;

	while (node->left)
	{
		smallest = node->left;
		if (node->right && heap->data_cmp(node->right->data, smallest->data) < 0)
			smallest = node->right;

		if (heap->data_cmp(node->data, smallest->data) <= 0)
			break;

		temp = node->data;
		node->data = smallest->data;
		smallest->data = temp;
		node = smallest;
	}
}

/**
 * heap_extract - extracts the root value from a Min Binary Heap
 * @heap: pointer to the heap structure
 *
 * Return: pointer to data stored in the extracted node, or NULL if it fails
 */
void *heap_extract(heap_t *heap)
{
	void *data;
	binary_tree_node_t *last_node, *parent;

	if (!heap || !heap->root || heap->size == 0)
		return (NULL);

	data = heap->root->data;
	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (data);
	}

	last_node = get_node_at(heap->root, heap->size);
	heap->root->data = last_node->data;
	parent = last_node->parent;

	if (parent->left == last_node)
		parent->left = NULL;
	else
		parent->right = NULL;

	free(last_node);
	heap->size--;
	shift_down(heap, heap->root);

	return (data);
}
