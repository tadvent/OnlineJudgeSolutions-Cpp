/*
 * File:   main.cpp
 * Author: tadvent
 *
 * Created on June 13, 2011, 4:39 PM
 */

// Wrong Answer !!
/*
#include <cstdlib>
#include <iostream>
#include <set>
#include <cstdio>
#include <cstring>

using namespace std;

int n, m;
set<int> row[105];
set<int> col[105];
int cnt[205];

bool input(){
    if(!(cin >> n >> m) || n == 0) return false;
    memset(cnt, 0, sizeof(cnt));
    for(int i=0; i<n; ++i)for(int j=0; j<m; ++j){
        int d;
        cin >> d;
        if(d == 1){
            row[i].insert(j);
            ++cnt[i];
            col[j].insert(i);
            ++cnt[n+j];
        }
    }
    return true;
}

bool reduce(){
    int max = 0, idx = 0;
    for(int i=0; i<m+n; ++i){
        if(cnt[i] > max){
            max = cnt[i];
            idx = i;
        }
    }
    if(max == 0) return false;
    cnt[idx] = 0;
    if(idx < n){
        for(set<int>::const_iterator i = row[idx].begin();
                i != row[idx].end(); ++i){
            col[*i].erase(idx);
            --cnt[n+(*i)];
        }
    } else {
        for(set<int>::const_iterator i = col[idx-n].begin();
                i != col[idx-n].end(); ++i){
            row[*i].erase(idx-n);
            --cnt[*i];
        }
    }
    return true;
}

int calc(){
    int count = 0;
    while(reduce()) ++count;
    return count;
}

int main(int argc, char** argv) {
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input()) cout << calc() << '\n';

    return 0;
}
/* */

#include<cstdio>
#include<cstring>

const int M = 100;
const int N = 100;

int map[M][N];  // edge link
int sz[M];      // size of map[i]
int m, n;

bool input(){
    if(scanf("%d%d", &m, &n) == EOF || m == 0 || n == 0){
        return false;
    }
    memset(map, 0, sizeof(map));
    memset(sz, 0, sizeof(sz));
    int tmp;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &tmp);
            if(tmp){
                map[i][sz[i]++] = j;
            }
        }
    }
    return true;
}

bool vis[N];    // visited
int  mat[N];    // mat[i] (0-M) link to node i (0-N)

bool dfs(int u){
    for (int i = 0; i < sz[u]; i++) {
        int v = map[u][i];
        if(!vis[v]){
            vis[v] = true;
            int t = mat[v];
            mat[v] = u;
            if(t == -1 || dfs(t))
                return true;
            mat[v] = t;
        }
    }
    return false;
}

int calc(){
    int ans = 0;
    memset(mat, -1, sizeof(mat));
    for (int i = 0; i < m; i++) {
        memset(vis, 0, sizeof(vis));
        if(dfs(i)) ++ans;
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input())
        printf("%d\n", calc());
    return 0;
}
