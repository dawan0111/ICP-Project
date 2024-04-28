#include "icp/icp.hpp"

namespace ICP {
ICP::ICP() { std::cout << "ICP Method!!" << std::endl; }

void ICP::setInputSource(InputPointsPtr source) {
  inputSource_.points = std::make_shared<Points>(*source);
  // source_.centeredPoints.reserve(source->size());

  source_.points = source;
  source_.centeredPoints.reserve(source->size());
}

void ICP::setInputTarget(InputPointsPtr target) {
  target_.points = target;
  target_.centeredPoints.reserve(target->size());
  setCenterPoint(target_);
}

void ICP::SVDAlign() {
  setCenterPoint(source_);

  auto corrs =
      getCorrespondenceIndices(source_.centeredPoints, target_.centeredPoints);
  auto conv = getCovarianceMatrix(source_.centeredPoints,
                                  target_.centeredPoints, corrs);

  Eigen::JacobiSVD<Eigen::MatrixXd> svd(conv, Eigen::ComputeThinU |
                                                  Eigen::ComputeThinV);

  auto R = svd.matrixU() * svd.matrixV().transpose();
  auto t = target_.center - R * source_.center;

  for (auto &point : *source_.points) {
    point = R * point + t;
  }
}

ICP::CorrespondenceIndices
ICP::getCorrespondenceIndices(const Points &sourcePoints,
                              const Points &targetPoints) {
  CorrespondenceIndices corr;
  int32_t sourceLength = sourcePoints.size();
  int32_t targetLength = targetPoints.size();

  for (int32_t i = 0; i < sourceLength; ++i) {
    int32_t index = -1;
    double minDist = MAXFLOAT;
    for (int32_t j = 0; j < targetLength; ++j) {
      auto dist = (targetPoints[j] - sourcePoints[i]).norm();
      if (dist < minDist) {
        minDist = dist;
        index = j;
      }
    }
    corr.emplace_back(i, index);
  }
  return corr;
}

void ICP::setCenterPoint(PointsStruct &pointsData) {
  int32_t length = pointsData.points->size();
  auto sum =
      std::accumulate(pointsData.points->begin(), pointsData.points->end(),
                      Eigen::Vector2d(0.0, 0.0),
                      [](const auto &x, const auto &y) { return x + y; });
  Eigen::Vector2d average(sum(0) / length, sum(1) / length);
  pointsData.center = average;
  pointsData.centeredPoints.clear();
  for (int32_t i = 0; i < length; ++i) {
    pointsData.centeredPoints.emplace_back(
        (*pointsData.points)[i](0) - average(0),
        (*pointsData.points)[i](1) - average(1));
  }
}

Eigen::Matrix2d ICP::getCovarianceMatrix(const Points &sourcePoints,
                                         const Points &targetPoints,
                                         const CorrespondenceIndices &indices) {
  Eigen::Matrix2d conv;
  for (auto &corr : indices) {
    auto source_p = sourcePoints[corr.first];
    auto target_p = targetPoints[corr.second];
    conv += target_p * source_p.transpose();
  }
  return conv;
}
} // namespace ICP