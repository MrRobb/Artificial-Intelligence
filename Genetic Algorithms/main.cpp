//
//  main.cpp
//  CPP
//
//  Created by Roberto Ariosa Hernández on 01/01/2018.
//  Copyright © 2018 Mr.Robb. All rights reserved.
//

#include <iostream>
#include "Population.hpp"
#include "Population.cpp"

int main(int argc, const char * argv[]) {
	string target = "i love you to the moon and back";
	int N_ind = 1000;
	float mutationRate = 0.01;
	
	
	vector<Population> populations = {};
	Population p(target, mutationRate, N_ind, 0);
	populations.push_back(p);
	bool finished = false;
	do {
		populations.back().calculateFitness();
		printf("%s\n", populations.back().getBest().getPhrase().c_str());
		printf("Generation: %d, Average: %f\n", populations.back().getGenerations(), populations.back().getAverage());
		populations.back().naturalSelection();
		finished = populations.back().isFinished();
		if (not finished) {
			Population p1 = populations.back().generate();
			populations.push_back(p1);
		}
	} while (not finished);
}
