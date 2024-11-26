#include "DataBase.h"
#include <iostream>
#include "Condition.h"

int main()
{
    DataBase db;
    auto response = db.query("");
    //db.load("db");
    //db.save("db");
    for (auto &it : response)
    {
        int s = it.get<int>("c2");
        std::cout << s << std::endl;
    }
    return 0;
}