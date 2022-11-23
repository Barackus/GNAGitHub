#ifndef FITNESSFUNCTOR_H
#define FITNESSFUNCTOR_H

#include "Evolution.h"

class FitnessFunctor {
public:
	virtual double operator()(individual&) = 0;
};

#endif