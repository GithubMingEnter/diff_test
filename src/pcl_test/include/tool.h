#pragma once

#include<bits/stdc++.h>
#include<Eigen/Dense>
/* time statistic */
#define ST_MS(Run) [&](){\
    auto t1 = std::chrono::system_clock::now();\
    auto res = Run;\
    auto t2 = std::chrono::system_clock::now();\
    auto dt = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();\
  std::cout << #Run << " elapsed time: " << dt << "ms" << std::endl;\
  return res;\
}()

#define TIMER_START(_X) auto _X##_start = std::chrono::steady_clock::now(),_X##_stop= _X##_start 
#define TIMER_STOP(_X) _X##_stop=std::chrono::steady_clock::now() 
#define TIMER_NS(_X,str) \
    std::cout<<str<<":"\
    <<std::chrono::duration_cast<std::chrono::nanoseconds>(_X##_stop-_X##_start).count()\
    <<" ns\n"
// 
#define TIMER_US(_X,str) \
    std::cout<<str<<":"\
    <<std::chrono::duration_cast<std::chrono::microseconds>(_X##_stop-_X##_start).count()\
    <<" us\n"
#define TIMER_MS(_X,str) \
    std::cout<<str<<":"\
    <<std::chrono::duration_cast<std::chrono::milliseconds>(_X##_stop-_X##_start).count()\
    <<" ms\n"

#define TIMER_S(_X,str) \
    std::cout<<str<<":"\
    <<std::chrono::duration_cast<std::chrono::seconds>(_X##_stop-_X##_start).count()\
    <<" s\n"

#define TIMER_MIN(_X,str) \
    std::cout<<str<<":"\
    <<std::chrono::duration_cast<std::chrono::minutes>(_X##_stop-_X##_start).count()\
    <<" min\n"
