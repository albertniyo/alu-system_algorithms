#include "graphs.h"

/**
 * dfs_explore - recursively processes and discovers vertex graph node path
 * @v: pointer to current vertex being evaluated
 * @visited: array tracking already discovered vertex indices
 * @action: pointer to the callback func executed on the search
 * @depth: depth level of the current traversal call
 */
static void dfs_explore(vertex_t *v, char *visited,
			void (*action)(const vertex_t *v, size_t depth),
			size_t depth)
{
	edge_t *edge;

	if (!v || visited[v->index])
		return;

	/* node as visited and hit the callback */
	visited[v->index] = 1;
	action(v, depth);

	/* deep into every unvisited connected target vertex path */
	edge = v->edges;
	while (edge)
	{
		if (edge->dest && !visited[edge->dest->index])
			dfs_explore(edge->dest, visited, action, depth + 1);
		edge = edge->next;
	}
}

/**
 * graph_traverse_dfs - traverses graph using DFS
 * @graph: pointer to the graph to traverse
 * @action: pointer to the func invoked when matching vertex
 *
 * Return: max depth reached during search, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
			void (*action)(const vertex_t *v, size_t depth))
{
	char *visited;
	vertex_t *start_node;

	if (!graph || !action || !graph->vertices)
		return (0);

	/* Allocate an evaluation lookup array for cycle checking */
	visited = calloc(graph->nb_vertices, sizeof(char));
	if (!visited)
		return (0);

	start_node = graph->vertices;

	/* Begin DFS walk tracing depth steps from the head entry point */
	dfs_explore(start_node, visited, action, 0);

	free(visited);
	return (graph->nb_vertices - 1);
}
