#include "heap.h"

/**
 * binary_tree_node - creates a generic Binary Tree node
 * @parent: pointer to the parent node of the node to be created
 * @data: data to be stored in the node
 *
 * Return: pointer to the created node or NULL if it fails
 */
bts *binary_tree_node(bts *parent, void *data)
{
	bts *node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);

	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;

	return (node);
}
