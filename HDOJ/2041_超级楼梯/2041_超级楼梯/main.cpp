#include<cstdio>
int arr[41] = {0,1};
void init(){
    for(int i=2; i<sizeof(arr)/sizeof(arr[0]); ++i)
        arr[i] = arr[i-1] + arr[i-2];
}
int main(){
    int n, m;
    init();
    scanf("%d", &n);
    while(n--){
        scanf("%d", &m);
        printf("%d\n", arr[m]);
    }
}