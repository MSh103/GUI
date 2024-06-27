#ifndef MessageBox_h
#define MessageBox_h

#ifdef _WIN32
#include "WINDOWS/MessageBoxForWindows.hpp"
#elif _WIN64
#include "WINDOWS/MessageBoxForWindows.hpp"
#elif __APPLE__ || __MACH__
//TO-DO
#elif __linux__
//TO-DO
#endif

#endif