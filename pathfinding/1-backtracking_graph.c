#include "pathfinding.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * backtrack_g - helper func to perform recursive graph backtracking
 * @curr: pointer to the curr vertex
 * @target: Pointer to the target vertex
 * @visited: arr of strings tracking visited vertex names
 * @visit_count: pointer to the current number of visited vertices
 * @path: queue storing the path of vertex names
 *
 * Return: 1 if path to target found, 0 otherwise
 */
int backtrack_g(vertex_t const *curr, vertex_t const *target,
		const char **visited, int *visit_count, queue_t *path)
{
	int i;
	edge_t *edge;

	if (!curr)
		return (0);

	for (i = 0; i < *visit_count; i++)
	{
		if (strcmp(visited[i], curr->content) == 0)
			return (0);
	}

	printf("checking %s\n", curr->content);
	visited[(*visit_count)++] = curr->content;

	if (strcmp(curr->content, target->content) == 0)
	{
		queue_push_front(path, strdup(curr->content));
		return (1);
	}

	for (edge = curr->edges; edge; edge = edge->next)
	{
		if (backtrack_g(edge->dest, target, visited, visit_count, path))
		{
			queue_push_front(path, strdup(curr->content));
			return (1);
		}
	}

	return (0);
}

/**
 * backtracking_graph - searches for the first path from a start vertex
 *                    to a target vertex in a graph.
 * @graph: pointer to the graph to process
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 *
 * Return: pointer to a queue containing the path names, or NULL on failure
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			   vertex_t const *target)
{
	queue_t *path;
	const char **visited;
	int visit_count = 0;

	if (!graph || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = calloc(graph->nb_vertices, sizeof(char *));
	if (!visited)
	{
		free(path);
		return (NULL);
	}

	if (!backtrack_g(start, target, visited, &visit_count, path))
	{
		free(visited);
		free(path);
		return (NULL);
	}

	free(visited);
	return (path);
}
