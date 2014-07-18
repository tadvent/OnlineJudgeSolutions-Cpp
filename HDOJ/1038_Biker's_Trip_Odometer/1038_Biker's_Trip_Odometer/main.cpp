#include<cstdio>

const double pi = 3.1415927;

int main(){
    int r, idx = 0;
    double d, t;
    while(scanf("%lf%d%lf", &d, &r, &t) != EOF && r){
        double dist = pi * d * r / (12 * 5280);
        printf("Trip #%d: %.2f %.2f\n", ++idx, dist, dist*3600.0/t);
    }
}
