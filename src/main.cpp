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
#include "StringHelper.h"
#include "Debug.h"

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;
using namespace boost::filesystem;


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


/// Prompts the human player to select pokemon, name, etc. to be used in the
/// game. Player Index is 1-indexed
HumanPlayer* createHumanPlayer(int playerIndex)
{
    // tmp var for getting input
    string input;

    // ask for player's name
    cout << "Player " << playerIndex << ", what is your name?" << endl;
    getline(cin, input);
    string name = input;

    // create player object
    HumanPlayer* player = new HumanPlayer(name);

    // list pokemon

    cout << name << ", Enter the id of the pokemon you want "
        << "or enter nothing to stop." << endl;
    
    // ask for pokemon
    bool continueGetInput = true;
    for(int i = 0; i < Environment::MAX_POKEMON and continueGetInput;
        i = player->getNumPokemon())
    {
        bool displayError = false;
        while(true)
        {
            // complain to user if they messed up
            if(displayError)
            {
                cout << "Invalid input." << endl;
            }
            displayError = true;

            // get input
            cout << "Pokemon " << (i+1) << " id: ";
            getline(cin, input);

            // parse input and create pokemon
            vector<string> splitInput = StringHelper::split(input);
            if(splitInput.size() == 0)
            {
                if(player->getNumPokemon() > 0)
                {
                    continueGetInput = false;
                }
                break;
            }
            else if(splitInput.size() > 1)
            {
                continue;
            }
            else
            {
                // parse to int
                char* endptr;
                const char* pokemonIdCStr = splitInput.at(0).c_str();
                int pokemonId = (int) strtol(pokemonIdCStr,
                    &endptr, 10);

                // if parse is success 
                if(*endptr == 0)
                {
                    // ask for pokemon nickname
                    cout << "Give a nickname to pokemon: " << endl;
                    getline(cin, input);
                    string nickname = input;

                    // add pokemon to id
                    Pokemon* pokemon = PokemonFactory::createPokemon(pokemonId,
                        nickname);
                    if(pokemon == NULL)
                    {
                        continue;
                    }
                    player->addPokemon(pokemon);
                    
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    return player;
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
    HumanPlayer* p1 = new HumanPlayer("Ash");
    Pokemon* poke1 = PokemonFactory::createPokemon(4, "");
    p1->addPokemon(poke1);
    HumanPlayer* p2 = new HumanPlayer("Gary");
    Pokemon* poke2 = PokemonFactory::createPokemon(1, "");
    p2->addPokemon(poke2);
    #else
    // Create human players with user input
    listPokemon();
    HumanPlayer* p1 = createHumanPlayer(1);
    HumanPlayer* p2 = createHumanPlayer(2);
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

