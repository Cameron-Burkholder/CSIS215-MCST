#pragma once

#include "GraphADT.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

enum MARK{ VISITED, UNVISITED };
enum INCLUDED{ INCLUDED, EXCLUDED };

class AMGraph : public Graph {
private:
	int numVertices;
	int numEdges;
	int** matrix;
	int* marks;
	std::ifstream readFile;
	std::ofstream writeFile;

	// Make sure filename is valid
	bool isValidFile(std::string file) {
		bool valid = file.find(".graph") != std::string::npos;
		if (!valid) {
			std::cout << "Unable to read file '" << file << "': invalid format." << std::endl;
		}
		return valid;
	}

	// Read graph from file
	void read(std::string file) {
		if (!isValidFile(file)) return;

		std::string buffer;
		int index = 0;
		int row = 0;
		bool valid = true;
		readFile.open(file);

		while (std::getline(readFile, buffer)) {

			// Update graph based on the state of the file input
			if (index == 0) {
				valid = (buffer == "_GRAPH_");
			}
			else if (index == 1) {
				int numIndex = (int)buffer.find("NUM_VERTICES=");
				int numVertices;
				valid = (numIndex != std::string::npos);
				if (valid) {
					numVertices = stoi(buffer.substr(numIndex + 13, (buffer.size() - numIndex + 13)));
					Init(numVertices);
				}
			}
			else {
				std::stringstream line;
				line.str(buffer);
				int weight = 0;
				for (int col = 0; col < numVertices; col++) {
					line >> weight;
					if (weight != 0) {
						setEdge(row, col, weight);
					}
					weight = 0;
				}
				row++;
			}

			// Check for validity of file input
			if (!valid) {
				std::cout << "Unable to read file '" << file << "': invalid format." << std::endl;
				return;
			}

			// Update variables
			buffer.clear();
			index++;
		}

		readFile.close();
	}

	// Find minimum cost vertex
	int minVertex(AMGraph* G, int* D) {
		int i, v = -1;
		// Get first unvisited node
		for (i = 0; i < G->n(); i++) {
			if (G->getMark(i) == UNVISITED) {
				v = i;
				break;
			}
		}
		// Check all subsequent nodes to see if one exists such that 
		// A) it is also unvisited
		// B) it has a cheaper cost
		for (i++; i < G->n(); i++) {
			if (G->getMark(i) == UNVISITED && D[i] < D[v]) {
				v = i;
			}
		}
		return v;
	}


public:
	AMGraph(int v) {
		Init(v);
	}
	AMGraph(std::string file) {
		read(file);
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
			marks[i] = UNVISITED;
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
		int n = this->n();
		for (int i = 0; i < n; i++) {
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
		return matrix[v1][v2];
	}

	// Get and Set the mark value for a vertex
	int getMark(int v) const {
		return marks[v];
	}
	void setMark(int v, int val) {
		marks[v] = val;
	}

	// Print Graph to console
	void print(bool mst) const {
		if (!mst) {
			std::cout << "Number of vertices is " << numVertices << std::endl;
			std::cout << "Number of edges is " << numEdges << std::endl;
			std::cout << "Matrix:" << std::endl;
		}
		for (int row = 0; row < numVertices; row++) {
			for (int col = 0; col < numVertices; col++) {
				std::cout << matrix[row][col] << " ";
			}
			std::cout << std::endl;
		}
	}

	// Write graph to file
	void write(std::string file) {
		if (!isValidFile(file)) return;

		writeFile.open(file);

		writeFile << "_GRAPH_" << std::endl;
		writeFile << "NUM_VERTICES=" << numVertices << std::endl;

		for (int row = 0; row < numVertices; row++) {
			for (int col = 0; col < numVertices; col++) {
				writeFile << matrix[row][col];
				if (col + 1 < numVertices) {
					writeFile << " ";
				}
			}
			writeFile << std::endl;
		}

		writeFile.close();
	}

	// Generate a minimum cost spanning tree starting from vertex v
	AMGraph* MCST(int s) {
		AMGraph* mst = new AMGraph(numVertices);
		std::cout << std::endl << "Begin MST starting at vertex " << s << std::endl;

		// Prim's Algorithm
		int* D = new int[this->n()]; // Array of weights
		int* V = new int[this->n()]; // Array of node markers, manages state of node included/excluded
		int i, w;
		// Set all weights to infinite
		for (int i = 0; i < this->n(); i++) {
			D[i] = INT_MAX;
			V[i] = INT_MAX;
			this->setMark(i, UNVISITED);
		}
		D[s] = 0;
		for (i = 0; i < this->n(); i++) {
			int v = minVertex(this, D);
			this->setMark(v, VISITED);
			if (v != s) {
				int a = (V[v] == INT_MAX ? s : V[v]);
				mst->setEdge(a, v, D[v]);
				mst->setEdge(v, a, D[v]);
			}
			if (D[v] == INFINITY) return mst;

			for (w = this->first(v); w < this->n(); w = this->next(v, w)) {
				if (D[w] > this->weight(v, w)) {
					D[w] = this->weight(v, w);
					V[w] = v;
				}
			}
		}

		mst->print(true);
		return mst;
	}
};