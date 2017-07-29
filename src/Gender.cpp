// 
// File: Gender.cpp 
// 
// Author: Sam Clotfelter
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

