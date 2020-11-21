#pragma once

#include "GraphADT.h"
#include "Node.h"

enum MARK{ VISITED, UNVISITED };

template <typename E>
class AMGraph : public Graph {
private:
	int numVertices;
	int numEdges;
	int** matrix;
	int* marks;
public:
	AMGraph(int v) {
		Init(v);
	}
	~AMGraph() {
		delete[] marks;
		for (int i = 0; i < numVertices; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	// Initialize a graph of n vertices
	void Init(int n) {
		int i;
		numVertices = n;
		numEdges = 0;
		marks = new int[n];

		// Mark all nodes as unvisited
		for (i = 0; i < numVertices; i++) {
			marks[i]->setMark(UNVISITED);
		}

		// Build matrix
		matrix = (int**) new int* [numVertices];
		for (i = 0; i < numVertices; i++) {
			matrix[i] = new int[numVertices];
		}

		// Set all edge weights to 0
		for (i = 0; i < numVertices; i++) {
			for (int j = 0; j < numVertices; j++) {
				matrix[i][j] = 0;
			}
		}
	}

	// Return: the number of vertices and edges
	int n() const {
		return numVertices;
	}
	int e() const {
		return numEdges;
	}

	// Return v’s first neighbor
	int first(int v) const {
		int n = numVertices;
		for (int i = 0; i < numVertices; i++) {
			if (matrix[v][i] != 0) {
				n = i;
				break;
			}
		}
		return n;
	}
	// Return v’s next neighbor
	int next(int v, int w) const {
		int n = numVertices;
		for (int i = w + 1; i < numVertices; i++) {
			if (matrix[v][i] != 0) {
				n = i;
				break;
			}
		}
		return n;
	}

	// Set the weight for an edge
	void setEdge(int v1, int v2, int wt) {
		if (wt >= 0) {
			if (matrix[v1][v2] == 0) {
				numEdges++;
			}
			matrix[v1][v2] = wt;
		}
	}
	// Delete an edge
	void delEdge(int v1, int v2) {
		if (matrix[v1][v2] != 0) {
			numEdges--;
		}
		matrix[v1][v2] = 0;
	}
	// Determine if an edge is in the graph
	bool isEdge(int v1, int v2) const {
		return matrix[v1][v2] != 0;
	}

	// Return an edge’s weight
	int weight(int v1, int v2) const {
		return matrix[v1][v2]
	}

	// Get and Set the mark value for a vertex
	int getMark(int v) const {
		return marks[v];
	}
	void setMark(int v, int val) {
		marks[v] = val;
	}
};