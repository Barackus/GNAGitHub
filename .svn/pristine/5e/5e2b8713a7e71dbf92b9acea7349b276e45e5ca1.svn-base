#ifndef OVERMINDFITNESSFUNCTOR_H
#define OVERMINDFITNESSFUNCTOR_H

#include "../../Genetic Algorithm/fitnessfunctor.h"

#include "../../World/src/world.h"
#include "../../Boids/src/boids.h"
#include "../../Neural Network/src/neuralnetwork.h"

/**
 * 
 **/
class OvermindFitnessFunctor : public FitnessFunctor {
private:
	DiscreteWorld2D* _world;
	BoidSystem2f* _bs;
	MLPerceptron5d* _mlp;
public:
	OvermindFitnessFunctor(DiscreteWorld2D*, BoidSystem2f*, MLPerceptron5d*);
	double operator()(individual&);
};

#endif