#include<cstdio>

inline bool leap(int year){
    return (year%4==0 && year%100!=0 || year%400==0);
}

int nth_leap(int year, int nth){
    while(!leap(year))++year;
    while(--nth != 0){
        for(year += 4; !leap(year); year += 4);
    }
    return year;
}

int main(){
    int T, Y, N;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &Y, &N);
        printf("%d\n", nth_leap(Y, N));
    }
}
