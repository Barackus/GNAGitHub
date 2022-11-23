#ifndef BOID_H
#define BOID_H

#define RECALCULATE			1
#define CYCLES_PER_SEC		12		// Hz

#define RUNNING_SPEED		2.5		// m/s
#define WALKING_SPEED		1.5		// m/s
#define ACCELERATION		0.5		// m/s^2

#define MAX_WALK_SPEED		WALKING_SPEED / CYCLES_PER_SEC
#define MAX_RUN_SPEED		RUNNING_SPEED / CYCLES_PER_SEC
#define MAX_ACCELERATION	ACCELERATION / CYCLES_PER_SEC

#include <vector>

#include "../../PhysMath/src/physmath.h"

#include "boidrule.h"

template<typename T, int D> class BrainRule;

typedef int ColonyID;
enum ColonyType { ANY = -1, NEUTRAL = 0, FRIENDLY = 1, HOSTILE = 2 };

template<typename T, int D> class BoidSystem;

/**
 * 
 **/
template<typename T, int D>
class Boid {
private:
	int _health;
	bool _saved;
	BoidSystem<T, D>* _bs;
	ColonyID _cid;
	std::vector<BoidRule<T, D>*> _rules;
	BrainRule<T, D>* _brain;
	int _recalculate;
private:
	pmPosition<T, D>* _pos;
	pmOrientation<T, D>* _ori;
	pmVelocity<T, D>* _vel;
	pmAcceleration<T, D>* _acc;
	T _walk_speed, _run_speed, _max_acceleration, _handicap;
public:
	inline const ColonyID getColonyID(void) const { return _cid; }
	inline const bool isAlive(void) const { return _health > 0; }
	inline const int getHealth(void) const { return _health; }
	inline BrainRule<T, D>* getBrain(void) const { return _brain; }
	inline bool isSaved() { return _saved; }
	inline pmPosition<T, D>* getpmPosition(void) const { return _pos; }
	inline pmOrientation<T, D>* getpmOrientation(void) const { return _ori; }
	inline pmVelocity<T, D>* getpmVelocity(void) const { return _vel; }
	inline pmAcceleration<T, D>* getpmAcceleration(void) const { return _acc; }
	inline const T getHandicap(void) const { return _handicap; }
public:
	inline void setHealth(int health) { _health = health; }
	inline void setBrain(BrainRule<T, D>* brain) { _brain = brain; }
	inline void setSaved(bool saved) {
		_saved = saved;
		if (_saved)
			_bs->increaseSaved();
		else
			_bs->decreaseSaved();
	}
	inline void setpmPosition(pmPosition<T, D> pos) { *_pos = pos; }
	inline void setpmVelocity(pmVelocity<T, D> vel) { *_vel = vel; }
	inline void setHandicap(T handicap) { _handicap = handicap; }
public:
	Boid(BoidSystem<T, D>*, ColonyID = NEUTRAL);
	~Boid(void);
public:
	void addRule(BoidRule<T, D>*);
	void update(void);
	void initializeNeighbors(void);
	std::vector<Boid<T, D>*> getNeighbors(T = 0, ColonyID = ANY);
private:
	std::vector<Boid<T, D>*> _neighbors;
	std::vector<T> _distances;
	void updateNeighbors(void);
};

/**
 * 
 **/
template<typename T, int D>
Boid<T, D>::Boid(BoidSystem<T, D>* bs, ColonyID cid)
	:	_bs(bs), _cid(cid), _health(100), _saved(false), _brain(NULL),
		_recalculate(rand() % RECALCULATE),
		_walk_speed(T(MAX_WALK_SPEED)),
		_run_speed(T(MAX_RUN_SPEED)),
		_max_acceleration(T(MAX_ACCELERATION)),
		_handicap(1),
		_pos(new pmPosition<T, D>),
		_ori(new pmOrientation<T, D>),
		_vel(new pmVelocity<T, D>),
		_acc(new pmAcceleration<T, D>) {}

/**
 * 
 **/
template<typename T, int D>
Boid<T, D>::~Boid(void) {
	delete _pos, _ori;
	delete _vel, _acc;
	// Clean up our rule set.
	std::vector<BoidRule<T, D>*>::iterator it;
	for(it = _rules.begin(); it != _rules.end(); ++it)
		delete *it;
}

/**
 * 
 **/
template<typename T, int D>
void Boid<T, D>::addRule(BoidRule<T, D>* rule) {
	_rules.push_back(rule);
}

/**
 * 
 **/
template<typename T, int D>
void Boid<T, D>::update(void) {
	// Do nothing if the boid is already in a safe zone.
	if (isSaved())
		return;
	// Do nothing if dead.
	if(!isAlive())
		return;
	T h = T(_health) / 100;
	// Recalculate.
	if(--_recalculate <= 0) {
		// Sort this boid's neighbors.
		updateNeighbors();
		_recalculate = RECALCULATE;
		// Update this boid's rules.
		_acc->fill(0);
		std::vector<BoidRule<T, D>*>::iterator it;
		for(it = _rules.begin(); it != _rules.end(); ++it)
			_acc->add(*(**it)());
		// Cannot accelerate faster.
		if(!_acc->isNil()) {
			if(_acc->magnitude() > _max_acceleration * _handicap)
				_acc->normalize(_max_acceleration * _handicap);
		}
		// Move slower when injured.
		_acc->scale(pmScalar<T>(h));
	}
	// Update this boid's movement.
	_vel->add(*_acc);
	if(!_vel->isNil()) {
		if(_vel->speed() < _walk_speed)
			_vel->normalize(_walk_speed * h);
		else if(_vel->speed() > _run_speed)
			_vel->normalize(_run_speed * h);
		else
			_vel->scale(pmScalar<T>(h));
	}
	for(int i = 0; i < D; ++i)
		_ori->set(_vel->get(i), i);
	_pos->add(*_vel);
}

/**
 * 
 **/
template<typename T, int D>
void Boid<T, D>::initializeNeighbors(void) {
	_neighbors = _bs->getBoids();
	_distances.resize(_neighbors.size());
	updateNeighbors();
}

/**
 * 
 **/
template<typename T, int D>
std::vector<Boid<T, D>*> Boid<T, D>::getNeighbors(T radius, ColonyID cid) {
	std::vector<Boid<T, D>*> result;
	std::vector<Boid<T, D>*>::iterator it;
	// Within any radius.
	if(radius <= 0) {
		for(it = _neighbors.begin(); it != _neighbors.end(); ++it)
			if(cid < 0 || (*it)->getColonyID() == cid)
				result.push_back(*it);
	// Within a specific radius.
	} else {
		int len = _neighbors.size();
		for(int i = 0; i < len; ++i)
			if((cid < 0 || _neighbors[i]->getColonyID() == cid) && _distances[i] <= radius)
				result.push_back(_neighbors[i]);
	}
	// Return the results.
	return result;
}

/**
 *
 **/
template<typename T, int D>
void Boid<T, D>::updateNeighbors(void) {
	pmPosition<T, D>* p = getpmPosition();
	int len = _distances.size();
	for(int i = 0; i < len; ++i)
		_distances[i] = p->distance(*(_neighbors[i]->getpmPosition()));
}

#endif