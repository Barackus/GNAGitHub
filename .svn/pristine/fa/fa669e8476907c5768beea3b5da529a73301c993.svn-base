#ifndef SAFERULE_H
#define SAFERULE_H

#define SAFE_WEIGHT	8.00f
#define SAFE_FACTOR	0.20f

#include "../boidrule.h"

#include "../boid.h"
#include "../boidsystem.h"

#include "../../../World/src/world.h"

/**
 * 
 **/
template<typename T, int D>
class SafeRule : public BoidRule<T, D> {
private:
	DiscreteWorld<D>* _world;
	pmVector<T>* calculate(void);
public:
	SafeRule(Boid<T, D>*, BoidSystem<T, D>*, DiscreteWorld<D>*);
};

/**
 * 
 **/
template<typename T, int D>
SafeRule<T, D>::SafeRule(Boid<T, D>* boid, BoidSystem<T, D>* bs, DiscreteWorld<D>* world )
	:	BoidRule<T, D>(boid, bs, SAFE_WEIGHT),
		_world(world) {}

/**
 * 
 **/
template<typename T, int D>
pmVector<T>* SafeRule<T, D>::calculate(void) {
	_result->fill(0);
	if(_boid->getColonyID() == NEUTRAL) {
		// Get list of safe zones
		std::vector<pmPosition2f*> safezones = *_world->getSafezones();
		// Calculate escape vector.
		std::vector<pmPosition2f*>::iterator it;
		for(it = safezones.begin(); it != safezones.end(); ++it) {
			pmVector<T> dist = *_boid->getpmPosition() - (*(*it));

			// The boid is saved if it is inside the safe zone.
			if (dist.magnitude() < 0.5f) {
				_boid->setSaved(true);
			}
		}
	}
	return _result;
}

#endif