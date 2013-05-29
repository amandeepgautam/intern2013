#include <iostream>
#include "kernel_def.h"

feature_vector::feature_vector() {
	//empty constructor.
}

void feature_vector::add(int key) {
	map<int, int>::iterator it = freq.find(key);
	if(it==freq.end())
		freq[key]=1;
	else
		++freq[key];
}

void feature_vector::print() const {
	map<int, int>::const_iterator it = freq.begin();
	while(it!=freq.end()) {
		cout<<it->first<<"\t";
		++it;
	}
	cout<<endl;
	it = freq.begin();
	while(it!=freq.end()) {
		cout<<it->second<<"\t";
		++it;
	}
	cout<<endl;
}

void kernel::setFirst(const feature_vector *first) {
	kernel::first = first;
}

void kernel::setSecond(const feature_vector *second) {
	kernel::second = second;
}

int kernel::calculate() {
	int num = 0;
	map<int, int>::const_iterator first_it = (first->freq).begin();
	map<int, int>::const_iterator second_it = (second->freq).begin();
	while(first_it!=(first->freq).end() && second_it!=(second->freq).end()) {
		if(first_it->first==second_it->first) {//equal
			num += (first_it->second<second_it->second?first_it->second:second_it->second);
			++first_it;
			++second_it;
		} else if(first_it->first<second_it->first) {
			++first_it;
		} else {
			++second_it;
		}
	}
	return num;
}
