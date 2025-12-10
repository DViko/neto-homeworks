#include "Counter.hpp"

Counter::Counter()
{
    _value = 0;
}

Counter::Counter(int initial_value)
{
    _value = initial_value;
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