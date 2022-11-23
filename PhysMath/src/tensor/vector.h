#ifndef PM_VECTOR_H
#define PM_VECTOR_H

#include "matrix.h"

/**
 * 
 **/
template<typename T>
class pmVector : public pmMatrix<T> {
public:
	pmVector(int);
	pmVector(const pmTensor<T>&);
public:
	const bool isColumnpmVector(void) const;
	const bool isRowpmVector(void) const;
	const T magnitude(void) const;
public:
	const T get(int) const;
	void set(const T, int);
public:
	const pmVector<T>& normalize(T = 1);
	const T angle(void) const;
	const T angle(const pmVector<T>&) const;
	const T inner(const pmVector<T>&) const;
	const T dot(const pmVector<T>&) const;
	const pmVector<T>& outer(const pmVector<T>&);
	const pmVector<T>& cross(const pmVector<T>&);
	static const pmVector<T> normalize(const pmVector<T>&);
	static const T angle(const pmVector<T>&, const pmVector<T>&);
	static const T inner(const pmVector<T>&, const pmVector<T>&);
	static const T dot(const pmVector<T>&, const pmVector<T>&);
	static const pmVector<T> outer(const pmVector<T>&, const pmVector<T>&);
	static const pmVector<T> cross(const pmVector<T>&, const pmVector<T>&);
};

/**
 * 
 **/
template<typename T>
pmVector<T>::pmVector(int d)
	:	pmMatrix<T>(1, d) {}

/**
 * 
 **/
template<typename T>
pmVector<T>::pmVector(const pmTensor<T>& other)
	:	pmMatrix<T>(other) {
	// Only allow pmVectors.
	if(!other.ispmVector())
		throw;
}

/**
 * 
 **/
template<typename T>
const bool pmVector<T>::isColumnpmVector(void) const {
	return _dim[0] == 1;
}

/**
 * 
 **/
template<typename T>
const bool pmVector<T>::isRowpmVector(void) const {
	return _dim[1] == 1;
}

/**
 * 
 **/
template<typename T>
const T pmVector<T>::magnitude(void) const {
	int len = getSize();
	T mag = 0, t;
	for(int i = 0; i < len; ++i) {
		t = get(i);
		mag += t * t;
	}
	return sqrt(mag);	// FIXME: Handle integers.
}

/**
 * 
 **/
template<typename T>
const T pmVector<T>::get(int index) const {
	if(_dim[0] == 1) {
		return pmTensor<T>::get(0, index);
	} else if(_dim[1] == 1) {
		return pmTensor<T>::get(index, 0);
	} else 
		throw;
}

/**
 * 
 **/
template<typename T>
void pmVector<T>::set(const T value, int index) {
	if(_dim[0] == 1) {
		pmTensor<T>::set(value, 0, index);
	} else if(_dim[1] == 1) {
		pmTensor<T>::set(value, index, 0);
	} else 
		throw;
}

/**
 * 
 **/
template<typename T>
const pmVector<T>& pmVector<T>::normalize(T scale) {
	if(isNil())
		throw;
	else
		*this *= pmScalar<T>(scale / magnitude());
	return *this;
}

/**
 * 
 **/
template<typename T>
const T pmVector<T>::angle(void) const {
	pmVector<T> v(*this);
	v.fill(0);
	v.set(1, 0);
	return v.angle(*this);
}

/**
 * 
 **/
template<typename T>
const T pmVector<T>::angle(const pmVector<T>& v) const {
	return acos(dot(*this, v) / (this->magnitude() * v.magnitude()));
}

/**
 * 
 **/
template<typename T>
const T pmVector<T>::inner(const pmVector<T>& v) const {
	if(hasSameDimensions(v)) {
		int len = getSize();
		T t = 0;
		for(int i = 0; i < len; ++i)
			t += get(i) * v.get(i);
		return t;
	} else
		throw;
}

/**
 * 
 **/
template<typename T>
const T pmVector<T>::dot(const pmVector<T>& v) const {
	return inner(v);
}

/**
 * 
 **/
template<typename T>
const pmVector<T>& pmVector<T>::outer(const pmVector<T>& v) {
	return pmMatrix<T>::multiply(v);
}

/**
 * 
 **/
template<typename T>
const pmVector<T>& pmVector<T>::cross(const pmVector<T>& v) {
	// Cross product only allowed for pmVectors of length 3 (forget 7).
	if(getSize() != 3 || v.getSize() != 3)
		throw;
	// Cross-produce :-P
	pmVector<T> t(*this);
	set((t.get(1) * v.get(2)) - (t.get(2) * v.get(1)), 0);
	set((t.get(2) * v.get(0)) - (t.get(0) * v.get(2)), 1);
	set((t.get(0) * v.get(1)) - (t.get(1) * v.get(0)), 2);
	// Return ourselves.
	return *this;
}

/**
 * 
 **/
template<typename T>
const pmVector<T> pmVector<T>::normalize(const pmVector<T>& v) {
	pmVector<T> n(v);
	return n.normalize();
}
template<typename T>
const pmVector<T> normalize(const pmVector<T>& v) {
	return pmVector<T>::normalize(v);
}

/**
 * 
 **/
template<typename T>
const T pmVector<T>::angle(const pmVector<T>& a, const pmVector<T>& b) {
	return a.angle(b);
}
template<typename T>
const T angle(const pmVector<T>& a, const pmVector<T>& b) {
	return pmVector<T>::angle(a, b);
}

/**
 * 
 **/
template<typename T>
const T pmVector<T>::inner(const pmVector<T>& a, const pmVector<T>& b) {
	return a.inner(b);
}
template<typename T>
const T inner(const pmVector<T>& a, const pmVector<T>& b) {
	return pmVector<T>::inner(a, b);
}

/**
 * 
 **/
template<typename T>
const T pmVector<T>::dot(const pmVector<T>& a, const pmVector<T>& b) {
	return pmVector<T>::inner(a, b);
}
template<typename T>
const T dot(const pmVector<T>& a, const pmVector<T>& b) {
	return pmVector<T>::dot(a, b);
}

/**
 * 
 **/
template<typename T>
const pmVector<T> pmVector<T>::outer(const pmVector<T>& a, const pmVector<T>& b) {
	return pmMatrix<T>::multiply(a, b);
}
template<typename T>
const pmVector<T> outer(const pmVector<T>& a, const pmVector<T>& b) {
	return pmVector<T>::outer(a, b);
}

/**
 * 
 **/
template<typename T>
const pmVector<T> pmVector<T>::cross(const pmVector<T>& a, const pmVector<T>& b) {
	pmVector<T> tmp(a);
	return tmp.cross(b);
}
template<typename T>
const pmVector<T> cross(const pmVector<T>& a, const pmVector<T>& b) {
	return pmVector<T>::cross(a, b);
}

#endif