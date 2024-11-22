#include "DataBase.h"
#include <iostream>

int main()
{
    DataBase db;
    //auto response = db.query("");
    db.load("db");
    db.save("db");
    return 0;
}