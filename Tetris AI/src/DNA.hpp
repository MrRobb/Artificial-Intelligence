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
#include <vector>

using namespace std;

class DNA {
	
public:
	
	/**
	 @brief Creates an empty DNA.
	 */
	DNA();
	
	/**
	 @brief Creates a DNA with a length with random genes between -1 and 1.
	 @param length Size of the genes container.
	 */
	DNA(int length);
	
	/**
	 @brief Set custom values to the genes.
	 @pre Must have the same lenght as the initial genes.
	 @param v It will be the genes of the individual.
	 */
	void operator=(const vector<float>& v);
	
	/**
	 @brief Access the genes directly.
	 @pre i must be between 0 and lenght-1.
	 @param i Position of the gene.
	 @return The gene at position i.
	 */
	float& operator[](int i);
	
	/**
	 @brief Get all of the genes at once.
	 @return A vector containing all of its genes.
	 */
	vector<float> getValues();
	
	/**
	 @brief Calculates the relative fitness of the individual.
	 @param score The score of the individual.
	 @param max_score Is the maximum score possible
	 		or the maximum score of the generation.
	 */
	void fitness(int score, int max_score);
	
	/**
	 @brief Get the fitness of the individual.
	 @pre Fitness function has been already executed.
	 @return The fitness of the individual.
	 @see DNA::fitness
	 */
	float getFitness();
	
	/**
	 @brief Creates a child with mixed genes via crossover.
	 @f$ itself + partner = child @f$
	 @param partner It will provide some genetic information.
	 @return The child.
	 */
	DNA crossover(DNA &partner);
	
	/**
	 @brief May mutate some gene of the individual.
	 @param mutationRate probability of mutation between 0 and 1.
	 */
	void mutate(float mutationRate);
	
private:
	
	/// @brief Contains the genetic information
	vector<float> genes;
	
	/// @brief Contains the fitness of the individual.
	float my_fitness;
};

#endif /* DNA_hpp */
