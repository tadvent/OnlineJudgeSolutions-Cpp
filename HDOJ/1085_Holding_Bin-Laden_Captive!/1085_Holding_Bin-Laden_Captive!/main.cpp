#include<cstdio>

int calc(int n1, int n2, int n5){
    if(n1 == 0)return 1;
    else if(n1 == 1){
        if(n2 == 0)return 2;
        if(n2 == 1)return 4;
    } else if(n1 == 2 && n2 == 0){
        return 3;
    } else if(n1 == 3 && n2 == 0){
        return 4;
    } else {
        return n1 + 2*n2 + 5*n5 + 1;
    }
}

int main(){
    int n1, n2, n5;
    while(scanf("%d%d%d", &n1, &n2, &n5) != EOF && (n1 || n2 || n5)){
        printf("%d\n", calc(n1, n2, n5));
    }
}
