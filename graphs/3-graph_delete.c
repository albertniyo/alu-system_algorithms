#include "graphs.h"

/**
 * graph_delete - deallocates and frees entire graph struct
 * @graph: pointer to the graph structure to delete
 */
void graph_delete(graph_t *graph)
{
	vertex_t *curr_vertex, *next_vertex;
	edge_t *curr_edge, *next_edge;

	if (!graph)
		return;

	curr_vertex = graph->vertices;
	while (curr_vertex)
	{
		next_vertex = curr_vertex->next;

		curr_edge = curr_vertex->edges;
		while (curr_edge)
		{
			next_edge = curr_edge->next;
			free(curr_edge);
			curr_edge = next_edge;
		}

		if (curr_vertex->content)
			free(curr_vertex->content);

		free(curr_vertex);
		curr_vertex = next_vertex;
	}

	free(graph);
}
