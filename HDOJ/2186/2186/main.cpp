#include<cstdio>

int calc(int n){
    int a, b, c;
    a = n/2;
    c = n - a;
    b = c * 2/3;
    c -= b;
    return (a+9)/10 + (b+9)/10 + (c+9)/10;
}

int main(){
    int C;
    scanf("%d", &C);
    while(C--){
        int n;
        scanf("%d", &n);
        printf("%d\n", calc(n));
    }
}
