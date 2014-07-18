#include<cstdio>
#include<cmath>

int leftmost(int n){
    double tmp;
    return (int)pow(10.0, modf(log10(double(n))*n, &tmp));
}

int main(){
    int T,n;
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        printf("%d\n", leftmost(n));
    }
}
