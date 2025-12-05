#pragma once

class Counter
{
private:

    int _value {0};

public:

    void SetValue(int value);
    void Increment();
    void Decrement();
    int GetValue() const ;
};