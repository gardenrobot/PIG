// 
// File: Battle.h 
// 
// Author: Sam Clotfelter
// 
// This class's functions will process a single battle step
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef BATTLE_H_
#define BATTLE_H_

class Pokemon;
class Move;


class Battle
{

  public:

    /// Performs a battle on the two pokemon using the move. Move must belong
    /// to attacking pokemon.
    static void doBattle(Pokemon& attacking, Pokemon& defending, Move& move);

    /// Rounds damage to be inflicted on pokemon.
    static int roundDamage(float damage);

  private:

    /// Determines whether this move will hit the defending pokemon
    static bool willMoveHit(Pokemon& attacking, Pokemon& defending, Move& move);

    /// Calculates the probability that a move will hit
    static float calcHitProb(Pokemon& attacking, Pokemon& defending, Move& move);

    /// Returns the damage that the move does to the defending pokemon.
    static int getDamage(Pokemon& attacking, Pokemon& defending, Move& move);

};

#endif // BATTLE_H_

