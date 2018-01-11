//
//  Population.hpp
//  CPP
//
//  Created by Roberto Ariosa Hernández on 01/01/2018.
//  Copyright © 2018 Mr.Robb. All rights reserved.
//

#ifndef Population_hpp
#define Population_hpp

#include <iostream>
#include <vector>
#include <stdio.h>
#include "DNA.hpp"

using namespace std;

class Population {
private:
	float mutationRate;
	vector<DNA> population;
	vector<DNA> pool;
	string target;
	int generation;
	bool finished;
	int perfectScore;
	
public:
	Population();
	
	// construct
	Population(int length, float mutationRate, int N_ind, int generation);
	
	DNA operator[](int i);
	
	// call fitness for every specimen
	void calculateFitness(vector<int> scores);
	
	// reproduce
	void naturalSelection();
	
	// create new generation
	Population generate(int length);
	
	// most fit
	int getBest();
	
	// finished
	bool isFinished();
	
	int getGenerations();
	
	float getAverage();
	
	vector< vector<float> > allValues();
};

#endif /* Population_hpp */
