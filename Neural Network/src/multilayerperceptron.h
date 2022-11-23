#ifndef MULTILAYERPERCEPTRON_H
#define MULTILAYERPERCEPTRON_H

#include <cstdarg>
#include <vector>

#include "../../PhysMath/src/physmath.h"

/**
 * 
 **/
template<typename T, int L>
class MultilayerPerceptron {
private:
	std::vector<pmVector<T>*> _activations;
	std::vector<pmMatrix<T>*> _weights;
	void activate(int, int);
public:
	const int countConnections(void);
	void setWeights(std::vector<T>&);
public:
	MultilayerPerceptron(int, ...);
	~MultilayerPerceptron(void);
	pmVector<T> process(pmVector<T>&);
	void randomize(void);
	void printCompleteStatus(void);
};

/**
 * 
 **/
template<typename T, int L>
MultilayerPerceptron<T, L>::MultilayerPerceptron(int n, ...) {
	// Ensure we have at least two layers (input + output).
	if(L < 2)
		throw;
	// Process variable number of arguments.
	va_list va;
	va_start(va, n);
	_activations.push_back(new pmVector<T>(n));
	int d;
	for(int i = 1; i < L; ++i) {
		// Get next argument.
		d = va_arg(va, int);
		// Must have at least one node in a layer.
		if(d < 1)
			throw;
		// Load new activation vectors.
		_activations.push_back(new pmVector<T>(d));
		// Load new weight matrix.
		_weights.push_back(new pmMatrix<T>(n, d));
		n = d;
	}
	// Clean up variable argument list.
	va_end(va);
}

/**
 * 
 **/
template<typename T, int L>
MultilayerPerceptron<T, L>::~MultilayerPerceptron(void) {
	// Clean up activation vectors.
	std::vector<pmVector<T>*>::iterator ait;
	for(ait = _activations.begin(); ait != _activations.end(); ++ait)
		delete *ait;
	// Clean up weight matrices.
	std::vector<pmMatrix<T>*>::iterator wit;
	for(wit = _weights.begin(); wit != _weights.end(); ++wit)
		delete *wit;
}

/**
 * 
 **/
template<typename T, int L>
void MultilayerPerceptron<T, L>::activate(int layer, int node) {
	// Input layer cannot be activated.
	if(layer <= 0)
		throw;
	// Shortcuts.
	pmMatrix<T>* weights = _weights[layer - 1];
	pmVector<T>* prev = _activations[layer - 1];
	// Calculate raw weighted activation.
	T activation = 0;

	for(int i = 0; i <  weights->getNumColumns(); ++i)
		activation += weights->get(i, node) * prev->get(i);
	// Apply activation function and store.
	_activations[layer]->set(tanh(activation / weights->getNumColumns()), node);
}

/**
 * 
 **/
template<typename T, int L>
const int MultilayerPerceptron<T, L>::countConnections(void) {
	int count = 0;
	std::vector<pmMatrix<T>*>::iterator it;
	for(it = _weights.begin(); it != _weights.end(); ++it)
		count += (*it)->getSize();
	return count;
}

/**
 * 
 **/
template<typename T, int L>
void MultilayerPerceptron<T, L>::setWeights(std::vector<T>& weights) {
	int rows, cols, count = -1;
	std::vector<pmMatrix<T>*>::iterator wit;
	for(wit = _weights.begin(); wit != _weights.end(); ++wit) {
		rows = (*wit)->getNumRows(), cols = (*wit)->getNumColumns();
		for(int r = 0; r < rows; ++r)
			for(int c = 0; c < cols; ++c)
				(*wit)->set(weights[++count], c, r);
	}
}

/**
 * 
 **/
template<typename T, int L>
pmVector<T> MultilayerPerceptron<T, L>::process(pmVector<T>& input) {
	// Clamp input activations.
	*_activations[0] = input;
	// Feed forward.
	int layers = _activations.size(), nodes;
	for(int layer = 1; layer < layers; ++layer) {
		nodes = _activations[layer]->getSize();
		for(int node = 0; node < nodes; ++node)
			activate(layer, node);
	}
	return *(_activations.back());
}

/**
 * 
 **/
template<typename T, int L>
void MultilayerPerceptron<T, L>::randomize(void) {
	int rows, cols;
	std::vector<pmMatrix<T>*>::iterator wit;
	for(wit = _weights.begin(); wit != _weights.end(); ++wit) {
		rows = (*wit)->getNumRows(), cols = (*wit)->getNumColumns();
		for(int r = 0; r < rows; ++r)
			for(int c = 0; c < cols; ++c)
				(*wit)->set(2 * (T(rand()) / RAND_MAX) - 1, c, r);
	}
}

/**
 * 
 **/
template<typename T, int L>
void MultilayerPerceptron<T, L>::printCompleteStatus(void) {
	cout << "ACTIVATIONS:" << endl;
	std::vector<pmVector<T>*>::iterator ait;
	for(ait = _activations.begin(); ait != _activations.end(); ++ait)
		cout << **ait << endl;
	cout << "WEIGHTS:" << endl;
	std::vector<pmMatrix<T>*>::iterator wit;
	for(wit = _weights.begin(); wit != _weights.end(); ++wit)
		cout << **wit << endl;
}

#endif