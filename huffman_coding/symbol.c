#include "heap/heap.h"
#include "huffman.h"

/**
 * symbol_create - generic tree node containing a Huffman node
 * @data: char to be stored in the inner node structure
 * @freq: freq value associated with the character node
 *
 * Return: pointer to the newly allocated structural tree node,
 *         or NULL on failure.
 */
binary_tree_node_t *symbol_create(char data, size_t freq)
{
	binary_tree_node_t *tree_node;
	huffman_node_t *huff_payload;

	tree_node = malloc(sizeof(binary_tree_node_t));
	if (tree_node == NULL)
		return (NULL);

	huff_payload = malloc(sizeof(huffman_node_t));
	if (huff_payload == NULL)
	{
		free(tree_node);
		return (NULL);
	}

	huff_payload->data = data;
	huff_payload->freq = freq;

	tree_node->data = huff_payload;
	tree_node->left = NULL;
	tree_node->right = NULL;
	tree_node->parent = NULL;

	return (tree_node);
}
