
#include<iostream>
#include<math.h>

inline double Normalize2PI(double angle)
{
    return fmod(fmod(angle, 2.0 * M_PI) + 2.0 * M_PI, 2.0 * M_PI);
}

inline double NormalizePI(double angle)
{
    double a = Normalize2PI(angle);
    if (a > M_PI)
    {
        a -= 2.0 * M_PI;
    }

    return a;
}

int main(){
   double x=NormalizePI(-171.0/180.*M_PI);

    return 0;
}