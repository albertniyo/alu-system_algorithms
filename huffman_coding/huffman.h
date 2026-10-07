#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap/heap.h"

/**
 * struct symbol_s - stores a char and its associated frequency
 *
 * @data: character
 * @freq: associated frequency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

/**
 * struct huffman_node_s - Huffman node data structure
 *
 * @data: Character value (or 0 for internal combined nodes)
 * @freq: Frequency count of the character
 */
typedef struct huffman_node_s
{
	char data;
	size_t freq;
} huffman_node_t;

binary_tree_node_t *huffman_node_create(char data, size_t freq);


#endif
