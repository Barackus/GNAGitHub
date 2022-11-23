#ifndef PM_TENSOR_H
#define PM_TENSOR_H

#include <cstdarg>
#include <algorithm>
#include <vector>

/**
 * 
 **/
template<typename T>
class pmTensor {
protected:
	std::vector<int> _dim;
	std::vector<T> _data;
public:
	pmTensor(int, ...);
	pmTensor(std::vector<int>);
public:
	pmTensor(const pmTensor<T>&);
	const pmTensor<T>& operator=(const pmTensor<T>&);
public:
	const T get(int, ...) const;
	void set(const T, int, ...);
	void fill(const T, bool = false);
	void abs(void);
public:
	const int getOrder(void) const;
	const int getSize(void) const;
	const int getMemory(void) const;
	const std::vector<T> getData(void) const;
	const std::vector<int> getDimensions(void) const;
	const bool ispmScalar(void) const;
	const bool ispmVector(void) const;
	const bool ispmMatrix(void) const;
	const bool isNil(void) const;
	const bool isOfSameOrder(const pmTensor<T>&) const;
	const bool hasSameDimensions(const pmTensor<T>&) const;
public:
	pmTensor<T>& add(const pmTensor<T>&);
	pmTensor<T>& subtract(const pmTensor<T>&);
	pmTensor<T>& scale(const pmTensor<T>&);
	pmTensor<T>& divide(const pmTensor<T>&);
	static pmTensor<T> add(const pmTensor<T>&, const pmTensor<T>&);
	static pmTensor<T> subtract(const pmTensor<T>&, const pmTensor<T>&);
	static pmTensor<T> scale(const pmTensor<T>&, const pmTensor<T>&);
	static pmTensor<T> divide(const pmTensor<T>&, const pmTensor<T>&);
public:
	pmTensor<T>& operator+=(const pmTensor<T>&);
	pmTensor<T>& operator-=(const pmTensor<T>&);
	pmTensor<T>& operator/=(const pmTensor<T>&);
	pmTensor<T>& operator*=(const pmTensor<T>&);
	pmTensor<T> operator+(const pmTensor<T>&);
	pmTensor<T> operator-(const pmTensor<T>&);
	pmTensor<T> operator/(const pmTensor<T>&);
	pmTensor<T> operator*(const pmTensor<T>&);
	pmTensor<T> operator-(void) const;
};

/**
 * 
 **/
template<typename T>
pmTensor<T>::pmTensor(int dim, ...) {
	// Process variable number of arguments.
	va_list va;
	va_start(va, dim);
	_dim.resize(dim);
	int count = 1, d;
	for(int i = 0; i < dim; ++i) {
		d = va_arg(va, int);
		if(d <= 0)
			throw;
		_dim[i] = d;
		count *= d;
	}
	va_end(va);
	// Allocate memory in data structure.
	_data.resize(count);
}

/**
 * 
 **/
template<typename T>
pmTensor<T>::pmTensor(std::vector<int> dim) {
	int count = 1;
	int len = dim.size();
	_dim.resize(len);
	for(int i = 0; i < len; ++i) {
		int d = dim[i];
		if(d <= 0)
			throw;
		_dim[i] = d;
		count *= d;
	}
	_data.resize(count);
}

/**
 * 
 **/
template<typename T>
pmTensor<T>::pmTensor(const pmTensor<T>& other) {
	// Copy all relevant data.
	_dim.resize(other._dim.size());
	_data.resize(other._data.size());
	std::copy(other._dim.begin(), other._dim.end(), _dim.begin());
	std::copy(other._data.begin(), other._data.end(), _data.begin());
}

/**
 * 
 **/
template<typename T>
const pmTensor<T>& pmTensor<T>::operator=(const pmTensor<T>& other) {
	// Only allow assignments of the same order.
	if(getOrder() != other.getOrder())
		throw;
	// Copy all relevant data.
	if (this != &other) {
		_dim.resize(other._dim.size());
		_data.resize(other._data.size());
		std::copy(other._dim.begin(), other._dim.end(), _dim.begin());
		std::copy(other._data.begin(), other._data.end(), _data.begin());
	}
	return *this;
}

/**
 * 
 **/
