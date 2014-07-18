#include<cstdio>

int main(){
    int n, prz;
    double t, pp, expect;
    while(scanf("%d%lf", &n, &t) != EOF && (n || t != 0.0)){
        expect = prz = 1<<n;
        while(n--){
            prz >>= 1;
            pp = prz/expect;
            if(pp > t){
                expect = (prz*(pp-t) + 0.5*expect*(1.0-pp*pp)) / (1.0-t);
            } else {
                expect = 0.5*expect*(1.0-t*t)/(1.0-t);
            }
        }
        printf("%.3f\n", expect);
    }
}

/*
均匀分布，概率密度 1/(1-t)
   prz[] = 1, 2, 4, 8, ..., 1<<n
expect[i] = $[t, 1.0] 1/(1-t) max{prz[i], p*exp[i-1]}dp
          = (prz[i]*(pp-t) + expect[i-1]*0.5*(1-pp*pp)) / (1-t)
      pp = prz[i] / expect[i-1];
需要 概率论 及 微积分 知识
*/
