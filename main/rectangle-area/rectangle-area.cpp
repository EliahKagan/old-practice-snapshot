#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

namespace {
    class Rectangle {
    public:
        void Display() { cout << width << ' ' << height << '\n'; }

    protected:
        int width, height;
    };

    class RectangleArea final : public Rectangle {
    public:
        void Input() { cin >> width >> height; }
        void Display() { cout << width * height << '\n'; }
    };
}

int main() {
      RectangleArea r_area;
      r_area.Input();
        Rectangle *r;
        r=&r_area;
        r->Display();
        r_area.Display();
    return 0;
}
