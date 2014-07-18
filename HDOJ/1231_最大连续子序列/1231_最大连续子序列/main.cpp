#include<cstdio>

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int K;
    while(scanf("%d", &K) != EOF && K>0){
        int maxsum = -1, maxbeg, maxend, tsum, tbeg, tval;
        int lastsum = 0, lastbeg, lastval;
        scanf("%d", &maxbeg);
        lastbeg = lastval = lastsum = maxbeg;
        if(lastsum > maxsum) maxsum = maxbeg = maxend = lastsum;
        while(--K){
            scanf("%d", &tval);
            if(lastsum >= 0){
                tsum = tval + lastsum;
                tbeg = lastbeg;
            } else tsum = tbeg = tval;
            if(tsum > maxsum){
                maxsum = tsum;
                maxbeg = tbeg;
                maxend = tval;
            }
            lastsum = tsum;
            lastbeg = tbeg;
            lastval = tval;
        }
        if(maxsum < 0){
            maxsum = 0;
            maxend = lastval;
        }
        printf("%d %d %d\n", maxsum, maxbeg, maxend);
    }
}
