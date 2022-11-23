#ifndef PM_POSITION_H
#define PM_POSITION_H

template<typename T, int D>
class pmPosition : public pmVector<T> {
public:
	pmPosition(void);
	pmPosition(T, T = T(), T = T(), T = T());
	pmPosition(T, ...);
public:
	T distance(const pmPosition<T, D>&);
};

/**
 * 
 **/
template<typename T, int D>
pmPosition<T, D>::pmPosition(void)
	:	pmVector<T>(D) {}

/**
 * 
 **/
template<typename T, int D>
pmPosition<T, D>::pmPosition(T a, T b, T c, T d)
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
pmPosition<T, D>::pmPosition(T dim, ...)
	:	pmVector<T>(D) {
	va_list va;
	va_start(va, dim);
	set(dim, 0);
	for(int i = 1; i < D; ++i)
		set(va_arg(va, T), i);
	va_end(va);
}

/**
 * 
 **/
template<typename T, int D>
T pmPosition<T, D>::distance(const pmPosition<T, D>& p) {
	return pmVector<T>(*this - p).magnitude();
}

#endif