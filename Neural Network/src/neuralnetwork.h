#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

// Include all types of Artificial Neural Network.
#include "multilayerperceptron.h"

// Typedefs for multilayer perceptrons with floats.
typedef MultilayerPerceptron<float, 2> MLPerceptron2f;
typedef MultilayerPerceptron<float, 3> MLPerceptron3f;
typedef MultilayerPerceptron<float, 4> MLPerceptron4f;
typedef MultilayerPerceptron<float, 5> MLPerceptron5f;

// Typedefs for multilayer perceptrons with doubles.
typedef MultilayerPerceptron<double, 2> MLPerceptron2d;
typedef MultilayerPerceptron<double, 3> MLPerceptron3d;
typedef MultilayerPerceptron<double, 4> MLPerceptron4d;
typedef MultilayerPerceptron<double, 5> MLPerceptron5d;

#endif