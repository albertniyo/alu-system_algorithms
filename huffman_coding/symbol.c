#include "huffman.h"

/**
 * symbol_create - generic tree node containing a Huffman node
 * @data: char to be stored in the inner node structure
 * @freq: freq value associated with the character node
 *
 * Return: pointer to the newly allocated huffman_node_t struct,
 *         or NULL on failure.
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol;

	/* Allocate memory for the symbol structure directly */
	symbol = malloc(sizeof(symbol_t));
	if (symbol == NULL)
		return (NULL);

	/* Assign internal metrics */
	symbol->data = data;
	symbol->freq = freq;

	return (symbol);
}
