class Solution {
public:
    bool judgeCircle(string moves) {
        auto x = 0, y = 0;

        for (const auto m : moves) {
            switch (m) {
                case 'U':   ++y;    break;
                case 'D':   --y;    break;
                case 'L':   --x;    break;
                case 'R':   ++x;    break;
                default:    throw invalid_argument("invalid move");
            }
        }

        return x == 0 && y == 0;
    }
};
