#include <type_traits>

namespace {
    struct S {
        constexpr bool f() const noexcept
        {
            using Foo = decltype(this);
            return std::is_same_v<const S*, decltype(this)>;
        }
    };
}

int main()
{
    constexpr auto res = S{}.f();
}
