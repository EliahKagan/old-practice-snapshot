#include <iostream>
#include <sstream>
#include <string>
using namespace std;

namespace {
    class Student {
    public:
        void set_age(int age) { this->age = age; }
        void set_standard(int standard) { this->standard = standard; }
        void set_first_name(const string& first_name) { this->first_name = first_name; }
        void set_last_name(const string& last_name) { this->last_name = last_name; }

        int get_age() const { return age; }
        int get_standard() const { return standard; }
        const string& get_first_name() const { return first_name; }
        const string& get_last_name() const { return last_name; }

        string to_string();

    private:
        int age {0}, standard {0};
        string first_name, last_name;
    };

    string Student::to_string()
    {
        ostringstream out;
        out << age << ',' << first_name << ',' << last_name << ',' << standard;
        return out.str();
    }
}

int main() {
    int age, standard;
    string first_name, last_name;
    
    cin >> age >> first_name >> last_name >> standard;
    
    Student st;
    st.set_age(age);
    st.set_standard(standard);
    st.set_first_name(first_name);
    st.set_last_name(last_name);
    
    cout << st.get_age() << "\n";
    cout << st.get_last_name() << ", " << st.get_first_name() << "\n";
    cout << st.get_standard() << "\n";
    cout << "\n";
    cout << st.to_string();
    
    return 0;
}
