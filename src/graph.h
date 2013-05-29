#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <fstream>

#include "kernel_def.h"

using namespace std;

typedef vector<bool> Array;
typedef vector<Array> TwoDArray;

class baseGraph {
	private:
		int nodes;	/*Number of nodes.*/
		vector<feature_vector *> vec;	/*vector of feature nector.*/
	public:
		baseGraph(int nodes);
		virtual ~baseGraph();
		/*set-get functions*/
		int getNodes();
		void setNodes(int nodes);
		const feature_vector *getVec(int pos);
		void setVec(int pos, feature_vector *fVec);

		/*Input edges from file and set up in corresponding representation.*/
		virtual void setGraph(ifstream &ipf) = 0;

		/*Utility functions*/
		virtual void printGraph() = 0;
		virtual feature_vector *subgraph_d(int node, int depth) = 0;	/*subgraph upto depth d.*/
};

class matGraph: public baseGraph {
	private:
		TwoDArray matrix;
	public:
		matGraph(int nodes, ifstream &ipf);
		TwoDArray getMatrix();
		void setGraph(ifstream &ipf);
		void printGraph();
		feature_vector *subgraph_d(int nodes, int depth);
};

#endif
