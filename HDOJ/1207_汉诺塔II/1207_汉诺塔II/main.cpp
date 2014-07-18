#include<cstdio>
#include<climits>
typedef unsigned long long ull;

int main(){
    ull cnt3[65], cnt4[65]={0,1,3,5};
    for(ull s=1, i=0; i<65; ++i, s<<=1)cnt3[i] = s-1;
    for(int i=4; i<65; ++i){
        ull m = ULONG_MAX;
        for(int j=1; j<i-1; ++j){
            ull move = 2*(cnt4[j] + cnt3[i-1-j]) + 1;
            if(move < m)m = move;
        }
        cnt4[i] = m;
    }

    int n;
    while(scanf("%d", &n) != EOF)
        printf("%I64u\n", cnt4[n]);
}
