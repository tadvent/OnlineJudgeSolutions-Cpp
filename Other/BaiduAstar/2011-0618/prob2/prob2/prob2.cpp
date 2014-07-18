#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int filepos[100005][2] = {0};
int filepos_sz[100005] = {0};
int file_sz = 100004;
int n;

void input(){
    scanf("%d", &n);
    for(int i=1; i<=n; ++i){
        int m;
        scanf("%d", &m);
        while(m--){
            int fnb;
            scanf("%d", &fnb);

            if(filepos_sz[fnb] == 0){
                filepos[fnb][filepos_sz[fnb]++] = i;
            } else if(filepos_sz[fnb] == 1){
                if(filepos[fnb][0] != i)
                    filepos[fnb][filepos_sz[fnb]++] = i;
            } else {
                if(filepos[fnb][1] != i) ++filepos_sz[fnb];
            }
        }
    }
}

int match[10005];
bool visited[10005];

int rdpos, wtpos;
bool init(){
    rdpos = 0;
    wtpos = 0;
    memset(match, -1, sizeof(match));
    for(; rdpos < file_sz; ++rdpos){
        if(filepos_sz[rdpos] > 0 && filepos_sz[rdpos] < 3){
            memcpy(filepos[wtpos], filepos[rdpos], sizeof(filepos[0]));
            filepos_sz[wtpos] = filepos_sz[rdpos];
            ++wtpos;
        }
    }
    file_sz = wtpos;
    if(wtpos == 0)return false;
    return true;
}

bool dfs(int fileid){
    int t, i;
    for(int i=0; i<filepos_sz[fileid]; ++i){
        if(!visited[filepos[fileid][i]]){
            visited[filepos[fileid][i]] = true;
            t = match[filepos[fileid][i]];
            match[filepos[fileid][i]] = fileid;
            if(t == -1 || dfs(t)) return true;
            match[filepos[fileid][i]] = t;
        }
    }
    return false;
}

int maxmatch(){
    int sum = 0;
    for(int i=0; i<wtpos; ++i){
        memset(visited, 0, sizeof(visited));
        if(dfs(i)) ++sum;
    }
    return sum;
}

void reduce(){
    for(int i=1; i<=n; ++i){
        filepos[match[i]][filepos_sz[match[i]]++] = i;
    }
}

int main(){
#ifdef LOCAL
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    input();

    int ans = 0;
    while(init()){
        maxmatch();
        ++ans;
        reduce();
    }
    printf("%d\n", ans);

    return 0;
}
