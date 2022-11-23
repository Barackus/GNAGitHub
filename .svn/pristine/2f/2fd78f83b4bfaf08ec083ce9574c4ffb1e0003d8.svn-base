#ifndef PM_VELOCITY_H
#define PM_VELOCITY_H

#include <cstdarg>

template<typename T, int D>
class pmVelocity : public pmVector<T> {
public:
	pmVelocity(void);
	pmVelocity(T, T = T(), T = T(), T = T());
	pmVelocity(T, ...);
	T speed(void) const;
};

/**
 * 
 **/
template<typename T, int D>
pmVelocity<T, D>::pmVelocity(void)
	:	pmVector<T>(D) {}

/**
 * 
 **/
template<typename T, int D>
pmVelocity<T, D>::pmVelocity(T a, T b, T c, T d)
	:	pmVector<T>(D) {
	if(D >= 1) set(a, 0);
	if(D >= 2) set(b, 1);
	if(D >= 3) set(c, 2);
	if(D >= 4) set(d, 3);
}

/**
 * 
 **/
template<typename T, int D>
pmVelocity<T, D>::pmVelocity(T dim, ...)
	:	pmVector<T>(D) {
	va_list va;
	va_start(va, dim);
	set(dim, 0);
	for(int i = 1; i < D; ++i) {
		T t = (T) va_arg(va, double);
		set(t, i);
	}
	va_end(va);
}

/**
 * 
 **/
template<typename T, int D>
T pmVelocity<T, D>::speed(void) const {
	return magnitude();
}

#endif