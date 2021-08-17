class DiningPhilosophers {
public:
    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork)
    {
        const auto left = philosopher;
        const auto right = (count + philosopher - 1) % count;
        assert(left != right);

        if (left < right) {
            const auto leftLock = lock_guard{mutexes.at(left)};
            pickLeftFork();

            {
                const auto rightLock = lock_guard{mutexes.at(right)};
                pickRightFork();
                eat();
                putRightFork();
            }

            putLeftFork();
        } else {
            const auto rightLock = lock_guard{mutexes.at(right)};
            pickRightFork();

            {
                const auto leftLock = lock_guard{mutexes.at(left)};
                pickLeftFork();
                eat();
                putLeftFork();
            }

            putRightFork();
        }
    }

private:
    static constexpr auto count = 5;

    array<mutex, count> mutexes {};
};
