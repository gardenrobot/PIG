// 
// File: HumanPlayer.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Player.h"
#include "HumanPlayer.h"
#include "StringHelper.h"
#include "Pokemon.h"
#include "Move.h"
#include "MajorAffliction.h"
#include "Gender.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;


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

HumanPlayer::HumanPlayer(string name)
:Player(name)
{
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

    // parse input into a list of token
    vector<string> splitInput(StringHelper::split(input));

    // if no token
    if(splitInput.size() < 1)
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

