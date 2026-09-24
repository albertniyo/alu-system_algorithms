#include "graphs.h"

int main(void) {

    graph_t *graph;
    graph = graph_create();

    if (!graph){
        fprintf(stderr," Failed to create the graph");
        return (EXIT_FAILURE);
    }

    if (!graph_add_vertex(graph, "Santo Domingo")){
        fprintf(stderr," Failed to create vertex");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    if (!graph_add_vertex(graph, "Seattle") ||
	    !graph_add_vertex(graph, "New York") ||
	    !graph_add_vertex(graph, "Miami") ||
	    !graph_add_vertex(graph, "Chicago") ||
	    !graph_add_vertex(graph, "Houston") ||
	    !graph_add_vertex(graph, "Las Vegas") ||
	    !graph_add_vertex(graph, "Boston"))
	{
		fprintf(stderr, "Failed to add vertex\n");
		return (EXIT_FAILURE);
	}

	graph_display(graph);

	if (!graph_add_vertex(graph, "San Francisco"))
		fprintf(stderr, "Failed to add San Francisco\n");

	return (EXIT_SUCCESS);
}
