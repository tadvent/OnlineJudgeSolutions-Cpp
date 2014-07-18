#include<cstdio>

inline int calc(int n, int m){
    int upper = (m-n)/4, lower = 0;
    if(m > 2*n){
        lower = m - 2*n;
        if(lower % 3 == 0)lower /= 3;
        else lower = lower/3 + 1;
    }
    return upper - lower + 1;
}

int main(){
    int t, n, m;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &n, &m);
        printf("%d\n", calc(n, m));
    }
}
