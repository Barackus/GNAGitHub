#ifndef BOIDRULE_H
#define BOIDRULE_H

#include "../../PhysMath/src/physmath.h"

template<typename T, int D> class Boid;
template<typename T, int D> class BoidSystem;

/**
 * 
 **/
template<typename T, int D>
class BoidRule {
protected:
	Boid<T, D>* _boid;
	BoidSystem<T, D>* _bs;
	T _weight;
	pmVector<T>* _result;
public:
	BoidRule(Boid<T, D>*, BoidSystem<T, D>*, T = 1);
	virtual ~BoidRule(void);
	pmVector<T>* operator()(void);
private:
	virtual pmVector<T>* calculate(void) = 0;
};

/**
 * 
 **/
template<typename T, int D>
BoidRule<T, D>::BoidRule(Boid<T, D>* boid, BoidSystem<T, D>* bs, T weight)
	:	_boid(boid), _bs(bs), _weight(weight),
		_result(new pmVector<T>(D)) {}

/**
 * 
 **/
template<typename T, int D>
BoidRule<T, D>::~BoidRule(void) {
	delete _result;
}

/**
 * 
 **/
template<typename T, int D>
pmVector<T>* BoidRule<T, D>::operator()(void) {
	return calculate();
}

#endif