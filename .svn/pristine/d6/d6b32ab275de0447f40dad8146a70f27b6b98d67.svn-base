#ifndef PM_SCALAR_H
#define PM_SCALAR_H

#include "tensor.h"

/**
 * 
 **/
template<typename T>
class pmScalar : public pmTensor<T> {
public:
	pmScalar(const pmTensor<T>&);
	pmScalar(void);
	pmScalar(T);
	const T get(void) const;
	void set(const T);
};

/**
 * 
 **/
template<typename T>
pmScalar<T>::pmScalar(const pmTensor<T>& other)
	:	pmTensor<T>(other) {}

/**
 * 
 **/
template<typename T>
pmScalar<T>::pmScalar(void)
	:	pmTensor<T>(0, 1) {}

/**
 * 
 **/
template<typename T>
pmScalar<T>::pmScalar(T t)
	:	pmTensor<T>(0, 1) {
	set(t);
}

/**
 * 
 **/
template<typename T>
const T pmScalar<T>::get(void) const {
	return pmTensor<T>::get(0);
}

/**
 * 
 **/
template<typename T>
void pmScalar<T>::set(const T value) {
	pmTensor<T>::set(value, 0);
}

#endif