#include<stdio.h>

int month[12] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int n, m1, d1, m2, d2;
    long rst;
    for(n=2; n<12; ++n)month[n]+=month[n-1];
    scanf("%d", &n);
    while(n--){
        scanf("%d%d%ld%d%d", &m1, &d1, &rst, &m2, &d2);
        printf("%ld\n", rst<<((month[m2-1]+d2)-(month[m1-1]+d1)));
    }
}
