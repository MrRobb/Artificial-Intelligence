//
//  Population.cpp
//  CPP
//
//  Created by Roberto Ariosa Hernández on 01/01/2018.
//  Copyright © 2018 Mr.Robb. All rights reserved.
//

#include "Population.hpp"

Population::Population() {
	
}

// construct
Population::Population(int length, float mutationRate, int N_ind, int generation) {
	this->mutationRate = mutationRate;
	this->generation = generation;
	pool = vector<DNA> ();
	population = vector<DNA> (N_ind, DNA());
	for (int i = 0; i < N_ind; i++) {
		population[i] = DNA(length);
	}
}

DNA Population::operator[](int i) {
	return this->population[i];
}

// call fitness for every specimen
void Population::calculateFitness(vector<int> scores) {
	int max_score = *max_element(scores.begin(), scores.end());
	for (int i = 0; i < population.size(); i++) {
		population[i].fitness(scores[i], max_score);
	}
}

// reproduce
void Population::naturalSelection() {
	int i = getBest();
	float maxFitness = population[i].getFitness();

	for (int i = 0; i < population.size(); i++) {
		float relative_fitness = population[i].getFitness() / maxFitness;
		int percentage = int(relative_fitness * 100);
		for (int j = 0; j < percentage; j++) {
			pool.push_back(population[i]);
		}
	}
}

// create new generation
Population Population::generate(int length) {
	Population p (length, mutationRate, int(population.size()), generation + 1);
	if (pool.size() > 0) {
		for (int i = 0; i < population.size(); i++) {
			int a = int(rand() % pool.size());
			int b = int(rand() % pool.size());
			DNA dna_a = this->pool[a];
			DNA dna_b = this->pool[b];
			DNA child = dna_a.crossover(dna_b);
			child.mutate(mutationRate);
			p.population[i] = child;
		}
		pool = vector<DNA>();
	}
	return p;
}

// most fit
int Population::getBest() {
	float record = 0.0;
	int index = 0;
	for (int i = 0; i < population.size(); i++) {
		if (population[i].getFitness() > record) {
			index = i;
			
			record = population[i].getFitness();
		}
	}
	return index;
}

// finished
bool Population::isFinished() {
	finished = (population[getBest()].getFitness() == perfectScore);
	return finished;
}

int Population::getGenerations() {
	return generation;
}

float Population::getAverage() {
	float total = 0.0;
	for (int i = 0; i < population.size(); i++) {
		total += population[i].getFitness();
	}
	return total / (float) population.size();
}

vector< vector<float> > Population::allValues() {
	vector< vector<float> > all (population.size(), vector<float> (4));
	for (int i = 0; i < population.size(); i++) {
		for (int j = 0; j < 4; j++) {
			all[i][j] = population[i][j];
		}
	}
	return all;
}

