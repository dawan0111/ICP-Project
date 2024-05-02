#include "icp/icp.hpp"

namespace ICP {
ICP::ICP(Method method) : icpMethod_(method) {}

void ICP::setInputSource(InputPointsPtr source) {
  inputSource_.points = std::make_shared<Points>(*source);

  source_.points = source;
  source_.centeredPoints.reserve(source->size());
}

void ICP::setInputTarget(InputPointsPtr target) {
  target_.points = target;
  target_.centeredPoints.reserve(target->size());
  setCenterPoint(target_);
}

void ICP::setUpdateMethod(Method method) { icpMethod_ = method; }

void ICP::align() {
  if (icpMethod_ == Method::SVD) {
    SVDAlign();
  } else if (icpMethod_ == Method::GAUSS_NEWTON) {
    GaussNewtonAlign();
  } else if (icpMethod_ == Method::POINT_TO_PLANE) {
    pointToPlaneAlign();
  }
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

void ICP::GaussNewtonAlign() {
  Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
  Eigen::Vector3d g = Eigen::Vector3d::Zero();
  Eigen::Vector3d x = Eigen::Vector3d::Zero();
  double chi = 0;

  auto corrs = getCorrespondenceIndices(*source_.points, *target_.points);

  auto R = getR(x(2));
  auto dR = getDR(x(2));

  for (auto &corr : corrs) {
    auto sourceP = (*source_.points)[corr.first];
    auto targetP = (*target_.points)[corr.second];
    Eigen::Matrix<double, 2, 3> J;

    /* clang-format off */
    J.block(0, 0, 2, 2) = Eigen::Matrix2d::Identity();
    J.block(0, 2, 2, 1) = dR * sourceP;
    /* clang-format on */

    Eigen::Vector2d error = (R * sourceP + x.segment(0, 2)) - targetP;
    H += J.transpose() * J;
    g += J.transpose() * error;
    chi += error.transpose() * error;
  }

  auto dx = H.colPivHouseholderQr().solve(-g);
  x += dx;
  x(2) = atan2(sin(x(2)), cos(x(2)));
  auto R_1 = getR(x(2));

  for (auto &point : *source_.points) {
    point = R_1 * point + x.segment(0, 2);
  }
}

void ICP::pointToPlaneAlign() {
  std::cout << "Point To Plane Method" << std::endl;
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
Eigen::Matrix2d ICP::getR(double theta) {
  Eigen::Matrix2d rotationMatrix;

  /* clang-format off */
  rotationMatrix << cos(theta), sin(theta) * -1.0,
                    sin(theta), cos(theta);

  /* clang-format on */
  return rotationMatrix;
}

Eigen::Matrix2d ICP::getDR(double theta) {
  Eigen::Matrix2d rotationDMatrix;

  /* clang-format off */
  rotationDMatrix << sin(theta) * -1.0, cos(theta) * -1.0,
                    cos(theta), sin(theta) * -1.0;

  /* clang-format on */
  return rotationDMatrix;
}
} // namespace ICP