#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops
namespace {
    struct Workshop {
        int start, finish;
        
        constexpr Workshop(const int start_time, const int duration)
                : start{start_time}, finish{start_time + duration} { }
    };
    
    constexpr bool operator<(const Workshop& lhs, const Workshop& rhs)
    {
        return lhs.finish < rhs.finish;
    }
    
    constexpr bool operator>(const Workshop& lhs, const Workshop& rhs)
    {
        return lhs.finish > rhs.finish;
    }
    
    const vector<Workshop>* initialize(const int* start_times,
                                       const int* durations, int count)
    {
        static vector<Workshop> ws;
        ws.reserve(static_cast<vector<Workshop>::size_type>(count));
        
        while (count-- > 0) ws.emplace_back(*(start_times++), *(durations++));
        
        sort(begin(ws), end(ws));
        return &ws;
    }
    
    int CalculateMaxWorkshops(const vector<Workshop>* const wsp)
    {
        assert(!wsp->empty());
        
        auto max = 0, time = 0;
        
        for (const auto& w : *wsp) {
            if (time <= w.start) {
                time = w.finish;
                ++max;
            }
        }
        
        return max;
    }
    
    using Available_Workshops = const vector<Workshop>;
}
int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
