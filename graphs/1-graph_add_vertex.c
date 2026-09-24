#include "graphs.h"

/**
 * graph_add_vertex - adds vertex to an existing graph
 * @graph: pointer to the graph to add the vertex to
 * @str: string to store in the new vertex
 *
 * Return: pointer to created vertex, or NULL on failure.
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex, *curr;

	if (!graph || !str)
		return (NULL);

	curr = graph->vertices;

	while (curr)
	{
		if (strcmp(curr->content, str) == 0)
			return (NULL);
		if (!curr->next)
			break;
		curr = curr->next;
	}

	new_vertex = malloc(sizeof(vertex_t));
	if (!new_vertex)
		return (NULL);

	new_vertex->content = strdup(str);
	if (!new_vertex->content)
	{
		free(new_vertex);
		return (NULL);
	}

	new_vertex->index = graph->nb_vertices++;
	new_vertex->nb_edges = 0;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	if (!curr)
		graph->vertices = new_vertex;
	else
		curr->next = new_vertex;

	return (new_vertex);
}

