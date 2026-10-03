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

#endif
