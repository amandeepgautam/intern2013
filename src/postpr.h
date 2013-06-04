#ifndef POSTPR_H
#define POSTPR_H

#include <vector>
#include <fstream>
#include <map>

using namespace std;

typedef vector<int> ArrayI;	//Array of integers.
//not exactly Two dimensional. Symmetry is taken into account.
typedef vector<ArrayI> TwoDMatrix;
typedef map<int, ArrayI> classList;

/*Class for post-processing the results of kernel matrix.*/
class postpr {
	private:
		const TwoDMatrix &result;		//Result of the kernel Matrix.
		classList communities;		//list of classes. Taken from input file.
		vector<TwoDMatrix> ppMat;	//Post-precessed Matrices.
		vector< pair<float, float> > avgVar;	//average-variance pair for each class.
	public:
		postpr(const TwoDMatrix &res ,ifstream &commInfo);
		/*Set get funcitons.*/
		const TwoDMatrix& getResult();
		const classList& getCommunities();
		void setCommunities(ifstream &commInfo);
		const vector<TwoDMatrix> &getPPMat();
		void segregate();	//make different classes of result, viz. inter community, intra community.
		void setAvgVar();	//set the average and variance of the data in matrix.
		void write(ofstream &opf);
};
#endif
