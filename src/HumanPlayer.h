// 
// File: HumanPlayer.h 
// 
// Author: Sam Clotfelter
// 
// A player that prompts the user for input
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Player.h"
#include "Choice.h"

#include <string>


class HumanPlayer : public Player
{
  public:

    HumanPlayer(int playerIndex);

    /// Prompts the user for input. The user can enter a command to take an
    /// action or view info. Stops prompting when user takes action.
    Choice getInput(Player& otherPlayer);

  private:

    /// Prompts the user for input once. Returns the choice, valid or not.
    Choice* askForInput(Player& otherPlayer);

    /// Ask user for player name
    std::string askForName(int playerIndex);


    /// Commands strings

    /// Use a pokemon's move.
    static const std::string MOVE_COMMAND;

    /// Swap current pokemon for another.
    static const std::string SWAP_POKEMON_COMMAND;

    /// Do nothing this round.
    static const std::string SKIP_COMMAND;

    /// Lose.
    static const std::string SURRENDER_COMMAND;

    /// Print info about game. Does not continue game.
    static const std::string INFO_COMMAND;

    /// Print info about commands. Does not continue game.
    static const std::string HELP_COMMAND;


    /// Possible arguments of info command
    static const std::string PLAYER;
    static const std::string ENEMY;
    static const std::string POKEMON;
};

#endif // HUMANPLAYER_H_

