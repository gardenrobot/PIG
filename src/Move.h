// 
// File: Move.h 
// 
// Author: Lucas Clotfelter
// 
// Moves are different kinds of attacks that the pokemon can use on each other.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef MOVE_H_
#define MOVE_H_

#include "Type.h"
#include "Category.h"

class Pokemon;

#include <string>


class Move
{

  public:

    /// The move's accuracy is this value if it always hits.
    static const float ALWAYS_HIT = -1;

    ~Move();

    std::string getName() const;

    Type getType() const;

    int getPower() const;

    float getAccuracy() const;

    Category getCategory() const;

    /// Called at the end of every turn that this's move's owner is the current
    /// pokemon
    void onRoundEnd() const;

    /// Performs the effect in place of an attack, if special category
    void doEffect(Pokemon& owner, Pokemon& defending);

    Move(std::string name, Type type, int damage, float accuracy,
        Category category);

  private:

    /// The name used to identify this kind of move to the user
    std::string name;

    /// The type of damage this move deals
    Type type;

    /// The amount of base damage the move inflicts on the opponent
    int damage;

    /// The base probability that the move will hit the target. This is
    /// ALWAYS_HIT if it always hits. Otherwise, it is a value 0 to 1.
    /// There is a difference between ALWAYS_HIT and 1 (100%); ALWAYS_HIT
    /// is not effected by outside factors.
    float accuracy;

    /// The category of this move's attack
    Category category;

};

#endif // MOVE_H_

