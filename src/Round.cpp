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
#include "Debug.h"


void Round::doRound(Environment& env, Player& playerOne, Player& playerTwo)
{
    Choice choiceOne = playerOne.getInput();
    Choice choiceTwo = playerTwo.getInput();

    Player* firstPlayer;
    Player* secondPlayer;
    Choice* firstChoice;
    Choice* secondChoice;

    determineFirstPlayer(playerOne, playerTwo, choiceOne, choiceTwo,
        firstPlayer, secondPlayer, firstChoice, secondChoice);

    processChoice(*firstPlayer, *secondPlayer, *firstChoice);
    processChoice(*secondPlayer, *firstPlayer, *secondChoice);
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

          Battle::doBattle(*attackingPokemon, *defendingPokemon, *chosenMove);
          break;
      }

      case SWITCH_POKEMON:
      {
          println_debug("switch");
          break;
      }

      case SURRENDER:
      {
          attacking.surrender();
          break;
      }

      default:
      {
          println_debug("Unknown command");
          break;
      }
    }
}

