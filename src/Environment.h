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

    static const int PRNG_SEED;

    /// The directory that contains all data files
    static const std::string DATA_DIR;

    /// The limit on the number of rounds that will be run, or -1 for no limit
    static const int MAX_ROUNDS;

    /// The maximum number of moves each pokemon can have
    static const int MAX_MOVES;

    /// The maximum number of pokemon each player can have
    static const int MAX_POKEMON;

    /// The data file for pokemon stats
    static const std::string POKEMON_DATA_FILE;

    /// The data file for move stats
    static const std::string MOVE_DATA_FILE;

    /// The data file for type modifiers
    static const std::string TYPE_DATA_FILE;


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

