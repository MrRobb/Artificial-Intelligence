//
//  DNA.cpp
//  CPP
//
//  Created by Roberto Ariosa Hernández on 01/01/2018.
//  Copyright © 2018 Mr.Robb. All rights reserved.
//

#include "DNA.hpp"

DNA::DNA(){
	
}

// constructor
DNA::DNA(int length) {
	this->genes = vector<float> (length);
	for (int i = 0; i < length; i++) {
		this->genes[i] = (float(rand()) - float(RAND_MAX / 2)) / float(RAND_MAX);
	}
	return *this;
}

float DNA::operator[](int i) {
	return this->genes[i];
}

vector<float> DNA::getValues() {
	return genes;
}

// fitness function
void DNA::fitness (int score, int max_score) {
	if (max_score != 0) {
		my_fitness = float(score) / float(max_score);
	}
	else {
		my_fitness = 0;
	}
}

float DNA::getFitness() {
	return my_fitness;
}

// crossover
DNA DNA::crossover(DNA &partner) {
	DNA child(int(partner.genes.size()));
	
	int midpoint = int(rand() % genes.size());
	
	for (int i = 0; i < genes.size(); i++) {
		child.genes[i] = (i < midpoint) ? genes[i] : partner.genes[i];
	}
	
	return child;
}

// mutation
void DNA::mutate(float mutationRate, int generation) {
	for (int i = 0; i < genes.size(); i++) {
		float r = ((double) rand() / (RAND_MAX));
		if (r < mutationRate) {
			genes[i] += 1/generation * (float(float(rand()) - float(RAND_MAX)/2) / float(RAND_MAX));
		}
	}
}
