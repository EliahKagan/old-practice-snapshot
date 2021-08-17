// multiwait.cxx - Spawns multiple threads that wait different amounts of time.
//     Surprisingly, this program is not totally useless. It can be used to
//     get a ballpark benchmark on how much added delay to expect when a thread
//     sleeps, beyond the specified sleep time. (At least on non-RTOSes,
//     a thread cannot avoid sleeping longer than the specified time, though
//     usually the delay is slight, given sufficiently low system load.)

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <regex>
#include <stdexcept>
#include <string>
#include <system_error>
#include <thread>
#include <vector>

// Timer class interface and implementation
namespace {
    class Timer {
    public:
        static void stats();

        explicit Timer(int t_in_ms) : t{t_in_ms} { }
        void operator()() const;

    private:
        using TimePoint
            = std::chrono::time_point<std::chrono::high_resolution_clock>;
        using Lock = std::lock_guard<std::mutex>;

        static std::string s_if_plural(int i) { return i == 1 ? "" : "s"; }
        static std::ostream& progress(std::ostream& out);
        static inline TimePoint now();

        static std::mutex m;
        static int threads_started, threads_ended, time_expected;
        static float time_elapsed;

        void start() const;
        void finish(const TimePoint& ti, const TimePoint& tf) const;

        const int t;
    };

    void Timer::stats()
    {
        Lock lk {m};

        std::cout << "Total elapsed time is " << time_elapsed << "ms (from "
            << threads_ended << " thread" << s_if_plural(threads_ended) << ')';

        if (threads_ended != 0) {
            std::cout << ", avg. delay = " << std::showpos
                << (time_elapsed - time_expected) / threads_ended
                << std::noshowpos << "ms.";
        }

        std::cout << std::endl;
    }

    std::ostream& Timer::progress(std::ostream& out)
    {
        return out << "\n   " << threads_ended << " of " << threads_started
                   << " thread" << s_if_plural(threads_started) << ' '
                   << (threads_ended == 1 ? "has" : "have") << " finished."
                   << std::endl;
    }

    Timer::TimePoint Timer::now()
    {
        return std::chrono::high_resolution_clock::now();
    }

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
    std::mutex Timer::m {};
#ifdef __clang__
#pragma clang diagnostic pop
#endif
    int Timer::threads_started {0}, Timer::threads_ended {0};
    int Timer::time_expected {0};
    float Timer::time_elapsed {0.f};

    void Timer::start() const
    {
        Lock lk {m};
        ++threads_started;
        std::cout << "*  " << t << "ms thread starting." << progress;
    }

    void Timer::finish(const TimePoint& ti, const TimePoint& tf) const
    {
        auto dt = std::chrono::duration<float, std::milli>{tf - ti}.count();
        Lock lk {m};
        time_expected += t, time_elapsed += dt, ++threads_ended;
        std::cout << "*  " << t << "ms thread ending (took " << dt << "ms, delay="
            << std::showpos << dt - t << std::noshowpos << "ms)." << progress;
    }

    void Timer::operator()() const
    {
        start();
        auto ti = now();
        std::this_thread::sleep_for(std::chrono::milliseconds(t));
        finish(ti, now());
    }
}

// utility functions
namespace {
    const char* progname; // set in main

    std::string basename(std::string path)
    {
#ifdef _WIN32
        constexpr bool windows {true};
#else
        constexpr bool windows {false};
#endif

        const auto last_sep = path.rfind(windows ? '\\' : '/');
        if (last_sep != std::string::npos) path.erase(0, last_sep + 1);

        return windows ? std::regex_replace(path, std::regex{"\\.exe$"}, "")
                       : path;
    }

    inline std::string progbase()
    {
        return basename(progname);
    }

    [[noreturn]] void die(const std::string& msg)
    {
        std::cerr << progbase() << ": error: " << msg << '\n';
        std::exit(EXIT_FAILURE);
    }

    [[noreturn]] void die(const std::error_code& code)
    {
        std::cerr << progbase() << ": error " << code.value() << ": "
            << code.message() << '\n';
        std::exit(EXIT_FAILURE);
    }

    [[noreturn]] void help()
    {
        std::cout << "multiwait, v.0.1\n"
            "Usage:  " << progbase() << " <time_in_milliseconds>...\n";
        std::exit(EXIT_SUCCESS);
    }

    bool need_help(int argc, const char* const* argv)
    {
        const std::vector<std::string> hopts {"--help", "-h", "/?"};
        return std::find_first_of(
            hopts.cbegin(), hopts.cend(), argv, argv + argc) != hopts.cend();
    }

    std::vector<int> times(int argc, const char* const* argv)
    {
        assert(argc >= 0 && argv != nullptr);

        std::vector<int> ts;
        ts.reserve(static_cast<std::vector<int>::size_type>(argc));
        std::for_each(argv, argv + argc, [&](const char* arg) {
            try {
                auto t = std::stoi(arg);
                if (t < 0) die("a negative time value was given");
                ts.push_back(t);
            }
            catch (const std::invalid_argument&) {
                die("a non-numeric time value was given");
            }
            catch (const std::out_of_range&) {
                die("a time value is out of range");
            }
        });

        return ts;
    }
}

int main(int argc, const char* const* argv)
{
    progname = argv[0];
    if (need_help(--argc, ++argv)) help();

    std::vector<std::thread> threads;
    threads.reserve(static_cast<std::vector<int>::size_type>(argc));

    try {
        for (const auto t : times(argc, argv)) threads.emplace_back(Timer{t});
        for (auto& th : threads) th.join();
    }
    catch (const std::system_error& e) { die(e.code()); }

    Timer::stats();
}
