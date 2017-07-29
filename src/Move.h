// 
// File: Move.h 
// 
// Author: Sam Clotfelter
// 
// Moves are different kinds of attacks that the pokemon can use on each other.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef MOVE_H_
#define MOVE_H_

#include "Type.h"
#include "Category.h"

class Pokemon;
class Effect;

#include <string>

/// This accuracy value means that the move always hits no matter what. Usually,
/// used for moves that only effect user. Ex: Agility, Bulk up, etc.
#define ALWAYS_HIT -1

/// This accuracy value means that the move will hit unless the defending
/// pokemon is semi-unvulnerable. Ex: Effects of Dig, Fly, Protect.
#define HIT_UNLESS_SEMI_INVUL -2

class Move
{

  public:

    ~Move();


    /// Getters for read-only vars

    std::string getName() const;

    std::string getType() const;

    int getPower() const;

    float getAccuracy() const;

    Category getCategory() const;


    /// Called at the end of every turn that this move's owner is the current
    /// pokemon
    void onRoundEnd() const;

    /// Performs the effect in place of an attack, if special category
    void doEffect(Pokemon& owner, Pokemon& defending);

    /// Called after the move is done.
    void onMoveEnd(Pokemon& owner, Pokemon& defending, bool moveHit);

    Move(std::string name, std::string type, int damage, float accuracy,
        Category category, Effect* effect);

  private:

    /// The name used to identify this kind of move to the user
    std::string name;

    /// The type of damage this move deals
    std::string type;

    /// The amount of base damage the move inflicts on the opponent
    int damage;

    /// The base probability that the move will hit the target. This is either
    /// a float between 0-1, or a special value declared in Move
    float accuracy;

    /// The category of this move
    Category category;

    /// The object that handles any effect of using the move other than damage
    Effect* effect;

};

#endif // MOVE_H_