template<typename T>
const T pmTensor<T>::get(int dim, ...) const {
	// Process variable number of arguments.
	va_list va;
	va_start(va, dim);
	int index = dim, aux = 1;
	int order = _dim.size();
	for(int i = 1; i < order; ++i) {
		aux *= _dim[i - 1];
		index += aux * va_arg(va, int);
	}
	va_end(va);
	// Return value at index.
	return _data[index];
}

/**
 * 
 **/
template<typename T>
void pmTensor<T>::set(const T value, int dim, ...) {
	// Process variable number of arguments.
	va_list va;
	va_start(va, dim);
	int index = dim, aux = 1;
	int order = _dim.size();
	for(int i = 1; i < order; ++i) {
		aux *= _dim[i - 1];
		index += aux * va_arg(va, int);
	}
	va_end(va);
	// Set value at index.
	_data[index] = value;
}

/**
 * TODO: incr from bool to T?
 **/
template<typename T>
void pmTensor<T>::fill(const T value, bool incr) {
	if(!incr)
		std::fill(_data.begin(), _data.end(), value);
	else {
		T v = value - 1;
		std::for_each(_data.begin(), _data.end(),
			[&v](T& t) { t = ++v; });
	}
}

/**
 * 
 **/
template<typename T>
void pmTensor<T>::abs(void) {
	std::vector<T>::iterator it;
	for(it = _data.begin(); it != _data.end(); ++it)
		if(*it < 0)
			*it = 0 - *it;
}

/**
 * 
 **/
template<typename T>
const int pmTensor<T>::getOrder(void) const {
	int count = 0;
	for(unsigned int i = 0; i < _dim.size(); ++i)
		if(_dim[i] > 1)
			++count;
	return count;
}

/**
 * 
 **/
template<typename T>
const std::vector<int> pmTensor<T>::getDimensions(void) const {
	return _dim;
}

/**
 * 
 **/
template<typename T>
const bool pmTensor<T>::ispmScalar(void) const {
	return getOrder() == 0;
}

/**
 * 
 **/
template<typename T>
const bool pmTensor<T>::ispmVector(void) const {
	return getOrder() == 1;
}

/**
 * 
 **/
template<typename T>
const bool pmTensor<T>::ispmMatrix(void) const {
	return getOrder() == 2;
}

/**
 * 
 **/
template<typename T>
const bool pmTensor<T>::isNil(void) const {
	int len = _data.size();
	for(int i = 0; i < len; ++i)
		if(_data[i] != 0)
			return false;
	return true;
}

/**
 * 
 **/
template<typename T>
const int pmTensor<T>::getSize(void) const {
	return _data.size();
}

/**
 * 
 **/
template<typename T>
const int pmTensor<T>::getMemory(void) const {
	return getSize() * sizeof(T);
}

/**
 * 
 **/
template<typename T>
const std::vector<T> pmTensor<T>::getData(void) const {
	return _data;
}
	 
/**
 * 
 **/
template<typename T>
const bool pmTensor<T>::isOfSameOrder(const pmTensor<T>& t) const {
	return getOrder() == t.getOrder();
}

/**
 * 
 **/
template<typename T>
const bool pmTensor<T>::hasSameDimensions(const pmTensor<T>& t) const {
	return isOfSameOrder(t) &&
		[](std::vector<int> _dim, std::vector<int> dim) -> bool {
			int len = dim.size();
			for(int i = 0; i < len; ++i)
				if(dim[i] != _dim[i])
					return false;
			return true;
		}(getDimensions(), t.getDimensions());
}

/**
 * 
 **/
template<typename T>
pmTensor<T>& pmTensor<T>::add(const pmTensor<T>& t) {
	if(!hasSameDimensions(t))
		throw;
	int len = getSize();
	for(int i = 0; i < len; ++i)
		_data[i] += t._data[i];
	return *this;
}

/**
 * 
 **/
template<typename T>
pmTensor<T>& pmTensor<T>::subtract(const pmTensor<T>& t) {
	if(!hasSameDimensions(t))
		throw;
	int len = getSize();
	for(int i = 0; i < len; ++i)
		_data[i] -= t._data[i];
	return *this;
}

/**
 * 
 **/
