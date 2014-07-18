#include<cstdio>

int main(){
    int T, N;
    scanf("%d", &T);
    while(T--){
        int Sum = 0, Max = 0, Num;
        scanf("%d", &N);
        while(N--){
            scanf("%d", &Num);
            if(Max < Num) Max = Num;
            Sum += Num;
            if(Sum >= 1999999){
                scanf("%*[^\n]%*c");
                break;
            }
        }
        if(Sum >= 2*Max - 1)puts("Yes");
        else puts("No");
    }
}
