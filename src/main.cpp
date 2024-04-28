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

  std::cout << "T: " << T << std::endl;

  for (int i = 0; i < 100; ++i) {
    icp.align();
  }

  std::vector<double> x, y;
  std::vector<double> x1, y1;

  for (const auto &point : *sourcePointsPtr) {
    x.push_back(point[0]);
    y.push_back(point[1]);
  }

  for (const auto &point : targetPoints) {
    x1.push_back(point[0]);
    y1.push_back(point[1]);
  }

  // 그래프 설정
  plt::figure_size(800, 600); // 그래프 크기 설정
  plt::plot(x, y, "ro-");     // 빨간색 원 포인트와 선으로 연결
  plt::plot(x1, y1, "bo-");   // 빨간색 원 포인트와 선으로 연결
  plt::title("Plot of Vector<Eigen::Vector2d>");
  plt::xlabel("x axis");
  plt::ylabel("y axis");
  plt::show(); // 그래프 보여주기

  return 0;
}