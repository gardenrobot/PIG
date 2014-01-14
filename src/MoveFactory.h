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

    static Move* createMove(int moveId);

};

#endif // MOVE_FACTORY_H_
