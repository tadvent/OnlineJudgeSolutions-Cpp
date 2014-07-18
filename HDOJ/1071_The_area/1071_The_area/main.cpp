#include<cstdio>
#include<cmath>

double p1x, p1y, p2x, p2y, p3x, p3y;
inline double area(){
    double s1 = (p1y - (p2y+p3y)/2) * (p3x - p2x);
    double dx3 = p3x - p1x, dx2 = p2x - p1x;
    double s2 = (p1y - p2y)/(dx2*dx2) * (dx3*dx3*dx3 - dx2*dx2*dx2) / 3;
    return s1 - s2;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%lf%lf%lf%lf%lf%lf", &p1x, &p1y, &p2x, &p2y, &p3x, &p3y);
        printf("%.2f\n", abs(area()));
    }
}
