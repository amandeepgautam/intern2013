#include <iostream>
#include <iterator>

#include "postpr.h"

using namespace std;

/*@num: number of */
postpr::postpr(const TwoDMatrix &res, ifstream &commInfo) : result(res) {
	//Get communnity information from file.
	setCommunities(commInfo);
}

const TwoDMatrix& postpr::getResult() {
       return result;
}

const classList& postpr::getCommunities() {
	return communities;
}

void postpr::setCommunities(ifstream &commInfo) {
	int node, comm;
	while(commInfo>>node>>comm) {
		communities[comm].push_back(node);
	}
}

const vector<TwoDMatrix>& postpr::getPPMat() {
	return ppMat;
}

void postpr::segregate() {
	for(map<int, ArrayI>::iterator one = communities.begin(); one!=communities.end(); ++one) {
		for(map<int, ArrayI>::iterator two = one; two!=communities.end(); ++two) {
			ArrayI one_vec = one->second, sec_vec = two->second;
			TwoDMatrix temp;
			for(ArrayI::iterator it_one = one_vec.begin(); it_one!=one_vec.end(); ++it_one) {
				ArrayI row;
				for(ArrayI::iterator it_sec = sec_vec.begin(); it_sec!=sec_vec.end(); ++it_sec) {
					int r=*it_one, c=*it_sec;
					if(c>r)
						swap(r,c);
					row.push_back(result[r-1][c-1]);
				}
				temp.push_back(row);
			}
			ppMat.push_back(temp);
		}
	}
}

void postpr::setAvgVar() {
	int sum, count;
	float avg, var;
	for(vector<TwoDMatrix>::iterator it = ppMat.begin(); it!=ppMat.end(); ++it) {
		TwoDMatrix matrix = *it;
		count=sum=0;
		for(TwoDMatrix::iterator mat_it = matrix.begin(); mat_it!=matrix.end(); ++mat_it) {
			ArrayI vec = *mat_it;
			for(ArrayI::iterator vec_it=vec.begin(); vec_it!=vec.end(); ++vec_it) {
				sum += *vec_it;
				++count;
			}
		}
		avg = (float)sum/count;
		sum = 0;
		for(TwoDMatrix::iterator mat_it = matrix.begin(); mat_it!=matrix.end(); ++mat_it) {
			ArrayI vec = *mat_it;
			for(ArrayI::iterator vec_it=vec.begin(); vec_it!=vec.end(); ++vec_it) {
				sum += (((*vec_it)-avg)*((*vec_it)-avg));
			}
		}
		cout<<endl;
		var = (float)sum/count;
		pair<float, float> x = make_pair(avg, var);
		avgVar.push_back(x);
	}
}

void postpr::write(ofstream &opf) {
	map<int, pair<int, int> > matId;
	int count=0;
	for(unsigned int i=0; i<communities.size(); ++i) {
		for(unsigned int j=i; j<communities.size(); ++j) {
			matId[count++] = make_pair(i+1, j+1);
		}
	}
	vector<pair<float, float> >::iterator itVec = avgVar.begin();
	count=0;
	for(; itVec!=avgVar.end(); ++itVec, ++count) {
		opf<<"Matrix pair for communities: "<<matId[count].first<<","<<matId[count].second<<endl;
		opf<<"average: "<<(*itVec).first<<" variance: "<<(*itVec).second<<endl;
	}
}
