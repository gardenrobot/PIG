// 
// File: Debug.h 
// 
// Author: Lucas Clotfelter
// 
// Some macros and functions for debugging
// 
// //////////////////////////////////////////////////////////////////// 

#ifdef DEBUG_MODE

#include <iostream>
#include <cassert>


#define println_debug(x) std::cout << "DEBUG: " << x << std::endl

#define print_debug(x) std::cout << "DEBUG: " << x

#define assert_debug(x) assert(x)


#else


#define println_debug(x)

#define print_debug(x)

#define assert_debug(x)


#endif

