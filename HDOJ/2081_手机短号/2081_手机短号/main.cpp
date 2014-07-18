#include<cstdio>
int main(){
    int n;
    char a[12];
    scanf("%d", &n);
    while(n--){
        scanf("%s", a);
        printf("6%s\n", a+6);
    }
}