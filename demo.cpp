#include "DataBase.h"
#include <iostream>
#include <vector>

std::string prettybarr(std::vector<uint8_t> barr)
{
    std::string s = "0x";
    for (int i = 0; i < barr.size(); i++)
    {
        int c1 = barr[i] / 16;
        int c2 = barr[i] % 16;
        s += (c1 < 10 ? '0' + c1 : 'a' + c1 - 10);
        s += (c2 < 10 ? '0' + c2 : 'a' + c2 - 10);
    }
    return s;
}

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
    response = db.execute("select c1,c2,c3 from amogus where c1*5>c2+(2+2)");
    for (auto &it : response)
    {
        int c1 = it.get<int>("c1");
        int c2 = it.get<int>("c2");
        std::string c3 = it.get<std::string>("c3");
        std::cout << c1 << ' ' << c2 << ' ' << c3 << std::endl;
    }
    std::cout << std::endl;

    // response = db.execute("join amogus,bebra on b1=b2");
    response = db.join("amogus", "bebra", "b1=0xffffff");
    for (auto &it : response)
    {
        int c1 = it.get<int>("c1");
        int c2 = it.get<int>("c2");
        std::string c3 = it.get<std::string>("c3");
        std::vector<uint8_t> b1 = it.get<std::vector<uint8_t>>("b1");
        int b2 = it.get<int>("b2");
        std::cout << c1 << ' ' << c2 << ' ' << c3 << ' ' << prettybarr(b1) << ' ' << b2 << std::endl;
    }

    return 0;
}