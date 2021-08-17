#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define XSTR(a) STR(a)
#define STR(a) #a

#define NAME_MAXLEN 100

namespace {
    class Person {
    public:
        virtual ~Person() = default;

        virtual void getdata() = 0;
        virtual void putdata() = 0;

    protected:
        int id;

    private:
        static constexpr size_t name_buflen = NAME_MAXLEN + 1;

        // using vector<char> for name (why didn't we #include <string>?)
        vector<char> name = vector<char>(name_buflen);
        int age;
    };

    void Person::getdata()
    {
        scanf(" %" XSTR(NAME_MAXLEN) "s %d", name.data(), &age);
    }

    void Person::putdata()
    {
        printf("%s %d", name.data(), age);
    }

    class Professor final : public Person {
    public:
        Professor() { id = ++n; }
        virtual void getdata() final override;
        virtual void putdata() final override;

    private:
        static int n;

        int publications = 0;
    };

    void Professor::getdata()
    {
        Person::getdata();
        scanf(" %d", &publications);
    }

    void Professor::putdata()
    {
        Person::putdata();
        printf(" %d %d\n", publications, id);
    }

    int Professor::n = 0;

    class Student final : public Person {
    public:
        Student() { id = ++n; }
        virtual void getdata() final override;
        virtual void putdata() final override;

    private:
        static int n;

        vector<int> marks = vector<int>(6);
    };

    void Student::getdata()
    {
        Person::getdata();
        for (auto& mark : marks) scanf(" %d", &mark);
    }

    void Student::putdata()
    {
        Person::putdata();

        auto sum = 0; // why didn't we #include <numeric> (for std::accumulate)
        for (const auto mark : marks) sum += mark;

        printf(" %d %d\n", sum, id);
    }

    int Student::n = 0;
}


// code from HackerRank (not to be modified while completing this exercise)
int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}
