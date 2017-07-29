// 
// File: PokemonSpecies.h 
// 
// Author: Sam Clotfelter
// 
// Pokemon species are configurations used by the factory to create pokemon. They
// are used like structs with only public variables.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef POKEMON_SPECIES_H_
#define POKEMON_SPECIES_H_

#include "Type.h"
#include "Gender.h"

#include <string>

class Pokemon;


class PokemonSpecies
{

  public:

    /// See Pokemon.h for descriptions of these variables.

    std::string speciesName;
    std::string typeOne;
    std::string typeTwo;
    int maxHp;
    int baseAttack;
    int baseDefense;
    int baseSpecialAttack;
    int baseSpecialDefense;
    int baseSpeed;
    std::vector<int> moveIds;

    /// The probability 0-1 that a pokemon is female, or NO_GENDER_DIST
    float genderDist;

    PokemonSpecies(std::string speciesName, std::string typeOne,
        std::string typeTwo, int maxHp, int baseAttack, int baseDefense,
        int baseSpecialAttack, int baseSpecialDefense, int baseSpeed,
        std::vector<int> moveIds, float genderDist)
    :speciesName(speciesName)
    ,typeOne(typeOne)
    ,typeTwo(typeTwo)
    ,maxHp(maxHp)
    ,baseAttack(baseAttack)
    ,baseDefense(baseDefense)
    ,baseSpecialAttack(baseSpecialAttack)
    ,baseSpecialDefense(baseSpecialDefense)
    ,baseSpeed(baseSpeed)
    ,moveIds(moveIds)
    ,genderDist(genderDist)
    {}

};

#endif // POKEMON_SPECIES_H_
