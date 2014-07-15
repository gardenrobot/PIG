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
#include "MajorAffliction.h"
#include "MinorAffliction.h"
#include "Pokemon.h"
#include "PokemonFactory.h"
#include "PokemonSpecies.h"
#include "PokemonId.h"
#include "MoveId.h"
#include "MoveFactory.h"
#include "EffectId.h"
#include "EffectFactory.h"
#include "StringHelper.h"

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;


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
    for(int i = 0; i < Player::MAX_POKEMON and continueGetInput; i++)
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
                PokemonId pokemonId = (PokemonId) strtol(pokemonIdCStr,
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
 * Print information on all pokemon species to stdout
 */
void listPokemon()
{
    cout << "Listing all pokemon species." << endl;
    const map<PokemonId, const PokemonSpecies*> allSpecies =
        PokemonFactory::getAllSpecies();
    for(map<PokemonId, const PokemonSpecies*>::const_iterator it =
        allSpecies.begin(); it != allSpecies.end(); it++)
    {
        PokemonId id = it->first;
        const PokemonSpecies* species = it->second;
        cout << id << ": " << species->speciesName << endl;
    }
    cout << endl;
}


/**
 * 
 */
int main(int argc, char** argv)
{
    PokemonFactory::initialize();
    MoveFactory::initialize();
    srand(50);

    #ifdef DEBUG_MODE
    // Hard coded players for testing
    HumanPlayer* p1 = new HumanPlayer("Ash");
    p1->addPokemon(PokemonFactory::createPokemon(CHARMANDER, "Flameo"));
    HumanPlayer* p2 = new HumanPlayer("Gary");
    p2->addPokemon(PokemonFactory::createPokemon(SQUIRTLE, "Watery"));
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

