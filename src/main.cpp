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


/**
 * Print information on all pokemon species to stdout
 */
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


/**
 * Prompts the human player to select pokemon, name, etc. to be used in the
 * game. Player Index is 1-indexed
 */
HumanPlayer* createHumanPlayer(int playerIndex)
{
    string input;

    // ask name
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
    for(int i = 0; i < Player::MAX_POKEMON and continueGetInput;
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


/**
 * Run the main loop of the game.
 */
int run(int argc, char** argv)
{
    srand(50);
    Type::initialize();
    MoveFactory::initialize();
    PokemonFactory::initialize();

    #ifdef DEBUG_MODE
    // Hard coded players for testing
    println_debug("Debug mode");
    HumanPlayer* p1 = new HumanPlayer("Ash");
    Pokemon* poke1 = PokemonFactory::createPokemon(4, "");
    p1->addPokemon(poke1);
    HumanPlayer* p2 = new HumanPlayer("Gary");
    Pokemon* poke2 = PokemonFactory::createPokemon(1, "");
    p2->addPokemon(poke2);
    //poke1->addMinorAffliction(new Infatuation(*poke1, *poke2));
    #else
    // Create players
    listPokemon();
    HumanPlayer* p1 = createHumanPlayer(1);
    HumanPlayer* p2 = createHumanPlayer(2);
    #endif

    Environment env(p1, p2);

    cout << endl;
    cout << "Starting game." << endl;
    for(int i = 0; not p1->hasLost() and not p2->hasLost(); ++i)
    {
        cout << "Round " << (i + 1) << endl;

        Round::doRound(env, *p1, *p2);
    }

    cout << "Done." << endl;
    PokemonFactory::destroy();
    MoveFactory::destroy();
}


int main(int argc, char** argv)
{
    return run(argc, argv);
}

