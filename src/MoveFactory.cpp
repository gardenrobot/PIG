// 
// File: MoveFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MoveFactory.h"
#include "MoveSpecies.h"
#include "Move.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;


map<int, MoveSpecies*> MoveFactory::allSpecies;

void MoveFactory::initialize()
{
    allSpecies.insert(std::pair<int, MoveSpecies*>(0,
        new MoveSpecies(string("Ember"), FIRE, 40, 0.75F, SPECIAL)));
    allSpecies.insert(std::pair<int, MoveSpecies*>(1,
        new MoveSpecies(string("Water Gun"), WATER, 40, 0.75F, SPECIAL)));
    allSpecies.insert(std::pair<int, MoveSpecies*>(2,
        new MoveSpecies(string("Confused Move"), NONE, 40, -1, PHYSICAL)));
}

Move* MoveFactory::createMove(int speciesId)
{
    // get the species
    MoveSpecies* species = allSpecies.at(speciesId);

    string name = species->name;
    Type type = species->type;
    int damage = species->damage;
    float accuracy = species->accuracy;
    Category category = species->category;

    return new Move(name, type, damage, accuracy, category);
}

