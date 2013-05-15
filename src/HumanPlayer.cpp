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

#include <iostream>
#include <string>
#include <sstream>

using namespace std;


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
    cout << getName() << ", enter choice..." << endl;

    string input;
    getline(cin, input);

    vector<string> splitInput(StringHelper::split(input));

    if(splitInput.size() < 1)
    {
        return NULL;
    }
    else if(splitInput[0] == MOVE_COMMAND)
    {
        if(splitInput.size() < 2)
        {
            return NULL;
        }

        int index;
        bool success = stringstream(splitInput[1]) >> index;

        if(not success)
        {
            return NULL;
        }

        return new Choice(MOVE, index);
    }
    else if(splitInput[0] == SWAP_POKEMON_COMMAND)
    {
        if(splitInput.size() < 2)
        {
            return NULL;
        }

        int index;
        bool success = stringstream(splitInput[1]) >> index;

        if(not success)
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
            otherPokemon->getNickname() << " ";
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
        cout << "surrender" << endl;
        cout << "  Give up" << endl;
        return NULL;
    }
    return NULL;
}

