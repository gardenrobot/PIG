// 
// File: PokemonFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "PokemonFactory.h"
#include "Pokemon.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;


void PokemonFactory::initialize()
{
}

Pokemon* PokemonFactory::createPokemon(int speciesId, string nickname)
{
    switch(speciesId)
    {
        case 4:
            return new Charmander(nickname);
            break;
        case 7:
            return new Squirtle(nickname);
            break;
        default:
            cerr << "Pokemon species " << speciesId << " not found." << endl;
            return NULL;
            break;
    }
}

