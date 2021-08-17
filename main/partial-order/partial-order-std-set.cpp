#include <iostream>
#include <set>

namespace {
    struct TaggedInt {
        int value, tag;

        explicit TaggedInt(int value) : value{value}, tag{++last_tag} { }

    private:
        static int last_tag;
    };

    int TaggedInt::last_tag {0};

    inline bool operator==(const TaggedInt& lhs, const TaggedInt& rhs)
    {
        return lhs.value == rhs.value && lhs.tag == rhs.tag;
    }

    inline bool operator!=(const TaggedInt& lhs, const TaggedInt& rhs)
    {
        return !(lhs == rhs);
    }

    inline bool operator<(const TaggedInt& lhs, const TaggedInt& rhs)
    {
        return lhs.value < rhs.value;
    }

    inline bool operator>(const TaggedInt& lhs, const TaggedInt& rhs)
    {
        return lhs.value > rhs.value;
    }

    std::ostream& operator<<(std::ostream& out, const TaggedInt& ti)
    {
        return out << ti.value << '[' << ti.tag << ']';
    }
}

int main()
{
    const TaggedInt i {5}, j {3}, k {5};
    std::cout << i << ' ' << j << ' ' << k << "\n\n";

    std::set<TaggedInt> s {i, j, k};
    for (const auto& e : s) std::cout << e << '\n';
    std::cout << "Done.\n";
}
