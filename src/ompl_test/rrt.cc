#include <ompl/base/SpaceInformation.h>
#include <ompl/base/spaces/SE3StateSpace.h>
#include <ompl/geometric/planners/rrt/RRT.h>
#include <ompl/geometric/SimpleSetup.h>
 
#include <ompl/config.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include "boost/bind.hpp"
 
using namespace std;
 
namespace ob = ompl::base;
namespace og = ompl::geometric;
 
bool isStateValid(const ob::State *state)
{
    // 将抽象状态类型强制转换为我们期望的类型
  const ob::SE3StateSpace::StateType *se3state = state->as<ob::SE3StateSpace::StateType>();
 
  // 提取状态的第一个组件并将其转换为我们期望的
  const ob::RealVectorStateSpace::StateType *pos = se3state->as<ob::RealVectorStateSpace::StateType>(0);
 
  // 提取状态的第二个组成部分并将其转换为我们的预期
  const ob::SO3StateSpace::StateType *rot = se3state->as<ob::SO3StateSpace::StateType>(1);
 
  // check validity of state defined by pos & rot
 
  // 返回一个始终为 true 的值，但使用我们定义的两个变量，因此我们避免编译器警告
  // warnings
  return (const void *)rot != (const void *)pos;
}
 
void planWithSimpleSetup(void)
{
  // 构建我们正在规划的状态空间
  ob::StateSpacePtr space(new ob::SE3StateSpace());
 
  // set the bounds for the R^3 part of SE(3)
  ob::RealVectorBounds bounds(3);
  bounds.setLow(-1);
  bounds.setHigh(1);
 
  space->as<ob::SE3StateSpace>()->setBounds(bounds);
 
  // 定义简单的启动程序类
  og::SimpleSetup ss(space);
 
  // 为此状态空间设置状态有效性检查e
  ss.setStateValidityChecker(boost::bind(&isStateValid, _1));
 
  // 创建随机启动状态
  ob::ScopedState<> start(space);
  start.random();
 
  // create a random goal state
  ob::ScopedState<> goal(space);
  goal.random();
 
  // set the start and goal states
  ss.setStartAndGoalStates(start, goal);
 
  ob::PlannerPtr planner(new og::RRT(ss.getSpaceInformation()));
  ss.setPlanner(planner);
 
  // attempt to solve the problem within one second of planning time
  ob::PlannerStatus solved = ss.solve(1.0);
 
  if (solved) {
    std::cout << "Found solution:" << std::endl;
    // print the path to screen
 
    std::ofstream ofs0("../plot/path0.dat");
    ss.getSolutionPath().printAsMatrix(ofs0);
 
    ss.simplifySolution();
    ss.getSolutionPath().print(std::cout);
 
    std::ofstream ofs("../plot/path.dat");
    ss.getSolutionPath().printAsMatrix(ofs);
  } else
    std::cout << "No solution found" << std::endl;
}
 
int main(int, char **)
{
  std::cout << "OMPL version: " << OMPL_VERSION << std::endl;
  planWithSimpleSetup();
 
  return 0;
}