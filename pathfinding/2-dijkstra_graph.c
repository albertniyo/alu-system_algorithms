#include "pathfinding.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/**
 * reconstruct_path - helper func to reconstruct the shortest path
 *                    queue from path pointers
 * @target: pointer to target vertex
 * @start: pointer to start vertex
 * @vertices: arr of vertex pointers matching indices
 * @parent: arr of parent indices
 * @path: path queue
 */
static void reconstruct_path(vertex_t const *target, vertex_t const *start,
			     vertex_t **vertices, int *parent, queue_t *path)
{
	int curr_idx = target->index;

	while (curr_idx != -1)
	{
		queue_push_front(path, strdup(vertices[curr_idx]->content));
		if (curr_idx == (int)start->index)
			break;
		curr_idx = parent[curr_idx];
	}
}

/**
 * find_min - finds the unvisited vertex with the minimum distance
 * @nb_vertices: tot nber of vertices
 * @dist: arr of shortest known distances
 * @visited: arr of visited flags
 *
 * Return: idx of the min distance vertex, or -1 if none found
 */
static int find_min(size_t nb_vertices, int *dist, int *visited)
{
	int min_dist = INT_MAX;
	int u_idx = -1;
	size_t i;

	for (i = 0; i < nb_vertices; i++)
	{
		if (!visited[i] && dist[i] < min_dist)
		{
			min_dist = dist[i];
			u_idx = (int)i;
		}
	}
	return (u_idx);
}

/**
 * update_distances - updates the distances of adjacent vertices
 * @u_idx: current vertex index
 * @vertices: arr of vertex pointers
 * @dist: arr of shortest known distances
 * @parent: arr of parent indices
 * @visited: arr of visited flags
 */
static void update_distances(int u_idx, vertex_t **vertices, int *dist,
			     int *parent, int *visited)
{
	edge_t *edge;
	int v_idx;

	for (edge = vertices[u_idx]->edges; edge; edge = edge->next)
	{
		v_idx = edge->dest->index;
		if (!visited[v_idx] && dist[u_idx] + edge->weight < dist[v_idx])
		{
			dist[v_idx] = dist[u_idx] + edge->weight;
			parent[v_idx] = u_idx;
		}
	}
}

/**
 * dijkstra_graph - finds the shortest path using Dijkstra's algorithm
 * @graph: pointer to the graph
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 *
 * Return: pointer to queue forming the shortest path, or NULL on failure
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target)
{
	queue_t *path;
	int *dist, *parent, *visited, u_idx;
	size_t i;
	vertex_t *v, **vertices;

	if (!graph || !start || !target)
		return (NULL);
	dist = malloc(graph->nb_vertices * sizeof(int));
	parent = malloc(graph->nb_vertices * sizeof(int));
	visited = calloc(graph->nb_vertices, sizeof(int));
	vertices = malloc(graph->nb_vertices * sizeof(vertex_t *));
	for (v = graph->vertices, i = 0; v; v = v->next, i++)
	{
		dist[i] = INT_MAX;
		parent[i] = -1;
		vertices[i] = v;
	}
	dist[start->index] = 0;
	while ((u_idx = find_min(graph->nb_vertices, dist, visited)) != -1)
	{
		visited[u_idx] = 1;
		printf("Checking %s, distance from %s is %d\n",
		       vertices[u_idx]->content, start->content, dist[u_idx]);
		if (vertices[u_idx] == target)
			break;
		update_distances(u_idx, vertices, dist, parent, visited);
	}
	path = queue_create();
	if (path && dist[target->index] != INT_MAX)
		reconstruct_path(target, start, vertices, parent, path);
	else if (path)
	{
		free(path);
		path = NULL;
	}
	free(dist);
	free(parent);
	free(visited);
	free(vertices);
	return (path);
}
