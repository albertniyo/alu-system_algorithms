#include "graphs.h"

/**
 * find_vertex - finds vertex by its content str
 * @graph: pointer to the graph
 * @str: str identifying the vertex
 *
 * Return: pointer to the vertex, or NULL
 */
static vertex_t *find_vertex(graph_t *graph, const char *str)
{
	vertex_t *curr = graph->vertices;

	while (curr)
	{
		if (strcmp(curr->content, str) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/**
 * connect_edge - helper func to attach single directional edge node
 * @src: pointer to source vertex
 * @dest: pointer to destination vertex
 *
 * Return: 1 on success, 0 on failure
 */
static int connect_edge(vertex_t *src, vertex_t *dest)
{
	edge_t *new_edge, *curr;

	new_edge = malloc(sizeof(edge_t));
	if (!new_edge)
		return (0);

	new_edge->dest = dest;
	new_edge->next = NULL;

	if (!src->edges)
	{
		src->edges = new_edge;
	}
	else
	{
		curr = src->edges;
		while (curr->next)
			curr = curr->next;
		curr->next = new_edge;
	}

	src->nb_edges++;
	return (1);
}

/**
 * graph_add_edge - adds edge between two vertices to an existing graph
 * @graph: Pointer to the graph to add the edge to
 * @src: str identifying vertex to make the connection from
 * @dest: str identifying vertex to connect to
 * @type: type of edge
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
		   edge_type_t type)
{
	vertex_t *v_src, *v_dest;
	edge_t *edge, *prev;

	if (!graph || !src || !dest)
		return (0);

	v_src = find_vertex(graph, src);
	v_dest = find_vertex(graph, dest);

	if (!v_src || !v_dest)
		return (0);

	if (!connect_edge(v_src, v_dest))
		return (0);

	if (type == BIDIRECTIONAL && !connect_edge(v_dest, v_src))
	{
		edge = v_src->edges;
		prev = NULL;
		while (edge->next)
		{
			prev = edge;
			edge = edge->next;
		}
		if (!prev)
			v_src->edges = NULL;
		else
			prev->next = NULL;
		free(edge);
		v_src->nb_edges--;
		return (0);
	}

	return (1);
}
