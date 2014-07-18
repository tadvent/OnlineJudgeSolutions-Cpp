#include<cstdio>

const int digits[10][4] = {
    0, 0, 0, 0,
    1, 0, 0, 0,
    6, 2, 4, 8,
    1, 3, 9, 7,
    6, 4, 0, 0,
    5, 0, 0, 0,
    6, 0, 0, 0,
    1, 7, 9, 3,
    6, 8, 4, 2,
    1, 9, 0 ,0
};
const int d_sz[10] = {1, 1, 4, 4, 2, 1, 1, 4, 4, 2};

inline int rightmost(const int &n){
    int tail = n % 10;
    int idx = n % d_sz[tail];
    return digits[tail][idx];
}

int main(){
    int t, n;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        printf("%d\n", rightmost(n));
    }
}
