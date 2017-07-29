// 
// File: MinorAffliction.cpp 
// 
// Author: Sam Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MinorAffliction.h"

#include <iostream>
#include <string>

using namespace std;


MinorAffliction::MinorAffliction(string name, Pokemon& afflictedPokemon)
:name(name)
,afflictedPokemon(afflictedPokemon)
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

