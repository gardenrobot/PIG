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

using namespace std;


void PokemonFactory::initialize()
{
    cout << "Initializing" << endl;
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
            cerr << "Species not found." << endl;
            return NULL;
    }
}

