#include <array>
#include <cstddef>
#include <iostream>
#include <sstream>

namespace {
    template<typename T, std::size_t M, std::size_t N>
    using Matrix = std::array<std::array<T, N>, M>;

    template<typename T, std::size_t L, std::size_t M, std::size_t N>
    Matrix<T, L, N> operator*(const Matrix<T, L, M>& a,
                              const Matrix<T, M, N>& b)
    {
        Matrix<T, L, N> c {};

        for (std::size_t i {0u}; i != L; ++i) {
            for (std::size_t k {0u}; k != N; ++k) {
                for (std::size_t j {0u}; j != M; ++j)
                    c[i][k] += a[i][j] * b[j][k];
            }
        }

        return c;
    }

    template<typename T, std::size_t N>
    std::istream& operator>>(std::istream& in, std::array<T, N>& row)
    {
        for (auto& x : row) in >> x;
        return in;
    }

    template<typename T, std::size_t N>
    std::ostream& operator<<(std::ostream& out, const std::array<T, N>& row)
    {
        auto sep = "";
        for (const auto x : row) {
            out << sep << x;
            sep = " ";
        }

        return out;
    }

    template<typename T, std::size_t M, std::size_t N>
    std::istream& operator>>(std::istream& in, Matrix<T, M, N>& matrix)
    {
        for (auto& row : matrix) in >> row;
        return in;
    }

    template<typename T, std::size_t M, std::size_t N>
    std::ostream& operator<<(std::ostream& out, const Matrix<T, M, N>& matrix)
    {
        for (const auto& row : matrix) out << row << '\n';
        return out;
    }
}

int main()
{
    const Matrix<int, 2, 2> a {{{{10, 20}}, {{30, 40}}}};
    const Matrix<int, 2, 1> b {{{{7}}, {{9}}}};
    std::cout << a << '\n' << b << '\n' << a * b;

    const Matrix<double, 3, 3> c {{{{1.2, 3.4, 5.6}},
                                   {{6.9, 5.8, 4.7}},
                                   {{2.5, 4.1, 7.7}}}};
    const Matrix<double, 3, 2> d {{{{1.1, 2.2}},
                                   {{3.3, 4.4}},
                                   {{5.5, 6.6}}}};
    std::cout << '\n' << c << '\n' << d << '\n' << c * d;

    std::istringstream ss {"1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1"};
    Matrix<float, 4, 4> e {};
    if (ss >> e) std::cout << '\n' << e;
}
