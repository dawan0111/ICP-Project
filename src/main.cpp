#include "icp/icp.hpp"
#include "icp/utils.hpp"
#include <iostream>

int32_t main() {
  ICP::ICP icp;
  ICP::Points sourcePoints;
  auto targetPoints = ICP::utils::generateRandomPoints(20);
  auto T = ICP::utils::transformPoints(targetPoints, sourcePoints);

  auto sourcePointsPtr = std::make_shared<ICP::Points>(sourcePoints);
  auto targetPointsPtr = std::make_shared<ICP::Points>(targetPoints);

  icp.setInputSource(sourcePointsPtr);
  icp.setInputTarget(targetPointsPtr);

  std::cout << "T: " << T << std::endl;

  icp.align();
  icp.align();
  icp.align();
  return 0;
}