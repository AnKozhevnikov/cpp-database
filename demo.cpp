#include "DataBase.h"
#include <iostream>

int main()
{
    DataBase db;
    auto response = db.query("");
    db.save("db");
    return 0;
}