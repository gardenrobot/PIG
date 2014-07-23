// 
// File: Type.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Type.h"
#include "Debug.h"
#include <string>
#include <vector>

#include <map>

using namespace std;


vector<string> Type::allTypes;
map<TypePair, float> Type::typeMultipliers;

void Type::initialize()
{
    // define all types and register them
    string water = "Water";
    string grass = "Grass";
    string fire = "Fire";
    string normal = "Normal";
    string noType = "No Type";
    allTypes.push_back(water);
    allTypes.push_back(grass);
    allTypes.push_back(noType);
    allTypes.push_back(fire);
    allTypes.push_back(normal);

    // define all type modifiers
    typeMultipliers.insert(pair<TypePair, float>(TypePair(water, water), 0.5F));
    typeMultipliers.insert(pair<TypePair, float>(TypePair(water, grass), 0.5F));
    typeMultipliers.insert(pair<TypePair, float>(TypePair(water, fire), 2.0F));
    typeMultipliers.insert(pair<TypePair, float>(TypePair(grass, water), 2.0F));
    typeMultipliers.insert(pair<TypePair, float>(TypePair(grass, grass), 0.5F));
    typeMultipliers.insert(pair<TypePair, float>(TypePair(grass, fire), 0.5F));
    typeMultipliers.insert(pair<TypePair, float>(TypePair(fire, water), 0.5F));
    typeMultipliers.insert(pair<TypePair, float>(TypePair(fire, grass), 2.0F));
    typeMultipliers.insert(pair<TypePair, float>(TypePair(fire, fire), 0.5F));
}

bool Type::isType(string s)
{
    // check if the string is in the list
    for(vector<string>::iterator it = allTypes.begin(); it != allTypes.end();
        it++)
    {
        if(*it == s)
        {
            return true;
        }
    }
    return false;
}

float Type::getMultiplier(string move, string defending)
{
    assert_debug(isType(move));
    assert_debug(isType(defending));

    // search map for value
    TypePair pair(move, defending);
    map<TypePair, float>::iterator it = typeMultipliers.find(pair);

    if(it == typeMultipliers.end())
    {
        return 1;
    }
    else
    {
        return it->second;
    }
}

float Type::getMultiplier(std::string move, string defending1,
    string defending2)
{
    float mult = getMultiplier(move, defending1) * getMultiplier(move, defending2);
    return mult;
}


TypePair::TypePair(std::string move, std::string defending)
:move(move)
,defending(defending)
{}

bool TypePair::operator<(const TypePair& other) const
{
    if(move == other.move)
    {
        return defending < other.defending;
    }
    else
    {
        return move < other.move;
    }
}

bool TypePair::operator>(const TypePair& other) const
{
    if(move == other.move)
    {
        return defending > other.defending;
    }
    else
    {
        return move > other.move;
    }
}

bool TypePair::operator==(const TypePair& other) const
{
    return move == other.move and defending == other.defending;
}

