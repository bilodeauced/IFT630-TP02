#ifndef ASTAR_H 
#define ASTAR_H

#include <queue>
#include <limits>
#include <cmath>
#include <string>
#include <vector>
#include <list>

using namespace std;

// represents a single pixel
class Node {
public:
	int idx;     // index in the flattened grid
	float cost;  // cost of traversing this pixel
	Node* parent; // Pointer to the parent node

	Node(int i, float c) : idx(i), cost(c), parent(nullptr) {}

};

class AStar {

private:
	float* weights;
	int height;
	int width;
	int start;
	int goal;

public:
	AStar(int height, int width, int start, int goal);
	int findPath(string role, vector<char> map);
	vector<int> getWalkableNeighbors(string role, int currentPos, vector<char>& map);
	int findNodePosition(vector<Node>& v, Node& n);
	int findNextMove(Node& currentNode);
};


#endif