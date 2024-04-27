#include "icp/icp.hpp"

ICP::ICP() { std::cout << "ICP Method!!" << std::endl; }
void ICP::setInputSource(InputPointsPtr source) { source_ = source; }
void ICP::setInputTarget(InputPointsPtr target) { target_ = target; }