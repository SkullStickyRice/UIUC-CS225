/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
	vector<Edge> AllEdges = graph.getEdges();
	
	int EdgesSize = AllEdges.size();
	int shortest = AllEdges[0].weight;
	int theEdge = 0;
	
	for (int i = 1; i < EdgesSize; i++) {
		if (AllEdges[i].weight < shortest) {
			shortest = AllEdges[i].weight;
			theEdge = i;
		}
	}	

	Vertex start = AllEdges[theEdge].source;
	Vertex end = AllEdges[theEdge].dest;
	
	graph.setEdgeLabel(start, end, "MIN");
	

    return shortest;


}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
	setUnexplored(graph);
	unordered_map<Vertex, Vertex> Vertmap;

	queue<Vertex> q;
	graph.setVertexLabel(start,"VISITED");
	q.push(start);

	while(!q.empty()) {
		Vertex v = q.front();
		vector<Vertex> adj = graph.getAdjacent(v);
		q.pop();
		for (int i = 0 ; i<adj.size(); i++) {
			Vertex w = adj[i];
			if (graph.getVertexLabel(w).compare("UNEXPLORED") == 0) {
				Vertmap[w] = v;
				graph.setEdgeLabel(v,w,"DISCOVERY");
				graph.setVertexLabel(w,"VISITED");
				q.push(w);
			}
			else if(graph.getEdgeLabel(v,w).compare("UNEXPLORED") == 0) {
				graph.setEdgeLabel(v,w,"CROSS");
			}
		}
	
       	}
	
	int count = 0;
	while(end != start) {
		graph.setEdgeLabel(end, Vertmap[end], "MINPATH");
		end = Vertmap[end];
		count++;
	}
	
    return count;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
	vector<Edge> Edgeslist = graph.getEdges();
	sort(Edgeslist.begin(), Edgeslist.end());

	DisjointSets vertices;

	vector<Vertex> Vertexlist = graph.getVertices();
	
	for (int i=0; i < Vertexlist.size(); i++) {
		vertices.addelements(Vertexlist[i]);
	}
	
	for (int i=0; i< Edgeslist.size();i++) {
		Vertex start = Edgeslist[i].source;
		Vertex end = Edgeslist[i].dest;
		if (vertices.find(start) != vertices.find(end)) {
			vertices.setunion(start, end);
			graph.setEdgeLabel(start,end,"MST");
		}
	}

}

void GraphTools::setUnexplored(Graph &graph) 
{
	queue<Vertex> q;

	Vertex start = graph.getStartingVertex();
	graph.setVertexLabel(start,"UNEXPLORED");
	
	q.push(start);
	
	while(!q.empty()) {
		Vertex v = q.front();
		vector<Vertex> adjacent = graph.getAdjacent(v);
		q.pop();
	
		for(int i = 0; i < adjacent.size(); i++) {
			Vertex w = adjacent[i];
			if(graph.getVertexLabel(w).compare("UNEXPLORED") != 0) {
				graph.setEdgeLabel(v,w,"UNEXPLORED");
				graph.setVertexLabel(w,"UNEXPLORED");
				q.push(w);
			}
			else if (graph.getEdgeLabel(v,w).compare("UNEXPLORED") != 0) {
				graph.setEdgeLabel(v,w,"UNEXPLORED");
			}
		}
	}
	
	
}



