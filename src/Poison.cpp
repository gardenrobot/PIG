// 
// File: Poison.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MajorAffliction.h"
#include "Pokemon.h"

#include <iostream>

using namespace std;


Poison::Poison(Pokemon& afflictedPokemon)
:MajorAffliction(afflictedPokemon, "Poison", "PSN")
{
}


void Poison::onRoundEnd()
{
    int damage(afflictedPokemon.getHp() / 16.0);
    afflictedPokemon.setHp(afflictedPokemon.getHp() - damage);
}


bool Poison::isFinished()
{
    return false;
}

