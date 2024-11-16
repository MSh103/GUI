#ifndef MessageBoxForWindows_h
#define MessageBoxForWindows_h

#include <windows.h>
#include <string>
#include "../../GLOBALS/globals.hpp"


namespace Gui
{
class MessageBoxM {
private:
    int choice;

public:
    MessageBoxM(sf::RenderWindow& target, LPCSTR Title, LPCSTR Message, DWORD type)
    {
        choice = MessageBoxA(target.getSystemHandle(), Message, Title, type);
    }

    int getChoice() { return choice; }
};
}

#endif