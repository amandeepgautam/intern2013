#include <iostream>
#include <fstream>

#include "global.h"
#include "graph.h"
#include "kernel_def.h"
#include "postpr.h"

using namespace std;

#ifdef LOGGING
string logFileName = ".log";
ofstream logFileObj;
#endif

#ifdef DEBUG
int debugLevel = 1;
#endif

const feature_vector * kernel::first;
const feature_vector * kernel::second;

int main(int argc, char *argv[]) {
	if(argc!=5) {
		cout<<"Please enter proper format."<<endl;
		cout<<"arg 0: By default name of program"<<endl;
		cout<<"arg 1: The format of the graph."<<endl;
		cout<<"arg 2: The graph input file"<<endl;
		cout<<"arg 3: Output file"<<endl;
		cout<<"arg 4: ground truth"<<endl;
		return 0;
	}
	if(!isdigit(*(argv[1]))) { 
		printf("Enter digit as argument.\n");
		return 0;
	}
#ifdef LOGGING
	logFileObj.open(logFileName.c_str());
	logFileObj<<"depth: "<<DEPTH<<endl;
#endif
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
		feature_vector *fVec = graph->subgraphD(i, DEPTH);
		graph->setVec(i, fVec);
	}
	/*Final answer matrix*/
	vector< vector<int> > answer;
	for(int i=0; i<no_of_nodes; ++i) {
		vector<int> row(i+1);
		answer.push_back(row);
	}
	for(int i=0; i<no_of_nodes; ++i) {
		for(int j=0; j<=i; ++j) {
			kernel::setFirst(graph->getVec(i));
			kernel::setSecond(graph->getVec(j));
			answer[i][j] = kernel::calculate();
		}
	}
	/*Write the main result to file*/
	ofstream opf;
	opf.open(argv[3]);
	for(int i=0; i<no_of_nodes; ++i) {
		for(int j=0; j<no_of_nodes; ++j) {
			if(i<=j)
				opf<<answer[j][i];
			else
				opf<<answer[i][j];
			opf<<"\t";
		}
		opf<<endl;
	}
	opf.close();
	/*Writing Finished.*/
	/*Post-Processing*/
	ipf.open(argv[4]);
	postpr postProcessing(answer, ipf);
	ipf.close();
	postProcessing.segregate();
	postProcessing.setAvgVar();
	opf.open(argv[3], fstream::app);
	postProcessing.write(opf);

	delete(graph);
#ifdef LOGGING
	logFileObj.close();
#endif
	return 0;
}
