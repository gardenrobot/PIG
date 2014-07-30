// 
// File: MajorAffliction.h 
// 
// Author: Lucas Clotfelter
// 
// A major affliction will effect a pokemon throughout the game using hooks. A
// pokemon can have only major affliction at a time.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef MAJORAFFLICTION_H_
#define MAJORAFFLICTION_H_

class Pokemon;

#include <iostream>


class MajorAffliction
{

  public:

    /// The name of the afflicition
    const std::string name;

    /// An abbrev. of the name
    const std::string shortName;

    /// Called when the round ends
    virtual void onRoundEnd();

    /// Called before the afflicted pokemon attacks. Return true to cancel the
    /// attack.
    virtual bool whenAttacks();

    /// Returns true if this affliction should be removed from the pokemon.
    virtual bool isFinished() = 0;

  protected:

    MajorAffliction(Pokemon& afflictedPokemon, std::string name,
        std::string shortName);

    /// The pokemon that this is afflicting.
    Pokemon& afflictedPokemon;

};


class Burn : public MajorAffliction
{

  public:

    Burn(Pokemon& afflictedPokemon);

    void onRoundEnd();

    bool isFinished();

};

#endif // MAJORAFFLICTION_H_

