#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

vector<int> seq;

void sswitch(int x){
    x %= seq.size();
    std::rotate(seq.begin(), seq.begin()+x, seq.begin()+x+1);
}

int case_proc(){
    int n, m, x;
    scanf("%d%d", &n, &m);
    if(n <= 0) return 0;
    seq.resize(n);
    for(int i=0; i<n; ++i) seq[i] = i+1;
    while(m--){
        scanf("%d", &x);
        sswitch(x);
    }
    return seq[0];
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int T;
    scanf("%d", &T);
    while(T--){
        printf("%d\n", case_proc());
    }
}
