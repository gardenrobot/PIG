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

    MoveSpecies(std::string name, Type type, int damage, float accuracy,
        Category category)
    :name(name)
    ,type(type)
    ,damage(damage)
    ,accuracy(accuracy)
    ,category(category)
    {}

};

#endif // MOVE_SPECIES_H_
