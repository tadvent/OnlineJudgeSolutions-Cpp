/*
ID: wjl1241
PROG: cowcycle
LANG: C++
*/

#include<cstdio>
#include<algorithm>
using namespace std;

const int maxratio = 50, maxf = 5, maxr = 10;
double ratios[maxratio], bestvar = 1.0e10;
int num, fb, fe, rb, re, nf, nr;
int bestf[maxf], bestr[maxr], testf[maxf], testr[maxr];

double variance(){
    double ave = 0.0, sqr = 0.0;
    for(int i=0; i<num; ++i){
        ave += ratios[i];
        sqr += ratios[i]*ratios[i];
    }
    ave /= (double)num;
    return sqr/double(num) - ave*ave;
}

void dfs_r(int k = 1){
    if(k+1 >= nr){
        int idx = 0;
        for(int i=0; i<nf; ++i)for(int j=nr-1; j>=0; --j)
            ratios[idx++] = double(testf[i]) / double(testr[j]);
        sort(ratios, ratios + idx);
        for(int i=1; i<idx; ++i)ratios[i-1] = ratios[i] - ratios[i-1];
        num = idx-1;
        double tmpvar;
        if((tmpvar = variance()) < bestvar){
            bestvar = tmpvar;
            memcpy(bestf, testf, sizeof(bestf));
            memcpy(bestr, testr, sizeof(bestr));
        }
    } else {
        if(k == 0)testr[k] = rb;
        else testr[k] = testr[k-1] + 1;
        for(; testr[k] <= re+k-nr+1; ++testr[k])
            dfs_r(k+1);
    }
}

void dfs_f(int k = 1){
    if(k+1 >= nf){
        dfs_r();
    } else {
        if(k == 0)testf[k] = fb;
        else testf[k] = testf[k-1] + 1;
        for(; testf[k] <= fe+k-nf+1; ++testf[k])
            dfs_f(k+1);
    }
}

int main(){
    int f1, f2, r1, r2;
    freopen("cowcycle.in", "r", stdin);
    freopen("cowcycle.out", "w", stdout);
    scanf("%d%d%d%d%d%d", &nf, &nr, &f1, &f2, &r1, &r2);
    for(fb = f1; fb <= f2-nf+1; ++fb)
        for(fe = f2; fe >= fb+nf-1; --fe)
            for(rb = r1; rb <= r2-nr+1; ++rb)
                for(re = r2; re >= rb+nr-1; --re)
                    if(fe*re >= 3*fb*rb){
                        testf[0] = fb; testf[nf-1] = fe;
                        testr[0] = rb; testr[nr-1] = re;
                        dfs_f();
                    }
    printf("%d", bestf[0]);
    for(int i=1; i<nf; ++i)printf(" %d", bestf[i]);
    printf("\n%d", bestr[0]);
    for(int i=1; i<nr; ++i)printf(" %d", bestr[i]);
    printf("\n");
    return 0;
}