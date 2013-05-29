#include <iostream>
#include <queue>

#include "graph.h"

using namespace std;

baseGraph::baseGraph(int nodes) {
	setNodes(nodes);
	/*feature vetors will be assigned later.*/
	vec.resize(nodes);
	for(int i=0;i<nodes; ++i)
		vec.at(i) = NULL;
}

baseGraph::~baseGraph() {
	for(int i=0; i<nodes; ++i)
		delete(vec.at(i));
}

int baseGraph::getNodes() {
	return nodes;
}

void baseGraph::setNodes(int nodes) {
	this->nodes = nodes;
}

void baseGraph::printGraph() {
	cout<<"Number of nodes: "<<nodes<<endl;
}

const feature_vector *baseGraph::getVec(int pos) {
	return (const feature_vector *)vec.at(pos);
}

void baseGraph::setVec(int pos, feature_vector *fVec) {
	vec.at(pos) = fVec;
}

matGraph::matGraph(int nodes, ifstream &ipf): baseGraph(nodes) {
	for(int i=0; i<nodes; ++i) {
		Array row(nodes);
		matrix.push_back(row);
	}
	setGraph(ipf);
}

TwoDArray matGraph::getMatrix() {
	return matrix;
}

void matGraph::setGraph(ifstream &ipf) {
	int first, second;
	while(ipf>>first>>second) {
		/*Node number in the input file starts from 1.*/
		matrix[first-1][second-1] = true;
		matrix[second-1][first-1] = true;
	}
}

void matGraph::printGraph() {
	baseGraph::printGraph();
	int nodes = getNodes();
	for(int i=0; i<nodes; ++i) {
		for(int j=0; j<nodes; ++j) {
			cout<<matrix[i][j]<<"  ";
		}
		cout<<endl;
	}
}

feature_vector *matGraph::subgraph_d(int node, int depth) {
	feature_vector *fv = new feature_vector;
	int this_level=0, next_level=0;
	queue<int> que;
	queue<int> parent_que;
	que.push(node);
	parent_que.push(-1);	/*No parent.*/
	++this_level;
	int number_of_nodes = getNodes();
	while(depth!=0 && !que.empty()) {
		int temp = que.front();
		int parent = parent_que.front();
		que.pop();
		parent_que.pop();
		fv->add(temp);	/*add the key.*/
		--this_level;
		for(int i=0; i<number_of_nodes; ++i) {
			if(matrix[temp][i] && i!=parent) {
				que.push(i);
				parent_que.push(temp);
				++next_level;
			}
		}
		if(!this_level) {
			this_level = next_level;
			next_level = 0;
			--depth;
		}
	}
	return fv;
}
