// 
// File: main.h 
// 
// Author: Lucas Clotfelter
// 
// Runs a pokemon game
// 
// //////////////////////////////////////////////////////////////////// 

#include "Round.h"
#include "HumanPlayer.h"
#include "Environment.h"
#include "Pokemon.h"
#include "PokemonFactory.h"
#include "MajorAffliction.h"
#include "MinorAffliction.h"
#include "PokemonFactory.h"
#include "MoveFactory.h"

#include <iostream>
#include <stdlib.h>

using namespace std;


int main(int argc, char** argv)
{
    PokemonFactory::initialize();
    MoveFactory::initialize();
    srand(50);

    HumanPlayer* p1 = new HumanPlayer("Ash");
    p1->addPokemon(PokemonFactory::createPokemon(CHARMANDER, "Hotman"));
    //p1->getPokemon(0)->setMajorAffliction(new Burn(*(p1->getPokemon(0))));
    //p1->getPokemon(0)->addMinorAffliction(new Confusion(*(p1->getPokemon(0))));
    HumanPlayer* p2 = new HumanPlayer("Gary");
    p2->addPokemon(PokemonFactory::createPokemon(SQUIRTLE, "Watery"));

    Environment env(p1, p2);

    for(int i = 0; not p1->hasLost() and not p2->hasLost(); ++i)
    {
        cout << "Round " << (i + 1) << endl;

        Round::doRound(env, *p1, *p2);
    }

    cout << "Done." << endl;
}

