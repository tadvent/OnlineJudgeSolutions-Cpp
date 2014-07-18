/***************************************************************/
/* first solution, not complete... too complicated
// 思想是找出满足条件的所有数字组合，然后再计算排列数。。。

#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;

const int sq[10] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};
const int MaxPrimeNum = 1000;
bool isPrime[MaxPrimeNum];
void calcPrime(){
    fill(isPrime, isPrime+MaxPrimeNum, true);
    isPrime[0] = isPrime[1] = false;
    int lim = (int)sqrt((double)MaxPrimeNum);
    for(int i = 2; i <= lim; ++i){
        if(!isPrime[i]) continue;
        for(int n = i+i; n < MaxPrimeNum; n += i) isPrime[n] = false;
    }
}

int digits[10];
inline int d2i(int d){
    return 10-d;
}

int s;
void fill_digit(int st, int dig_left, int dsum, int ssum){
    if(dig_left == 0){
        if(isPrime[dsum] && isPrime[ssum]) ++s; return;
    }
    for(int n = st; n < 10; ++n){
        digits[d2i(dig_left)] = n;
        fill_digit(n, dig_left-1, dsum+n, ssum+sq[n]);
    }
}


int main(){
    calcPrime();
    s = 0;
    fill_digit(0, 9, 0, 0);
    fill_digit(1, 9, 1, 1);
    printf("Count: %d\n", s);
    system("pause");
}

/**********************************************************/
//* Another solution
// 思路简洁明快，dp思想用来剪枝优化

#include<Windows.h>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cassert>
#include<ctime>
#include<algorithm>
using namespace std;

const int sq[10] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};
const int MaxPrimeNum = 1000;
bool isPrime[MaxPrimeNum];
void calcPrime(){
    fill(isPrime, isPrime+MaxPrimeNum, true);
    isPrime[0] = isPrime[1] = false;
    int lim = (int)sqrt((double)MaxPrimeNum);
    for(int i = 2; i <= lim; ++i){
        if(!isPrime[i]) continue;
        for(int n = i+i; n < MaxPrimeNum; n += i) isPrime[n] = false;
    }
}

int dp[10][85][735];
int luckyDP(int dig_left, int dsum, int ssum){
    if(dp[dig_left][dsum][ssum] >= 0) return dp[dig_left][dsum][ssum];
    if(dig_left == 0){
        return dp[0][dsum][ssum] = ((isPrime[dsum] && isPrime[ssum])? 1:0);
    }
    int s = 0;
    for(int n=0; n<10; ++n){
        s += luckyDP(dig_left-1, dsum+n, ssum+sq[n]);
    }
    return dp[dig_left][dsum][ssum] = s;
}

int xs[10], ys[10];
void i2s(int x, int *xs, int len){
    memset(xs, 0, len*sizeof(int));
    for(int i=len-1; i>=0; --i){
        if(x == 0) break;
        xs[i] = x % 10;
        x /= 10;
    }
}

int edgeCnt(int idx, int dsum, int ssum, int rng){  // rng: 0: ll~ul, 1: ll~9, -1: 0~ul
    int d, s = 0;
    if(idx == 10) return luckyDP(0, dsum, ssum);
    if(rng == 0){
        d = xs[idx];
        if(xs[idx] == ys[idx]){
            return edgeCnt(idx+1, dsum+d, ssum+sq[d], 0);
        }
        s = edgeCnt(idx+1, dsum+d, ssum+sq[d], 1);
        while(++d < ys[idx]){
            s += luckyDP(9-idx, dsum+d, ssum+sq[d]);
        }
        s += edgeCnt(idx+1, dsum+d, ssum+sq[d], -1);
        return s;
    } else if(rng == 1){
        d = xs[idx];
        s = edgeCnt(idx+1, dsum+d, ssum+sq[d], 1);
        while(++d < 10){
            s += luckyDP(9-idx, dsum+d, ssum+sq[d]);
        }
        return s;
    } else if(rng == -1){
        for(d=0; d<ys[idx]; ++d){
            s += luckyDP(9-idx, dsum+d, ssum+sq[d]);
        }
        s += edgeCnt(idx+1, dsum+d, ssum+sq[d], -1);
        return s;
    }
    return -1;
}

int lucky(int x, int y){
    assert(x <= y);
    calcPrime();
    memset(dp, -1, sizeof(dp));
    i2s(x, xs, 10);
    i2s(y, ys, 10);
    return edgeCnt(0, 0, 0, 0);
}

int rawlucky(int x, int y){
    int s = 0;
    for(int n = x; n <= y; ++n){
        int ns = 0, sqs = 0, d, num = n;
        while(num > 0){
            d = num % 10;
            ns += d;
            sqs += sq[d];
            num /= 10;
        }
        if(isPrime[ns] && isPrime[sqs]) ++s;
    }
    return s;
}

int main(){
    LARGE_INTEGER liFreq;
    LARGE_INTEGER liStartTime, liEndTime;
    LONGLONG llLastTime;
    QueryPerformanceFrequency(&liFreq);

    for(;;){
        int x, y;
        //clock_t st, fn;
        scanf("%d%d", &x, &y);
        if(x == 0 && y == 0) break;
        if(x <= 0 || y <= 0 || x > y){
            printf("Input Error...\n");
            continue;
        }
        //st = clock();
        QueryPerformanceCounter(&liStartTime);
        printf("%d\n", lucky(x, y));
        QueryPerformanceCounter(&liEndTime);
        //fn = clock();
        llLastTime = 1000000 * (liEndTime.QuadPart - liStartTime.QuadPart) / liFreq.QuadPart;
        //printf("Time: %.3f secs\n\n", (fn-st)/CLOCKS_PER_SEC);
        printf("Time: %ld us\n\n", llLastTime);
        //printf("ST Ans: %d\n\n", rawlucky(x, y));
    }
}

/***************************************************************/
