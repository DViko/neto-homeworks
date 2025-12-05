#include "Counter.hpp"

void Counter::SetValue(int value)
{
    _value = value;
}

void Counter::Increment()
{
    _value ++;
}

void Counter::Decrement()
{
    _value --;
}

int Counter::GetValue() const
{
    return _value;
}