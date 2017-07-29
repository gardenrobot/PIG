// 
// File: MinorAffliction.h 
// 
// Author: Sam Clotfelter
// 
// These can effect a pokemon throughout the game. A pokemon can have multiple
// minor afflictions at a time.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef MINORAFFLICTION_H_
#define MINORAFFLICTION_H_

#include "Pokemon.h"
#include "Gender.h"

#include <string>

class Pokemon;


class MinorAffliction
{

  public:

    /// This is used to identify derived minor afflictions.
    const std::string name;

    /// Called when the round ends
    virtual void onRoundEnd(Pokemon& enemyPokemon);

    /// Called before the afflicted pokemon attacks. Return true if this
    /// replaces the attack
    virtual bool whenAttacks(Pokemon& defending);

    /// Returns true iff the minor affliction should be removed from the pokemon
    virtual bool isFinished() = 0;

    /// Returns true iff this affliction is preventing the pokemon from being
    /// swapped
    virtual bool isTrapped();

  protected:

    MinorAffliction(std::string name, Pokemon& afflictedPokemon);

    /// The pokemon that this is afflicted.
    Pokemon& afflictedPokemon;

};


class Confusion : public MinorAffliction
{

  public:

    Confusion(Pokemon& afflictedPokemon);

    bool whenAttacks(Pokemon& defending);

    bool isFinished();

  private:

    int turnsLeft;

};


class PartialTrap : public MinorAffliction
{

  public:

    PartialTrap(Pokemon& afflictedPokemon);

    void onRoundEnd(Pokemon& enemyPokemon);

    bool isFinished();

  private:

    int turnsLeft;

};


class Flinch : public MinorAffliction
{

  public:

    Flinch(Pokemon& afflictedPokemon);

    bool whenAttacks(Pokemon& defending);

    bool isFinished();

};


class Infatuation : public MinorAffliction
{

  public:

    Infatuation(Pokemon& afflictedPokemon, Pokemon& infatSrc);

    bool whenAttacks(Pokemon& defending);

    bool isFinished();

  private:

    Pokemon& infatSrc;

    bool infatSrcHasChanged;

    bool oppositeGender(Gender g1, Gender g2);

};


class Seeding : public MinorAffliction
{

  public:

    Seeding(Pokemon& afflictedPokemon);

    void onRoundEnd(Pokemon& enemyPokemon);

    bool isFinished();

  private:

    int turnsLeft;

};

#endif // MINORAFFLICTION_H_

