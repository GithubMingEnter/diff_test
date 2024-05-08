#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "curve.hpp"
static double normlizeAngle(double ang)
{
    double a = std::fmod(ang + M_PI, 2.0 * M_PI);
    if (a < 0.0)
    {
        a = a + 2.0 * M_PI;
    }
    return a - M_PI;    
}
template <int N = 2, int PointDim = 2>
class Arc: public Curve<N, PointDim>
{
public:
  using PointType = typename Curve<N, PointDim>::PointType;
  using PointsType = typename Curve<N, PointDim>::PointsType;
  double mAngle_start,mAngle_end;
public:
  Arc(){ 
    mDer_pre_points[0] = PointsType::Zero();
    mAngle_start=mAngle_end=0.;
     }
  Arc(const std::vector<PointType> &list,const PointType& center):mCenter(center)
    {
      if (list.size() != (N))
        std::cerr << "Please check points num" << std::endl;
      mR=(list[0]-center).norm();
      auto dxys=list[0]-center;
      auto dxye=list[1]-center;
      // start from x axis +, direction anti-clockwise
       mAngle_start=normlizeAngle(std::atan2(dxys[1],dxys[0]))/M_PI ;
       mAngle_end = normlizeAngle(std::atan2(dxye[1],dxye[0]))/M_PI;
      std::cout<<"Angle_end= "<<mAngle_end<<"\n"<<"Angle_start = "<<mAngle_start<<std::endl;
      int i=0;
      for(const auto it:list){
          mDer_pre_points[0].col(i) = it;
          ++i;
          if(i>=N){
              break;
          }    
      }
      computeLength();
    };

  auto at(const double &t, const int &derivative_order = 0) const -> PointType override
  {
    double t_;
    
    if(t<0.0){
            std::cerr<<"outside range "<<std::endl;
            t_=0.0;
        } 
        else if(t>1.0)
        {
            std::cerr<<"outside range "<<std::endl;
            t_=1.0;
        }
        else {
            t_=t;
        }
    t_=t_*(mAngle_end-mAngle_start)+mAngle_start;
    t_*=M_PI;

    if (derivative_order > N)
    {
        return PointType::Zero();
        std::cerr << " parameter of derivative_order error " << std::endl;
    }
    PointType temp ;
    if(derivative_order == 0)
    {
      temp=mCenter+mR*PointType(std::cos(t_),std::sin(t_));

      return temp;
    }
    if(derivative_order == 1)
    {
      temp=mR*PointType(-std::sin(t_),std::cos(t_))*M_PI;
      
      return temp;
    }
    else if(derivative_order == 2)
    {
      temp=mR*PointType(-std::cos(t_),-std::sin(t_))*M_PI*M_PI;
      return temp;
    }
    else{
      std::cerr << " parameter of derivative_order error " << std::endl;
      return temp;
    }

  }
  void print(std::ostream &out, const std::string &s = "") const override
  {
      out << s << mDer_pre_points[0] << "\n";
  }
  void computeLength() override
  {
    Curve<N, PointDim>::computeLength();
    std::cout<<"lenghth = "<<this->length_<<std::endl;
  }

private:
  PointsType mDer_pre_points[N]; // derivative
  PointType mCenter;
  double mDer_prefix[N];
  double mR;
  // double mAngle_start,mAngle_end;

  
  

};
