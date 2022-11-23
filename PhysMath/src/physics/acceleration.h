#ifndef PM_ACCELERATION_H
#define PM_ACCELERATION_H

#include <cstdarg>

template<typename T, int D>
class pmAcceleration : public pmVector<T> {
public:
	pmAcceleration(void);
	pmAcceleration(T, T = T(), T = T(), T = T());
	//pmAcceleration(T, ...);
};

/**
 * 
 **/
template<typename T, int D>
pmAcceleration<T, D>::pmAcceleration(void)
	:	pmVector<T>(D) {}

/**
 * 
 **/
template<typename T, int D>
pmAcceleration<T, D>::pmAcceleration(T a, T b, T c, T d)
	:	pmVector<T>(D) {
	if(D >= 1) set(a, 0);
	if(D >= 2) set(b, 1);
	if(D >= 3) set(c, 2);
	if(D >= 4) set(d, 3);
}

/**
 * 
 **/
/*template<typename T, int D>
pmAcceleration<T, D>::pmAcceleration(T dim, ...)
	:	pmVector<T>(D) {
	va_list va;
	va_start(va, dim);
	set(dim, 0);
	for(int i = 1; i < D; ++i) {
		T t = (T) va_arg(va, double);
		set(t, i);
	}
	va_end(va);
}*/

#endif