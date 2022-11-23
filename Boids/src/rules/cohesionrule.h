#ifndef COHESIONRULE_H
#define COHESIONRULE_H

#define COHESION_WEIGHT	1.00f
#define COHESION_RADIUS	4.0f

#include "../boidrule.h"

#include "../boid.h"
#include "../boidsystem.h"

/**
 * 
 **/
template<typename T, int D>
class CohesionRule : public BoidRule<T, D> {
	pmVector<T>* calculate(void);
public:
	CohesionRule(Boid<T, D>*, BoidSystem<T, D>*);
};

/**
 * 
 **/
template<typename T, int D>
CohesionRule<T, D>::CohesionRule(Boid<T, D>* boid, BoidSystem<T, D>* bs)
	:	BoidRule<T, D>(boid, bs, COHESION_WEIGHT) {}

/**
 * 
 **/
template<typename T, int D>
pmVector<T>* CohesionRule<T, D>::calculate(void) {
	_result->fill(0);
	// Get neighboring boids.
	std::vector<Boid<T, D>*> neighbors =
		_boid->getNeighbors(COHESION_RADIUS, _boid->getColonyID());
	// Determine average position.
	std::vector<Boid<T, D>*>::iterator it;
	int count = 0;
	for(it = neighbors.begin(); it != neighbors.end(); ++it) {
		_result->add(*(*it)->getpmPosition());
		++count;
	}
	_result->scale(pmScalar<T>(T(1) / count));
	// Determine vector to center.
	_result->subtract(*_boid->getpmPosition());
	// Return weighted and normalized vector to center.
	if(!_result->isNil())
		_result->normalize(_weight);
	return _result;
}

#endif