#include<cstdio>

int group[1001];

int grpid(int i){
    while(i != group[i])i = group[i];
    return i;
}

void setid(int grp, int id){
    int fwd = group[grp];
    while(fwd != id){
        group[grp] = id;
        grp = fwd;
        fwd = group[grp];
    }
}

bool uni(int u, int v){
    int idu = grpid(u);
    int idv = grpid(v);
    if(idu == idv)return false;

    int m = idu<idv? idu:idv;
    setid(idu, m);
    setid(idv, m);
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int T, nTable, m, u, v;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &nTable, &m);
        for(int i=0; i<=nTable; ++i)group[i] = i;
        while(m--){
            scanf("%d%d", &u, &v);
            if(uni(u, v))--nTable;
        }
        printf("%d\n", nTable);
    }
}
