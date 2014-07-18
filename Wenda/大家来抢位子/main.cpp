#include<cstdio>
#include<vector>
using namespace std;

int n, maxScope;
vector<int[2]> scope;

int a, b;
vector<int> com;

bool input(){
    if(scanf("%d", &n) != 1) return false;
    scope.resize(n);
    for(int i=0; i<n; ++i){
        if(scanf("%d%d", &scope[i][0], &scope[i][1]) != 2)
            return false;
        if(scope[i][1] > maxScope) maxScope = scope[i][1];
    }
    return true;
}

bool tryStu(int stu){
    if(stu >= n) return true;
    int ns = scope[stu][0] - a;
    int nt = scope[stu][1] + b;
    for(int i=(ns < 0? 0:ns); i<=nt; ++i){
        if(com[i] == 1) continue;
        com[i] = 1;
        if(tryStu(stu+1)) return true;
        com[i] = 0;
    }
    return false;
}

bool tryK(int k){
    for(a = 0; a <= k; ++a){
        b = k - a;
        com.resize(maxScope + n, 0);
        if(tryStu(0)) return true;
    }
    return false;
}

int caseProc(){
    for(int k=0; k<maxScope; ++k){
        if(tryK(k)) return k;
    }
    return -1;
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    while(input()){
        printf("%d\n", caseProc());
    }
}
