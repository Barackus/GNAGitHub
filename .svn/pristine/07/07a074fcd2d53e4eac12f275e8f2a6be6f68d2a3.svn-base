#ifndef VOIDRULE_H
#define VOIDRULE_H

#define VOID_WEIGHT	1.00f

#include "../boidrule.h"

#include "../boid.h"
#include "../boidsystem.h"

/**
 * 
 **/
template<typename T, int D>
class VoidRule : public BoidRule<T, D> {
	pmVector<T>* calculate(void);
public:
	VoidRule(Boid<T, D>*, BoidSystem<T, D>*);
};

/**
 * 
 **/
template<typename T, int D>
VoidRule<T, D>::VoidRule(Boid<T, D>* boid, BoidSystem<T, D>* bs)
	:	BoidRule<T, D>(boid, bs, VOID_WEIGHT) {}

/**
 * 
 **/
template<typename T, int D>
pmVector<T>* VoidRule<T, D>::calculate(void) {
	// TODO: Implement.
	_result->normalize(_weight);
	return _result;
}

#endif