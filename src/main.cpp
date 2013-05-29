#include <iostream>
#include <fstream>

#include "global.h"
#include "graph.h"
#include "kernel_def.h"

using namespace std;

const feature_vector * kernel::first;
const feature_vector * kernel::second;

int main(int argc, char *argv[]) {
	if(argc!=4) {
		cout<<"Please enter proper format."<<endl;
		cout<<"arg 0: By default name of program"<<endl;
		cout<<"arg 1: The format of the graph."<<endl;
		cout<<"arg 2: The input file"<<endl;
		cout<<"arg 3: Output file"<<endl;
		return 0;
	}
	if(!isdigit(*(argv[1]))) { 
		printf("Enter digit as argument.\n");
		return 0;
	}
	int num = *((argv[1])+0)-'0';
	int no_of_nodes;
	baseGraph *graph;
	ifstream ipf;
	ipf.open( argv[2]);
	ipf>>no_of_nodes;
	if(!num) {	//num=0 implies matrix representation.
		graph = new matGraph(no_of_nodes, ipf);
	}//put else here to add another format of graph.
	graph->setGraph(ipf);
	ipf.close();
	for(int i=0; i<no_of_nodes; ++i) {
		feature_vector *fVec = graph->subgraph_d(i, DEPTH);
		graph->setVec(i, fVec);
	}
	/*Final answer matrix*/
	vector< vector<int> > answer;
	for(int i=0; i<no_of_nodes; ++i) {
		vector<int> row(i);
		answer.push_back(row);
	}
	for(int i=0; i<no_of_nodes; ++i) {
		for(int j=0; j<i; ++j) {
			kernel::setFirst(graph->getVec(i));
			kernel::setSecond(graph->getVec(j));
			answer[i][j] = kernel::calculate();
		}
	}
	ofstream opf;
	opf.open(argv[3]);
	for(int i=0; i<no_of_nodes; ++i) {
		for(int j=0; j<no_of_nodes; ++j) {
			if(i<j)
				opf<<answer[j][i];
			else if(i==j)
				opf<<1;
			else
				opf<<answer[i][j];
			opf<<"  ";
		}
		opf<<endl;
	}
	opf.close();
	delete(graph);
	return 0;
}
