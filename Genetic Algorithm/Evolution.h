#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <vector>

struct individual {
	std::vector<double> genes; //the initial values of all nodes (with size nrOfNodes).
	double fitness;
};

class FitnessFunctor;

class Evolution {

public:
	Evolution(FitnessFunctor*, int);
	~Evolution(void);

public:
	void train();
	int readFromFile(); //manipulates pop by inputting the latest genes, or puts in random genes if there is no EVOLUTION_RESULTS.txt file.
	inline std::vector<individual>* getPopulation() {
		return &pop;
	}

private:
	FitnessFunctor* _fitnessFunction; // Can be executed for each individual

	int nrOfNodes; //total number of nodes of a single Neural Network.
	int genSize; //the size of each generation
	int survivorSize; //the number of survivors in each generation
	int nrOfGens; //the total number of generations before the algorithm stops.
	int allSlices; //the total number of slices to mate defined by genSize * (genSize+1) / 2
	double mutationProbability; //the probability that a single gene is replaced 
	int seed;

	std::vector<std::vector<double>> simplepop; //the current entire population
	std::vector<individual> pop;
	
	std::vector<double> createRandomGenome();
	void makeBabies(std::vector<individual>& pop);
	void writeToFile(int GenerationNumber,std::vector<individual>& pop, int seed);
	int readFromFile(std::vector<individual>& pop); //manipulates pop by inputting the latest genes, or puts in random genes if there is no EVOLUTION_RESULTS.txt file.
};

#endif