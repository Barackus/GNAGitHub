#ifndef SCRIPTEDBRAINRULE_H
#define SCRIPTEDBRAINRULE_H

#define GUARD_RADIUS 1.5
#define GUARD_CHANCE 1.0
#define SCRIPTEDBRAINRULE_WEIGHT 5

#include "../boidrule.h"

#include "../boid.h"
#include "../boidsystem.h"

/**
 * 
 **/
template<typename T, int D>
class Scriptedbrainrule : public BoidRule<T, D> {
	pmVector<T>* calculate(void);
private:
	//pmPosition<T, D>* _target;
	DiscreteWorld<D>* _world;

public:
	Scriptedbrainrule(Boid<T, D>*, BoidSystem<T, D>*, DiscreteWorld<D>*);
	//inline void setTarget(pmPosition<T, D> target) { *_target = target; }
	//TargetRule(Boid<T, D>*, BoidSystem<T, D>*);


};

/**
 * 
 **/
template<typename T, int D>
Scriptedbrainrule<T, D>::Scriptedbrainrule(Boid<T, D>* boid, BoidSystem<T, D>* bs, DiscreteWorld<D>* world)
	:	BoidRule<T, D>(boid, bs, FEAR_WEIGHT),
		_world(world) {}

/**
 * 
 **/
template<typename T, int D>
pmVector<T>* Scriptedbrainrule<T, D>::calculate(void) {

	//*_result = *(( -*(_boid->getpmPosition())));
	float decision = float(rand())/ RAND_MAX;

	if(decision < GUARD_CHANCE){
		pmPosition2f guardPosition;
		T bombrange = _world->getBombs()->at(0).getRange();
		T saferange = bombrange + T(GUARD_RADIUS);
		guardPosition.set(((T(rand()) / (RAND_MAX * 0.5f))-1),0); //a random unitvector times
		guardPosition.set(((T(rand()) / (RAND_MAX * 0.5f))-1),1);
		guardPosition.normalize(saferange); //normalize it to a safe range, so the desired position should be around the bomb.
		
		pmPosition2f bombpos = _world->getBombs()->at(0).getpmPosition();
		guardPosition += bombpos; //translate the guardposition to the bomb
		*_result = guardPosition - *(_boid->getpmPosition());
		_result->scale(pmScalar<T>(T(SCRIPTEDBRAINRULE_WEIGHT)));

	}
	
	else {
		pmPosition2f noDirection;
		noDirection.set(0,0);
		noDirection.set(0,1);
		*_result = noDirection;
	}
	
	//*_result = *( -*(_boid->getpmPosition());



	//_world->
	/*
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
	*/
	return _result;
}

#endif