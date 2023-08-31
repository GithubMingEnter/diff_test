#include <iostream> 
#include <fstream>
#include <ompl/base/spaces/DubinsStateSpace.h>
#include <ompl/base/spaces/ReedsSheppStateSpace.h>  
#include <ompl/base/ScopedState.h>  
//空间状态的定义 http://ompl.kavrakilab.org/classompl_1_1base_1_1ScopedState.html
#include <ompl/geometric/SimpleSetup.h> 
//几何问题通常所需要的类集 http://ompl.kavrakilab.org/classompl_1_1geometric_1_1SimpleSetup.html
#include <ompl/config.h>
//定义了OMPL版本号信息，及相关功能是否编译过~
#include <boost/program_options.hpp> 
//程序命令行参数的输入及解析 https://blog.csdn.net/morning_color/article/details/50241987
using namespace std;
namespace ob = ompl::base;
namespace og = ompl::geometric;
namespace po = boost::program_options;

bool isStateValidEasy(const ob::SpaceInformation *si, const ob::State *state) {
	const auto *s = state->as<ob::SE2StateSpace::StateType>();
	double x = s->getX(), y = s->getY();
	return si->satisfiesBounds(s) && (x < 5 || x>13 || (y > 8.5 && y < 9.5));
	
}
bool isStateValidHard(const ob::SpaceInformation *si, const ob::State *state) {
	return si->satisfiesBounds(state);
}
void printTrajectory(const ob::StateSpacePtr& space, const std::vector<double>& pt) {
	if (pt.size() != 3) throw ompl::Exception("3 arguments required for trajectory option");
	const unsigned int num_pts = 50;
	ob::ScopedState<> from(space), to(space), s(space);
	std::vector<double> reals;

	from[0] = from[1] = from[2] = 0.;

	to[0] = pt[0];
	to[1] = pt[1];
	to[2] = pt[2];

	std::cout << "distance: " << space->distance(from(), to()) << "\npath:\n";
	for (unsigned int i = 0; i <= num_pts; ++i)
	{
		space->interpolate(from(), to(), (double)i / num_pts, s());
		reals = s.reals();
		std::cout << "path " << reals[0] << ' ' << reals[1] << ' ' << reals[2] << ' ' << std::endl;
	}
}
void printDistanceGrid(const ob::StateSpacePtr& space) {
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

	/*ofstream outf;
	outf.open("distance.txt");*/
	const unsigned int num_pts = 200;
	ob::ScopedState<> from(space), to(space);
	from[0] = from[1] = from[2] = 0.;

	for (unsigned int i = 0; i < num_pts; ++i)
		for (unsigned int j = 0; j < num_pts; ++j)
			for (unsigned int k = 0; k < num_pts; ++k)
			{
				to[0] = 5. * (2. * (double)i / num_pts - 1.);
				to[1] = 5. * (2. * (double)j / num_pts - 1.);
				to[2] = boost::math::constants::pi<double>() * (2. * (double)k / num_pts - 1.);
				//outf << space->distance(from(), to()) << " ";
				//std::cout << space->distance(from(), to()) << '\n';
			}
	//outf.close();
}

