#ifndef ICP_HPP_
#define ICP_HPP_
#include <Eigen/Dense>
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
class ICP {
public:
  using CorrespondenceIndices = std::vector<std::pair<int32_t, int32_t>>;

  ICP();
  void setInputSource(const InputPointsPtr points);
  void setInputTarget(const InputPointsPtr points);
  void align();

private:
  PointsStruct inputSource_;
  PointsStruct source_;
  PointsStruct target_;

  CorrespondenceIndices getCorrespondenceIndices(const Points &sourcePoints,
                                                 const Points &targetPoints);
  Eigen::Matrix2d getCovarianceMatrix(const Points &sourcePoints,
                                      const Points &targetPoints,
                                      const CorrespondenceIndices &indices);
  void setCenterPoint(PointsStruct &pointsData);
};
} // namespace ICP
#endif