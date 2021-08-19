/* graph.cpp
 * ---------
 * Authors: Darwin Jacob Groskleg
 *
 * IMPLEMENTATION of Weighted_Graph
 */
#include "graph.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>

#include <climits> // INT_MAX

using namespace std;

// parameterized constructor
    Weighted_Graph::
Weighted_Graph(int node_count) :
    number_of_nodes(node_count)
{
    if (node_count > MAX_NODES)
        throw "Fail to Construct: node_count exceeds MAX_NODES!";
}

//add an edge to the graph, update the vertex and edge structure
    void Weighted_Graph::
Add_Edge(const int Node_1, const int Node_2, int edge_weight)
{
    if (!validVertex(Node_1) || !validVertex(Node_2)) throw "Invalid node!";
    weight[Node_1][Node_2] = edge_weight;
}

//display the weight between the vertexes
    void Weighted_Graph::
Display() const
{
    cout << setw(4) << " ";
    for (int i = 1; i <= number_of_nodes; ++i) {
        cout << setw(4) << i << " ";
    }
    cout << '\n';

    for (int i = 1; i <= number_of_nodes; ++i) {
        cout << setw(4) << i;
        for (int j = 1; j <= number_of_nodes; ++j) {
            cout << setw(4) << weight[i][j] << " ";
        }
        cout << '\n';
    }
}

// Find Shortest path between Start and Dest
//  Approach: use Dijkstra's algorithm, greedy
    deque<int> Weighted_Graph::
Best_Path(const int Start_ID, const int Dest_ID, bool verbose) const
{
    deque<int> best_path; //a queue to store the best path
    if (!(validVertex(Start_ID) && validVertex(Dest_ID))) {
        cout << "Invalid start or destination\n";
        return best_path;  // empty deque
    }

    //an array storing the distance label for each vertex
    // distance from start node
    int distance[MAX_NODES+1];
    //an array storing the parent label for each vertex
    int parent[MAX_NODES+1];
    //a array indicating whether the vertex is already in the solved set
    bool is_solved[MAX_NODES+1];

    for (int i = 1; i <= MAX_NODES; ++i) {
        // if node i is connected to Start node
        if (weight[Start_ID][i] > 0) {
            distance[i] = weight[Start_ID][i];
            parent[i] = Start_ID;
        }
        else {
            distance[i] = INT_MAX;
            parent[i] = -1;
        }
        // want to initialize the array
        is_solved[i] = false;
    }

    // HELPER LAMBDAS FOR LOGGED OPERATIONS
    auto addToSolved = [&] (int node) {
        // Operation 1
        is_solved[node] = true;
        if (verbose) {
            clog << "Adding node " << node << " to the solved set S={";
            // Operation 2: show solved set S
            //  nodes are false if not solved
            for (int x=1; x<=MAX_NODES; x++)
                if (is_solved[x]) clog << x << ' ';
            clog << "}\n";
        }
    };
    auto updateDistanceLabel = [&] (int parent_node, int node) {
        // Operation 3: show nodes whose labels are updated and the
        //              corresponding updated label (distance and parent).
        auto new_distance = distance[parent_node] + weight[parent_node][node];
        if (verbose)
            clog << "Updating labels for node " << node
                << "\n\tdistance: " << distance[node] << " -> " << new_distance
                << "\n\tparent:   " << parent[node]   << " -> " << parent_node
                << '\n';
        distance[node] = new_distance;
        parent[node] = parent_node;
        // Operation 4: show labels of all the nodes
        if (verbose) {
            clog << "\tLabelled Nodes: ";
            for (int x=1; x<=MAX_NODES; x++) {
                if (x%3 == 1) clog << "\n\t    ";
                clog << x << "(d:" << distance[x] << ", p:" << parent[x]<< ") ";
            }
            clog << '\n';
        }
    };

    // THE ALGORITHM
    distance[Start_ID] = 0;
    addToSolved(Start_ID);

    while (!is_solved[Dest_ID]) {
        // Determine the node with least distance among
        // all nodes whose best distance is not yet known.
        int min_best_dist = INT_MAX;
        int best_node_id = -1;
        // find the node that is not in the solved set and has the minimal
        // distance
        for (int i = 1; i <= number_of_nodes; ++i) {
            // best distance so far?
            if (!is_solved[i] && distance[i] < min_best_dist) {
                min_best_dist = distance[i];
                best_node_id = i;
            }
        }

        if (best_node_id == -1) {
            // Destination is unreachable.
            cerr << Dest_ID << " is unreachable from " << Start_ID << '\n';
            return best_path;  // empty deque
        }

        // Best total distance so far for this node is the actual
        // best total distance.
        int v = best_node_id;
        addToSolved(v);

        // if applicable, update the label of the neighbours of the active node
        // (that is, the distance and parent)
        for (int i = 1; i <= number_of_nodes; ++i) {
            if (!is_solved[i]
                && weight[v][i] > 0
                && (distance[v] + weight[v][i]) < distance[i]
            ) {
                // It does.
                updateDistanceLabel(v, i);
            }
        }
    }

    // At this point we know parent of each node on the
    // best path from Start to Dest
    clog << "shortest distance from " << Start_ID << " To " << Dest_ID 
        << " is " << distance[Dest_ID] << '\n';
    best_path.push_front(Dest_ID);
    int next_node_id = Dest_ID;
    while (next_node_id != Start_ID) {
        next_node_id = parent[next_node_id];
        best_path.push_front(next_node_id);
    }
    return best_path;
}


void Weighted_Graph::Show_Best_Path(int Start, int Dest) const
{
    deque<int> best_path = this->Best_Path(Start, Dest, true);

    if (best_path.size() == 0) {
        clog << "No path found\n";
    }
    else {
        clog << "Showing best path:\n";
        while (best_path.size() > 0) {
            int next = best_path.front();
            best_path.pop_front();
            cout << next << '\n';
        }
    }
    clog << '\n';
}



    bool Weighted_Graph::
validVertex(int node) const
{
    return node > 0 && node <= number_of_nodes;
}

