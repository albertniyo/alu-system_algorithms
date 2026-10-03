#include "heap.h"

/**
 * shift_up - restores min-heap property by bubbling up the node
 * @heap: pointer to heap
 * @node: pointer to newly inserted node
 *
 * Return: pointer to the node's final position containing the data
 */
binary_tree_node_t *shift_up(heap_t *heap, binary_tree_node_t *node)
{
	void *temp;

	while (node->parent && heap->data_cmp(node->data, node->parent->data) < 0)
	{
		temp = node->data;
		node->data = node->parent->data;
		node->parent->data = temp;
		node = node->parent;
	}
	return (node);
}

/**
 * get_parent - navigates the binary tree to find the target parent node
 * @root: pointer to root node of the heap
 * @target_size: size index of the node to insert
 *
 * Return: pointer to the target parent node
 */
binary_tree_node_t *get_parent(binary_tree_node_t *root, size_t target_size)
{
	size_t mask;

	mask = 1;
	while (mask <= target_size)
		mask <<= 1;
	mask >>= 2;

	while (mask > 1)
	{
		if (target_size & mask)
			root = root->right;
		else
			root = root->left;
		mask >>= 1;
	}
	return (root);
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
	size_t target_size;

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
	parent = get_parent(heap->root, target_size);

	node = binary_tree_node(parent, data);
	if (!node)
		return (NULL);

	if (target_size & 1)
		parent->right = node;
	else
		parent->left = node;

	heap->size++;
	return (shift_up(heap, node));
}
