#include<cstdlib>
#include<cstdio>
#include<cmath>

int prime[135] = {2,3,5,7};

void init_prime(){
    int idx, num;
    for(idx=4, num=11; idx<135; num+=2){
        int root = (int)sqrt((double)num)+1, i;
        for(i=1; prime[i]<=root; ++i)
            if(num % prime[i] == 0)break;
        if(prime[i] > root)prime[idx++] = num;
    }
}

int yzsum(int n){
    int yinzi[10], yzidx[10]={0}, yz_sz, pri=0;
    for(yz_sz=0; n>1; ++yz_sz){
        while(pri<135 && n % prime[pri] != 0)++pri;
        if(pri == 135){
            yinzi[yz_sz] = n;
            yzidx[yz_sz++] = 1;
            break;
        } else {
            yinzi[yz_sz] = prime[pri];
            while(n % prime[pri] == 0){
                ++yzidx[yz_sz];
                n /= prime[pri];
            }
        }
    }

    int rst = 1;
    for(int i=0; i<yz_sz; ++i){
        int sum = 1, prd = 1;
        for(int j=0; j<yzidx[i]; ++j){
            prd *= yinzi[i];
            sum += prd;
        }
        rst *= sum;
    }
    return rst;
}

int main(){
    init_prime();

    int t, n;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        printf("%d\n", yzsum(n)-n);
    }
}
