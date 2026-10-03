#include "heap.h"

/**
 * shift_up - restores min-heap property by bubbling up the node
 * @heap: pointer to heap
 * @node: pointer to newly inserted node
 */
void shift_up(heap_t *heap, binary_tree_node_t *node)
{
	void *temp;

	while (node->parent && heap->data_cmp(node->data, node->parent->data) < 0)
	{
		temp = node->data;
		node->data = node->parent->data;
		node->parent->data = temp;
		node = node->parent;
	}
}

/**
 * heap_insert - inserts a value in a Min Binary Heap
 * @heap: pointer to heap which has to be inserted
 * @data: pointer containing the data to store in the new node
 *
 * Return: pointer to the created node containing data, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node, *parent;
	size_t target_size, mask;

	if (!heap || !data)
		return (NULL);

	if (!heap->root)
	{
		node = binary_tree_node(NULL, data);
		if (!node)
			return (NULL);
		heap->root = node;
		heap->size = 1;
		return (node);
	}

	target_size = heap->size + 1;
	mask = 1;
	while (mask <= target_size)
		mask <<= 1;
	mask >>= 2;

	parent = heap->root;
	while (mask > 1)
	{
		if (target_size & mask)
			parent = parent->right;
		else
			parent = parent->left;
		mask >>= 1;
	}

	node = binary_tree_node(parent, data);
	if (!node)
		return (NULL);

	if (target_size & 1)
		parent->right = node;
	else
		parent->left = node;

	heap->size++;
	shift_up(heap, node);

	return (node);
}
