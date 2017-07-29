// 
// File: Gender.h 
// 
// Author: Sam Clotfelter
// 
// The gender of the pokemon
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef GENDER_H_
#define GENDER_H_

#include <string>


typedef enum
{
    NO_GENDER = -1,
    MALE = 0,
    FEMALE = 1,
} Gender;

namespace GenderString
{
    /// Returns a single capial letter for gender
    std::string genderToLetter(Gender g);
}

/// Gender distribution of all-male species
#define ALL_MALE_DIST 0.0F

/// Gender distribution of all-female species
#define ALL_FEMALE_DIST 1.0F

/// Assign this to pokemon species with no gender
#define NO_GENDER_DIST -1.0F

#endif // GENDER_H_

