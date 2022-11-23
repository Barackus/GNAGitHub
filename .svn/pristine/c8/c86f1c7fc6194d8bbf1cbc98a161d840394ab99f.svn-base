#ifndef FEARRULE_H
#define FEARRULE_H

#define FEAR_WEIGHT	5.00f
#define FEAR_RADIUS	3.0f
#define FEAR_FACTOR	0.10f

#include "../boidrule.h"

#include "../boid.h"
#include "../boidsystem.h"

/**
 * 
 **/
template<typename T, int D>
class FearRule : public BoidRule<T, D> {
private:
	pmVector<T>* calculate(void);
public:
	FearRule(Boid<T, D>*, BoidSystem<T, D>*);
};

/**
 * 
 **/
template<typename T, int D>
FearRule<T, D>::FearRule(Boid<T, D>* boid, BoidSystem<T, D>* bs)
	:	BoidRule<T, D>(boid, bs, FEAR_WEIGHT) {}

/**
 * 
 **/
template<typename T, int D>
pmVector<T>* FearRule<T, D>::calculate(void) {
	_result->fill(0);
	// Get closest neighbors.
	std::vector<Boid<T, D>*> neighbors =
		_boid->getNeighbors(FEAR_RADIUS, HOSTILE);
	// Calculate escape vector.
	std::vector<Boid<T, D>*>::iterator it;
	for(it = neighbors.begin(); it != neighbors.end(); ++it) {
		pmVector<T> dist = *_boid->getpmPosition() - *(*it)->getpmPosition();
		if(!dist.isNil()) {
			T factor = (T(FEAR_RADIUS) - dist.magnitude()) / T(FEAR_RADIUS);
			factor *= factor;
			if(factor < 0) factor = 0;
			_result->add(dist.normalize(factor));
		}
	}
	// Return normalized and weighted escape vector.
	if(!_result->isNil())
		_result->normalize(_weight);
	T handicap = _boid->getHandicap() + _result->magnitude() * FEAR_FACTOR;
	if(handicap > 1)
		handicap = 1;
	_boid->setHandicap(handicap);
	return _result;
}

#endif