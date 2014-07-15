// 
// File: MinorAffliction.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MinorAffliction.h"

#include <iostream>

using namespace std;


MinorAffliction::MinorAffliction(Pokemon& afflictedPokemon)
:afflictedPokemon(afflictedPokemon)
{
}


void MinorAffliction::onRoundEnd(Pokemon& enemyPokemon)
{
}


bool MinorAffliction::whenAttacks(Pokemon& defending)
{
    return false;
}


bool MinorAffliction::isTrapped()
{
    return false;
}

