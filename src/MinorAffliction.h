// 
// File: MinorAffliction.h 
// 
// Author: Lucas Clotfelter
// 
// These can effect a pokemon throughout the game. A pokemon can have multiple
// minor afflictions at a time.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef MINORAFFLICTION_H_
#define MINORAFFLICTION_H_

#include "Pokemon.h"


class MinorAffliction
{

  public:

    /// Called when the round ends
    virtual void onRoundEnd();

    /// Called before the afflicted pokemon attacks. Return true if this
    /// replaces the attack
    virtual bool whenAttacks();

    /// Returns true iff the minor affliction should be removed from the pokemon
    virtual bool isFinished() = 0;

    /// Returns true iff this affliction is preventing the pokemon from being
    /// swapped
    virtual bool isTrapped();

  protected:

    MinorAffliction(Pokemon& afflictedPokemon);

    /// The pokemon that this is afflicted.
    Pokemon& afflictedPokemon;

};


class Confusion : public MinorAffliction
{

  public:

    Confusion(Pokemon& afflictedPokemon);

    bool whenAttacks();

    bool isFinished();

  private:

    int turnsLeft;

};


// this is just for testing the isTrapped function; remove this later
class PartialTrap : public MinorAffliction
{

  public:

    PartialTrap(Pokemon& afflictedPokemon);

    bool isTrapped();

    bool isFinished();

  private:

    int turnsLeft;

};

#endif // MINORAFFLICTION_H_

