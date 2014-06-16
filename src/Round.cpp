// 
// File: Round.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Round.h"
#include "Environment.h"
#include "Player.h"
#include "Pokemon.h"
#include "Battle.h"
#include "Choice.h"
#include "Stat.h"
#include "MinorAffliction.h"
#include "Debug.h"

#include <iostream>

using namespace std;


void Round::doRound(Environment& env, Player& playerOne, Player& playerTwo)
{
    Choice choiceOne = playerOne.getInput(playerTwo);
    Choice choiceTwo = playerTwo.getInput(playerOne);

    Player* firstPlayer;
    Player* secondPlayer;
    Choice* firstChoice;
    Choice* secondChoice;

    determineFirstPlayer(playerOne, playerTwo, choiceOne, choiceTwo,
        firstPlayer, secondPlayer, firstChoice, secondChoice);

    processChoice(*firstPlayer, *secondPlayer, *firstChoice);
    processChoice(*secondPlayer, *firstPlayer, *secondChoice);

    playerOne.onRoundEnd();
    playerTwo.onRoundEnd();
}

void Round::determineFirstPlayer(Player& playerOne, Player& playerTwo,
    Choice& choiceOne, Choice& choiceTwo, Player*& firstPlayer,
    Player*& secondPlayer, Choice*& firstChoice, Choice*& secondChoice)
{
    bool isPlayerOneFirst = false;

    // if a player has chosen anything that is not a move, they will go first
    if(choiceOne.choiceType != MOVE)
    {
        isPlayerOneFirst = true;
    }
    else if(choiceTwo.choiceType != MOVE)
    {
        isPlayerOneFirst = false;
    }
    else
    {
        // if both players have chosen moves, the pokemon with the highest
        // speed goes first

        isPlayerOneFirst = playerOne.getPokemon(0)->getSpeed().getModValue() >
            playerTwo.getPokemon(0)->getSpeed().getModValue();
    }

    // set the pointers to the appropriate objects
    if(isPlayerOneFirst)
    {
        firstPlayer = &playerOne;
        firstChoice = &choiceOne;
        secondPlayer = &playerTwo;
        secondChoice = &choiceTwo;
    }
    else
    {
        firstPlayer = &playerTwo;
        firstChoice = &choiceTwo;
        secondPlayer = &playerOne;
        secondChoice = &choiceOne;
    }
}


void Round::processChoice(Player& attacking, Player& defending, Choice& choice)
{
    switch(choice.choiceType)
    {
        case MOVE:
        {
            Pokemon* attackingPokemon = attacking.getPokemon(0);
            Pokemon* defendingPokemon = defending.getPokemon(0);
            Move* chosenMove = attackingPokemon->getMove(choice.index - 1);

            bool skipBattle = false;
            for(int i = 0; i < attackingPokemon->getNumMinorAfflictions(); ++i)
            {
                if(attackingPokemon->getMinorAffliction(i)->whenAttacks())
                {
                    skipBattle = true;
                }
            }

            if(not skipBattle)
            {
                Battle::doBattle(*attackingPokemon, *defendingPokemon, *chosenMove);
            }

            break;
        }

        case SWAP_POKEMON:
        {
            int index = choice.index - 1;
            assert_debug(attacking.canSwap(index));

            cout << attacking.getPokemon(0)->getNickname() <<
                " was swapped for " <<
                attacking.getPokemon(index)->getNickname() << endl;
            attacking.swapPokemon(index);

            break;
        }

        case SURRENDER:
        {
            attacking.surrender();
            break;
        }

        case SKIP:
        {
            break;
        }

        default:
        {
            println_debug("Unknown command");
            break;
        }
    }
}

