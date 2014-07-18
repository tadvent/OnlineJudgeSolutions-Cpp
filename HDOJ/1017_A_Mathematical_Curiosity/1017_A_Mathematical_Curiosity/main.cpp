#include<iostream>
using namespace std;

inline bool VaPair(int a, int b, int m){
    return (a*a + b*b + m)%(a*b) == 0;
}
int VaCount(int n, int m){
    int cnt = 0;
    for(int i=1; i<n-1; ++i)
        for(int j=i+1; j<n; ++j)
            if(VaPair(i,j,m))++cnt;
    return cnt;
}

int main(){
#ifndef ONLINE_JUDGE
   freopen("i.txt", "r", stdin);
   freopen("o.txt", "w", stdout);
#endif
    int t, m, n;
    bool first = true;
    cin>>t;
    while(t--){
        if(first)first=false;
        else cout.put('\n');

        int idx = 1;
        while(cin>>n>>m && (m||n)){
            cout<< "Case " << idx++ << ": " << VaCount(n, m) << '\n';
        }
    }
}
