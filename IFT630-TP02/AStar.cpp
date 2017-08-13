#include "AStar.h"

using namespace std;

bool operator<(const Node &n1, const Node &n2) {
	return n1.cost > n2.cost;
}

bool operator==(const Node &n1, const Node &n2) {
	return n1.idx == n2.idx;
}

// manhattan distance: requires each move to cost >= 1
float heuristic(int i0, int j0, int i1, int j1) {
	return std::abs(i0 - i1) + std::abs(j0 - j1);
}

AStar::AStar(int height, int width, int start, int goal) {
	this->height = height;
	this->width = width;
}

Node AStar::findPath(string role, vector<char> map, int start, int goal) {

	const float INF = std::numeric_limits<float>::infinity();
	Node start_node(start, 0.);
	Node goal_node(goal, 0.);
	vector<int> solution;

	// initialze all costs at the highest value possible
	float* costs = new float[height * width];
	for (int i = 0; i < height * width; ++i)
		costs[i] = INF;

	costs[start] = 0.;

	vector<Node> nodes_to_visit;
	vector<Node> closed_Nodes;
	nodes_to_visit.push_back(start_node);

	while (true)
	{
		if (nodes_to_visit.empty())
			return Node(-1, -1);


		Node currentNode = nodes_to_visit.front();
		nodes_to_visit.pop_back();
		closed_Nodes.push_back(currentNode);

		if (currentNode.idx == goal_node.idx)
			return findNextMove(currentNode);

		for (int walkablePosition : getWalkableNeighbors(role, currentNode.idx, map)) {
			float currentHeuristic = heuristic(currentNode.idx / width, currentNode.idx % width, goal / width, goal % width);
			float walkableHeuristic = heuristic(walkablePosition / width, walkablePosition % width, goal / width, goal % width);

			Node walkableNode(walkablePosition, currentNode.cost - currentHeuristic + walkableHeuristic + 1);
			walkableNode.parent = &currentNode;

			int nodePositionOpen = findNodePosition(nodes_to_visit, walkableNode);
			int nodePositionClosed = findNodePosition(closed_Nodes, walkableNode);

			if (nodePositionOpen != -1) {
				if (walkableNode.cost < nodes_to_visit.at(nodePositionOpen).cost) {
					nodes_to_visit.erase(nodes_to_visit.begin() + nodePositionOpen);
					nodes_to_visit.push_back(walkableNode);
				}
			}

			else if (nodePositionClosed != -1) {
				if (walkableNode.cost < closed_Nodes.at(nodePositionClosed).cost) {
					closed_Nodes.erase(nodes_to_visit.begin() + nodePositionOpen);
					nodes_to_visit.push_back(walkableNode);
				}
			}

			else {
				nodes_to_visit.push_back(walkableNode);
			}

			sort(nodes_to_visit.begin(), nodes_to_visit.end());
		}
	}
}

vector<int> AStar::getWalkableNeighbors(string role, int currentPos, vector<char>& map) {
	vector<int> neighbors;
	// Up
	if (currentPos / width > 0) neighbors.push_back(currentPos - width);
	// Right
	if (currentPos % width > 0) neighbors.push_back(currentPos - 1);
	// Down
	if (currentPos / width + 1 < height) neighbors.push_back(currentPos + width);
	// Left
	if (currentPos % width + 1 < width) neighbors.push_back(currentPos + 1);

	if (role == "rat") {
		// Up-Right
		if (currentPos / width > 0 && currentPos % width > 0) neighbors.push_back(currentPos - width - 1);
		// Up-Left
		if (currentPos / width > 0 && currentPos % width + 1 < width) neighbors.push_back(currentPos - width + 1);
		// Down-Right
		if (currentPos / width + 1 < height && currentPos % width > 0) neighbors.push_back(currentPos + width - 1);
		// Down-Left
		if (currentPos / width + 1 < height && currentPos % width + 1 < width) neighbors.push_back(currentPos + width + 1);
	}

	for (int neighbor : neighbors)
		if (map.at(neighbor) == '#') neighbors.erase(neighbors.begin() + neighbor);

	return neighbors;
}

int AStar::findNodePosition(vector<Node>& v, Node& n) {
	auto it = find_if(v.begin(), v.end(), [&n](const Node& obj) {return obj.idx == n.idx; });
	if (it != v.end())
		return std::distance(v.begin(), it);
	return -1;
}

Node AStar::findNextMove(Node& currentNode) {
	if (currentNode.parent)
		findNextMove(*currentNode.parent);
	else
		return currentNode;

	return Node(-1, -1);
}


int AStar::findNextMoveToBestGoal(string role, vector<char> map, int start, vector<int> goals) {
	Node bestNode;
	for (int goal : goals) {
		Node currentNode = findPath(role, map, start, goal);

		if (currentNode.cost < bestNode.cost)
			bestNode = currentNode;
	}

	return bestNode.idx;
}

int AStar::getCostToGoal() {
	return costToGoal;
}




