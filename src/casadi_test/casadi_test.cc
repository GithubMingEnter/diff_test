#include<iostream>
#include<vector>
#include <casadi/casadi.hpp>
#include<chrono>
using namespace std;



int main(int argc, char * argv[] )
{
    cout<<"casadi_test"<<endl;
    auto ts=chrono::steady_clock::now();
    casadi::SX x=casadi::SX::sym("x",4);
/*
  *    min  x1*x4*(x1 + x2 + x3) + x3
  *    s.t.    x1*x2*x3*x4 >=25
                  x1^2 + x2^2 + x3^2 + x4^2 = 40
                  1 <= x1, x2, x3, x4 <= 5
*/// Optimization variables
    casadi::SX f=x(0)*x(3)*(x(0)+x(1)+x(2))+x(2);
    // Objective
    // Constraints
    casadi::SX g=vertcat(x(0)*x(1)*x(3),pow(x(0),2)+pow(x(1),2)+pow(x(2),2)+pow(x(3),2));
    std::cout << "g:" << g << std::endl;
    // Initial guess and bounds for the optimization variables
    vector<double> x0{5,5,0.5,0.5};
    vector<double> lbx{1,1,1,1};
    vector<double> ubx{5,5,5,5};

    //Nonlinear bounds
    vector<double> lbg = {25,40};
    vector<double> ubg={casadi::inf,40};

    casadi::SXDict nlp = {{"x",x},{"f",f},{"g",g}};
    // Create NLP solver and buffers
    casadi::Function solver =casadi::nlpsol("solver","ipopt",nlp);
    std::map<std::string,casadi::DM> arg,res;
    // Solve the NLP
    arg["lbx"]=lbx;
    arg["ubx"]=ubx;
    arg["lbg"]=lbg;
    arg["ubg"]=ubg;
    arg["x0"]=x0;
    res = solver(arg);
    // solving again makes no difference
    auto sol1=solver(arg);
    auto sol2=casadi::Opti();
    sol2.subject_to();
    /* int solver_status = res.at("return_status").scalar<int>();
    if(solver_status==0)
    {
      cout<<"Optimization successful "<<endl;
    }
    else{
      cout << "Optimization failed with status code: " << solver_status << endl;
     
    } */
    casadi::Dict solver_status=solver.stats();
    cout<<solver.stats()<<endl;
    cout<<solver.stats().at("success")<<endl;
    auto te=chrono::steady_clock::now();
    auto time_diff = std::chrono::duration_cast<chrono::microseconds>(te-ts);
    cout<<" time lost :"<<time_diff.count()/1000<<endl;

    // Print the solution
  cout << "--------------------------------" << endl;
  std::cout << res << std::endl;
  cout << "--------------------------------" << endl;
  cout << "Optimal solution for p = " << arg.at("p") << ":" << endl;
  cout<<"objective: "<<res.at("f")<<endl;
  cout<<"solution: " <<res.at("x")<<endl;
  // cout << setw(30) << "Dual solution (x): " << res.at("lam_x") << endl;
  // cout << setw(30) << "Dual solution (g): " << res.at("lam_g") << endl;

}






