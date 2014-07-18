#include<iostream>
using namespace std;
int dp[121][121];
int main(){
    for(int i=0; i<121; ++i){
        dp[0][i] = 1;
        dp[i][0] = 0;
    }
    for(int i=1; i<121; ++i)for(int j=1; j<121; ++j){
        if(j>i){dp[i][j]=dp[i][i];continue;}
        dp[i][j]=dp[i][j-1]+dp[i-j][j];
    }
    int n;
    while(cin>>n)
        cout<<dp[n][n]<<'\n';
}
