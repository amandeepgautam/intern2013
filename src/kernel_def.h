#ifndef KERNEL_DEF_H
#define KERNEL_DEF_H

#include <map>

using namespace std;

class feature_vector;

class kernel {
	private:
		static const feature_vector *first;
		static const feature_vector *second;
	public:
		static void setFirst(const feature_vector *first);
		static void setSecond(const feature_vector *second);
		static int calculate();
};

class feature_vector {
	private:
		map<int, int> freq;	//<id_of_node, corresponding frequency>
	public:
		feature_vector();
		void add(int key);
		void print() const;
		friend int kernel::calculate();
};

#endif
