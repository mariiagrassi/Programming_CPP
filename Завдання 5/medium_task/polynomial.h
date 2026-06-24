#pragma once
#include <iostream>

class Polynomial
{
private:
    int a2, a1, a0; // коефіцієнти при x^2, x^1, x^0

public:
    Polynomial(int a2 = 0, int a1 = 0, int a0 = 0);

    int operator()(int x) const; // обчислення значення поліному в точці x

    Polynomial operator+(const Polynomial &other) const;
    Polynomial operator-(const Polynomial &other) const;
    Polynomial operator*(int scalar) const; // множення поліному на число (множення двох поліномів степеня 2 дало б степінь 4, що не влізе в a2,a1,a0)

    bool operator==(const Polynomial &other) const;
    bool operator!=(const Polynomial &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Polynomial &p);
};