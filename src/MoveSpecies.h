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

    /// See Move.h for descriptions of these variables.

    std::string name;
    Type type;
    int damage;
    float accuracy;
    Category category;
    EffectId effectId;

    MoveSpecies(std::string name, Type type, int damage, float accuracy,
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
