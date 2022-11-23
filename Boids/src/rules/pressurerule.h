#ifndef PRESSURERULE_H
#define PRESSURERULE_H

#define PRESSURE_WEIGHT			0.00f
#define PRESSURE_RADIUS			1.0f
#define PRESSURE_MAX_NEIGHBORS	10
#define PRESSURE_MAX_HANDICAP	0.90f

#include "../boidrule.h"

#include "../boid.h"
#include "../boidsystem.h"

/**
 * 
 **/
template<typename T, int D>
class PressureRule : public BoidRule<T, D> {
	pmVector<T>* calculate(void);
public:
	inline void setTarget(pmPosition<T, D> target) { *_target = target; }
	PressureRule(Boid<T, D>*, BoidSystem<T, D>*);
};

/**
 * 
 **/
template<typename T, int D>
PressureRule<T, D>::PressureRule(Boid<T, D>* boid, BoidSystem<T, D>* bs)
	:	BoidRule<T, D>(boid, bs, PRESSURE_WEIGHT) {}

/**
 * 
 **/
template<typename T, int D>
pmVector<T>* PressureRule<T, D>::calculate(void) {
	// Get number of neighboring boids.
	int neighbors = 0;
	std::vector<Boid<T, D>*> boids = _boid->getNeighbors(PRESSURE_RADIUS);
	std::vector<Boid<T, D>*>::iterator it;
	for(it = boids.begin(); it != boids.end(); ++it)
		if((*it)->getHealth() > 0)
			++neighbors;
	T pressure = T(neighbors) / PRESSURE_MAX_NEIGHBORS;
	pressure *= pressure;
	if(pressure >= 1)
		pressure = 1;
	if(pressure == 1)
		_boid->setHealth(_boid->getHealth() - 1);
	_boid->setHandicap(1 - pressure * PRESSURE_MAX_HANDICAP);
	// Return nil vector.
	return _result;
}

#endif