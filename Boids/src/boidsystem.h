#ifndef BOIDSYSTEM_H
#define BOIDSYSTEM_H

#define NUM_BOIDS_0	32
#define NUM_BOIDS_1	8
#define NUM_BOIDS_2	0

#define BS_SEED		0

#define NUM_BOIDS	NUM_BOIDS_0 + NUM_BOIDS_1 + NUM_BOIDS_2

#include <vector>

#include "boid.h"

#include "rules/separationrule.h"
#include "rules/alignmentrule.h"
#include "rules/cohesionrule.h"
#include "rules/wanderrule.h"
#include "rules/targetrule.h"
#include "rules/pressurerule.h"
#include "rules/fearrule.h"
#include "rules/obstaclerule.h"
#include "rules/bombrule.h"
#include "rules/pushrule.h"
#include "rules/brainrule.h"
#include "rules/saferule.h"
#include "rules/scriptedbrainrule.h"

template<int D> class DiscreteWorld;

/**
 * 
 **/
template<typename T, int D>
class BoidSystem {
protected:
	DiscreteWorld<D>* _world;
	std::vector<Boid<T, D>*> _boids;
	int _nrOfSavedBoids;

protected:
	int _totalHealth;

public:
	BoidSystem(void) : _nrOfSavedBoids(0) { }
public:
	virtual void update(void);
	virtual void initialize(DiscreteWorld<D>* = NULL);
	void reset(void);
protected:
	void addBoid(Boid<T, D>*);
	void addRules(DiscreteWorld<D>* = NULL);
public:
	std::vector<Boid<T, D>*> getBoids(ColonyID = ANY);
public:
	int getTotalBoidHealth(ColonyID = ANY); 
	const int countBoids(ColonyID, bool = false);
	inline void increaseSaved() {
		++_nrOfSavedBoids;
		//std::cout << _nrOfSavedBoids << std::endl;
	}
	inline void decreaseSaved() {
		--_nrOfSavedBoids;
	}

	inline int getNrOfSavedBoids() {
		return _nrOfSavedBoids;
	}
};

/**
 * 
 **/
template<typename T, int D>
int BoidSystem<T, D>::getTotalBoidHealth(ColonyID cid) {
	std::vector<Boid<T, D>*>::iterator it;
	_totalHealth = 0;
	for(it = _boids.begin(); it != _boids.end(); ++it){
		//if a boid is alive and of the right colony id, count its health.
		if((*it)->isAlive() && (*it)->getColonyID() == cid ) _totalHealth += (*it)->getHealth(); 
	}
	return _totalHealth;
}

/**
 * 
 **/
template<typename T, int D>
void BoidSystem<T, D>::update(void) {
	std::vector<Boid<T, D>*>::iterator it;
	for(it = _boids.begin(); it != _boids.end(); ++it)
		(*it)->update();
}

/**
 * 
 **/
template<typename T, int D>
void BoidSystem<T, D>::initialize(DiscreteWorld<D>* world) {
	srand(BS_SEED);
	
	_world = world;
	T area = T(min(world->width(), world->height()));
	// Add a number of boids to the system.
	for(int i = 0; i < NUM_BOIDS; ++i) {
		int cid = i < NUM_BOIDS_0 ? 0 :
			(i < NUM_BOIDS_0 + NUM_BOIDS_1 ? 1 : 2);
		addBoid(new Boid<T, D>(this, cid));
		// Random position.
		pmPosition<T, D> pos;
		pmAcceleration<T, D>* check;
		do {
			
			for(int j = 0; j < D; ++j) {
				pos.set(0.8f * area * ((T(rand()) / RAND_MAX) - T(0.5f)), j);
			}
			
			check = world->getProximity(pos);
		} while(check->magnitude() < T(0.5));
		_boids[i]->setpmPosition(pos);
		// Random velocity.
		pmVelocity<T, D> vel;
		for(int j = 0; j < D; ++j) {
			vel.set((T(rand()) / RAND_MAX) - T(0.5f), j);
		}
		_boids[i]->setpmVelocity(vel);
	}
	
	// Add all rules to all boids.
	addRules(world);
	// Let all boids see their neighbors.
	for(int i = 0; i < NUM_BOIDS; ++i)
		_boids[i]->initializeNeighbors();
}

/**
 * 
 **/
template<typename T, int D>
void BoidSystem<T, D>::reset(void) {
	_boids.clear();
	initialize(_world);
	_nrOfSavedBoids = 0;
}

/**
 *
 **/
template<typename T, int D>
void BoidSystem<T, D>::addBoid(Boid<T, D>* boid) {
	_boids.push_back(boid);
}

/**
 * 
 **/
template<typename T, int D>
void BoidSystem<T, D>::addRules(DiscreteWorld<D>* world) {
	ColonyID cid;
	std::vector<Boid<T, D>*>::iterator it;
	for(it = _boids.begin(); it != _boids.end(); ++it) {
		cid = (*it)->getColonyID();
		(*it)->addRule(new SeparationRule<T, D>(*it, this));
		(*it)->addRule(new AlignmentRule<T, D>(*it, this));
		if(cid != HOSTILE) {
			(*it)->addRule(new CohesionRule<T, D>(*it, this));
		}
		(*it)->addRule(new WanderRule<T, D>(*it, this));
		//(*it)->addRule(new TargetRule<T, D>(*it, this));
		(*it)->addRule(new PressureRule<T, D>(*it, this));
		(*it)->addRule(new BombRule<T, D>(*it, this, world));
		if(cid == NEUTRAL) {
			//(*it)->addRule(new FearRule<T, D>(*it, this));
			(*it)->addRule(new PushRule<T, D>(*it, this));
			(*it)->addRule(new SafeRule<T, D>(*it, this, world));
		}
		(*it)->addRule(new ObstacleRule<T, D>(*it, this, world));
		// Add a brain to every friendly boid.
		if(cid == FRIENDLY) {
			//(*it)->addRule(new Scriptedbrainrule<T, D>(*it, this, world));
			BrainRule<T, D>* brain = new BrainRule<T, D>(*it, this);
			(*it)->addRule(brain);
			(*it)->setBrain(brain);
		}
	}
}

/**
 * 
 **/
template<typename T, int D>
std::vector<Boid<T, D>*> BoidSystem<T, D>::getBoids(ColonyID cid) {
	if(cid == ANY)
		return _boids;
	std::vector<Boid<T, D>*> result;
	std::vector<Boid<T, D>*>::iterator it;
	for(it = _boids.begin(); it != _boids.end(); ++it)
		if((*it)->getColonyID() == cid)
			result.push_back(*it);
	return result;
}

/**
 * 
 **/
template<typename T, int D>
const int BoidSystem<T, D>::countBoids(ColonyID cid, bool only_alive) {
	if(cid == ANY)
		return _boids.size();
	int counter = 0;
	std::vector<Boid<T, D>*>::iterator it;
	for(it = _boids.begin(); it != _boids.end(); ++it) {
		if((*it)->getColonyID() == cid) {
			if(only_alive)
				counter += (*it)->isAlive() ? 1 : 0;
			else
				++counter;
		}
	}
	return counter;
}

#endif