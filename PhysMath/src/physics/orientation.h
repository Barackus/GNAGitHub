#ifndef PM_ORIENTATION_H
#define PM_ORIENTATION_H

template<typename T, int D>
class pmOrientation : public pmVector<T> {
public:
	pmOrientation(void);
	pmOrientation(T, T = T(), T = T(), T = T());
	pmOrientation(T, ...);
};

/**
 * 
 **/
template<typename T, int D>
pmOrientation<T, D>::pmOrientation(void)
	:	pmVector<T>(D) {}

/**
 * 
 **/
template<typename T, int D>
pmOrientation<T, D>::pmOrientation(T a, T b, T c, T d)
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
pmOrientation<T, D>::pmOrientation(T dim, ...)
	:	pmVector<T>(D) {
	va_list va;
	va_start(va, dim);
	set(dim, 0);
	for(int i = 1; i < D; ++i)
		set(va_arg(va, T), i);
	va_end(va);
}

#endif