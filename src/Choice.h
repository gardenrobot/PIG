// 
// File: Choice.h 
// 
// Author: Lucas Clotfelter
// 
// This struct holds information about user input
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef CHOICE_H_
#define CHOICE_H_


/// These enums are actions that the players can take
typedef enum
{
    MOVE, SWAP_POKEMON, SKIP, SURRENDER
} ChoiceType;

struct Choice
{
    Choice(ChoiceType choiceType, int index);

    /// The action that the player decided to take
    ChoiceType choiceType;

    /// The index of the pokemon or move that the player choice for the action
    int index;
};

#endif // CHOICE_H_

