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

class Move;

class MoveFactory
{

  public:

    /// Must be called once per process before use of this class.
    static void initialize();

    /// Create pokemon of the species id. Calling function must de-allocate.
    static Move* createMove(int speciesId);

};

#endif // MOVE_FACTORY_H_
