// 
// File: Pokemon.h 
// 
// Author: Lucas Clotfelter
// 
// Pokemon are the cute little animals that fight each other.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef POKEMON_H_
#define POKEMON_H_

#include "Type.h"

class Stat;
class Move;
class MajorAffliction;
class MinorAffliction;

#include <string>
#include <vector>


class Pokemon
{

  public:

    /// A pokemon can have no more than this many moves
    static const int MAX_MOVES = 4;

    ~Pokemon();

    /// Returns the name of the pokemon's species.
    std::string getSpeciesName() const;

    /// Returns the given name of the pokemon.
    std::string getNickname() const;

    int getHp() const;

    int getMaxHp() const;

    Move* getMove(int index);

    int getNumMoves() const;

    const std::vector< Move* > getMovesContainer() const;

    const MajorAffliction* getMajorAffliction() const;

    const MinorAffliction* getMinorAffliction(int index) const;

    const Stat& getAttack() const;
    const Stat& getDefense() const;
    const Stat& getSpecialAttack() const;
    const Stat& getSpecialDefense() const;
    const Stat& getSpeed() const;
    const Stat& getAccuracy() const;
    const Stat& getEvasiveness() const;

    int getLevel() const;

    /// Returns true of health is 0
    bool isFainted() const;

    /// Use this to change the hp.
    void setHp(int hp);

    void changeHp(int change);

    /// Called when the environment finishes a round.
    void onRoundEnd();

    Type getTypeOne() const;

    Type getTypeTwo() const;

  protected:

    Pokemon(std::string nickname, std::string speciesName, Type typeOne,
        Type typeTwo, int maxHp, int baseAttack, int baseDefense,
        int baseSpecialAttack, int baseSpecialDefense, int baseSpeed,
        Move* move1, Move* move2, Move* move3, Move* move4);

  private:

    /// The pokemon's given name.
    const std::string nickname;

    /// The name used to identify the pokemon's species
    const std::string speciesName;

    /// Current health
    int hp;
    /// Maximum health
    const int maxHp;

    /// Stats that affect how the pokemon battles
    Stat* const attack;
    Stat* const defense;
    Stat* const specialAttack;
    Stat* const specialDefense;
    Stat* const speed;
    Stat* const accuracy;
    Stat* const evasiveness;

    int level;

    Type typeOne;
    Type typeTwo;

    /// The moves that the pokemon can use. These are to be deleted by the
    /// pokemon.
    std::vector< Move* > moves;

    /// The major affliction of the pokemon. For example, sleep, paralysis, etc.
    /// This can be null, which means the pokemon is healthy.
    MajorAffliction* majorAffliction;

    /// The minor afflictions of the pokemon. Unlike major, there can be more
    /// than one minor. For example, confusion, constrict, etc.
    std::vector< MinorAffliction* > minorAfflictions;

};


/// All derived classes go here


class Charmander : public Pokemon
{

  public:

    Charmander(const std::string nickname);

};

class Squirtle : public Pokemon
{

  public:

    Squirtle(const std::string nickname);

};

#endif // POKEMON_H_

