#include <iostream>
#include <queue>

#include "graph.h"
#include "global.h"

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

feature_vector *matGraph::subgraphD(int node, int depth) {
#ifdef LOGGING
	logFileObj<<"node: "<<node<<endl;
#endif
	feature_vector *fv = new feature_vector;
	int prev_level=0, curr_level=1, next_level = 2, nodes=getNodes();
	vector< map<int, int> > node_count(3);
	++((node_count.at(curr_level))[node]);
	++depth;
	while(depth!=1) {
		map<int, int> &nPM = node_count.at(prev_level);			//nodePreviousMap
		map<int, int> &nCM = node_count.at(curr_level);			//nodeCurrentMap
		map<int, int> &nNM = node_count.at(next_level);			//nodeNextMap
		for(map<int, int>::iterator it = nCM.begin(); it!=nCM.end(); ++it) {
			int temp = it->first;	//get a node.
			fv->add(temp, it->second);
			for(int i=0; i<nodes; ++i) {
				if(matrix[temp][i] && nPM.count(i)==0) {
					nNM[i] += it->second;
				}
			}
		}
#ifdef DEBUG
		if(debugLevel>=1) {
			cout<<"Prev. level node list"<<endl;
			cout<<"nodes:\t";
			for(map<int, int>::iterator it = nPM.begin(); it!=nPM.end();++it) {
				cout<<it->first<<"\t";
			}
			cout<<endl<<"count:\t";
			for(map<int, int>::iterator it = nPM.begin(); it!=nPM.end();++it) {
				cout<<it->second<<"\t";
			}
			cout<<endl<<"Current level node list"<<endl;
			cout<<"nodes:\t";
			for(map<int, int>::iterator it = nCM.begin(); it!=nCM.end();++it) {
				cout<<it->first<<"\t";
			}
			cout<<endl<<"count:\t";
			for(map<int, int>::iterator it = nCM.begin(); it!=nCM.end();++it) {
				cout<<it->second<<"\t";
			}
			cout<<endl<<"Next level node list"<<endl;
			cout<<"nodes:\t";
			for(map<int, int>::iterator it = nNM.begin(); it!=nNM.end();++it) {
				cout<<it->first<<"\t";
			}
			cout<<endl<<"count:\t";
			for(map<int, int>::iterator it = nNM.begin(); it!=nNM.end();++it) {
				cout<<it->second<<"\t";
			}
			cout<<endl<<"----------------------------"<<endl;
		}
#endif
		nPM.clear();
		int swapInt = prev_level;
		prev_level = curr_level;
		curr_level = next_level;
		next_level = swapInt;
		--depth;
	}
	for(map<int, int>::const_iterator it= (node_count.at(curr_level).begin()); it!=(node_count.at(curr_level).end()); ++it) {
		fv->add(it->first, it->second);
	}
#ifdef DEBUG
	if(debugLevel>=1) {
		cout<<"Printing the vector"<<endl;
		fv->print();
	}
#endif
	return fv;
}
