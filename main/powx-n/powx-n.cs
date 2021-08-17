public class Solution {
    public double MyPow(double x, int n) {
        double Pow(double b, long e) {
            if (e <= 0L) return e == 0L ? 1.0 : 1.0 / Pow(b, -e);

            var r = Pow(b, e / 2L);
            r *= r;
            if (e % 2 != 0L) r *= b;
            return r;
        }

        return Pow(x, n);
    }
}
