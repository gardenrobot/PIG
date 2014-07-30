// 
// File: MoveSpecies.h 
// 
// Author: Lucas Clotfelter
// 
// Move species are configurations used by the factory to create moves. They
// are used like structs with only public variables.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef MOVE_SPECIES_H_
#define MOVE_SPECIES_H_

#include "Type.h"
#include "Category.h"
#include "EffectId.h"

#include <string>

class Move;


class MoveSpecies
{

  public:

    /// These correspond to variables in Move class. See that class for
    /// descriptions.

    std::string name;
    std::string type;
    int damage;
    float accuracy;
    Category category;
    EffectId effectId;

    MoveSpecies(std::string name, std::string type, int damage, float accuracy,
        Category category, EffectId effectId)
    :name(name)
    ,type(type)
    ,damage(damage)
    ,accuracy(accuracy)
    ,category(category)
    ,effectId(effectId)
    {}

};

#endif // MOVE_SPECIES_H_
