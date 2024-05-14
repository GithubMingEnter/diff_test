#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "curve.hpp"

template <int N = 2, int PointDim = 2>
class Arc : public Curve<N, PointDim>
{
public:
  using PointType = typename Curve<N, PointDim>::PointType;
  using PointsType = typename Curve<N, PointDim>::PointsType;
  double mAngle_start, mAngle_end;
  bool mIsBig;
  bool mIsAntiClockwise;
  bool mIsImageCoord;

public:
  Arc()
  {
    mDer_pre_points[0] = PointsType::Zero();
    mAngle_start = mAngle_end = 0.;
  }
  Arc(const std::vector<PointType> &list, const PointType &center, const bool isAntiClockwise, const bool IsImageCoord)
   : mCenter(center), mIsAntiClockwise(isAntiClockwise),mIsImageCoord(IsImageCoord)
  {
    if (list.size() != (N))
      std::cerr << "Please check points num" << std::endl;
    mR = (list[0] - center).norm();
    Eigen::Vector2d dxys;
    Eigen::Vector2d dxye;
    if (mIsImageCoord)
    {
       dxys = Eigen::Vector2d( list[0](0)-center(0), center(1) - list[0](1));
       dxye = Eigen::Vector2d( list[1](0)-center(0), center(1) - list[1](1));
    }
    else{
      dxys = Eigen::Vector2d(list[0](0)-center(0), list[0](0)-center(0));
      dxye = Eigen::Vector2d(list[1](0)-center(0), list[1](0)-center(0));
    
    }
    
    // start from x axis +, direction anti-clockwise
    mAngle_start = std::atan2(dxys[1], dxys[0]);
    mAngle_end = std::atan2(dxye[1], dxye[0]);
    if (isAntiClockwise)
    {
      mAngle_start = Arc::normlizeAngle2PI(mAngle_start) / (2 * M_PI);
      mAngle_end = Arc::normlizeAngle2PI(mAngle_end) / (2 * M_PI);
    }
    else
    {
      // // start from x axis -
      mAngle_start = normlizeAngle2PI(M_PI - mAngle_start) / (2 * M_PI);
      mAngle_end = normlizeAngle2PI(M_PI - mAngle_end) / (2 * M_PI);
    }

    if (mAngle_end < mAngle_start)
    {
      mIsBig = false;
    }
    else
    {
      mIsBig = true;
    }
    std::cout << "Angle_end= " << mAngle_end << "\n"
              << "Angle_start = " << mAngle_start << std::endl;
    int i = 0;
    for (const auto it : list)
    {
      mDer_pre_points[0].col(i) = it;
      ++i;
      if (i >= N)
      {
        break;
      }
    }
    computeLength();
  };
  auto at(const double &t, const int &derivative_order = 0) const -> PointType override
  {
    double t_;

    if (t < 0.0)
    {
      std::cerr << "outside range " << std::endl;
      t_ = 0.0;
    }
    else if (t > 1.0)
    {
      std::cerr << "outside range " << std::endl;
      t_ = 1.0;
    }
    else
    {
      t_ = t;
    }
    if (derivative_order > N)
    {
      return PointType::Zero();
      std::cerr << " parameter of derivative_order error " << std::endl;
    }
    double diff_t;

    if (mIsAntiClockwise)
    {
      if (mIsBig)
      {
        t_ = t_ * (mAngle_end - mAngle_start) + mAngle_start;
        t_ *= 2 * M_PI;
        diff_t = 2 * M_PI * (mAngle_end - mAngle_start);
      }
      else
      {
        t_ = t_ * (1 - mAngle_start + mAngle_end) + mAngle_start;
        t_ *= 2 * M_PI;
        diff_t = 2 * M_PI * (1 - mAngle_start + mAngle_end);
      }
    }
    else
    {
      if (mIsBig)
      {
        t_ = t_ * (mAngle_end - mAngle_start) + mAngle_start;
        // t_ = 1 - t_;
        t_ *= 2 * M_PI;
        t_ = t_ + M_PI;
        diff_t = -2 * M_PI * (mAngle_end - mAngle_start);
      }
      else
      {
        t_ = t_ * (1 - mAngle_start + mAngle_end) + mAngle_start;
        t_ = 1 - t_;
        t_ *= 2 * M_PI;
        t_ = t_ + M_PI;
        diff_t = -2 * M_PI * (1 - mAngle_start + mAngle_end);
      }
    }

    PointType temp;
    if (derivative_order == 0)
    {
      // TODO NOTE -sin
      temp = mCenter + mR * PointType(std::cos(t_), -std::sin(t_));
      return temp;
    }
    if (derivative_order == 1)
    {
      temp = mR * PointType(-std::sin(t_), -std::cos(t_)) * diff_t;
      return temp;
    }
    else if (derivative_order == 2)
    {
      temp = mR * PointType(-std::cos(t_), +std::sin(t_)) * std::pow(diff_t, 2);
      return temp;
    }
    else
    {
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
    std::cout << "lenghth = " << this->length_ << std::endl;
  }

  static double normlizeAngle(double ang)
  {
    double a = std::fmod(ang + M_PI, 2.0 * M_PI);
    if (a < 0.0)
    {
      a = a + 2.0 * M_PI;
    }
    return a - M_PI;
  }
  static double normlizeAngle2PI(double ang)
  {
    if (ang < 0.)
    {
      ang += 2 * M_PI;
    }
    double a = std::fmod(ang, 2.0 * M_PI);
    if (a < 0.0)
    {
      a = a + 2.0 * M_PI;
    }
    return a;
  }

private:
  PointsType mDer_pre_points[N]; // derivative
  PointType mCenter;
  double mDer_prefix[N];
  double mR;
  // double mAngle_start,mAngle_end;
};
