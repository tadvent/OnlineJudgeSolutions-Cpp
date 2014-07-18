#include<cstdio>

int main(){
    int n, m, p;
    while(scanf("%d", &n) != EOF){
        m = 0; p = 1; n = 2*n + 1;
        do{
            ++m;
            p = (p<<1) % n;
        }while(p != 1);
        printf("%d\n", m);
    }
}
