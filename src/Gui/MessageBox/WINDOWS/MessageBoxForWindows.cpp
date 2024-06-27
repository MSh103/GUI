#include "MessageBoxForWindows.hpp"

MessageBoxM::MessageBoxM(LPCSTR Title, LPCSTR Message, DWORD type)
{
    MessageBoxA(NULL, Title, Message, type);
}