#ifndef PM_MATRIX_H
#define PM_MATRIX_H

#include <iostream>
#include <sstream>

#include "tensor.h"

/**
 * 
 **/
template<typename T>
class pmMatrix : public pmTensor<T> {
public:
	pmMatrix(int, int);
	pmMatrix(const pmTensor<T>&);
	std::string toString(void) const;
public:
	const int getNumColumns(void) const;
	const int getNumRows(void) const;
public:
	pmMatrix<T>& transpose(void);
	T determinant(void) const;	// TODO
	void loadIdentity(const int);
public:
	pmMatrix<T>& multiply(const pmMatrix<T>&);
	static pmMatrix<T> multiply(const pmMatrix<T>&, const pmMatrix<T>&);
public:
	pmMatrix<T>& operator*=(const pmTensor<T>&);
	pmMatrix<T> operator*(const pmTensor<T>&);
public:
	friend std::ostream& operator<<(std::ostream& out, const pmMatrix<T>& m){
		out << m.toString();
        return out;
    }
};

/**
 * 
 **/
template<typename T>
pmMatrix<T>::pmMatrix(int w, int h)
	:	pmTensor<T>(2, w, h) {}

/**
 * 
 **/
template<typename T>
pmMatrix<T>::pmMatrix(const pmTensor<T>& other)
	:	pmTensor<T>(other) {}

/**
 * 
 **/
template<typename T>
std::string pmMatrix<T>::toString(void) const {
	std::stringstream ss;
	ss << "[ ";
	for(int y = 0; y < _dim[1]; ++y) {
		ss << (y == 0 ? "" : "  ") << "[ ";
		for(int x = 0; x < _dim[0]; ++x) {
			ss << get(x, y) << " ";
		}
		ss << "]";
		if(y < _dim[1] - 1)
			ss << endl;
	}
	ss << " ]";
	return ss.str();
}

/**
 * 
 **/
template<typename T>
const int pmMatrix<T>::getNumColumns(void) const {
	return _dim[0];
}

/**
 * 
 **/
template<typename T>
const int pmMatrix<T>::getNumRows(void) const {
	return _dim[1];
}

/**
 * 
 **/
template<typename T>
pmMatrix<T>& pmMatrix<T>::transpose(void) {
	int w = _dim[0], h = _dim[1];
	pmMatrix<T> tmp(h, w);
	for(int y = 0; y < h; ++y)
		for(int x = 0; x < w; ++x)
			tmp.set(get(x, y), y, x);
	*this = tmp;
	return *this;
}

/**
 * 
 **/
template<typename T>
void pmMatrix<T>::loadIdentity(const int n) {
	_dim[0] = n, _dim[1] = n;
	_data.resize(n * n);
	fill(0);
	for(int i = 0; i < n; ++i)
		set(1, i, i);
}

/**
 * 
 **/
template<typename T>
pmMatrix<T>& pmMatrix<T>::multiply(const pmMatrix<T>& m) {
	// Scale or outer product.
	if(m.ispmScalar())
		scale(m);
	// Cannot store pmMatrix in a pmVector.
	else if(m.ispmVector())
		throw;
	else
		*this = pmMatrix<T>::multiply(*this, m);
	// Return ourselves.
	return *this;
}

/**
 * 
 **/
template<typename T>
pmMatrix<T> pmMatrix<T>::multiply(const pmMatrix<T>& a, const pmMatrix<T>& b) {
	// pmMatrix multiplication.
	if((a.ispmMatrix() || a.ispmVector()) && (b.ispmMatrix() || b.ispmVector())) {
		int h = a.getNumRows(), j = a.getNumColumns(), w = b.getNumColumns();
		// Check dimensions.
		if(j != b.getNumRows())
			throw;
		// Multiply.
		pmMatrix<T> c(w, h);
		for(int y = 0; y < h; ++y)
			for(int x = 0; x < w; ++x)
				for(int i = 0; i < j; ++i)
					c.set(c.get(x, y) + a.get(i, y) * b.get(x, i), x, y);
		// Pass on the result.
		return c;
	} else
		throw;
}
template<typename T>
pmMatrix<T> multiply(const pmMatrix<T>& a, const pmMatrix<T>& b) {
	return pmMatrix<T>::multiply(a, b);
}

/**
 * 
 **/
template<typename T>
pmMatrix<T>& pmMatrix<T>::operator*=(const pmTensor<T>& t) {
	multiply(t);
	return *this;
}

/**
 * 
 **/
template<typename T>
pmMatrix<T> pmMatrix<T>::operator*(const pmTensor<T>& t) {
	return t.ispmScalar() ? scale(*this, t) : multiply(*this, t);
}

#endif