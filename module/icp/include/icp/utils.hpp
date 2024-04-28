#ifndef ICP_UTILS_HPP_
#define ICP_UTILS_HPP_
#define RANDOM_SEED 1500
#include "icp.hpp"
#include <Eigen/Core>
#include <cmath>
#include <iostream>
#include <random>

namespace ICP::utils {
static std::mt19937_64 rng1(RANDOM_SEED);
Points generateRandomPoints(int16_t length, const double min = 20.0,
                            const double max = 80.0);
Eigen::Matrix3d transformPoints(const Points &source, Points &target,
                                const double minAngle = 20.0,
                                const double maxAngle = 60.0,
                                const double minTransition = 4.0,
                                double maxTransition = 10.0);
} // namespace ICP::utils

#endif