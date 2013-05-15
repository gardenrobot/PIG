// 
// File: Burn.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MajorAffliction.h"
#include "Pokemon.h"

#include <iostream>

using namespace std;


Burn::Burn(Pokemon& afflictedPokemon)
:MajorAffliction(afflictedPokemon, "Burn", "BRN")
{
}


void Burn::onRoundEnd()
{
    int damage(afflictedPokemon.getHp() / 8.0);
    cout << afflictedPokemon.getNickname() << " took " << damage <<
        " burn damage" << endl;
    afflictedPokemon.setHp(afflictedPokemon.getHp() - damage);
}


bool Burn::isFinished()
{
    return false;
}

