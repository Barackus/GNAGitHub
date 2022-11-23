#ifndef BOMB_H
#define BOMB_H

#include "../../PhysMath/src/physmath.h"

template<typename T, int D>
class Bomb {
public:
	Bomb();
	Bomb(T x, T y, T range) {
		_range = range;
		_position.set(x, 0);
		_position.set(y, 1);
	}

	inline T getRange() {
		return _range;
	}
	inline pmPosition<T, D> getpmPosition() {
		return _position;
	}

	inline T getDistanceFrom(pmPosition<T, D>* from) {
		return _position.distance(from);
	}
protected:
	pmPosition<T, D> _position;
	T _range;
};
#endif