#include "Row.h" 
#include <string>

int Row::getPos(std::string name) const
{
    if ((*columns).find(name) != columns->end())
    {
        return (*columns)[name].number;
    }
    columns->erase(name);
    return -1;
}