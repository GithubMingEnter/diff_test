/*
 * main.c
 *
 *  Created on: Oct 9, 2018
 *      Author: ming
 * x=[x_1,x_2,x_3,x_4]^{\mathrm{T}}
    \\
    目标函数：f(x)=x_1*x_4*(x_1+x_2+x_3)+x_3
    \\
    g_1(x)=x_1*x_2*x_3*x_4\ge 25
    \\
    g_2(x)=x_{1}^{2}+x_{2}^{2}+x_{3}^{2}+x_{4}^{2}=40
 # Set the project name

# 终端直接编译 g++ nlopt_test1.cc -lnlopt -o nlopt_test
 */


#include <stdio.h>
#include <math.h>
#include "nlopt.h"
#include <chrono>
#include <ostream>
#include <iostream>
#define INF (1.0/0.0)
int i=0;
using namespace std;
//目标函数；
double utility(unsigned n, const double *x, double *grad, void *data)
{
    if(grad){
        grad[0]=2*x[0]*x[3]+x[3]*(x[1]+x[2]);
        grad[1]=x[3]*x[0];
        grad[2]=x[0]*x[3]+1;
        grad[4]=x[0]*(x[0]+x[1]+x[2]);
    }
//    printf("迭代次数 i= %d, x[0]=%f, x[1]= %f，x[2]= %f，x[3]= %f，f(x1,x2,x3,x4)=%f\n",
//            i++,x[0],x[1],x[2],x[3],x[0]*x[3]*(x[0]+x[1]+x[2])+x[2]);
    return ( x[0]*x[3]*(x[0]+x[1]+x[2])+x[2] );
}

//等式限制条件；
double constraint(unsigned n,const double *x,double *grad, void *data)
{
    if(grad){
        grad[0]= 2*x[0];
        grad[1]= 2*x[1];
        grad[2]= 2*x[2];
        grad[3]= 2*x[3];
    }
//    cout<<"constaint="<<x[0]*x[0]+x[1]*x[1]+x[2]*x[2]+x[3]*x[3]-40<<endl;
    return (x[0]*x[0]+x[1]*x[1]+x[2]*x[2]+x[3]*x[3]-40);
}

//不等式限制条件；
double inconstraint(unsigned n,const double *x,double *grad, void *data)
{
    if(grad){
        grad[0]=x[1]*x[2]*x[3] ;
        grad[1]= x[0]*x[2]*x[3];
        grad[2]=x[0]*x[1]*x[3] ;
        grad[3]= x[0]*x[1]*x[2];
    }
//    cout<<"in="<<-x[0]*x[1]*x[2]*x[3]+25<<endl;
    return (-x[0]*x[1]*x[2]*x[3]+25);

}


using namespace std;
int main(int argc, char const *argv[])
{
    chrono::steady_clock::time_point ts=chrono::steady_clock::now();

    double tol=1e-6;
    double lb[4]={1,1,1,1};      //x1、x2的下边界；
    double ub[4]={5,5,5,5};
    double x[4]={1, 1,1,1};      //给x1、x2赋予初始值；
    double f_min;
    for(int i=0;i<10;i++)
    {
     nlopt_opt opt=nlopt_create(NLOPT_GN_ORIG_DIRECT,4);//NLOPT_GN_ISRES
     nlopt_set_lower_bounds(opt,lb);
     nlopt_set_upper_bounds(opt,ub);
     nlopt_set_min_objective(opt,utility,NULL);
     nlopt_add_inequality_constraint(opt,inconstraint,NULL,tol);
     nlopt_add_equality_constraint(opt,constraint,NULL,tol);

     nlopt_set_xtol_rel(opt,tol);


     if(nlopt_optimize(opt,x,&f_min))
     {
        cout<<"fmin= "<<f_min<<endl<<" x= "<<x[0]<<" "<<x[1]<<" "<<x[2]<<" "<<x[3]<<endl;
     }
     nlopt_destroy(opt);
    }

    chrono::steady_clock::time_point te=chrono::steady_clock::now();
    chrono::duration<double> time=chrono::duration_cast<chrono::duration<double>>(te-ts);
    std::cout<<"time:"<<time.count()<<" s"<<endl;
    std::cout<<"avg time:"<<time.count()/10<<" s"<<endl;

    return 0;
}