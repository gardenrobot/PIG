// 
// File: derp.h 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Type.h"

#include <map>

using namespace std;


/// Type Multiplier Map

TypeMultiplierMap::TypeMultiplierMap()
{
    // insert all strengths and weakness of types here

    theMap.insert(pair<TypePair, float>(TypePair(WATER, WATER), 0.5));
    theMap.insert(pair<TypePair, float>(TypePair(WATER, GRASS), 0.5));
    theMap.insert(pair<TypePair, float>(TypePair(WATER, FIRE), 2));

    theMap.insert(pair<TypePair, float>(TypePair(GRASS, WATER), 2));
    theMap.insert(pair<TypePair, float>(TypePair(GRASS, GRASS), 0.5));
    theMap.insert(pair<TypePair, float>(TypePair(GRASS, FIRE), 0.5));

    theMap.insert(pair<TypePair, float>(TypePair(FIRE, WATER), 0.5));
    theMap.insert(pair<TypePair, float>(TypePair(FIRE, GRASS), 2));
    theMap.insert(pair<TypePair, float>(TypePair(FIRE, FIRE), 0.5));
}

const map<TypePair, float>& TypeMultiplierMap::getMap() const
{
    return theMap;
}


/// TypePair

TypePair::TypePair(Type move, Type defending)
:move(move)
,defending(defending)
{
}


bool TypePair::operator<(const TypePair other) const
{
    if(this->move == other.move)
    {
        return this->defending < other.defending;
    }
    else
    {
        return this->move < other.move;
    }
}

bool TypePair::operator>(const TypePair other) const
{
    if(this->move == other.move)
    {
        return this->defending > other.defending;
    }
    else
    {
        return this->move > other.move;
    }
}


/// TypeMult

const TypeMultiplierMap TypeMult::typeMultipliers;

float TypeMult::getMultiplier(Type move, Type defending)
{
    TypePair key(move, defending);

    const map<TypePair, float>& multMap = typeMultipliers.getMap();

    map<TypePair, float>::const_iterator it = multMap.find(key);

    /// The move is not strong or weak against the defending type; return 1
    if(it == multMap.end())
    {
        return 1;
    }
    else
    {
        return it->second;
    }
}

float TypeMult::getMultiplier(Type move, Type defendingOne, Type defendingTwo)
{
    return getMultiplier(move, defendingOne) * getMultiplier(move, defendingTwo);
}

