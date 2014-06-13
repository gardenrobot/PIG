// 
// File: MoveFactory.h 
// 
// Author: Lucas Clotfelter
// 
// Factory that creates moves
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef MOVE_FACTORY_H_
#define MOVE_FACTORY_H_

#include <map>

class Move;
class MoveSpecies;


class MoveFactory
{

  public:

    /// Must be called once per process before use of this class.
    static void initialize();

    /// Create pokemon of the species id. Calling function must de-allocate.
    static Move* createMove(int speciesId);

  private:
    
    /// Holds one of each move species
    static std::map<int, MoveSpecies*> allSpecies;

};

#endif // MOVE_FACTORY_H_

