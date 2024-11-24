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
    virtual std::string toString() {
        return std::to_string(type);
    }
    Types type;
};

class ByteArrayType : public ValueType {
public:
    ByteArrayType(int s) : ValueType(ByteArray) {
        size = s;
    }

    virtual std::string toString() override {
        return std::to_string(type) + "[" + std::to_string(size) + "]";
    }

    int size;
};