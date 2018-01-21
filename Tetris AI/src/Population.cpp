//
//  Population.cpp
//  CPP
//
//  Created by Roberto Ariosa Hernández on 01/01/2018.
//  Copyright © 2018 Mr.Robb. All rights reserved.
//

#include "Population.hpp"

Population::Population() {}

Population::Population(int N_genes, int N_ind, float mutationRate, unsigned int generation)
{
	this->mutationRate = mutationRate;
	this->generation = generation;
	pool = vector<DNA> ();
	population = vector<DNA> (N_ind, DNA());
	
	for (int i = 0; i < N_ind; i++)
		population[i] = DNA(N_genes);
}

DNA& Population::operator[](int i)
{
	return this->population[i];
}

void Population::calculateFitness(vector<int> scores)
{
	int max_score = *max_element(scores.begin(), scores.end());
	
	// Call fitness() for every Individual
	for (int i = 0; i < population.size(); i++)
		population[i].fitness(scores[i], max_score);
}

Population Population::generate()
{
	// Fill the temporary reproduction pool
	naturalSelection();
	
	// Create container of the next generation
	int N_ind = int(population.size());
	int N_genes = int(population[0].getValues().size());
	Population p (N_genes, N_ind, mutationRate, generation + 1);
	
	// Fill pool
	if (pool.size() > 0)
	{
		for (int i = 0; i < population.size(); i++) {
			int a = int(rand() % pool.size());
			int b = int(rand() % pool.size());
			DNA dna_a = this->pool[a];
			DNA dna_b = this->pool[b];
			DNA child = dna_a.crossover(dna_b);
			child.mutate(mutationRate);
			p.population[i] = child;
		}
		
		// Free pool
		pool = vector<DNA>();
	}
	
	return p;
}

int Population::getBest()
{
	float record = 0.0;
	int index = 0;
	
	for (int i = 0; i < population.size(); i++)
	{
		float current = population[i].getFitness();
		
		if (current > record) {
			index = i;
			record = current;
		}
	}
	
	return index;
}

int Population::getGenerations()
{
	return generation;
}

float Population::getAverage()
{
	float total = 0.0;
	
	for (int i = 0; i < population.size(); i++)
		total += population[i].getFitness();
	
	return total / (float) population.size();
}

vector< vector<float> > Population::allValues()
{
	int N_ind = int(population.size());
	int N_genes = int(population[0].getValues().size());
	vector< vector<float> > all (N_ind, vector<float> (N_genes));
	
	for (int i = 0; i < N_ind; i++) {
		for (int j = 0; j < N_genes; j++) {
			all[i][j] = population[i][j];
		}
	}
	
	return all;
}

void Population::naturalSelection()
{
	for (int i = 0; i < population.size(); i++)
	{
		float fitness = population[i].getFitness();
		int percentage = int(fitness * 100);
		
		for (int j = 0; j < percentage; j++)
			pool.push_back(population[i]);
	}
}
