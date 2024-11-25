#pragma once

enum Types
{
    Int,
    Bool,
    String,
    ByteArray
};

class ValueType {
public:
    ValueType(Types t) : type(t) {}
    Types type;
    virtual ~ValueType() = default;
};

class ByteArrayType : public ValueType {
public:
    ByteArrayType(int s) : ValueType(ByteArray) {
        size = s;
    }

    int size;
};