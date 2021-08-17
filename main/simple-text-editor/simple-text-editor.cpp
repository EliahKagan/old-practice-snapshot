#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <utility>

namespace {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
    std::string buffer;
    std::stack<std::function<void()>> undos;
#ifdef __clang__
#pragma clang diagnostic pop
#endif
}

inline std::string::size_type from_end(const std::string::size_type k)
{
    return buffer.size() - k;
}

inline std::function<void()> appender(std::string&& w)
{
    return [w(w)]() { buffer += w; };
}

inline std::function<void()> eraser(const std::string::size_type k)
{
    return [=]() { buffer.resize(from_end(k)); };
}

template<typename T>
inline void read(T& x)
{
    std::cin >> x;
    assert(std::cin);
}

int main()
{
    buffer.reserve(6'000'000u); // reserve up to problem constraints' max size
    
    std::string::size_type k;
    std::cin >> k; // ignore Q value; apparently it is unreliable

    for (std::string w; std::cin >> k; ) {
        switch (k) {
        case 1: // append
            read(w);
            undos.push(eraser(w.size()));
            appender(std::move(w))();
            continue;

        case 2: // erase
            read(k);
            undos.push(appender(buffer.substr(from_end(k))));
            eraser(k)();
            continue;

        case 3: // get
            read(k);
            std::cout << buffer.at(--k) << '\n';
            continue;

        case 4: // undo
            assert(!undos.empty());
            undos.top()();
            undos.pop();
            continue;

        default:
            assert(false); // invalid query type
        }
    }
}
