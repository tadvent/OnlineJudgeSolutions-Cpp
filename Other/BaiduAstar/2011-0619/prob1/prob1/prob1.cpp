#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

int h[100005];
int dp[100005];
int n;

int main(){
#ifdef LOCAL
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for(int i=0; i<=n; ++i) scanf("%d", h + i);

    dp[n] = 0;
    for(int idx = n-1; idx >= 0; --idx){
        int mm = (int)1e9+1;
        int hh = 0;
        int ed = min(idx + h[idx], n);
        for(int i=idx+1; i<=ed; ++i){
            if(hh < h[idx] || hh < h[i]){
                int t = (h[i] > h[idx])? h[i]-h[idx]: 0;
                if(t + dp[i] < mm) mm = t + dp[i];
            }
            if(h[i] > hh) hh = h[i];
        }
        dp[idx] = mm;
    }

    printf("%d\n", dp[0]);
}
