#include "icp/icp.hpp"
#include "icp/utils.hpp"
#include <iostream>

int32_t main() {
  ICP::ICP icp;
  ICP::ICP::Points targetPoints;
  auto randomPoints = ICP::utils::generateRandomPoints(10);
  auto T = ICP::utils::transformPoints(randomPoints, targetPoints);

  for (int i = 0; i < randomPoints.size(); ++i) {
    std::cout << "=====" << i << "=====" << std::endl;
    std::cout << "SourcePoint: " << randomPoints[i] << std::endl;
    std::cout << "TransformPoint: " << targetPoints[i] << std::endl;
  }
  return 0;
}