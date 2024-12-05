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

    auto response = db.execute("create table amogus ({autoincrement} c1 : int32 = 0, c2 : int32 = 1, c3 : string[10])");
    response = db.execute("insert (,,\"bebra\") to amogus");
    response = db.execute("insert (,10,\"goyda\") to amogus");
    response = db.execute("select * from amogus");
    for (auto &it : response)
    {
        int c1 = it.get<int>("c1");
        int c2 = it.get<int>("c2");
        std::string c3 = it.get<std::string>("c3");
        std::cout << c1 << " " << c2 << " " << c3 << std::endl;
    }
    std::cout << std::endl;

    response = db.execute("update amogus set c1 = 10 where c2 = 10");
    response = db.execute("select * from amogus");
    for (auto &it : response)
    {
        int c1 = it.get<int>("c1");
        int c2 = it.get<int>("c2");
        std::string c3 = it.get<std::string>("c3");
        std::cout << c1 << " " << c2 << " " << c3 << std::endl;
    }
    std::cout << std::endl;

    response = db.execute("delete from amogus where c1 = 10");
    response = db.execute("select * from amogus");
    for (auto &it : response)
    {
        int c1 = it.get<int>("c1");
        int c2 = it.get<int>("c2");
        std::string c3 = it.get<std::string>("c3");
        std::cout << c1 << " " << c2 << " " << c3 << std::endl;
    }
    std::cout << std::endl;

    response = db.execute("insert (,5,\"skibidi\") to amogus");
    response = db.execute("insert (,6,\"skibidi\") to amogus");
    response = db.execute("select * from amogus where c3 = \"skibidi\"");
    for (auto &it : response)
    {
        int c1 = it.get<int>("c1");
        int c2 = it.get<int>("c2");
        std::string c3 = it.get<std::string>("c3");
        std::cout << c1 << " " << c2 << " " << c3 << std::endl;
    }
    std::cout << std::endl;

    response = db.execute("create table amogus2 ({unique} d1 : int32 = 0)");
    response = db.execute("insert () to amogus2");
    response = db.execute("insert () to amogus2");
    std::cout << response.what() << std::endl;
    std::cout << std::endl;

    db.save("db");

    DataBase db2;
    db2.load("db");

    response = db2.execute("select * from amogus");
    for (auto &it : response)
    {
        int c1 = it.get<int>("c1");
        int c2 = it.get<int>("c2");
        std::string c3 = it.get<std::string>("c3");
        std::cout << c1 << " " << c2 << " " << c3 << std::endl;
    }
    std::cout << std::endl;
    response = db2.execute("select * from amogus2");
    for (auto &it : response)
    {
        int d1 = it.get<int>("d1");
        std::cout << d1 << std::endl;
    }

    return 0;
}