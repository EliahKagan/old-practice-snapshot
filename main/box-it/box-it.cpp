#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int BoxesCreated,BoxesDestroyed;

namespace {
    class Box final {
    public:
        Box(int l, int b, int h) : l_{l}, b_{b}, h_{h} { ++BoxesCreated; }
        Box() : Box{0, 0, 0} { }
        Box(const Box& other) : Box{other.l_, other.b_, other.h_} { }
        Box(Box&& other) : Box{other.l_, other.b_, other.h_} { }
        ~Box() { ++BoxesDestroyed; }
        Box& operator=(const Box&) = default;
        Box& operator=(Box&&) = default;

        int getLength() const { return l_; }
        int getBreadth() const { return b_; }
        int getHeight() const { return h_; }

        long long CalculateVolume() const
        {
            return static_cast<long long>(l_) * static_cast<long long>(b_)
                                              * static_cast<long long>(h_);
        }

    private:
        int l_, b_, h_;
    };

    bool operator==(const Box& x, const Box& y)
    {
        return x.getLength() == y.getLength()
            && x.getBreadth() == y.getBreadth()
            && x.getHeight() == y.getHeight();
    }

    bool operator<(const Box& x, const Box& y)
    {
        return x.getLength() < y.getLength()
            || (x.getBreadth() < y.getBreadth()
                    && x.getLength() == y.getLength())
            || (x.getHeight() < y.getHeight()
                    && x.getBreadth() == y.getBreadth()
                    && x.getLength() == y.getLength());
    }

    // WARNING: The Box argument is passed by value to operator<<, which
    //          would be undesirable in a real-world program.
    ostream& operator<<(ostream& out, const Box box)
    {
        return out << box.getLength() << ' ' << box.getBreadth()
                                      << ' ' << box.getHeight();
    }
}

void check2()
{
int n;
cin>>n;
Box temp;
for(int i=0;i<n;i++)
    {
    int type;
    cin>>type;
    if(type ==1)
        {
            cout<<temp<<endl;
        }
        if(type == 2)
        {
            int l,b,h;
            cin>>l>>b>>h;
            Box NewBox(l,b,h);
            temp=NewBox;
            cout<<temp<<endl;
        }
        if(type==3)
        {
            int l,b,h;
            cin>>l>>b>>h;
            Box NewBox(l,b,h);
            if(NewBox<temp)
            {
                cout<<"Lesser"<<endl;
        }
            else
            {
                cout<<"Greater"<<endl;
            }
        }
        if(type==4)
        {
            cout<<temp.CalculateVolume()<<endl;
        }
        if(type==5)
        {
            Box NewBox(temp);
            cout<<NewBox<<endl;
        }

    }
}

int main()
{
    BoxesCreated = 0;
    BoxesDestroyed = 0;
    check2();
    cout<<"Boxes Created : "<<BoxesCreated<<endl<<"Boxes Destroyed : "<<BoxesDestroyed<<endl;
}
