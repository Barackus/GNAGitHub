#ifndef PHYSMATH_H
#define PHYSMATH_H

// Includes for tensors.
#include "tensor/tensor.h"
#include "tensor/matrix.h"
#include "tensor/vector.h"
#include "tensor/scalar.h"

// Includes for physics stuff.
#include "physics/position.h"
#include "physics/orientation.h"
#include "physics/velocity.h"
#include "physics/acceleration.h"

// pmTensor type definitions.
typedef pmTensor<char>		pmTensorc;
typedef pmTensor<short>		pmTensors;
typedef pmTensor<int>		pmTensori;
typedef pmTensor<long>		pmTensorl;
typedef pmTensor<float>		pmTensorf;
typedef pmTensor<double>	pmTensord;
typedef pmTensor<bool>		pmTensorb;

// pmMatrix type definitions.
typedef pmMatrix<char>		pmMatrixc;
typedef pmMatrix<short>		pmMatrixs;
typedef pmMatrix<int>		pmMatrixi;
typedef pmMatrix<long>		pmMatrixl;
typedef pmMatrix<float>		pmMatrixf;
typedef pmMatrix<double>	pmMatrixd;
typedef pmMatrix<bool>		pmMatrixb;

// pmVector type definitions.
typedef pmVector<char>		pmVectorc;
typedef pmVector<short>		pmVectors;
typedef pmVector<int>		pmVectori;
typedef pmVector<long>		pmVectorl;
typedef pmVector<float>		pmVectorf;
typedef pmVector<double>	pmVectord;
typedef pmVector<bool>		pmVectorb;

// pmScalar type definitions.
typedef pmScalar<char>		pmScalarc;
typedef pmScalar<short>		pmScalars;
typedef pmScalar<int>		pmScalari;
typedef pmScalar<long>		pmScalarl;
typedef pmScalar<float>		pmScalarf;
typedef pmScalar<double>	pmScalard;
typedef pmScalar<bool>		pmScalarb;

// pmPosition type definitions.
typedef pmPosition<int, 3>		pmPosition3i;
typedef pmPosition<float, 3>	pmPosition3f;
typedef pmPosition<double, 3>	pmPosition3d;
typedef pmPosition<int, 2>		pmPosition2i;
typedef pmPosition<float, 2>	pmPosition2f;
typedef pmPosition<double, 2>	pmPosition2d;

// pmOrientation type definitions.
typedef pmOrientation<int, 3>		pmOrientation3i;
typedef pmOrientation<float, 3>		pmOrientation3f;
typedef pmOrientation<double, 3>	pmOrientation3d;
typedef pmOrientation<int, 2>		pmOrientation2i;
typedef pmOrientation<float, 2>		pmOrientation2f;
typedef pmOrientation<double, 2>	pmOrientation2d;

// pmVelocity type definitions.
typedef pmVelocity<int, 3>		pmVelocity3i;
typedef pmVelocity<float, 3>	pmVelocity3f;
typedef pmVelocity<double, 3>	pmVelocity3d;
typedef pmVelocity<int, 2>		pmVelocity2i;
typedef pmVelocity<float, 2>	pmVelocity2f;
typedef pmVelocity<double, 2>	pmVelocity2d;

// pmAcceleration type definitions.
typedef pmAcceleration<int, 3>		pmAcceleration3i;
typedef pmAcceleration<float, 3>	pmAcceleration3f;
typedef pmAcceleration<double, 3>	pmAcceleration3d;
typedef pmAcceleration<int, 2>		pmAcceleration2i;
typedef pmAcceleration<float, 2>	pmAcceleration2f;
typedef pmAcceleration<double, 2>	pmAcceleration2d;

#endif