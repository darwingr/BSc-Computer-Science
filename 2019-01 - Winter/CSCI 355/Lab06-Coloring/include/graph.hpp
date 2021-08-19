/* graph.hpp
 * ---------
 * CSCI 355 Algorithm Analysis
 * Lab 6    m-Coloring Problem
 *
 * Authors: Martin van Bommel, Darwin Jacob Groskleg
 * Date:    Wednesday, March 13, 2019
 *
 * Purpose: data structures and functions given as part of the lab explanation.
 */
#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <iostream>

// There are 10 vertices
#define GRAPH_NODES 10

// Adjacency matrix representing an undirected graph:
//      true iff vertex i and vertex j are adjacent.
const bool W[GRAPH_NODES][GRAPH_NODES] = {
    { 0, 1, 0, 0, 1, 1, 0, 0, 0, 0 },
    { 1, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 1, 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 1, 0, 0, 0, 1, 0 },
    { 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 0, 0, 1, 0, 0, 1, 0, 0, 0, 1 },
    { 0, 0, 0, 1, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 1, 1, 0, 0 }
};

// Colors (ints) starting from 1.
int color[GRAPH_NODES * GRAPH_NODES];



/// promising
///
/// Determines for some vertex i whether all its adjacent vertices are not the
/// colour c, the same colour as i.
/// Arguments:
///     i - some vertex in the graph
///     c - some color value (>=1)
bool promising(int i, int c) {
    for (int j=0; j<i; j++)
        if (W[i][j] && color[j] == c)
            return false;
    return true;
}

/// m_color
///
/// Outputs the maximum number of colour used by each possible configuration
/// for the graph W using only m colours.
/// No two adjacent vertices can be the same colour.
/// Arguments:
///     i - some vertex in the graph
///     n - number of vertices in the graph
///     m - maximum number of colours to colour the graph with
void m_color(int i, int n, int m) {
    if (i == n)
        std::cout << color[i-1] << " ";
    else
        for (int c=1; c <= m; c++)
            if (promising(i,c)) {
                color[i] = c;
                m_color(i+1, n, m);
            }
}

#endif // GRAPH_HPP_INCLUDED
