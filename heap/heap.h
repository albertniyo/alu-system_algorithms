#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdlib.h>

/**
 * struct binary_tree_node_s - binary tree node data structure
 *
 * @data: data stored in a node
 * @left: pointer to the left child
 * @right: pointer to the right child
 * @parent: pointer to the parent node
 */
typedef struct binary_tree_node_s
{
	void *data;
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	struct binary_tree_node_s *parent;
} bts;

/**
 * struct heap_s - heap data structure
 *
 * @size: size of the heap (number of nodes)
 * @data_cmp: function to compare two nodes data
 * @root: pointer to the root node of the heap
 */
typedef struct heap_s
{
	size_t size;
	int (*data_cmp)(void *, void *);
	bts *root;
} heap_t;

heap_t *heap_create(int (*data_cmp)(void *, void *));
bts *binary_tree_node(bts *parent, void *data);
bts *heap_insert(heap_t *heap, void *data);

#endif
