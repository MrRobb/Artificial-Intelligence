//
//  DNA.hpp
//  CPP
//
//  Created by Roberto Ariosa Hernández on 01/01/2018.
//  Copyright © 2018 Mr.Robb. All rights reserved.
//

#ifndef DNA_hpp
#define DNA_hpp

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class DNA {
	
private:
	vector<float> genes;
	float my_fitness;
	
public:
	DNA();
	
	// constructor
	DNA(int length);
	
	float operator[](int i);
	
	// array --> string
	vector<float> getValues();
	
	// fitness function
	void fitness (int score, int max_score);
	
	float getFitness();
	
	// crossover
	DNA crossover(DNA &partner);
	
	// mutation
	void mutate(float mutationRate);
};

#endif /* DNA_hpp */
