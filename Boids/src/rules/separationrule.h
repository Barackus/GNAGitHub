#ifndef SEPARATIONRULE_H
#define SEPARATIONRULE_H

#define SEPARATION_WEIGHT	2.00f
#define SEPARATION_RADIUS	1.0f

#include "../boidrule.h"

#include "../boid.h"
#include "../boidsystem.h"

/**
 * 
 **/
template<typename T, int D>
class SeparationRule : public BoidRule<T, D> {
private:
	pmVector<T>* calculate(void);
public:
	SeparationRule(Boid<T, D>*, BoidSystem<T, D>*);
};

/**
 * 
 **/
template<typename T, int D>
SeparationRule<T, D>::SeparationRule(Boid<T, D>* boid, BoidSystem<T, D>* bs)
	:	BoidRule<T, D>(boid, bs, SEPARATION_WEIGHT) {}

/**
 * 
 **/
template<typename T, int D>
pmVector<T>* SeparationRule<T, D>::calculate(void) {
	_result->fill(0);
	// Get closest neighbors.
	std::vector<Boid<T, D>*> neighbors =
		_boid->getNeighbors(SEPARATION_RADIUS);
	// Calculate escape vector.
	std::vector<Boid<T, D>*>::iterator it;
	for(it = neighbors.begin(); it != neighbors.end(); ++it) {
		if((*it)->isAlive() && !(*it)->isSaved()) {
			pmVector<T> dist = *_boid->getpmPosition() - *(*it)->getpmPosition();
			if(!dist.isNil()) {
				T factor = (T(SEPARATION_RADIUS) - dist.magnitude()) / T(SEPARATION_RADIUS);
				factor *= factor;
				if(factor < 0) factor = 0;
				_result->add(dist.normalize(factor));
			}
		}
	}
	// Return normalized and weighted escape vector.
	if(!_result->isNil())
		_result->normalize(_weight);
	return _result;
}

#endif