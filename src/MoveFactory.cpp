// 
// File: MoveFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Move.h"
#include "MoveFactory.h"
#include "MoveSpecies.h"
#include "MoveId.h"
#include "Effect.h"
#include "EffectFactory.h"
#include "EffectId.h"

#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;


map<MoveId, MoveSpecies*> MoveFactory::allSpecies;

void MoveFactory::initialize()
{
    // add hard-coded moves to map
    allSpecies.insert(std::pair<MoveId, MoveSpecies*>(EMBER,
        new MoveSpecies(string("Ember"), FIRE, 40, 0.75F, SPECIAL,
        AFFLICT_BURN)));
    allSpecies.insert(std::pair<MoveId, MoveSpecies*>(WATER_GUN,
        new MoveSpecies(string("Water Gun"), WATER, 40, 0.75F, SPECIAL,
        NO_EFFECT)));
    allSpecies.insert(std::pair<MoveId, MoveSpecies*>(CONFUSED_MOVE,
        new MoveSpecies(string("Confused Move"), NO_TYPE, 40, -1, PHYSICAL,
        NO_EFFECT)));
    allSpecies.insert(std::pair<MoveId, MoveSpecies*>(STUN_SPORE,
        new MoveSpecies(string("Stun Spore"), GRASS, 0, -1, STATUS,
        NO_EFFECT)));
}

void MoveFactory::destroy()
{
    for(map<MoveId, MoveSpecies*>::iterator it = allSpecies.begin();
        it != allSpecies.end(); it++)
    {
        delete it->second;
    }
}

Move* MoveFactory::createMove(MoveId speciesId)
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
    EffectId effectId = species->effectId;

    // get effect from effect facotry

    Effect* effect = EffectFactory::createEffect(effectId);

    // create move from values
    Move* move = new Move(name, type, damage, accuracy, category, effect);
    return move;
}

