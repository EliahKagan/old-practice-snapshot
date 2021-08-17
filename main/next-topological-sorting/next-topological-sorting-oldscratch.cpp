#ifdef NDEBUG
#error Assertions unexpectedly disabled.
#endif

#include <cassert>
#include <iostream>
#include <vector>

namespace {
    class KahnBacktracker {
    public:
        explicit KahnBacktracker(int order);



    private:
        int order() const noexcept;

        std::vector<int> in_;
        std::vector<int> out_;
        int inpos_ {0};
        int outpos_ {0};
    };

    KahnBacktracker::KahnBacktracker(const int order)
        : in_(order + 1), out_(order + 1)
    {
    }

    inline int KahnBacktracker::order() const noexcept
    {
        return static_cast<int>(in_.size()) - 1;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);


}
