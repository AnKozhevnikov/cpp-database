#include "DataBase.h"
#include <iostream>
#include "Condition.h"

int main()
{
    DataBase db;
    //auto response = db.query("");
    db.load("db");
    //db.save("db");
    auto response = db.query("c1=c2");
    return 0;
}