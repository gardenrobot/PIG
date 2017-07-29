// 
// File: Round.cpp 
// 
// Author: Sam Clotfelter
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
    // get both players' choices
    Choice choiceOne = playerOne.getInput(playerTwo);
    Choice choiceTwo = playerTwo.getInput(playerOne);

    // create points to the players and choices based on who is going first
    Player* firstPlayer;
    Player* secondPlayer;
    Choice* firstChoice;
    Choice* secondChoice;
    determineFirstPlayer(playerOne, playerTwo, choiceOne, choiceTwo,
        firstPlayer, secondPlayer, firstChoice, secondChoice);

    // play each of their choices
    processChoice(*firstPlayer, *secondPlayer, *firstChoice);
    processChoice(*secondPlayer, *firstPlayer, *secondChoice);

    // hook for round end
    playerOne.onRoundEnd(playerTwo);
    playerTwo.onRoundEnd(playerOne);
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
            // create pointers to both pokemon and the move
            Pokemon* attackingPokemon = attacking.getPokemon(0);
            Pokemon* defendingPokemon = defending.getPokemon(0);
            Move* chosenMove = attackingPokemon->getMove(choice.index - 1);

            // hooks for minor afflictions; if one returns true, skip the battle
            bool skipBattle = false;
            for(int i = 0; i < attackingPokemon->getNumMinorAfflictions(); ++i)
            {
                if(attackingPokemon->getMinorAffliction(i)->whenAttacks(*defending.getPokemon(0)))
                {
                    skipBattle = true;
                }
            }

            // do the battle unless it was skipped
            if(not skipBattle)
            {
                Battle::doBattle(*attackingPokemon, *defendingPokemon, *chosenMove);
            }

            break;
        }

        case SWAP_POKEMON:
        {
            // make 0-indexed
            int index = choice.index - 1;

            // test that args are valid
            assert_debug(attacking.canSwap(index));

            // print swap message 
            cout << attacking.getPokemon(0)->getNickname() <<
                " was swapped for " <<
                attacking.getPokemon(index)->getNickname() << endl;

            // swap them
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
            // no nothing
            break;
        }

        default:
        {
            println_debug("Unknown command");
            break;
        }
    }
}

