#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

/**
 * free_huffman_tree - frees all allocated components of a Huffman tree
 * @root: pointer to the root of the Huffman tree struct
 */
void free_huffman_tree(binary_tree_node_t *root)
{
	if (!root)
		return;

	free_huffman_tree(root->left);
	free_huffman_tree(root->right);

	if (root->data)
		free(root->data);

	free(root);
}

/**
 * traverse_and_print - recursively walks a tree to track and print codes
 * @root: pointer to the current Huffman node traversal node
 * @buffer: char arr handling string generation metrics
 * @depth: current depth index within the generation tracking string
 */
void traverse_and_print(binary_tree_node_t *root, char *buffer, int depth)
{
	symbol_t *symbol;

	if (!root)
		return;

	symbol = (symbol_t *)root->data;

	/* If it is a leaf node, print its accumulated path code string */
	if (!root->left && !root->right)
	{
		buffer[depth] = '\0';
		printf("%c: %s\n", symbol->data, buffer);
		return;
	}

	/* Traversal downwards: 0 for Left, 1 for Right */
	if (root->left)
	{
		buffer[depth] = '0';
		traverse_and_print(root->left, buffer, depth + 1);
	}
	if (root->right)
	{
		buffer[depth] = '1';
		traverse_and_print(root->right, buffer, depth + 1);
	}
}

/**
 * huffman_codes - build Huffman tree and prints codes for each symbol
 * @data: arr of characters of size @size
 * @freq: arr containing the associated frequencies of size @size
 * @size: size of the input arrays
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char code_buffer[256];

	if (!data || !freq || size == 0)
		return (0);

	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	traverse_and_print(root, code_buffer, 0);

	free_huffman_tree(root);

	return (1);
}
