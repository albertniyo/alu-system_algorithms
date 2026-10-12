#include "huffman.h"

/**
 * huffman_tree - build Huffman tree
 * @data: arr of characters of size @size
 * @freq: arr containing the associated frequencies of size @size
 * @size: size of the input arrays
 *
 * Return: pointer to the root node of the Huffman tree, or NULL if it fails
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	binary_tree_node_t *huffman_root;

	if (!data || !freq || size == 0)
		return (NULL);

	priority_queue = huffman_priority_queue(data, freq, size);
	if (!priority_queue)
		return (NULL);

	while (priority_queue->size > 1)
	{
		if (!huffman_extract_and_insert(priority_queue))
		{
			heap_delete(priority_queue, free);
			return (NULL);
		}
	}

	huffman_root = (binary_tree_node_t *)priority_queue->root->data;

	free(priority_queue->root);
	free(priority_queue);

	return (huffman_root);
}
