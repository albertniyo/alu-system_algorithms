#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap/heap.h"

/**
 * struct symbol_s - stores a char and its associated frequency
 *
 * @data: character
 * @freq: associated frequency
 * @id: unique auto-incremented insertion Id for sorting
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
	size_t id;
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

symbol_t *symbol_create(char data, size_t freq);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
int huffman_extract_and_insert(heap_t *priority_queue);
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);
int huffman_codes(char *data, size_t *freq, size_t size);

#endif
