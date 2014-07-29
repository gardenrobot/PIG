// 
// File: Environment.h 
// 
// Author: Lucas Clotfelter
// 
// The environment in which the game happens
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <string>

class Player;

class Environment
{
  public:

    /// The directory that contains all data files
    static const std::string DATA_DIR;

    /// The limit on the number of rounds that will be run, or -1 for no limit
    static const int MAX_ROUNDS = 15;

    // Create environment with these players. Does not start game execution.
    Environment(Player* playerOne, Player* playerTwo);

    ~Environment();

    /// Starts the game
    Player* doGame();

  private:

    /// The two players playing the game
    Player* playerOne;
    Player* playerTwo;

    /// The current number of rounds that have passed
    int roundCount;

};

#endif // ENVIRONMENT_H_

