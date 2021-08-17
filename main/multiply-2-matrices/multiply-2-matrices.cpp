#include <array>
#include <cstddef>
#include <iostream>

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
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        Matrix<int, 3, 3> a {}, b {};
        std::cin >> a >> b;
        std::cout << a * b;
    }
}
