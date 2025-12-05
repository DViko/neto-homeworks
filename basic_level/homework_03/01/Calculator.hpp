#pragma once

class Calculator
{
    private:

        double _num_1, _num_2;

        bool _CheckZero(double num);

    public:

        bool SetNum_1(double num_1);
        bool SetNum_2(double num_2);

        double Add_1_2();
        double Multiply_1_2();
        double Subtract_1_2();
        double Subtract_2_1();
        double Divide_1_2();
        double Divide_2_1();
};