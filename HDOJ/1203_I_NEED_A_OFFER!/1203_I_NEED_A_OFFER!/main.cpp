#include<cstdio>
#include<algorithm>
const int maxn = 10001;

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF && (m||n)){
        float buf[maxn], t;
        std::fill_n(buf, n+1, 1.0f);
        while(m--){
            int c, i;
            float p;
            scanf("%d%f", &c, &p);
            p = 1.0f - p;
            for(i=n; i>=c; --i)if(buf[i]>(t=buf[i-c]*p))buf[i]=t;
        }
        printf("%.1f%%\n", (1.0 - buf[n])*100.0);
    }
}
