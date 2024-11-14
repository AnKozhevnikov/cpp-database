#include <DataBase.h>

template <typename... T>
typename std::unique_ptr<DataBase::Cell> DataBase::Creator::generateCell(Types type, T... args)
{
    switch (type)
    {
        std::vector<std::any> v;
        case Int:
            return std::make_unique<IntCell>(v[0]);
        case Bool:
            return std::make_unique<BoolCell>(v[0]);
        case String:
            return std::make_unique<StringCell>(v[0]);
        case ByteArray:
            return std::make_unique<ByteArrayCell>(v[0], v[1]);
    }
}