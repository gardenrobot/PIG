// 
// File: HumanPlayer.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Player.h"
#include "HumanPlayer.h"
#include "Environment.h"
#include "Pokemon.h"
#include "PokemonFactory.h"
#include "Move.h"
#include "MajorAffliction.h"
#include "Gender.h"

#include <iostream>
#include <string>
#include <sstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim_all.hpp>

using namespace std;
using namespace boost::algorithm;


// define command strings
const string HumanPlayer::MOVE_COMMAND = "move";
const string HumanPlayer::SWAP_POKEMON_COMMAND = "swap";
const string HumanPlayer::SKIP_COMMAND = "skip";
const string HumanPlayer::SURRENDER_COMMAND = "surrender";
const string HumanPlayer::INFO_COMMAND = "info";
const string HumanPlayer::HELP_COMMAND = "help";

const string HumanPlayer::PLAYER = "player";
const string HumanPlayer::ENEMY = "enemy";
const string HumanPlayer::POKEMON = "pokemon";

HumanPlayer::HumanPlayer(int playerIndex)
:Player(askForName(playerIndex))
{
    // tmp var for getting input
    string input;

    cout << getName() << ", Enter the id of the pokemon you want "
        << "or enter nothing to stop." << endl;
    
    // ask for pokemon
    bool continueGetInput = true;
    for(int i = 0; i < Environment::MAX_POKEMON and continueGetInput;
        i = getNumPokemon())
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
            trim(input);
            if(input == "")
            {
                if(getNumPokemon() > 0)
                {
                    continueGetInput = false;
                }
                break;
            }
            else
            {
                // parse to int
                char* endptr;
                const char* pokemonIdCStr = input.c_str();
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
                    addPokemon(pokemon);
                    
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
    }
}


string HumanPlayer::askForName(int playerIndex)
{
    // ask for player's name
    string input;
    cout << "Player " << playerIndex << ", what is your name?" << endl;
    getline(cin, input);

    // set the name
    return input;
}


Choice HumanPlayer::getInput(Player& otherPlayer)
{
    bool isValid = false;
    Choice* tmpChoice;
    while(not isValid)
    {
        tmpChoice = askForInput(otherPlayer);
        isValid = tmpChoice != NULL;
        cout << endl;

    }

    Choice choice = *tmpChoice;
    delete tmpChoice;
    return choice;
}


Choice* HumanPlayer::askForInput(Player& otherPlayer)
{
    // print prompt
    cout << getName() << ", enter choice..." << endl;

    // get input
    string input;
    getline(cin, input);
    trim_all(input);

    // parse input into a list of token
    vector<string> splitInput;
    split(splitInput, input, is_any_of(" "), token_compress_on);

    // if no token
    if(splitInput.size() == 0 or splitInput[0] == "")
    {
        return NULL;
    }
    else if(splitInput[0] == MOVE_COMMAND)
    {
        // check if number of tokens
        if(splitInput.size() != 2)
        {
            return NULL;
        }

        int index;
        bool success = stringstream(splitInput[1]) >> index;

        // check if error parsing to int
        if(not success)
        {
            return NULL;
        }
        // check if index is out of bounds
        if(index < 0 or index > getPokemon(0)->getNumMoves())
        {
            return NULL;
        }

        return new Choice(MOVE, index);
    }
    else if(splitInput[0] == SWAP_POKEMON_COMMAND)
    {
        // check if number of tokens
        if(splitInput.size() != 2)
        {
            return NULL;
        }

        int index;
        bool success = stringstream(splitInput[1]) >> index;

        if(not success)
        {
            return NULL;
        }

        if(not canSwap(index - 1))
        {
            return NULL;
        }

        return new Choice(SWAP_POKEMON, index);
    }
    else if(splitInput[0] == INFO_COMMAND)
    {
        // print info of all player's pokemon and basic info of the enemy's
        // lead pokemon
        cout << getName() << ", you have " << getNumPokemon() << " pokemon." <<
            endl;
        for(int i = 0; i < getNumPokemon(); ++i)
        {
            Pokemon* poke = getPokemon(i);
            cout << (i+1) << ": " << poke->getNickname() << " ";

            // print gender
            cout << GenderString::genderToLetter(poke->getGender()) << " ";

            // print major affliction if exists
            if(poke->getMajorAffliction() != NULL)
            {
                cout << poke->getMajorAffliction()->shortName;
            }
            cout << endl;

            cout << "   Species: " << poke->getSpeciesName() << endl;
            cout << "   HP: " << poke->getHp() << " / " << poke->getMaxHp() <<
                endl;

            cout << "   Moves:" << endl;
            for(int j = 0; j < poke->getNumMoves(); ++j)
            {
                Move* move = poke->getMove(j);
                cout << "      " << (j + 1) << ". " << move->getName() << " "
                    << endl;
            }

        }
        cout << endl;

        Pokemon* otherPokemon = otherPlayer.getPokemon(0);
        cout << otherPlayer.getName() << "'s lead pokemon is " <<
            otherPokemon->getNickname() << " " <<
            GenderString::genderToLetter(otherPokemon->getGender()) << " ";
        if(otherPokemon->getMajorAffliction() != NULL)
        {
            cout << otherPokemon->getMajorAffliction()->shortName;
        }
        cout << endl;
        cout << "   Species: " << otherPokemon->getSpeciesName() << endl;
        cout << "   HP: " << otherPokemon->getHp() << " / " <<
            otherPokemon->getMaxHp() << endl;

        return NULL;
    }
    else if(splitInput[0] == SKIP_COMMAND)
    {
        return new Choice(SKIP, 0);
    }
    else if(splitInput[0] == SURRENDER_COMMAND)
    {
        return new Choice(SURRENDER, 0);
    }
    else if(splitInput[0] == HELP_COMMAND)
    {
        cout << "All commands: " << endl;
        cout << "move <move index>" << endl;
        cout << "  Use your pokemon's move" << endl;
        cout << "swap <pokemon index>" << endl;
        cout << "  Switch current pokemon for another in team" << endl;
        cout << "skip" << endl;
        cout << "  Do nothing this turn" << endl;
        cout << "info" << endl;
        cout << "  Show information of battle" << endl;
        cout << "surrender" << endl;
        cout << "  Give up" << endl;
        return NULL;
    }
    return NULL;
}

