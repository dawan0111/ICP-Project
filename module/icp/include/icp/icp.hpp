#ifndef ICP_HPP_
#define ICP_HPP_
#include <Eigen/Core>
#include <iostream>
#include <memory>

class ICP {
public:
  using Points = std::vector<Eigen::Vector3d>;
  using InputPointsPtr = std::shared_ptr<Points>;
  ICP();
  void setInputSource(const InputPointsPtr points);
  void setInputTarget(const InputPointsPtr points);

private:
  InputPointsPtr source_;
  InputPointsPtr target_;
};
#endif