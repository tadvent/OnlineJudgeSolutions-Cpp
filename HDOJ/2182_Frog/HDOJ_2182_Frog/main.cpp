#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100;

int nInsectsAt[maxn];
int dp[maxn+maxn][maxn];

void calc(){
    int N, A, B, K;
    scanf("%d%d%d%d", &N, &A, &B, &K);
    for(int i=0; i<N; ++i)scanf("%d", nInsectsAt+i);

    memset(dp, 0, sizeof(dp));
    for(int p=N-1; p>=0; --p){
        dp[p][0] = nInsectsAt[p];
        for(int r=1; r<=K; ++r){
            int m = 0;
            for(int i=A; i<=B; ++i){
                m = max(m, dp[p+i][r-1]);
            }
            dp[p][r] = nInsectsAt[p] + m;
        }
    }
    printf("%d\n", dp[0][K]);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int nTest;
    scanf("%d", &nTest);
    while(nTest--)calc();
}
