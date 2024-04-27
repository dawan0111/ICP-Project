#include "icp/utils.hpp"

namespace ICP::utils {
ICP::Points generateRandomPoints(const int16_t length, const double min,
                                 const double max) {
  std::uniform_real_distribution xyDist(min, max);
  ICP::Points randomPoints;

  randomPoints.reserve(length);

  for (int16_t i = 0; i < length; i++) {
    randomPoints.emplace_back(xyDist(rng1), xyDist(rng1));
  }

  return randomPoints;
}
Eigen::Matrix3d transformPoints(const ICP::Points &source, ICP::Points &target,
                                const double minAngle, const double maxAngle,
                                const double minTransition,
                                double maxTransition) {
  std::uniform_real_distribution angleDist(minAngle, maxAngle);
  std::uniform_real_distribution tranDist(minTransition, maxTransition);

  double angle = M_PI / angleDist(rng1);
  double tranX = tranDist(rng1);
  double tranY = tranDist(rng1);

  Eigen::Matrix3d T;

  /* clang-format off */
  T << cos(angle), sin(angle) * -1.0, tranX,
       sin(angle), cos(angle), tranY,
       0, 0, 1;

  /* clang-format on */
  target.reserve(source.size());
  for (auto &point : source) {
    Eigen::Vector3d homogenousPoint;
    homogenousPoint(0) = point(0);
    homogenousPoint(1) = point(1);
    homogenousPoint(2) = 1.0;
    auto afterPoint = T * homogenousPoint;
    target.emplace_back(afterPoint(0), afterPoint(1));
  }
  return T;
}
} // namespace ICP::utils