#ifndef TARGETRULE_H
#define TARGETRULE_H

#define TARGET_WEIGHT	1.00f
#define TARGET_RADIUS	50.0f

#include "../boidrule.h"

#include "../boid.h"
#include "../boidsystem.h"

/**
 * 
 **/
template<typename T, int D>
class TargetRule : public BoidRule<T, D> {
	pmVector<T>* calculate(void);
private:
	pmPosition<T, D>* _target;
public:
	inline void setTarget(pmPosition<T, D> target) { *_target = target; }
	TargetRule(Boid<T, D>*, BoidSystem<T, D>*);
};

/**
 * 
 **/
template<typename T, int D>
TargetRule<T, D>::TargetRule(Boid<T, D>* boid, BoidSystem<T, D>* bs)
	:	BoidRule<T, D>(boid, bs, TARGET_WEIGHT),
		_target(new pmPosition<T, D>) {}

/**
 * 
 **/
template<typename T, int D>
pmVector<T>* TargetRule<T, D>::calculate(void) {
	// Determine vector to center.
	*_result = *_target - *_boid->getpmPosition();
	T factor = _result->magnitude() / TARGET_RADIUS;
	// Return weighted and normalized vector to center.
	if(!_result->isNil())
		_result->normalize(_weight * factor);
	return _result;
}

#endif