// 46MS	264K	1174 B
///*
#include<cstdio>
#include<cstring>
#include<algorithm>

char StuId[1000][21];
int  StuScore[1000], ProbVl[10];
int nStu, nProb, GradeLine, nAbvLine;

bool input(){
    if(scanf("%d%d%d", &nStu, &nProb, &GradeLine) == EOF
        || !nStu)return false;
    for(int i=0; i<nProb; ++i)scanf("%d", ProbVl+i);
    nAbvLine = 0;
    while(nStu--){
        int nSov, scsum = 0, ProbId;
        scanf("%s%d", StuId[nAbvLine], &nSov);
        while(nSov--){
            scanf("%d", &ProbId);
            scsum += ProbVl[ProbId-1];
        }
        if(scsum >= GradeLine)
            StuScore[nAbvLine++] = scsum;
    }
    return true;
}

struct idx_less{
    bool operator()(int i, int j)const{
        return (StuScore[i] > StuScore[j] ||
            StuScore[i] == StuScore[j] && strcmp(StuId[i], StuId[j]) < 0);
    }
};

void output(){
    int idx[1000], *ed, *it;
    ed = idx + nAbvLine;
    for(int i=0; i<nAbvLine; ++i)idx[i]=i;
    std::sort(idx, ed, idx_less());
    printf("%d\n", nAbvLine);
    for(it = idx; it < ed; ++it)
        printf("%s %d\n", StuId[*it], StuScore[*it]);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input())output();
}
//*/

///////////////////////////////////////////////////////////
// 46MS	268K 1208B
/*
#include<cstdio>
#include<cstring>
#include<algorithm>

struct Stu{
    char id[21];
    int sc;
} stu[1000];
struct pStu_less{
    bool operator()(const Stu *const p1, const Stu *const p2)const{
        return (p1->sc > p2->sc ||
            p1->sc == p2->sc && strcmp(p1->id, p2->id) < 0);
    }
};
int ProbVl[10], nAbvLine;

bool input(){
    int nStu, nProb, GradeLine;
    if(scanf("%d%d%d", &nStu, &nProb, &GradeLine) == EOF
        || !nStu)return false;
    for(int i=0; i<nProb; ++i)scanf("%d", ProbVl+i);
    nAbvLine = 0;
    while(nStu--){
        int nSov, scsum = 0, ProbId;
        scanf("%s%d", stu[nAbvLine].id, &nSov);
        while(nSov--){
            scanf("%d", &ProbId);
            scsum += ProbVl[ProbId-1];
        }
        if(scsum >= GradeLine)
            stu[nAbvLine++].sc = scsum;
    }
    return true;
}

void output(){
    Stu *pstu[1000], **it, **ed;
    ed = pstu + nAbvLine;
    for(int i=0; i<nAbvLine; ++i)pstu[i] = stu+i;
    std::sort(pstu, ed, pStu_less());
    printf("%d\n", nAbvLine);
    for(it = pstu; it < ed; ++it)
        printf("%s %d\n", (*it)->id, (*it)->sc);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input())output();
}
*/
