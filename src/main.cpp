// 
// File: main.h 
// 
// Author: Lucas Clotfelter
// 
// Runs PIG
// 
// //////////////////////////////////////////////////////////////////// 

#include "Round.h"
#include "Battle.h"
#include "HumanPlayer.h"
#include "Environment.h"
#include "MajorAffliction.h"
#include "MinorAffliction.h"
#include "Pokemon.h"
#include "PokemonFactory.h"
#include "PokemonSpecies.h"
#include "MoveFactory.h"
#include "EffectId.h"
#include "EffectFactory.h"
#include "Type.h"
#include "Debug.h"

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace std;
using namespace boost::filesystem;
using namespace boost::algorithm;


/// Print information on all pokemon species and their ids to stdout
void listPokemon()
{
    cout << "Listing all pokemon species." << endl;
    const map<int, const PokemonSpecies*> allSpecies =
        PokemonFactory::getAllSpecies();
    for(map<int, const PokemonSpecies*>::const_iterator it =
        allSpecies.begin(); it != allSpecies.end(); it++)
    {
        int id = it->first;
        const PokemonSpecies* species = it->second;
        cout << id << ": " << species->speciesName << endl;
    }
    cout << endl;
}


/// Initialize the players and start the game.
int run()
{
    // Seed prng
    srand(Environment::PRNG_SEED);

    // Intialize classes that need it
    Type::initialize();
    MoveFactory::initialize();
    PokemonFactory::initialize();

    // Create players
    #ifdef DEBUG_MODE
    // Use hard coded players for testing
    HumanPlayer* p1 = new HumanPlayer(1);
    Pokemon* poke1 = PokemonFactory::createPokemon(4, "");
    p1->addPokemon(poke1);
    HumanPlayer* p2 = new HumanPlayer(2);
    Pokemon* poke2 = PokemonFactory::createPokemon(1, "");
    p2->addPokemon(poke2);
    #else
    // Create human players
    listPokemon();
    HumanPlayer* p1 = new HumanPlayer(1);
    HumanPlayer* p2 = new HumanPlayer(2);
    #endif

    // Create environment with players
    Environment env(p1, p2);

    // Run the game loop
    cout << endl;
    cout << "Starting game." << endl;
    Player* winner = env.doGame();

    // Print the winner's name.
    if(winner == NULL)
    {
        cout << "Tie." << endl;
    }
    else
    {
        cout << winner->getName() << " wins." << endl;
    }

    cout << "Done." << endl;
    PokemonFactory::destroy();
    MoveFactory::destroy();
}


int main(int argc, char** argv)
{
    return run();
}

