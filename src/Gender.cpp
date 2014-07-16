// 
// File: Gender.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Gender.h"

#include <string>

using namespace std;


string GenderString::genderToLetter(Gender g)
{
    if(g == MALE)
    {
        return "M";
    }
    else if(g == FEMALE)
    {
        return "F";
    }
    else
    {
        return "X";
    }
}

