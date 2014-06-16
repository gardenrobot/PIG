// 
// File: MoveFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MoveFactory.h"
#include "MoveSpecies.h"
#include "Move.h"
#include "EffectFactory.h"
#include "Effect.h"

#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;


map<int, MoveSpecies*> MoveFactory::allSpecies;

void MoveFactory::initialize()
{
    // add hard-coded moves to map
    allSpecies.insert(std::pair<int, MoveSpecies*>(1,
        new MoveSpecies(string("Ember"), FIRE, 40, 0.75F, SPECIAL, 1)));
    allSpecies.insert(std::pair<int, MoveSpecies*>(2,
        new MoveSpecies(string("Water Gun"), WATER, 40, 0.75F, SPECIAL, 0)));
    allSpecies.insert(std::pair<int, MoveSpecies*>(3,
        new MoveSpecies(string("Confused Move"), NONE, 40, -1, PHYSICAL, 0)));
    allSpecies.insert(std::pair<int, MoveSpecies*>(4,
        new MoveSpecies(string("Stun Spore"), GRASS, 0, -1, STATUS, 0)));
}

Move* MoveFactory::createMove(int speciesId)
{
    // get the species from map
    MoveSpecies* species;
    try
    {
        species = allSpecies.at(speciesId);
    }
    catch(const out_of_range& e)
    {
        return NULL;
    }

    // get values from species
    string name = species->name;
    Type type = species->type;
    int damage = species->damage;
    float accuracy = species->accuracy;
    Category category = species->category;
    int effectId = species->effectId;

    // get effect from effect facotry

    Effect* effect = EffectFactory::createEffect(effectId);

    // create move from values
    Move* move = new Move(name, type, damage, accuracy, category, effect);
    return move;
}

