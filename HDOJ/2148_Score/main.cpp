/*
 * File:   main.cpp
 * Author: tadvent
 *
 * Created on March 18, 2012, 9:49 PM
 */

#include <cstdlib>
#include <cstdio>

using namespace std;

int score[1005];
int n, k;

void input(){
    scanf("%d%d", &n, &k);
    for(int i=0; i<n; ++i){
        scanf("%d", &score[i]);
    }
}

int calc(){
    int val = score[k-1];
    int cnt = 0;
    for(int i=0; i<n; ++i)
        if(score[i] > val) ++cnt;
    return cnt;
}
/*
 */
int main(int argc, char** argv) {
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int c;
    scanf("%d", &c);
    while(c--){
        input();
        printf("%d\n", calc());
    }

    return 0;
}

