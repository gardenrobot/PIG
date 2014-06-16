// 
// File: PokemonFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "PokemonFactory.h"
#include "Pokemon.h"
#include "PokemonSpecies.h"
#include "MoveFactory.h"

#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

class Move;

using namespace std;


map<int, PokemonSpecies*> PokemonFactory::allSpecies;

void PokemonFactory::initialize()
{
    allSpecies.insert(std::pair<int, PokemonSpecies*>(4,
        new PokemonSpecies(string("Charmander"), FIRE, NONE, 39, 52, 143, 60,
        150, 65, 1, 0, 0, 0)));
    allSpecies.insert(std::pair<int, PokemonSpecies*>(7,
        new PokemonSpecies(string("Squirtle"), WATER, NONE, 29, 30, 180, 23,
        121, 29, 2, 0, 0, 0)));
    allSpecies.insert(std::pair<int, PokemonSpecies*>(1,
        new PokemonSpecies(string("Bulbasaur"), GRASS, NONE, 29, 30, 180, 23,
        121, 29, 4, 0, 0, 0)));
}

Pokemon* PokemonFactory::createPokemon(int speciesId, string nickname)
{
    // get the species from map
    PokemonSpecies* species;
    try
    {
        species = allSpecies.at(speciesId);
    }
    catch(const out_of_range& e)
    {
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
    int moveId1 = species->moveId1;
    int moveId2 = species->moveId2;
    int moveId3 = species->moveId3;
    int moveId4 = species->moveId4;

    // create the pokemon's moves
    Move* move1 = MoveFactory::createMove(moveId1);
    Move* move2 = MoveFactory::createMove(moveId2);
    Move* move3 = MoveFactory::createMove(moveId3);
    Move* move4 = MoveFactory::createMove(moveId4);

    // create move from values
    Pokemon* pokemon = new Pokemon(nickname, speciesName, typeOne, typeTwo,
        maxHp, baseAttack, baseDefense, baseSpecialAttack, baseSpecialDefense,
        baseSpeed, move1, move2, move3, move4);
    return pokemon;
}

