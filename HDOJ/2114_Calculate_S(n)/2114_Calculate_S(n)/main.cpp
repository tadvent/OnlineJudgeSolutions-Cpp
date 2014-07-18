#include<cstdio>
#include<cstdlib>
using namespace std;

int sum[10001] = {0};

int main(){
    int n;
    for(int i=1; i<10001; ++i){
        sum[i] = (sum[i-1] + ((i*i)%10000)*i) % 10000;
    }
    while(scanf("%d", &n) != EOF){
        div_t t = div(n, 10000);
        printf("%04d\n", (t.quot * sum[10000] + sum[t.rem])%10000);
    }
}
