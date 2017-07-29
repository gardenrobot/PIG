// 
// File: Category.h 
// 
// Author: Sam Clotfelter
// 
// These are the different categories of moves. Categories describe what the
// move does. Status moves do not do direct damage but have a hook for effects.
// Special moves Special moves do direct damage and use special attack/defense
// damage calculation. Physical moves do direct damage and use attack/defense
// for damage calculation.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef CATEGORY_H_
#define CATEGORY_H_


typedef enum
{
    STATUS = 0,
    SPECIAL = 1,
    PHYSICAL = 2
} Category;

#endif // CATEGORY_H_

