// 
// File: Player.h 
// 
// Author: Lucas Clotfelter
// 
// Players hold a set of pokemon, and enter input when prompted.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Choice.h"

class Pokemon;

#include <vector>
#include <string>


class Player
{
  public:

    /// The player can have no more than this many pokemon
    static const int MAX_POKEMON = 6;

    ~Player();

    /// Add a pokemon to the player's team. It will be deleted by the player.
    void addPokemon(Pokemon* addedPokemon);

    /// This player gives up
    void surrender();

    /// Swaps the lead pokemon for the pokemon at the given index
    void swapPokemon(int index);

    /// Returns true if the player has been beaten
    bool hasLost() const;

    /// Prompt the user for input
    virtual Choice getInput(Player& otherPlayer) = 0;

    Pokemon* getPokemon(int index);

    int getNumPokemon() const;

    std::string getName() const;

  protected:

    Player(std::string name);

  private:

    /// The pokemon that the player owns.
    std::vector<Pokemon*> ownedPokemon;

    /// name: What the humans will use to identify the player
    std::string name;

    /// true if the player choose to surrender
    bool surrenders;

};

#endif // PLAYER_H_

