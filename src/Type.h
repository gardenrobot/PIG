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
#include <string>
#include <vector>

class TypePair;


class Type
{
  public:

    static std::string NO_TYPE;

    /// Must be called once per process before using this class
    static void initialize();

    /// Returns true iff the string is a valid type
    static bool isType(std::string);

    /// Returns the type multiplier of a move attacking a one-typed pokemon
    static float getMultiplier(std::string move, std::string defending);

    /// Same thing but the pokemon has two types
    static float getMultiplier(std::string move, std::string defending1,
        std::string defending2);

  private:

    /// This maps type pairs to the damage multiplier
    /// For example, if water attack are strong against fire pokemon, the pair
    /// {water, fire} is mapped to 2.
    static std::map<TypePair, float> typeMultipliers;

    /// Contains all valid types
    static std::vector<std::string> allTypes;
};

class TypePair
{
  public:
    TypePair(std::string move, std::string defending);

    const std::string move;
    const std::string defending;

    /// These will be keys in a map, so they need operator
    bool operator<(const TypePair& other) const;
    bool operator>(const TypePair& other) const;
    bool operator==(const TypePair& other) const;
};


#endif // TYPE_H_

