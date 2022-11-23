#ifndef BRAINRULE_H
#define BRAINRULE_H

#define BRAIN_WEIGHT	0.1f

#include "../boidrule.h"

#include "../boid.h"
#include "../boidsystem.h"

/**
 * 
 **/
template<typename T, int D>
class BrainRule : public BoidRule<T, D> {
private:
	pmVector<T> _target;
	pmVector<T>* calculate(void);
public:
	BrainRule(Boid<T, D>*, BoidSystem<T, D>*);
	inline void setTarget(const pmVector<T>& target) { _target = target; }
};

/**
 * 
 **/
template<typename T, int D>
BrainRule<T, D>::BrainRule(Boid<T, D>* boid, BoidSystem<T, D>* bs)
	:	BoidRule<T, D>(boid, bs, BRAIN_WEIGHT),
		_target(D) {}

/**
 * 
 **/
template<typename T, int D>
pmVector<T>* BrainRule<T, D>::calculate(void) {
	_result->fill(T());
	// Apply target thoughts ;-)
	_result->add(_target);

	// Normalize and return.
	if (!_result->isNil()) 
		_result->normalize(_weight);
	return _result;
}

#endif