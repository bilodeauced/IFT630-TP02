#ifndef ASTAR_H 
#define ASTAR_H

#include <queue>
#include <limits>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include "Map.h"

using namespace std;

// represents a single pixel
class Node {
public:
	int idx;     // index in the flattened grid
	float cost;  // cost of traversing this pixel
	Node* parent; // Pointer to the parent node

	Node(int i, float c) : idx(i), cost(c), parent(nullptr) {}
	Node() : idx(-1), cost(std::numeric_limits<float>::max()), parent(nullptr) {}

};

class AStar {

private:
	int height;
	int width;
	int costToGoal;

	Node* findPath(string role, vector<char> map, int start, int goal);
	Node* findNextMove(Node* currentNode);
	vector<int> getWalkableNeighbors(string role, int currentPos, vector<char>& map);
	int findNodePosition(vector<Node*>& v, Node* n);
public:
	AStar(int height, int width);	
	Case findNextMoveToBestGoal(string role, vector<char> map, Case start, vector<Case> goals);
	int getCostToGoal();
};

#endif