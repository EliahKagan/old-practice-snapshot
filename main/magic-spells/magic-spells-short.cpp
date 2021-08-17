#include <iostream>
#include <string> // omitted in original boilerplate code
#include <vector>
using namespace std;

class Spell {
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell {
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell {
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell {
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
};
string SpellJournal::journal = "";

void counterspell(Spell *spell) {
    // Finds the length of the longest common subsequence of s and t, by
    // an iterative algorithm similar to "Iterative LCS" as described in
    // https://www.ics.uci.edu/~eppstein/161/960229.html (Eppstein 1996).
    const auto lcslen = [](const string& s, const string& t) {
        const auto max = [](const int m, const int n) {
            return m > n ? m : n;
        };

        const vector<int> blank_row (t.size() + 1u, 0);
        vector<vector<int>> a (s.size() + 1u, blank_row);

        for (auto i = s.size(); i-- != 0u; ) {
            for (auto j = t.size(); j-- != 0u; ) {
                a[i][j] = (s[i] == t[j] ? 1 + a[i + 1u][j + 1u]
                           : max(a[i + 1u][j], a[i][j + 1u]));
            }
        }

        return a[0u][0u];
    };

    if (const auto fire = dynamic_cast<Fireball*>(spell))
        fire->revealFirepower();
    else if (const auto frost = dynamic_cast<Frostbite*>(spell))
        frost->revealFrostpower();
    else if (const auto thunder = dynamic_cast<Thunderstorm*>(spell))
        thunder->revealThunderpower();
    else if (const auto water = dynamic_cast<Waterbolt*>(spell))
        water->revealWaterpower();
    else {
        cout << lcslen(SpellJournal::journal, spell->revealScrollName())
             << endl;
    }
}

class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            }
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}
