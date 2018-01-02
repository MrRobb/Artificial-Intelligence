//
//  DNA.cpp
//  CPP
//
//  Created by Roberto Ariosa Hernández on 01/01/2018.
//  Copyright © 2018 Mr.Robb. All rights reserved.
//

#include "DNA.hpp"

class DNA {

private:
	vector<char> genes;
	float my_fitness;

public:
	// constructor
	DNA(int length) {
		genes = vector<char> (length);
		for (int i = 0; i < length; i++) {
			genes[i] = (char) (rand() % 96) + 32;
		}
	}
	
	DNA& operator=(const DNA& old) {
		genes = old.genes;
		my_fitness = old.my_fitness;
		return *this;
	}
	
	// array --> string
	string getPhrase() {
		string s (genes.begin(), genes.end());
		return s;
	}
	
	// fitness function
	void fitness (string target) {
		int score = 0;
		for (int i = 0; i < genes.size(); i++) {
			score += (genes[i] == target[i]);
		}
		my_fitness = (float) score / (float) genes.size();
	}
	
	float getFitness() {
		return my_fitness;
	}
	
	// crossover
	DNA crossover(DNA &partner) {
		DNA child(int(partner.genes.size()));
		
		int midpoint = int(rand() % genes.size());
		
		for (int i = 0; i < genes.size(); i++) {
			child.genes[i] = (i < midpoint) ? genes[i] : partner.genes[i];
		}
		
		return child;
	}
	
	// mutation
	void mutate(float mutationRate) {
		for (int i = 0; i < genes.size(); i++) {
			float r = ((double) rand() / (RAND_MAX));
			if (r < mutationRate) {
				genes[i] = (char) (rand() % 96) + 32;
			}
		}
	}
	
};
