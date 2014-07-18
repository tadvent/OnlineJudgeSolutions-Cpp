// G++: 0MS  C++: 15MS
#include<cstdio>
#include<cmath>
#include<algorithm>

bool isWan(int n){
    int cnt = 1, root = (int)(sqrt(double(n)) - 1e-6) + 1;
    if(root * root == n) cnt += root;
    for(int i=2; i<root; ++i){
        if(!(n%i)){
            cnt += i + n/i;
        }
    }
    if(cnt == n) return true;
    else return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int wancnt[10001] = {0, 1};
    for(int i=2; i<10001; ++i){
        if(isWan(i))wancnt[i] = wancnt[i-1] + 1;
        else wancnt[i] = wancnt[i-1];
    }

    int n, a, b;
    scanf("%d", &n);
    while(n--){
        scanf("%d%d", &a, &b);
        if(a>b)std::swap(a, b);
        printf("%d\n", wancnt[b] - wancnt[a-1]);
    }
} 
