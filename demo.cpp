#include "DataBase.h"
#include <iostream>
#include "Condition.h"

int main()
{
    DataBase db;
    //auto response = db.query("");
    db.load("db");
    //db.save("db");
    /*for (auto &it : response)
    {
        std::string s = it.get<std::string>("c3");
        std::cout << s << std::endl;
    }*/
    auto response = db.execute("select c3 from amogus where c1 = c2");
    return 0;
}