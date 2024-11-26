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
        std::string s = it.get<std::string>("c3");
        std::cout << s << std::endl;
    }
    return 0;
}