#include "DataBase.h"
#include <iostream>
#include "Condition.h"

int main()
{
    DataBase db;
    //auto response = db.query("");
    db.load("db");
    db.save("db");
    //std::string arithm = "c1=c2";
    //Condition cond(arithm);
    //bool res = cond.apply(db.tables["amogus"].rows.front());
    return 0;
}