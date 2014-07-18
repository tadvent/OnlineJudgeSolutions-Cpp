#include<cstdio>

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int np[3] = {1, 1, 1}, nq[3];
    int *p = np, *q = nq, *t, n;
    int count[10000] = {1, 2, 4};
    for(n=3; n<10000; ++n){
        q[0] = (p[0] + p[2]) % 9997;
        q[1] = p[0] % 9997;
        q[2] = (p[1] + p[2]) % 9997;
        count[n] = (q[0] + q[1] + (q[2]<<1)) % 9997;
        t = p; p = q; q = t;
    }

    while(scanf("%d", &n) != EOF && n > 0)
        printf("%d\n", count[n]);
}
