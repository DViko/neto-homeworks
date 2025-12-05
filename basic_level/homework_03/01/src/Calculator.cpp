#include "Calculator.hpp"

bool Calculator::_CheckZero(double num)
{
    return num == 0;
};

bool Calculator::SetNum_1(double num_1)
{
    if(this->_CheckZero(num_1))
    {
        return false;
    }

    this ->_num_1 = num_1;
    return true;
};

bool Calculator::SetNum_2(double num_2)
{
    if(this->_CheckZero(num_2))
    {
        return false;
    }

    this ->_num_2 = num_2;
    return true;
};

double Calculator::Add_1_2()
{
    return this->_num_1 + this->_num_2;
};

double Calculator::Multiply_1_2()
{
    return this->_num_1 * this->_num_2;
};

double Calculator::Subtract_1_2()
{
    return this->_num_1 - this->_num_2;
};

double Calculator::Subtract_2_1()
{
    return this->_num_2 - this->_num_1;
};

double Calculator::Divide_1_2()
{
    return this->_num_1 / this->_num_2;
};

double Calculator::Divide_2_1()
{
    return this->_num_2 / this->_num_1;
};