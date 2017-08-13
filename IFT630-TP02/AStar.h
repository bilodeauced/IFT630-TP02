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
	Node() : idx(-1), cost(01), parent(nullptr) {}

};

class AStar {

private:
	int height;
	int width;

	Node findPath(string role, vector<char> map, int start, int goal);
	Node findNextMove(Node& currentNode);
	vector<int> getWalkableNeighbors(string role, int currentPos, vector<char>& map);
	int findNodePosition(vector<Node>& v, Node& n);

public:
	AStar(int height, int width, int start, int goal);
	int findNextMoveToBestGoal(string role, vector<char> map, int start, vector<int> goals);
};

#endif