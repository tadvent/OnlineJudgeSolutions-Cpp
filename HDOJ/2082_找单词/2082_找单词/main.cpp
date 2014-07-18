#include<iostream>
#include<algorithm>
using namespace std;
long long dp[27][51];
int num[27];

long long calc(){
    dp[0][0] = 1;
    fill_n(dp[0] + 1, 50, 0);
    for(int i=1; i<27; ++i){
        dp[i][0] = 1;
        for(int j=1; j<51; ++j){
            dp[i][j] = dp[i-1][j];
            for(int cnt=1; cnt<=num[i] && j-cnt*i>=0; ++cnt)
                dp[i][j] += dp[i-1][j-cnt*i];
        }
    }
    long long sum = 0;
    for(int i=1; i<51; ++i)sum += dp[26][i];
    return sum;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        for(int i=1; i<=26; ++i)
            cin>>num[i];
        cout<<calc()<<'\n';
    }
}
