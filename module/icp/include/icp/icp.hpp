#ifndef ICP_HPP_
#define ICP_HPP_

#include <Eigen/Dense>
#include <Eigen/QR>
#include <Eigen/SVD>
#include <iostream>
#include <memory>
#include <numeric>
namespace ICP {
using Points = std::vector<Eigen::Vector2d>;
using InputPointsPtr = std::shared_ptr<Points>;
struct PointsStruct {
  InputPointsPtr points;
  Eigen::Vector2d center;
  Points centeredPoints;
};

enum class Method { SVD, GAUSS_NEWTON };
class ICP {
public:
  using CorrespondenceIndices = std::vector<std::pair<int32_t, int32_t>>;

  ICP(Method method = Method::SVD);
  void setInputSource(const InputPointsPtr points);
  void setInputTarget(const InputPointsPtr points);
  void setUpdateMethod(Method method);
  void align();

private:
  PointsStruct inputSource_;
  PointsStruct source_;
  PointsStruct target_;
  Method icpMethod_ = Method::SVD;

private:
  CorrespondenceIndices getCorrespondenceIndices(const Points &sourcePoints,
                                                 const Points &targetPoints);
  Eigen::Matrix2d getCovarianceMatrix(const Points &sourcePoints,
                                      const Points &targetPoints,
                                      const CorrespondenceIndices &indices);
  Eigen::Matrix2d getR(double theta);
  Eigen::Matrix2d getDR(double theta);
  void setCenterPoint(PointsStruct &pointsData);
  void SVDAlign();
  void GaussNewtonAlign();
};
} // namespace ICP
#endif