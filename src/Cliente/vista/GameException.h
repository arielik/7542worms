#pragma once
#ifndef __GAME_EXCEPTION__
#define __GAME_EXCEPTION__
#include <string>
struct GameException : public std::exception
{
   std::string s;
   GameException(std::string ss) : s(ss) {}
   ~GameException() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};
#endif /* defined(__GAME_EXCEPTION__) */
