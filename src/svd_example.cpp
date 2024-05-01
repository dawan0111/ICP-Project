#include "icp/icp.hpp"
#include "icp/utils.hpp"
#include <iostream>
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

int32_t main() {
  ICP::ICP icp;
  ICP::Points sourcePoints;
  auto targetPoints = ICP::utils::generateRandomPoints(20);
  auto T = ICP::utils::transformPoints(targetPoints, sourcePoints);

  auto sourcePointsPtr = std::make_shared<ICP::Points>(sourcePoints);
  auto targetPointsPtr = std::make_shared<ICP::Points>(targetPoints);

  icp.setInputSource(sourcePointsPtr);
  icp.setInputTarget(targetPointsPtr);

  std::vector<double> x1, y1;
  for (const auto &point : targetPoints) {
    x1.push_back(point[0]);
    y1.push_back(point[1]);
  }

  plt::figure_size(800, 600);
  plt::xlabel("x axis");
  plt::ylabel("y axis");

  for (int i = 0; i < 11; ++i) {
    std::vector<double> x, y;
    for (const auto &point : *sourcePointsPtr) {
      x.push_back(point[0]);
      y.push_back(point[1]);
    }
    plt::clf();
    plt::plot(x1, y1, "bo-");
    plt::title("SVD Iteration #" + std::to_string(i));
    plt::plot(x, y, "ro-");
    plt::pause(0.5);
    icp.align();
  }

  plt::show();

  return 0;
}