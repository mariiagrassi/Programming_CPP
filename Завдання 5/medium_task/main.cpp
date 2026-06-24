#include <iostream>
#include "polynomial.h"

int main()
{
    Polynomial p1(2, 3, 1);  // 2x^2 + 3x + 1
    Polynomial p2(1, -1, 5); // x^2 - x + 5

    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = " << p2 << std::endl;

    std::cout << "\np1(2) = " << p1(2) << std::endl;
    std::cout << "p2(0) = " << p2(0) << std::endl;

    std::cout << "\np1 + p2 = " << (p1 + p2) << std::endl;
    std::cout << "p1 - p2 = " << (p1 - p2) << std::endl;
    std::cout << "p1 * 3 = " << (p1 * 3) << std::endl;

    Polynomial p3(2, 3, 1);
    std::cout << "\np1 == p3: " << (p1 == p3 ? "true" : "false") << std::endl;
    std::cout << "p1 == p2: " << (p1 == p2 ? "true" : "false") << std::endl;
    std::cout << "p1 != p2: " << (p1 != p2 ? "true" : "false") << std::endl;

    Polynomial zero(0, 0, 0);
    std::cout << "\nzero = " << zero << std::endl;

    Polynomial onlyX(0, 1, 0);
    std::cout << "onlyX = " << onlyX << std::endl;

    Polynomial negative(-1, -2, -3);
    std::cout << "negative = " << negative << std::endl;

    return 0;
}