// 
// File: StringHelper.cpp
// 
// StringHelper.cpp Namespace that help with parsing of human input.
// 
// //////////////////////////////////////////////////////////////////// 

#include "StringHelper.h"

#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;


vector<string> StringHelper::split(const string& original, char delim)
{
    vector<string> list;

    string currentString;

    for(int i(0); i < original.length(); ++i)
    {
        if(original.at(i) == delim)
        {
            if(not currentString.empty())
            {
                list.push_back(currentString);
                currentString.erase();
            }
        }

        else
        {
            currentString.push_back(original[i]);
        }
    }

    if(not currentString.empty())
    {
        list.push_back(currentString);
    }

    return list;

}

vector<int> StringHelper::splitToInt(const string& original)
{
    vector<string> splitString(split(original));

    vector<int> splitInt;

    vector<string>::iterator it(splitString.begin());
    for( ; it != splitString.end(); ++it)
    {
        int i(atoi(it->c_str()));

        // only append if the string can be a valid int
        if(i != 0)
        {
            splitInt.push_back(i);
        }
    }

    return splitInt;
}

