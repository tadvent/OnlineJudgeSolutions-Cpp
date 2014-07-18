#include<iostream>
using namespace std;

long long wrong[13] = {1, 0};
long long comb[26][26] = {0};
long long ans[26] = {0};

void init(){
    for(int i=2; i<13; ++i)wrong[i] = (i-1)*(wrong[i-1]+wrong[i-2]);
    for(int i=1; i<26; ++i){
        comb[i][0] = comb[i][i] = 1;
        for(int j=1; j<i; ++j)
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
    }
    for(int i=1; i<26; ++i){
        int half = i/2;
        long long sum = 0;
        for(int j=0; j<=half; ++j)
            sum += comb[i][j]*wrong[j];
        ans[i] = sum;
    }
}

int main(){
    int n;
    init();
    while(cin>>n && n>0){
        cout<<ans[n]<<'\n';
    }
}
