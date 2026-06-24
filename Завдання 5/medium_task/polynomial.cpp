#include "polynomial.h"
#include <sstream>

Polynomial::Polynomial(int a2, int a1, int a0) : a2(a2), a1(a1), a0(a0) {}

int Polynomial::operator()(int x) const
{
    return a2 * x * x + a1 * x + a0;
}

Polynomial Polynomial::operator+(const Polynomial &other) const
{
    return Polynomial(a2 + other.a2, a1 + other.a1, a0 + other.a0);
}

Polynomial Polynomial::operator-(const Polynomial &other) const
{
    return Polynomial(a2 - other.a2, a1 - other.a1, a0 - other.a0);
}

Polynomial Polynomial::operator*(int scalar) const
{
    return Polynomial(a2 * scalar, a1 * scalar, a0 * scalar);
}

bool Polynomial::operator==(const Polynomial &other) const
{
    return a2 == other.a2 && a1 == other.a1 && a0 == other.a0;
}

bool Polynomial::operator!=(const Polynomial &other) const
{
    return !(*this == other);
}

// допоміжна функція - друкує один член полінома ("+ 3x^2", "- x", "+ 5")
static void printTerm(std::ostream &os, int coef, const std::string &power, bool &isFirst)
{
    if (coef == 0)
        return;

    if (!isFirst)
        os << (coef > 0 ? " + " : " - ");
    else if (coef < 0)
        os << "-";

    int absCoef = (coef < 0) ? -coef : coef;

    if (power.empty())
        os << absCoef; // вільний член друкуємо завжди з числом
    else if (absCoef == 1)
        os << power; // коефіцієнт 1 не друкуємо, просто "x" чи "x^2"
    else
        os << absCoef << power;

    isFirst = false;
}

std::ostream &operator<<(std::ostream &os, const Polynomial &p)
{
    bool isFirst = true;

    printTerm(os, p.a2, "x^2", isFirst);
    printTerm(os, p.a1, "x", isFirst);
    printTerm(os, p.a0, "", isFirst);

    if (isFirst) // всі коефіцієнти були нульові
        os << "0";

    return os;
}