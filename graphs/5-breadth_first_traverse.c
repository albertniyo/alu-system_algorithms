#include "graphs.h"

/**
 * run_bfs - iterates through the queue to perform the BFS
 * @queue: array of vertex pointers acting as the queue
 * @depths: array of depths matching the vertices in the queue
 * @visited: tracking array for visited node indices
 * @action: callback func to execute on vertex search
 *
 * Return: max vertex depth level reached
 */
static size_t run_bfs(vertex_t **queue, size_t *depths, char *visited,
		      void (*action)(const vertex_t *v, size_t depth))
{
	size_t head = 0, tail = 1, max_depth = 0, curr_depth;
	vertex_t *curr_v;
	edge_t *edge;

	while (head < tail)
	{
		curr_v = queue[head];
		curr_depth = depths[head];
		head++;

		action(curr_v, curr_depth);
		if (curr_depth > max_depth)
			max_depth = curr_depth;

		edge = curr_v->edges;
		while (edge)
		{
			if (edge->dest && !visited[edge->dest->index])
			{
				visited[edge->dest->index] = 1;
				queue[tail] = edge->dest;
				depths[tail] = curr_depth + 1;
				tail++;
			}
			edge = edge->next;
		}
	}
	return (max_depth);
}

/**
 * breadth_first_traverse - traverses a graph using the BFS algorithm
 * @graph: pointer to the graph to traverse
 * @action: pointer to the function to invoke for each visited vertex
 *
 * Return: max vertex depth level reached, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *v, size_t depth))
{
	char *visited;
	vertex_t **queue;
	size_t *depths, max_depth;

	if (!graph || !action || !graph->vertices)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(char));
	queue = malloc(graph->nb_vertices * sizeof(vertex_t *));
	depths = malloc(graph->nb_vertices * sizeof(size_t));

	if (!visited || !queue || !depths)
	{
		free(visited);
		free(queue);
		free(depths);
		return (0);
	}

	queue[0] = graph->vertices;
	depths[0] = 0;
	visited[graph->vertices->index] = 1;

	max_depth = run_bfs(queue, depths, visited, action);

	free(visited);
	free(queue);
	free(depths);

	return (max_depth);
}
