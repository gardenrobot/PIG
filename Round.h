// 
// File: Round.h 
// 
// Author: Lucas Clotfelter
// 
// Each game is separated into rounds
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef ROUND_H_
#define ROUND_H_

#include "Choice.h"

class Player;
class Environment;


class Round
{
  public:

    /// Performs a round of the game.
    static void doRound(Environment& env, Player& playerOne, Player& playerTwo);

  private:

    /// Determine which player should go first and  set "first" and "second"
    /// pointers to the appropriate objects.
    static void determineFirstPlayer(Player& playerOne, Player& playerTwo,
        Choice& choiceOne, Choice& choiceTwo, Player*& firstPlayer,
        Player*& secondPlayer, Choice*& firstChoice, Choice*& secondChoice);

    /// Does all the work of one player's choice
    static void processChoice(Player& attacking, Player& defending,
        Choice& choice);
};

#endif // ROUND_H_

