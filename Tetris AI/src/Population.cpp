//
//  Population.cpp
//  CPP
//
//  Created by Roberto Ariosa Hernández on 01/01/2018.
//  Copyright © 2018 Mr.Robb. All rights reserved.
//

#include "Population.hpp"

class Population {
private:
	float mutationRate;
	vector<DNA> population;
	vector<DNA> pool;
	string target;
	int generation;
	bool finished = false;
	int perfectScore = 1;

public:
	// construct
	Population() {
		
	}
	
	Population(float mutationRate, int N_ind, int generation) {
		this->mutationRate = mutationRate;
		this->generation = generation;
		
		population = vector<DNA> (N_ind, DNA());
		pool = vector<DNA> ();
		calculateFitness();
	}

	// call fitness for every specimen
	void calculateFitness() {
		for (int i = 0; i < population.size(); i++) {
			population[i].fitness(target);
		}
	}

	// reproduce
	void naturalSelection() {
		float maxFitness = getBest().getFitness();

		for (int i = 0; i < population.size(); i++) {
			float relative_fitness = population[i].getFitness() / maxFitness;
			int percentage = int(relative_fitness * 100);
			for (int j = 0; j < percentage; j++) {
				pool.push_back(population[i]);
			}
		}
	}

	// create new generation
	Population generate() {
		Population p (mutationRate, int(population.size()), generation + 1);
		if (pool.size() > 0) {
			for (int i = 0; i < population.size(); i++) {
				int a = int(rand() % pool.size());
				int b = int(rand() % pool.size());
				DNA dna_a = pool[a];
				DNA dna_b = pool[b];
				DNA child = dna_a.crossover(dna_b);
				child.mutate(mutationRate);
				p.population[i] = child;
			}
			pool = vector<DNA>();
		}
		return p;
	}

	// most fit
	DNA getBest() {
		float record = 0.0;
		int index = 0;
		for (int i = 0; i < population.size(); i++) {
			if (population[i].getFitness() > record) {
				index = i;
				record = population[i].getFitness();
			}
		}
		return population[index];
	}

	// finished
	bool isFinished() {
		finished = (getBest().getFitness() == perfectScore);
		return finished;
	}

	int getGenerations() {
		return generation;
	}

	float getAverage() {
		float total = 0.0;
		for (int i = 0; i < population.size(); i++) {
			total += population[i].getFitness();
		}
		return total / (float) population.size();
	}

	string allPhrases() {
		string all = "";
		for (int i = 0; i < population.size(); i++) {
			all += population[i].getPhrase() + "\n";
		}
		return all;
	}
};
