#pragma once

#include "GraphADT.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

enum MARK{ VISITED, UNVISITED };

class AMGraph : public Graph {
private:
	int numVertices;
	int numEdges;
	int** matrix;
	int* marks;
	std::ifstream readFile;
	std::ofstream writeFile;

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
					setEdge(row, col, weight);
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
	void print() const {
		std::cout << "Number of vertices is " << numVertices << std::endl;
		std::cout << "Number of edges is " << numEdges << std::endl;
		std::cout << "Matrix:" << std::endl;
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

};