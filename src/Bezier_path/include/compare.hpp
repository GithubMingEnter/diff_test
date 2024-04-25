#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "curve.hpp"

using namespace std;

template <int N = 3, int PointDim = 2>
class Bezier : public Curve<N, PointDim>
{
public:
    using PointType = typename Curve<N, PointDim>::PointType;
    using PointsType = typename Curve<N, PointDim>::PointsType;

private:
    PointsType derivative_precal_points_[N + 1];
    int derivative_precal_prefix_[N + 1];

    /**
     * @brief 计算导数缓存
     */
    void derivativePrecompute()
    {
        derivative_precal_prefix_[0] = 1;
        derivative_precal_prefix_[1] = N;
        for (int k = 1; k <= N; ++k)
        {
            int I_range = N - k;
            for (int i = 0; i <= I_range; ++i)
            {
                derivative_precal_points_[k].col(i) =
                    derivative_precal_points_[k - 1].col(i + 1) - derivative_precal_points_[k - 1].col(i);
            }

            derivative_precal_prefix_[k] = derivative_precal_prefix_[k - 1] * (N - k + 1);
        }
    }

    /**
     * @brief 基于数值积分，计算曲线的长度
     */
    void computeLength() override
    {
        derivativePrecompute();
        Curve<N, PointDim>::computeLength();
    }

public:
    Bezier() { derivative_precal_points_[0] = PointsType::Zero(); }

    Bezier(const std::initializer_list<PointType> &list) { set(std::forward<decltype(list)>(list)); }

    template <typename T = array<double, PointDim>>
    Bezier(const std::initializer_list<T> &list)
    {
        set(std::forward<decltype(list)>(list));
    }

    void set(const std::initializer_list<PointType> &list)
    {
        int i = 0;
        for (const auto &it : list)
        {
            derivative_precal_points_[0].col(i) = it;
            if (++i > N)
            {
                break;
            }
        }
        computeLength();
    }

    template <typename T = array<double, PointDim>>
    void set(const std::initializer_list<PointType> &list)
    {
        int i = 0;
        for (const auto &it : list)
        {
            derivative_precal_points_[0].col(i) = it;
            if (++i > N)
            {
                break;
            }
        }
        computeLength();
    }

    auto at(const double &t, const int &derivative_order = 0) const -> PointType override
    {
        double t_ = std::clamp(t, 0.0, 1.0);

        if (derivative_order > N)
        {
            return PointType::Zero();
        }

        /// De Casteljau’s Algorithm ///
        PointsType temp = derivative_precal_points_[derivative_order];

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
        return derivative_precal_prefix_[derivative_order] * temp.col(0);
    }

    void print(std::ostream &out, const string &s = "") const override
    {
        out << s << derivative_precal_points_[0] << '\n';
    }
};