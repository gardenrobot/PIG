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
#include "Gender.h"

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

    Gender getGender() const;

    int getHp() const;

    int getMaxHp() const;

    Move* getMove(int index);

    int getNumMoves() const;

    const std::vector<Move*> getMovesContainer() const;

    MajorAffliction* getMajorAffliction();

    int getNumMinorAfflictions() const;

    MinorAffliction* getMinorAffliction(int index);

    Stat& getAttack() const;
    Stat& getDefense() const;
    Stat& getSpecialAttack() const;
    Stat& getSpecialDefense() const;
    Stat& getSpeed() const;
    Stat& getAccuracy() const;
    Stat& getEvasiveness() const;

    int getLevel() const;

    /// Returns true of health is 0
    bool isFainted() const;

    /// Use this to change the hp.
    void setHp(int hp);

    void changeHp(int change);

    /// Called when the environment finishes a round.
    void onRoundEnd(Pokemon& enemyPokemon);

    void healMajorAffliction();

    /// Set the major affliction. New major afflictions cannot normally be
    /// applied when one already exists. Use force argument to override this.
    void setMajorAffliction(MajorAffliction* affliction, bool force=false);

    void addMinorAffliction(MinorAffliction* affliction);

    std::string getTypeOne() const;

    std::string getTypeTwo() const;

    Pokemon(std::string nickname, std::string speciesName, std::string typeOne,
        std::string typeTwo, int maxHp, int baseAttack, int baseDefense,
        int baseSpecialAttack, int baseSpecialDefense, int baseSpeed,
        std::vector<Move*> moves, Gender gender);

  private:

    /// The pokemon's given name.
    const std::string nickname;

    /// The name used to identify the pokemon's species
    const std::string speciesName;

    // The pokemon's gender
    const Gender gender;

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

    std::string typeOne;
    std::string typeTwo;

    /// The moves that the pokemon can use. These are to be deleted by the
    /// pokemon.
    std::vector<Move*> moves;

    /// The major affliction of the pokemon. For example, sleep, paralysis, etc.
    /// This can be null, which means the pokemon is healthy.
    MajorAffliction* majorAffliction;

    /// The minor afflictions of the pokemon. Unlike major, there can be more
    /// than one minor. For example, confusion, constrict, etc.
    std::vector<MinorAffliction*> minorAfflictions;

};

#endif // POKEMON_H_

