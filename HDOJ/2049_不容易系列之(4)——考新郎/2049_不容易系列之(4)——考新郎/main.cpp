#include<iostream>
using namespace std;
const int maxn = 20;
long long combi[maxn+1][maxn+1];
long long dp[maxn+1] = {0, 0, 1};

int main(){
    for(int i=0; i<=maxn; ++i){
        combi[i][0] = combi[i][i] = 1;
        for(int j=1; j<i; ++j)
            combi[i][j] = combi[i-1][j-1] + combi[i-1][j];
    }
    for(int i=3; i<=maxn; ++i)
        dp[i] = (i-1) * (dp[i-1] + dp[i-2]);

    int C, N, M;
    cin>>C;
    while(C--){
        cin>>N>>M;
        cout<<combi[N][M]*dp[M]<<'\n';
    }
    cout.flush();
}
