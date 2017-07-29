// 
// File: Player.h 
// 
// Author: Sam Clotfelter
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

    ~Player();

    /// Add a pokemon to the player's team. It will be deleted by the player.
    void addPokemon(Pokemon* addedPokemon);

    /// This player gives up
    void surrender();

    /// Swaps the lead pokemon for the pokemon at the given index
    void swapPokemon(int index);

    /// Notifies its pokemon of the round end.
    void onRoundEnd(Player& enemyPlayer);

    /// Returns true iff it is legal to swap head pokemon with the pokemon at
    /// the given index
    bool canSwap(int index); 

    /// Returns true iff the player has been beaten
    bool hasLost() const;

    /// Prompt the user for input
    virtual Choice getInput(Player& otherPlayer) = 0;


    // Getters

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

