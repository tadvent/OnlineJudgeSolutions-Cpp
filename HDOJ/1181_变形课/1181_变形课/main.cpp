#include<cstdio>
#include<list>
using namespace std;

list<int> graph[26];

bool input(){
    for(int i=0; i<26; ++i)
        graph[i].clear();
    int u, v;
    while((u = getchar()) != '0'){
        if(u == EOF)return false;
        char ch;
        while((ch = getchar()) != '\n')
            v = ch;
        graph[u-'a'].push_back(v-'a');
    }
    getchar();
    return true;
}

int visited[26];
bool canChange(int from, int to){ // 0 ~ 25
    visited[from] = 1;
    if(from == to)return true;
    for(list<int>::iterator it = graph[from].begin();
        it != graph[from].end(); ++it){
            if(!visited[*it] && canChange(*it, to))return true;
    }
    return false;
}

inline bool BtoM(){
    memset(visited, 0, sizeof(visited));
    return canChange('b'-'a', 'm'-'a');
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input()){
        if(BtoM())printf("Yes.\n");
        else printf("No.\n");
    }
}
