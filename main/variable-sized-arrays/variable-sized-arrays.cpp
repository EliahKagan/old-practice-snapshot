#include <iostream>
using namespace std;

int main()
{
    class Seq {
    public:
        static constexpr int error_val() { return -1; } // precedes min index
        static const Seq& error_seq() { static Seq er {0}; return er; }

        Seq()
        {
            if (cin >> k && k > 0) {
                s = new int[k] {};
                
                auto i = 0;
                for (; i != k && cin >> s[i] && s[i] > error_val(); ++i) { }
                if (i != k) release();
            }
        }

        Seq(const Seq&) = delete;
        Seq(Seq&&) = delete;
        Seq& operator=(const Seq&) = delete;
        Seq&& operator=(Seq&&) = delete;

        ~Seq() { release(); }

        explicit operator bool() const { return s != nullptr; }

        int operator[](const int i) const
        {
            return (*this && 0 <= i && i < k) ? s[i] : error_val();
        }

    private:
        int k = 0;
        int* s = nullptr;

        explicit Seq(const int) { } // only for initializing er in error_seq()

        void release() { delete[] s; s = nullptr; }
    };

    class SeqSeq {
    public:
        explicit SeqSeq(const int n_) : n{n_}
        {
            if (n > 0) ss = new Seq[n];
            else n = 0;

            for (auto i = 0; i != n; ++i)
                if (!ss[i]) release();
        }

        SeqSeq(const SeqSeq&) = delete;
        SeqSeq(SeqSeq&&) = delete;
        SeqSeq& operator=(const SeqSeq&) = delete;
        SeqSeq&& operator=(SeqSeq&&) = delete;

        ~SeqSeq() { release(); }

        explicit operator bool() const { return ss != nullptr; }

        const Seq& operator[](int i) const
        {
            return (*this && 0 <= i && i < n) ? ss[i] : Seq::error_seq();
        }

    private:
        int n;
        Seq *ss = nullptr;

        void release() { delete[] ss; ss = nullptr; }
    };

    auto n = 0, q = 0;
    cin >> n >> q;
    SeqSeq sequences {n};

    for (auto i = 0; i < q; ++i) {
        auto a = -1, b = -1;
        cin >> a >> b;
        cout << sequences[a][b] << '\n';
    }
}
