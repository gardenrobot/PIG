// 
// File: Type.h 
// 
// Author: Lucas Clotfelter
// 
// Each move and pokemon is assigned a type. Each type has strengths and
// weaknesses in battle.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef TYPE_H_
#define TYPE_H_

#include <map>


typedef enum
{
    NO_TYPE = 0,
    WATER = 1,
    GRASS = 2,
    FIRE = 3,
    NORMAL = 4,
} Type;


/// This is a helper to TypeMult.
struct TypePair
{
    TypePair(Type move, Type defending);

    Type move;
    Type defending;

    /// These will be keys in a map, so they need operator
    bool operator<(const TypePair other) const;
    bool operator>(const TypePair other) const;
};


/// This is a container for a map that is filled on instantiation. It is a
/// helper for TypeMult.
class TypeMultiplierMap
{
  public:

    TypeMultiplierMap();

    const std::map<TypePair, float>& getMap() const;

  private:

    std::map<TypePair, float> theMap;
};


class TypeMult
{
  public:

    /// Returns the type multiplier of a move attacking a one-typed pokemon
    static float getMultiplier(Type move, Type defending);

    /// Same thing but the pokemon has two types
    static float getMultiplier(Type move, Type defendingOne, Type defendingTwo);

  private:

    /// This maps type pairs to the damage multiplier
    /// For example, if water attack are strong against fire pokemon, the pair
    /// {water, fire} is mapped to 2.
    static const TypeMultiplierMap typeMultipliers;

};

#endif // TYPE_H_

