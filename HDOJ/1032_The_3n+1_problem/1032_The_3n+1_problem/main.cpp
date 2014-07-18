#include<cstdio>
using namespace std;
const unsigned long bufsize = 16*1024;
unsigned long loop[bufsize] = {0, 1, 2};
unsigned long cycle(unsigned long num){
    if(num < bufsize){
        if(loop[num])return loop[num];
        return loop[num] = 1 + cycle(num%2? 3*num+1 : num/2);
    }
    else return 1 + cycle(num%2? 3*num+1 : num/2);
}
int main(){
    int m, n;
    while(scanf("%d%d", &m, &n) != EOF){
        printf("%d %d ", m, n);
        if(m>n){int t=m;m=n;n=t;}
        unsigned long maxlen = 0;
        for(int i=m; i<=n; ++i){
            unsigned long len = cycle(i);
            if(len > maxlen)maxlen = len;
        }
        printf("%lu\n", maxlen);
    }
}
