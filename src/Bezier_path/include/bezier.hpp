#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "curve.hpp"
/* N is order of Bezier
  single segment Bezier spline
 */
template <int N = 2, int PointDim = 2>
class Bezier : public Curve<N, PointDim>
{
public:
    using PointType = typename Curve<N, PointDim>::PointType;
    using PointsType = typename Curve<N, PointDim>::PointsType;

private:
    PointsType mDer_pre_points[N + 1];//derivative 
    int mDer_prefix[N + 1];

    void derivativePrecompute()
    {
        mDer_prefix[0] = 1;
        mDer_prefix[1] = N;
        for (int k = 1; k <= N; ++k)
        {
            int I_range = N-k;
            for(int i=0;i<=I_range;++i)
            {
                mDer_pre_points[k].col(i) =
                mDer_pre_points[k - 1].col(i + 1) - mDer_pre_points[k - 1].col(i);
            }
            mDer_prefix[k] = mDer_prefix[k - 1] * (N - k + 1);
        }
        
    }

    void computeLength() override
    {
        derivativePrecompute();
        Curve<N, PointDim>::computeLength();
    }

public:
    Bezier() { mDer_pre_points[0] = PointsType::Zero(); }
    Bezier(const std::initializer_list<PointType> &list) { set(std::forward<decltype(list)>(list)); }


    Bezier(const std::vector<PointType> &list){
        for(int i=0;i<=N;++i){
            mDer_pre_points[0].col(i)=list[i];
        }
        computeLength();
    }

    void set(const std::initializer_list<PointType> &list)
    {
        int i=0;
        if(list.size()!=(N+1))
            std::cerr<<"Please check points num"<<std::endl;
        for(const auto it:list){
            mDer_pre_points[0].col(i) = it;
            ++i;
            if(i>N){
                break;
            }    
        }
        // TODO change pos of putting
        computeLength();
    }
    


    auto at(const double &t, const int &derivative_order = 0) const -> PointType override
    {
        double t_ = std::clamp(t, 0.0, 1.0);
        if (derivative_order > N)
        {
            return PointType::Zero();
            std::cerr << " parameter of derivative_order error " << std::endl;
        }
        /* De Casteljau’s Algorithm 德卡斯特里奥算法 */
        PointsType temp = mDer_pre_points[derivative_order];
        int I_range = N - derivative_order;
        for (int i = 0; i < I_range; ++i)
        {
            int J_range = I_range - i;
            for (int j = 0; j < J_range; ++j)
            {
                {
                    temp.col(j) = (1.0 - t_) * temp.col(j) + t_ * temp.col(j + 1);
                }
            }
        }
        return mDer_prefix[derivative_order] * temp.col(0);
    }

    void print(std::ostream &out, const std::string &s = "") const override
    {
        out << s << mDer_pre_points[0] << "\n";
    }
};
