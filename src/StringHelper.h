// 
// File: StringHelper.h 
// 
// Author: Lucas Clotfelter
// 
// Namespace that help with parsing of strings
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include <string>
#include <vector>


namespace StringHelper
{

    /// Splits a string into a vector of strings based on a delimiting char
    std::vector<std::string> split(const std::string& original, char delim = ' ');

    /// Splits a string into a vector of ints based on a delimiting char;
    /// if any of the 
    std::vector<int> splitToInt(const std::string& original);

}

#endif // STRINGHELPER_H_

