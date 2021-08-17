#include <iostream>

struct Multiplier {
    double scale(double multiplicand)
    {
        return multiplicand * value;
    }

    double scale_twice(double multiplicand)
    {
        return multiplicand * value * value;
    }

    double value;
};

typedef double (Multiplier::*Scaling)(double);

int main()
{

    Scaling p = &Multiplier::scale, q = &Multiplier::scale_twice;

    // Calling with the binary .* operator.
    Multiplier by_three {3.0};
    std::cout << (by_three.*p)(1.5) << '\n';
    std::cout << (by_three.*q)(1.5) << '\n';

    // Calling with the binary ->* operator.
    Multiplier *r = &by_three;
    std::cout << (r->*p)(1.5) << '\n';
    std::cout << (r->*q)(1.5) << '\n';
}
