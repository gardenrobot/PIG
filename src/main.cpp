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

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{

    HumanPlayer* p1 = new HumanPlayer("Alpha");
    p1->addPokemon(new Charmander("Firey"));
    HumanPlayer* p2 = new HumanPlayer("Beta");
    p2->addPokemon(new Squirtle("Watery"));

    Environment env(p1, p2);

    while(not p1->hasLost() and not p2->hasLost())
    {
        Round::doRound(env, *p1, *p2);
    }

    cout << "Done." << endl;
}