void plan(const ob::StateSpacePtr &space, bool easy) {
	ob::ScopedState<> start(space), goal(space); //根据所使用的空间分配状态
	ob::RealVectorBounds bounds(2);  //边界空间的维度 此处2维 每个维度都有个low和high值 故bounds.low 有两个值
	bounds.setLow(0);
	int k=bounds.high.size();
	if (easy)
		bounds.setHigh(18);
	else
	{
		bounds.high[0] = 6;
		bounds.high[1] = .6;
	}
	space->as<ob::SE2StateSpace>()->setBounds(bounds);//as转换为某个实例所需要的类型

	og::SimpleSetup ss(space); //构造所需的规划空间

	//对此空间的有效性进行检查 http://ompl.kavrakilab.org/stateValidation.html
	const ob::SpaceInformation *si = ss.getSpaceInformation().get();
	auto isStateValid = easy ? isStateValidEasy : isStateValidHard; //函数作为右值赋值给函数指针，成员函数需取地址后赋值给函数指针（语法）
	ss.setStateValidityChecker([isStateValid, si](const ob::State *state) {return isStateValid(si, state); });

	if (easy) {
		start[0] = start[1] = 1.0; start[2] = 0;
		goal[0] = goal[1] = 16; goal[2] = -.99*boost::math::constants::pi<double>();
	}
	else
	{
		start[0] = start[1] = .5; start[2] = .5*boost::math::constants::pi<double>();;
		goal[0] = 5.5; goal[1] = .5; goal[2] = .5*boost::math::constants::pi<double>();
	}
	ss.setStartAndGoalStates(start, goal);

	//可选的参数，从而获得更多的输出信息
	ss.getSpaceInformation()->setStateValidityCheckingResolution(0.005);//设置需要验证状态有效性的分辨率，以便将两个状态之间的运动视为有效。该值指定为空间范围的一部分
	ss.setup();//自动创建规划所需的类，slove()函数的
	ss.print();

	ob::PlannerStatus sloved = ss.solve(/*const base::PlannerTerminationCondition &ptc*/);	//按时间，也有按自定义函数
	if (sloved) {
		vector<double> reals;
		cout << "solution" << endl;
		ss.simplifySolution();//尝试简化当前路径，简化方式，默认0s内简化，或按自定义函数简化
		og::PathGeometric path = ss.getSolutionPath(); //获取路径，
		path.interpolate(); //默认插值，指定插值数量插值法
		path.printAsMatrix(cout); //打印矩阵形式
		
	}
	else
		cout << "no solution" << endl;
}



int main(int argc,char** argv) {
	cout << OMPL_VERSION << endl;
	argc = 7;
	argv[0] = "";
	argv[1] = "--easyplan";
	argv[2] = "--trajectory";
	argv[3] = "7.1";
	argv[4] = "6.2";
	argv[5] = "1.34";
	argv[6] = "--distance";
	try
	{
		//深入浅出boost::program_options ，命令行或配置文件读取参数选项 https://blog.csdn.net/Windgs_YF/article/details/81201456
		po::options_description desc("Options"); //输入参数的描述
		desc.add_options()
			("help", "show help message")
			("dubins", "use Dubins state space")
			("dubinssym", "use symmetrized Dubins state space")
			("reedsshepp", "use reeds-shepp state space(default)")
			("easyplan", "easy planning problem & print path")
			("hardplan", "hard planning problem & print path")
			("trajectory", po::value<vector<double>>()->multitoken(), "print x y theta from start goal") //multitoken()的作用就是告诉编译器,该选项可接受多个值
			("distance", "print distance grid")
			;
		
		po::variables_map vm; //容器,用于存储解析后的选项,是std::map的派生类,可以像关联容器一样使用
		po::store(po::parse_command_line(argc, argv, desc), vm); //命令行的参数用store解析出来并存储至vm
		po::notify(vm);//更新所有外部变量
		//count()->检测某个选项是否被输入
		if (vm.count("help")) { cout << desc << "/n"; return 1; };
		
		ob::StateSpacePtr space(make_shared<ob::ReedsSheppStateSpace>() );//指向reedsshepp状态空间的智能指针
		if (vm.count("dubins")!=0u) 
			space = make_shared<ob::DubinsStateSpace>();
		if (vm.count("dubinssym")!=0u) 
			space = make_shared<ob::DubinsStateSpace>(1., true); //对称dubins状态空间
		if (vm.count("easyplan") != 0u) 
			plan(space, true);
		if (vm.count("hardplan") != 0u) 
			plan(space, false);
		if (vm.count("trajectory") != 0u)
			printTrajectory(space, vm["trajectroy"].as<std::vector<double>>());//variables_map(选项存储器)是std::map的派生类,可以像关联容器一样使用,通过operator[]来取出其中的元素.但其内部的元素类型value_type是boost::any,用来存储不确定类型的参数值,必须通过模板成员函数as<type>()做类型转换后,才能获取其具体值.
		if (vm.count("distance") != 0u) 
			printDistanceGrid(space);
	}
	catch (const std::exception&e)
	{
		cerr << "error:" << e.what() << "\n";
		return 1;
	}
	catch (...) {
		cerr << "exception of unkonw type!\n";
	}
	return 0;

}
