#include "icp/utils.hpp"

namespace ICP::utils {
ICP::Points generateRandomPoints(const int16_t length, const double min,
                                 const double max) {
  std::uniform_real_distribution dist1(min, max);
  ICP::Points randomPoints;

  randomPoints.reserve(length);

  for (int16_t i = 0; i < length; i++) {
    randomPoints.emplace_back(dist1(rng1), dist1(rng1));
  }

  return randomPoints;
}
} // namespace ICP::utils