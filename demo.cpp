#include "DataBase.h"
#include <iostream>
#include "Condition.h"

int main()
{
    DataBase db;
    db.load("db");
    auto response = db.execute("select c3 from amogus where c1 = c2");
    for (auto &it : response)
    {
        std::string s = it.get<std::string>("c3");
        std::cout << s << std::endl;
    }
    response = db.execute("insert (5,5,\"goyda\") to amogus");
    response = db.execute("select c1,c2,c3 from amogus where c1*5>c2+4");
    for (auto &it : response) {
        int c1 = it.get<int>("c1");
        int c2 = it.get<int>("c2");
        std::string c3 = it.get<std::string>("c3");
        std::cout << c1 << ' ' << c2 << ' ' << c3 << std::endl;
    }
    return 0;
}