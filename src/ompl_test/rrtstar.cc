#include <ompl/base/SpaceInformation.h>
#include <ompl/base/spaces/SE3StateSpace.h>
#include <ompl/base/StateSpace.h>
#include <ompl/base/Path.h>
#include <ompl/base/spaces/RealVectorBounds.h>
#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl/base/StateValidityChecker.h>
#include <ompl/base/OptimizationObjective.h>
#include <ompl/base/objectives/PathLengthOptimizationObjective.h>
// #include <ompl/geometric/planners/rrt/RRT.h>
#include <ompl/geometric/planners/rrt/RRTstar.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/config.h>
 
#include <iostream>
#include <fstream>
#include <ostream>
#include "boost/bind.hpp"
 
namespace ob = ompl::base;
namespace og = ompl::geometric;
 
/*  使用和不使用ompl::geometric::SimpleSetup类。主要区别在于，
 在不使用SimpleSetup类的情况下，需要显式实例化ompl::base::SpaceInformation
 和ompl::base::ProblemDefinition。此外，还必须显式地实例化要使用的规划算法。 */
class ValidityChecker: public ob::StateValidityChecker{
  public:
  ValidityChecker(const ob::SpaceInformationPtr & si):
    ob::StateValidityChecker(si){}
  
  bool isValid(const ob::State* state) const{
    return this->clearance(state)>0.0;
  }
  
  double clearance(const ob::State* state) const{
    const ob::RealVectorStateSpace::StateType* state2D = 
       state->as<ob::RealVectorStateSpace::StateType>();
 
       double x = state2D->values[0];
       double y = state2D->values[1];
 
       return sqrt((x - 0.5)*(x - 0.5) + (y-0.5)*(y-0.5)) - 0.25;
  }
};
 
ob::OptimizationObjectivePtr getPathLengthObjective(const ob::SpaceInformationPtr& si){
  return ob::OptimizationObjectivePtr(new ob::PathLengthOptimizationObjective(si));
}
 
void OptimalPlanningRRTStar(){
  ob::StateSpacePtr space(new ob::RealVectorStateSpace(2));
 
  space->as<ob::RealVectorStateSpace>()->setBounds(0.0,1.0);
 
  ob::SpaceInformationPtr si(new ob::SpaceInformation(space));
  si->setStateValidityChecker(ob::StateValidityCheckerPtr(new ValidityChecker(si)));
  si->setup();
 
  ob::ScopedState<> start(space);
  start->as<ob::RealVectorStateSpace::StateType>()->values[0] = 0.0;
  start->as<ob::RealVectorStateSpace::StateType>()->values[1] = 0.0;
 
  ob::ScopedState<> goal(space);
  goal->as<ob::RealVectorStateSpace::StateType>()->values[0] = 1.0;
  goal->as<ob::RealVectorStateSpace::StateType>()->values[1] = 1.0;
//  创建ompl::base::ProblemDefinition的实例：
  ob::ProblemDefinitionPtr pdef(new ob::ProblemDefinition(si));
  pdef->setStartAndGoalStates(start,goal);
  pdef->setOptimizationObjective(getPathLengthObjective(si));
 
  ob::PlannerPtr optimizingPlanner(new og::RRTstar(si));
  optimizingPlanner->setProblemDefinition(pdef);
  optimizingPlanner->setup();
 
  ob::PlannerStatus solved = optimizingPlanner->solve(1.0);
 
  if(solved){
    std::cout<<"---------solved!--------"<<std::endl;
    og::PathGeometric* path = pdef->getSolutionPath()->as<og::PathGeometric>();
    std::cout<<"path point number="<<path->getStateCount()<<std::endl;
    std::ofstream ofs0("../path_rrt_star.dat");
 
    for(size_t path_idx = 0; path_idx < path->getStateCount(); path_idx++){
      const ob::RealVectorStateSpace::StateType *state = path->getState(path_idx)->as<ob::RealVectorStateSpace::StateType>();
      std::cout<<"i="<<path_idx<<",(x,y)="<<state->values[0]<<","<<state->values[1]<<std::endl;
      ofs0<<state->values[0]<<" "<<state->values[1]<<std::endl;
    }
    pdef->getSolutionPath()->print(std::cout);
  }
 
}
 
int main(){
  OptimalPlanningRRTStar();
  return 0;
}