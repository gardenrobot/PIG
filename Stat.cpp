// 
// File: Stat.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Stat.h"

#include <iostream>

using namespace std;


Stat::Stat(int base)
:base(base)
,currentStage(6)
{
}


Stat::Stat(const Stat& original)
:base(original.base)
,currentStage(original.currentStage)
{
}


Stat& Stat::operator-=(int change)
{
    return operator+=(-change);
}


Stat& Stat::operator+=(int change)
{
    currentStage += change;
    if(currentStage < 0)
    {
        currentStage = 0;
    }
    else if(currentStage > 12)
    {
        currentStage = 12;
    }

    return *this;
}


float Stat::getBaseValue() const
{
    return base;
}


float Stat::getModValue() const
{
    float mod = getModAt(currentStage);

    return base * mod;
}


float Stat::getModAt(int stage) const
{
    switch(stage)
    {
        case 0:
            return (float)2/8;
        case 1:
            return (float)2/7;
        case 2:
            return (float)2/6;
        case 3:
            return (float)2/5;
        case 4:
            return (float)2/4;
        case 5:
            return (float)2/3;
        case 6:
            return (float)2/2;
        case 7:
            return (float)3/2;
        case 8:
            return (float)4/2;
        case 9:
            return (float)5/2;
        case 10:
            return (float)6/2;
        case 11:
            return (float)7/2;
        case 12:
            return (float)8/2;
    }
}

