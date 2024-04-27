#ifndef ICP_HPP_
#define ICP_HPP_
#include <Eigen/Core>
#include <iostream>
#include <memory>

namespace ICP {
class ICP {
public:
  using Points = std::vector<Eigen::Vector2d>;
  using InputPointsPtr = std::shared_ptr<Points>;
  ICP();
  void setInputSource(const InputPointsPtr points);
  void setInputTarget(const InputPointsPtr points);

private:
  InputPointsPtr source_;
  InputPointsPtr target_;
};
} // namespace ICP
#endif