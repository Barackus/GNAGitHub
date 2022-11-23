#ifndef OBSTACLERULE_H
#define OBSTACLERULE_H

#define OBSTACLE_WEIGHT	128.00f
#define OBSTACLE_RADIUS	0.5f

#include "../boidrule.h"

#include "../boid.h"
#include "../boidsystem.h"

#include "../../../World/src/world.h"

/**
 * 
 **/
template<typename T, int D>
class ObstacleRule : public BoidRule<T, D> {
private:
	DiscreteWorld<D>* _world;
	pmVector<T>* calculate(void);
public:
	ObstacleRule(Boid<T, D>*, BoidSystem<T, D>*, DiscreteWorld<D>*);
};

/**
 * 
 **/
template<typename T, int D>
ObstacleRule<T, D>::ObstacleRule(Boid<T, D>* boid, BoidSystem<T, D>* bs, DiscreteWorld<D>* world)
	:	BoidRule<T, D>(boid, bs, FEAR_WEIGHT),
		_world(world) {}

/**
 * 
 **/
template<typename T, int D>
pmVector<T>* ObstacleRule<T, D>::calculate(void) {
	*_result = *(_world->getProximity(*(_boid->getpmPosition())));
	T mag = _result->magnitude();
	// Handle collisions.
	if(mag == 0) {
		pmPosition<T, D>* pos = _boid->getpmPosition();
		pmVelocity<T, D>* vel = _boid->getpmVelocity();
		pmAcceleration<T, D>* acc = _boid->getpmAcceleration();
		vel->scale(pmScalar<T>(1.001f));
		pos->subtract(*vel);	// Step back.
		vel->fill(T());			// Lose speed.
		acc->fill(T());
	}
	// Ignore walls outside radius.
	if(mag > OBSTACLE_RADIUS)
		_result->fill(T());
	// Move away from walls.
	_result->set(-_result->get(1), 1);
	_result->scale(pmScalar<T>(T(OBSTACLE_WEIGHT)));
	return _result;
}

#endif