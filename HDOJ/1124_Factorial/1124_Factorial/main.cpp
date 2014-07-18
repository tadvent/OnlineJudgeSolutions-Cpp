#include<cstdio>

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int t, n, rst;
    scanf("%d", &t);
    while(t--){
        rst = 0;
        scanf("%d", &n);
        while(n){
            n/=5;
            rst+=n;
        }
        printf("%d\n", rst);
    }
}
