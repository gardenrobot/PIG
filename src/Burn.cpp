// 
// File: Burn.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MajorAffliction.h"
#include "Pokemon.h"
#include "Battle.h"

#include <iostream>
#include <cmath>

using namespace std;


Burn::Burn(Pokemon& afflictedPokemon)
:MajorAffliction(afflictedPokemon, "Burn", "BRN")
{
}


void Burn::onRoundEnd()
{
    int damage = Battle::roundDamage(afflictedPokemon.getMaxHp() / 8.0);
    cout << afflictedPokemon.getNickname() << " took " << damage <<
        " burn damage" << endl;
    afflictedPokemon.changeHp(-damage);
}


bool Burn::isFinished()
{
    return false;
}