template<typename T>
pmTensor<T>& pmTensor<T>::scale(const pmTensor<T>& s) {
	if(!s.ispmScalar())
		throw;
	T scalar = s.get(0);
	int len = getSize();
	for(int i = 0; i < len; ++i)
		_data[i] *= scalar;
	return *this;
}

/**
 * 
 **/
template<typename T>
pmTensor<T>& pmTensor<T>::divide(const pmTensor<T>& s) {
	if(!s.ispmScalar())
		throw;
	T scalar = s.get(0);
	int len = getSize();
	for(int i = 0; i < len; ++i)
		_data[i] /= scalar;
	return *this;
}

/**
 * 
 **/
template<typename T>
pmTensor<T> pmTensor<T>::add(const pmTensor<T>& a, const pmTensor<T>& b) {
	pmTensor<T> tmp(a);
	tmp.add(b);
	return tmp;
}
template<typename T>
pmTensor<T> add(const pmTensor<T>& a, const pmTensor<T>& b) {
	return pmTensor<T>::add(a, b);
}

/**
 * 
 **/
template<typename T>
pmTensor<T> pmTensor<T>::subtract(const pmTensor<T>& a, const pmTensor<T>& b) {
	pmTensor<T> tmp(a);
	tmp.subtract(b);
	return tmp;
}
template<typename T>
pmTensor<T> subtract(const pmTensor<T>& a, const pmTensor<T>& b) {
	return pmTensor<T>::subtract(a, b);
}

/**
 * 
 **/
template<typename T>
pmTensor<T> pmTensor<T>::scale(const pmTensor<T>& a, const pmTensor<T>& b) {
	if(a.ispmScalar()) {
		pmTensor<T> tmp(b);
		tmp.scale(a);
		return tmp;
	} else if(b.ispmScalar()) {
		pmTensor<T> tmp(a);
		tmp.scale(b);
		return tmp;
	} else
		throw;
}
template<typename T>
pmTensor<T> scale(const pmTensor<T>& a, const pmTensor<T>& b) {
	return pmTensor<T>::scale(a, b);
}

/**
 * 
 **/
template<typename T>
pmTensor<T> pmTensor<T>::divide(const pmTensor<T>& a, const pmTensor<T>& b) {
	if(!b.ispmScalar())
		throw;
	pmTensor<T> tmp(a);
	tmp.divide(b);
	return tmp;
}
template<typename T>
pmTensor<T> divide(const pmTensor<T>& a, const pmTensor<T>& b) {
	return pmTensor<T>::divide(a, b);
}

/**
 * 
 **/
template<typename T>
pmTensor<T> pmTensor<T>::operator+(const pmTensor<T>& other) {
	return pmTensor<T>::add(*this, other);
}

/**
 * 
 **/
template<typename T>
pmTensor<T> pmTensor<T>::operator-(const pmTensor<T>& other) {
	return pmTensor<T>::subtract(*this, other);
}

/**
 * 
 **/
template<typename T>
pmTensor<T> pmTensor<T>::operator/(const pmTensor<T>& other) {
	return pmTensor<T>::divide(*this, other);
}

/**
 * 
 **/
template<typename T>
pmTensor<T> pmTensor<T>::operator*(const pmTensor<T>& other) {
	return pmTensor<T>::scale(*this, other);
}

/**
 * 
 **/
template<typename T>
pmTensor<T>& pmTensor<T>::operator+=(const pmTensor<T>& other) {
	this->add(other);
	return *this;
}

/**
 * 
 **/
template<typename T>
pmTensor<T>& pmTensor<T>::operator-=(const pmTensor<T>& other) {
	this->subtract(other);
	return *this;
}

/**
 * 
 **/
template<typename T>
pmTensor<T>& pmTensor<T>::operator/=(const pmTensor<T>& other) {
	this->divide(other);
	return *this;
}

/**
 * 
 **/
template<typename T>
pmTensor<T>& pmTensor<T>::operator*=(const pmTensor<T>& other) {
	this->scale(other);
	return *this;
}

/**
 * 
 **/
template<typename T>
pmTensor<T> pmTensor<T>::operator-(void) const {
	pmScalar<T> s;
	s.set(-1);
	return scale(*this, s);
}

#endif