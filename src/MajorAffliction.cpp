// 
// File: MajorAffliction.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MajorAffliction.h"

#include <iostream>

using namespace std;


/// Do nothing for all of these. Interesting things can be done in derived
/// classes.

MajorAffliction::MajorAffliction(Pokemon& afflictedPokemon, string name,
    string shortName)
:afflictedPokemon(afflictedPokemon)
,name(name)
,shortName(shortName)
{
}


void MajorAffliction::onRoundEnd()
{
}


bool MajorAffliction::whenAttacks()
{
    return false;
}

