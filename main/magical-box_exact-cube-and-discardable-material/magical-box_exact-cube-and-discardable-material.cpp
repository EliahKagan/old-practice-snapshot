#include <math.h>
#include <stdio.h>

static inline double min(const double x, const double y)
{
    return x < y ? x : y;
}

static inline double volume_from_total_edge_length(const double p)
{
    static const double edge_count = 12.0, cubed = 3.0;
    return pow(p / edge_count, cubed);
}

static inline double volume_from_surface_area(const double s)
{
    static const double face_count = 6.0, sqrt_then_cubed = 1.5;
    return pow(s / face_count, sqrt_then_cubed);
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        double p = 0.0, s = 0.0;
        (void)scanf("%lf%lf", &p, &s);
        
        printf("DEBUG: %.5f %.5f\n", volume_from_total_edge_length(p),
                                     volume_from_surface_area(s));
        
        printf("%.5f\n", min(volume_from_total_edge_length(p),
                             volume_from_surface_area(s)));
    }
}
