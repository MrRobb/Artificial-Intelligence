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
	
public:
	/**
	 @brief Creates an empty Population.
	 */
	Population();
	
	/**
	 @brief Creates a Population with N_ind individuals with random genes.
	 @param N_genes Number of genes of each individual.
	 @param N_ind Number of individuals.
	 @param mutationRate Probability of mutating a gene, between 0 and 1.
	 @param generation Number of the generation.
	 */
	Population(int N_genes, int N_ind, float mutationRate, unsigned int generation);
	
	/**
	 @brief Access the individual directly.
	 @pre i must be between 0 and N_ind-1.
	 @param i Position of the Individual.
	 @return The individual at position i.
	 */
	DNA& operator[](int i);
	
	/**
	 @brief Calculates the fitness of the population.
	 @param scores Vector containing the scores of all of the individuals.
	 */
	void calculateFitness(vector<int> scores);
	
	/**
	 @brief Generates the next generation.
	 @pre calculateFitness have already been executed.
	 @pre Population has at least one individual.
	 @return The next generation.
	 */
	Population generate();
	
	/**
	 @brief Get position of the fittest individual. In case of having more than one, the first one is returned.
	 @return The position of the fittest.
	 */
	int getBest();
	
	/**
	 @brief Get the number of the generation.
	 @return The number of the generation.
	 */
	int getGenerations();
	
	/**
	 @brief Get the average fitness of the population.
	 @return The average fitness of the population, between 0 and 1.
	 */
	float getAverage();
	
	/**
	 @brief Get all of the genes of the individuals.
	 @return Vector of vector of genes. Each vector represents an individual. Each value represents a gene.
	 */
	vector< vector<float> > allValues();
	
private:
	
	/// @brief Probability of mutation between 0 and 1.
	float mutationRate;
	
	/// @brief Contains all of the individuals.
	vector<DNA> population;
	
	/// @brief Creates a temporary reproduction pool.
	vector<DNA> pool;
	
	/// @brief Number of the generation.
	unsigned int generation;
	
	/**
	 @brief Fills the reproduction pool based on the fitness of every individual. The fittest have more probabilities of being selected out of the reproduction pool.
	 */
	void naturalSelection();
	
};

#endif /* Population_hpp */
