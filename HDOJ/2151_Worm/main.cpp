/*
 * File:   main.cpp
 * Author: tadvent
 *
 * Created on March 18, 2012, 10:14 PM
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

int cnt[105][105];
int start, n, m, tree;

void init(){
    memset(cnt, -1, sizeof(cnt));
}

bool input(){
    if(scanf("%d%d%d%d", &n, &start, &m, &tree) == EOF)
        return false;
    else return true;
}

int cntf(int pos, int step){
    if(cnt[pos][step] >= 0) return cnt[pos][step];
    int dist = abs(pos - start);
    if(dist > step) return cnt[pos][step] = 0;
    if(dist == step) return cnt[pos][step] = 1;
    cnt[pos][step] = 0;
    if(pos - 1 > 0) cnt[pos][step] += cntf(pos-1, step-1);
    if(pos + 1 <= n) cnt[pos][step] += cntf(pos+1, step-1);
    return cnt[pos][step];
}

int calc(){
    int dist = abs(tree - start);
    if(dist > m || (dist - m) % 2 != 0) return 0;
    return cntf(tree, m);
}

/*
 *
 */
int main(int argc, char** argv) {
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif

    while(input()) {
        init();
        printf("%d\n", calc());
    }

    return 0;
}

