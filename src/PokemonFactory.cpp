// 
// File: PokemonFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Pokemon.h"
#include "PokemonFactory.h"
#include "PokemonSpecies.h"
#include "PokemonId.h"
#include "MoveFactory.h"
#include "MoveId.h"
#include "Debug.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <stdlib.h>
#include <fstream>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/json.h>

class Move;

using namespace std;
using namespace Json;


map<PokemonId, PokemonSpecies*> PokemonFactory::allSpecies;

void PokemonFactory::initialize()
{
    allSpecies.insert(std::pair<PokemonId, PokemonSpecies*>(BULBASAUR,
        new PokemonSpecies(string("Bulbasaur"), GRASS, NO_TYPE, 29, 30, 180, 23,
        121, 29, STUN_SPORE, NO_MOVE, NO_MOVE, NO_MOVE, ALL_MALE_DIST)));
    allSpecies.insert(std::pair<PokemonId, PokemonSpecies*>(CHARMANDER,
        new PokemonSpecies(string("Charmander"), FIRE, NO_TYPE, 39, 52, 143, 60,
        150, 65, EMBER, AGILITY, NO_MOVE, NO_MOVE, ALL_FEMALE_DIST)));
    allSpecies.insert(std::pair<PokemonId, PokemonSpecies*>(SQUIRTLE,
        new PokemonSpecies(string("Squirtle"), WATER, NO_TYPE, 29, 30, 180, 23,
        121, 29, WATER_GUN, NO_MOVE, NO_MOVE, NO_MOVE, ALL_MALE_DIST)));

    Reader reader;
    const char* filename = "Pokemon.json";
    ifstream stream;
    stream.open(filename, ifstream::in);
    stream.close();

}

void PokemonFactory::destroy()
{
    for(map<PokemonId, PokemonSpecies*>::iterator it = allSpecies.begin();
        it != allSpecies.end(); it++)
    {
        delete it->second;
    }
}

Pokemon* PokemonFactory::createPokemon(PokemonId speciesId, string nickname="")
{
    // get the species from map
    PokemonSpecies* species;
    try
    {
        species = allSpecies.at(speciesId);
    }
    catch(const out_of_range& e)
    {
        println_debug("Pokemon ID " << speciesId << " not found.");
        return NULL;
    }

    // get values from species
    string speciesName = species->speciesName;
    Type typeOne = species->typeOne;
    Type typeTwo = species->typeTwo;
    int maxHp = species->maxHp;
    int baseAttack = species->baseAttack;
    int baseDefense = species->baseDefense;
    int baseSpecialAttack = species->baseSpecialAttack;
    int baseSpecialDefense = species->baseSpecialDefense;
    int baseSpeed = species->baseSpeed;
    MoveId moveId1 = species->moveId1;
    MoveId moveId2 = species->moveId2;
    MoveId moveId3 = species->moveId3;
    MoveId moveId4 = species->moveId4;

    // Determine the gender
    float genderDist = species->genderDist;
    Gender gender;
    if(genderDist == NO_GENDER_DIST)
    {
        gender = NO_GENDER;
    }
    else if(((rand() % 100) * 0.01) < genderDist)
    {
        gender = FEMALE;
    }
    else
    {
        gender = MALE;
    }

    // if there is no nickname, use the species name
    if(nickname == "")
    {
        nickname = speciesName;
    }

    // create the pokemon's moves
    Move* move1 = MoveFactory::createMove(moveId1);
    Move* move2 = MoveFactory::createMove(moveId2);
    Move* move3 = MoveFactory::createMove(moveId3);
    Move* move4 = MoveFactory::createMove(moveId4);

    // create move from values
    Pokemon* pokemon = new Pokemon(nickname, speciesName, typeOne, typeTwo,
        maxHp, baseAttack, baseDefense, baseSpecialAttack, baseSpecialDefense,
        baseSpeed, move1, move2, move3, move4, gender);
    return pokemon;
}

const map<PokemonId, const PokemonSpecies*> PokemonFactory::getAllSpecies()
{
    map<PokemonId, const PokemonSpecies*> allSpeciesList;

    for(map<PokemonId, PokemonSpecies*>::iterator it = allSpecies.begin();
        it != allSpecies.end(); it++)
    {
        PokemonId id = it->first;
        PokemonSpecies* species = it->second;
        allSpeciesList.insert(pair<PokemonId, const PokemonSpecies*>(id, species));
    }

    return allSpeciesList;
}

