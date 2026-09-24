#include "graphs.h"

/**
 * bfs_explore - BFS traversal using an explicit queue
 * @graph: pointer to the graph
 * @visited: tracking array for visited node indices
 * @action: callback func to execute on vertex search
 */
static void bfs_explore(const graph_t *graph, char *visited,
			void (*action)(const vertex_t *v, size_t depth))
{
	vertex_t **queue;
	size_t *depths;
	size_t head = 0, tail = 0;
	vertex_t *curr;
	edge_t *edge;

	queue = malloc(graph->nb_vertices * sizeof(vertex_t *));
	depths = malloc(graph->nb_vertices * sizeof(size_t));
	if (!queue || !depths)
	{
		free(queue), free(depths);
		return;
	}
	/* enqueue root node */
	queue[tail] = graph->vertices;
	depths[tail] = 0;
	visited[graph->vertices->index] = 1;
	tail++;
	while (head < tail)
	{
		curr = queue[head];
		action(curr, depths[head]);
		edge = curr->edges;
		while (edge)
		{
			if (edge->dest && !visited[edge->dest->index])
			{
				visited[edge->dest->index] = 1;
				queue[tail] = edge->dest;
				depths[tail] = depths[head] + 1;
				tail++;
			}
			edge = edge->next;
		}
		head++;
	}
	free(queue);
	free(depths);
}

/**
 * graph_traverse_bfs - traverses a graph using BFS
 * @graph: pointer to the graph to walk
 * @action: pointer to the func invoked when matching a vertex
 *
 * Return: max depth reached during search, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
			  void (*action)(const vertex_t *v, size_t depth))

{
	char *visited;

	if (!graph || !action || !graph->vertices)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(char));
	if (!visited)
		return (0);

	bfs_explore(graph, visited, action);

	free(visited);
	return (graph->nb_vertices - 1);
}
