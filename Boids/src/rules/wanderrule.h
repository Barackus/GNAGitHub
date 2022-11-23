#ifndef WANDERRULE_H
#define WANDERRULE_H

#define WANDER_WEIGHT	0.50f
#define WANDER_CYCLES	500

#include "../boidrule.h"

#include "../boid.h"
#include "../boidsystem.h"

/**
 * 
 **/
template<typename T, int D>
class WanderRule : public BoidRule<T, D> {
	pmVector<T>* calculate(void);
private:
	int _wait;
public:
	WanderRule(Boid<T, D>*, BoidSystem<T, D>*);
};

/**
 * 
 **/
template<typename T, int D>
WanderRule<T, D>::WanderRule(Boid<T, D>* boid, BoidSystem<T, D>* bs)
	:	BoidRule<T, D>(boid, bs, WANDER_WEIGHT),
		_wait(0) {}

/**
 * 
 **/
template<typename T, int D>
pmVector<T>* WanderRule<T, D>::calculate(void) {
	// New heading.
	if(_wait <= 0) {
		_result->fill(0);
		_wait = WANDER_CYCLES + rand() % WANDER_CYCLES;
		for(int i = 0; i < D; ++i)
			_result->set(T(rand() - 0.5 * RAND_MAX), i);
		_result->normalize(_weight);
	} else
		--_wait;
	// Return the current heading.
	return _result;
}

#endif