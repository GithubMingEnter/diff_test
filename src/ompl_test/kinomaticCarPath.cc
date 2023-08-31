#include <ompl/base/spaces/DubinsStateSpace.h>
#include <ompl/base/spaces/ReedsSheppStateSpace.h>
#include <ompl/base/ScopedState.h>
//空间状态的定义 http://ompl.kavrakilab.org/classompl_1_1base_1_1ScopedState.html
#include <ompl/geometric/SimpleSetup.h>
//几何问题通常所需要的类集 http://ompl.kavrakilab.org/classompl_1_1geometric_1_1SimpleSetup.html
#include <boost/program_options.hpp>
//程序命令行参数的输入及解析 https://blog.csdn.net/morning_color/article/details/50241987
namespace ob = ompl::base;
namespace og= ompl::geometric;
namespace po = boost::program_options;

// The easy problem is the standard narrow passage problem: two big open
// spaces connected by a narrow passage. The hard problem is essentially
// one long narrow passage with the robot facing towards the long walls
// in both the start and goal configurations.




bool isStateValidEasy(const ob::SpaceInformation *si, const ob::State *state)
{
    const auto *s =state->as<ob::SE2StateSpace::StateType>();
    double x=s->getX(),y=s->getY();
    return si->satisfiesBounds(s) && (x<5||x>13 ||(y>8.5 &&y<9.5));
}
bool isStateValidHard(const ob::SpaceInformation *si, const ob::State *state)
{
    return si->satisfiesBounds(state);
}
void plan(const ob::StateSpacePtr& space,bool easy)
{
    ob::ScopedState<> start(space),goal(space);
    ob::RealVectorBounds bounds(2);
    bounds.setLow(0);
    if(easy)
        bounds.setHigh(18);
    else
    {
        bounds.high[0]=6;
        bounds.high[1]=.6;
    }
    space->as<ob::SE2StateSpace>()->setBounds(bounds);

    og::SimpleSetup ss(space);

    const ob::SpaceInformation *si= ss.getSpaceInformation().get();
    auto isStateValid = easy? isStateValidEasy:isStateValidHard;
    ss.setStateValidityChecker([isStateValid,si](const ob::State *state)
    {
        return isStateValid(si,state);
    });

    if(easy)
    {
        start[0]=start[1]=1.0;
        start[2]=0.0;
        goal[0]=goal[1]=17;
        goal[2]=-.99*boost::math::constants::pi<double>();
    }
    else
    {
         start[0] = start[1] = .5; start[2] = .5*boost::math::constants::pi<double>();;
        goal[0] = 5.5; goal[1] = .5; goal[2] = .5*boost::math::constants::pi<double>();
    }
    ss.setStartAndGoalStates(start,goal);

    ss.getSpaceInformation()->setStateValidityCheckingResolution(0.005);
    ss.setup();
    ss.print();

    ob::PlannerStatus solved = ss.solve(30.0);

    if(solved)
    {
        std::vector<double> real;
        std::cout<<"Found solution"<<std::endl;
        ss.simplifySolution();
        og::PathGeometric path =ss.getSolutionPath();//get path
        path.interpolate(1000);
        // path.printAsMatrix(std::cout);
    }
    else
        std::cout << "No solution found" << std::endl;
}

void printDistanceGrid(const ob::StateSpacePtr& space)
{
    // print the distance for (x,y,theta) for all points in a 3D grid in SE(2)
    // over [-5,5) x [-5, 5) x [-pi,pi).
    //
    // The output should be redirected to a file, say, distance.txt. This
    // can then be read and plotted in Matlab like so:
    //     x = reshape(load('distance.txt'),200,200,200);
    //     for i=1:200,
    //         contourf(squeeze(x(i,:,:)),30);
    //         axis equal; axis tight; colorbar; pause;
    //     end;
    const unsigned int num_pts = 200;
    ob::ScopedState<> from(space), to(space);
    from[0] = from[1] = from[2] = 0.;

    for (unsigned int i=0; i<num_pts; ++i)
        for (unsigned int j=0; j<num_pts; ++j)
            for (unsigned int k=0; k<num_pts; ++k)
            {
                to[0] = 5. * (2. * (double)i/num_pts - 1.);
                to[1] = 5. * (2. * (double)j/num_pts - 1.);
                to[2] = boost::math::constants::pi<double>() * (2. * (double)k/num_pts - 1.);
                std::cout << space->distance(from(), to()) << '\n';
            }

}

void printTrajectory(const ob::StateSpacePtr& space, const std::vector<double>& pt)
{
    if (pt.size()!=3) throw ompl::Exception("3 arguments required for trajectory option");
    const unsigned int num_pts = 50;
    ob::ScopedState<> from(space), to(space), s(space);
    std::vector<double> reals;

    from[0] = from[1] = from[2] = 0.;

    to[0] = pt[0];
    to[1] = pt[1];
    to[2] = pt[2];

    std::cout << "distance: " << space->distance(from(), to()) << "\npath:\n";
    for (unsigned int i=0; i<=num_pts; ++i)
    {
        space->interpolate(from(), to(), (double)i/num_pts, s());
        reals = s.reals();
        std::cout << "path " << reals[0] << ' ' << reals[1] << ' ' << reals[2] << ' ' << std::endl;
    }
}

int main(int argc,char* argv[])
{
    try
    {
        ob::StateSpacePtr space_ptr(std::make_shared<ob::ReedsSheppStateSpace>());
        // space_ptr = std::make_shared<ob::DubinsStateSpace>();
        plan(space_ptr,true);
        printDistanceGrid(space_ptr);



    }
    catch(std::exception & e){
        std::cerr<<"error : "<<e.what()<<"\n";
        return 1;
    }
    catch(...){ //TODO ...
        std::cerr << "Exception of unknown type!\n";
    }

    return 0;
}





