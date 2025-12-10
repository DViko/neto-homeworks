#pragma once

class Counter
{
    private:

        int _value {};

    public:

        Counter();
        Counter(int initial_value);

        void Increment();
        void Decrement();
        int GetValue() const ;
};