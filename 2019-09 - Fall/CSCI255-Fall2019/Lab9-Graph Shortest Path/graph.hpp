/* graph.hpp (Graph.h)
 * -------------------
 * Authors: Darwin Jacob Groskleg, Man Lin
 */
#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <deque>

#ifndef MAX_NODES
#define MAX_NODES 100
#endif

//modify from Turner's Weighted_Graph_demo
class Weighted_Graph
{
  public:
    Weighted_Graph(int node_count);

    //add an edge to the graph
    void Add_Edge(const int Node_1, const int Node_2, int edge_weight);

    // Print the ajacency matrix to stdout
    void Display() const;

    //find the best path from start to dest
    auto Best_Path(const int Start, const int Dest, bool verbose=false) const
        -> std::deque<int>;

    // Prints the shortest path between two nodes to stderr/console
    void Show_Best_Path(int Start, int Dest) const;

  private:
    int number_of_nodes; //the number of vertexes in the graph
    // The Node ID 0 is not used.  The first real node has ID 1
    int weight[MAX_NODES+1][MAX_NODES+1];   //store the weight of the edges

    bool validVertex(int node) const;
};

#endif // GRAPH_HPP_INCLUDED
