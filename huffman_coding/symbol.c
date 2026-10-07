#include "heap/heap.h"
#include "huffman.h"

/**
 * huffman_data_cmp - compares the frequency metrics of two Huffman tree nodes
 * @p1: pointer to first generic binary tree node
 * @p2: pointer to second generic binary tree node
 *
 * Return: difference between the frequency counts (p1 - p2)
 */
int huffman_data_cmp(void *p1, void *p2)
{
	binary_tree_node_t *node1;
	binary_tree_node_t *node2;
	huffman_node_t *huff1;
	huffman_node_t *huff2;

	if (p1 == NULL || p2 == NULL)
		return (0);

	node1 = (binary_tree_node_t *)p1;
	node2 = (binary_tree_node_t *)p2;

	huff1 = (huffman_node_t *)node1->data;
	huff2 = (huffman_node_t *)node2->data;

	return (huff1->freq - huff2->freq);
}

/**
 * free_huffman_node - custom destructor function to free a nested Huffman node
 * @p: pointer to the generic binary tree node to be completely cleared
 */
void free_huffman_node(void *p)
{
	binary_tree_node_t *node;

	if (p == NULL)
		return;

	node = (binary_tree_node_t *)p;

	if (node->data != NULL)
	{
		free(node->data);
	}

	free(node);
}
