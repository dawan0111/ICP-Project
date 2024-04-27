#ifndef ICP_UTILS_HPP_
#define ICP_UTILS_HPP_
#define RANDOM_SEED 3244
#include "icp.hpp"
#include <Eigen/Core>
#include <cmath>
#include <iostream>
#include <random>

namespace ICP::utils {
static std::mt19937_64 rng1(RANDOM_SEED);
ICP::Points generateRandomPoints(int16_t length, const double min = 1.0,
                                 const double max = 4.0);
Eigen::Matrix3d transformPoints(const ICP::Points &source, ICP::Points &target,
                                const double minAngle = 10.0,
                                const double maxAngle = 40.0,
                                const double minTransition = 1.0,
                                double maxTransition = 4.0);
} // namespace ICP::utils

#endif