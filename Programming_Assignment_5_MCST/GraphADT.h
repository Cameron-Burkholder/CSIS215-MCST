#pragma once
class Graph {
private:
	void operator =(const Graph&) {} // Protect assignment
	Graph(const Graph&) {} // Protect copy constructor
public:
	Graph() {} // Default constructor
	virtual ~Graph() {} // Base destructor
	// Initialize a graph of n vertices
	virtual void Init(int n) = 0;
	// Return: the number of vertices and edges
	virtual int n() const = 0;
	virtual int e() const = 0;
	// Return v’s first neighbor
	virtual int first(int v) const = 0;
	// Return v’s next neighbor
	virtual int next(int v, int w) const = 0;
	// Set the weight for an edge
	// i, j: The vertices
	// wgt: Edge weight
	virtual void setEdge(int v1, int v2, int wght) = 0;
	// Delete an edge
	// i, j: The vertices
	virtual void delEdge(int v1, int v2) = 0;
	// Determine if an edge is in the graph
	// i, j: The vertices
	// Return: true if edge i,j has non-zero weight
	virtual bool isEdge(int i, int j) const = 0;
	// Return an edge’s weight
	// i, j: The vertices
	// Return: The weight of edge i,j, or zero
	virtual int weight(int v1, int v2) const = 0;
	// Get and Set the mark value for a vertex
	// v: The vertex
	// val: The value to set
	virtual int getMark(int v) const = 0;
	virtual void setMark(int v, int val) = 0;
};