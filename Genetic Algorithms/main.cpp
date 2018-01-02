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
	cout << "Enter the target phrase:" << endl;
	getline(cin, target);

	int N_ind = 1000;
	cout << "Enter the number of individuals (recommended from 200 to 1000):" << endl;
	cin >> N_ind;

	float mutationRate = 0.01;
	cout << "Enter the mutation rate (recommended from 0.001 to 0.05):" << endl;
	cin >> mutationRate;

	printf("Target phrase: %s\n", target.c_str());
	printf("Number of individuals: %d\n", N_ind);
	printf("Mutation rate: %f\n", mutationRate);

	vector<Population> populations;
	Population p(target, mutationRate, N_ind, 0);
	populations.push_back(p);
	bool finished = false;
	do {
		populations.back().calculateFitness();
		printf("Best specimen: %s\n", populations.back().getBest().getPhrase().c_str());
		printf("Generation: %d, Average: %f\n", populations.back().getGenerations(), populations.back().getAverage());
		populations.back().naturalSelection();
		finished = populations.back().isFinished();
		if (not finished) {
			Population p1 = populations.back().generate();
			populations.push_back(p1);
		}
	} while (not finished);
}
