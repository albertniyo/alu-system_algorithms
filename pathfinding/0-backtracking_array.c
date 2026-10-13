#include "pathfinding.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * backtrack - helper func to perform recursive backtracking pathfinding
 * @map: pointer to the read-only two-dimensional array
 * @rows: tot number of rows in the map
 * @cols: tot number of columns in the map
 * @x: curr X coordinate
 * @y: curr Y coordinate
 * @target: pointer to the target point struct
 * @visited: 1D array representing the visited status of each map cell
 * @path: queue storing the final successful path nodes
 *
 * Return: 1 if a path to the target is found, 0 otherwise
 */
int backtrack(char **map, int rows, int cols, int x, int y,
	      point_t const *target, char *visited, queue_t *path)
{
	point_t *point;

	if (x < 0 || x >= cols || y < 0 || y >= rows)
		return (0);

	if (map[y][x] == '1' || visited[y * cols + x] == 1)
		return (0);

	printf("Checking coordinates [%d, %d]\n", x, y);
	visited[y * cols + x] = 1;

	if (x == target->x && y == target->y)
	{
		point = malloc(sizeof(point_t));
		if (!point)
			return (0);
		point->x = x;
		point->y = y;
		queue_push_front(path, point);
		return (1);
	}

	if (backtrack(map, rows, cols, x + 1, y, target, visited, path) ||
	    backtrack(map, rows, cols, x, y + 1, target, visited, path) ||
	    backtrack(map, rows, cols, x - 1, y, target, visited, path) ||
	    backtrack(map, rows, cols, x, y - 1, target, visited, path))
	{
		point = malloc(sizeof(point_t));
		if (!point)
			return (0);
		point->x = x;
		point->y = y;
		queue_push_front(path, point);
		return (1);
	}

	return (0);
}

/**
 * backtracking_array - searches for the first path from a starting point
 *                      to a target point within a two-dimensional array
 * @map: pointer to a read-only two-dimensional array
 * @rows: nber of rows of the map
 * @cols: nber of columns of the map
 * @start: stores the coordinates of the starting point
 * @target: stores the coordinates of the target point
 *
 * Return: pointer to a queue from start to target, or NULL on failure
 */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	queue_t *path;
	char *visited;

	if (!map || rows <= 0 || cols <= 0 || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = calloc(rows * cols, sizeof(char));
	if (!visited)
	{
		free(path);
		return (NULL);
	}

	if (!backtrack(map, rows, cols, start->x, start->y, target, visited, path))
	{
		free(visited);
		free(path);
		return (NULL);
	}

	free(visited);
	return (path);
}
