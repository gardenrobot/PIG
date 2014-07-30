// 
// File: MinorAffliction.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MinorAffliction.h"

#include <iostream>

using namespace std;


/// Do nothing for all of these. Interesting things can be done in derived
/// classes.

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

