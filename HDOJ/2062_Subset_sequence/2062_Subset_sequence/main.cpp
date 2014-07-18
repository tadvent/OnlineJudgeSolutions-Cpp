#include<iostream>
#include<algorithm>
using namespace std;

long long subcnt[21] = {1};
int numseq[21];

void init(){
    for(int i=1; i<21; ++i)
        subcnt[i] = 1 + i*subcnt[i-1];
}

void arng(int si, int len, long long nth){
    if(nth == 1)return;  // numseq[si] == 0;
    int idx = (nth-2)/subcnt[len-1] + 1;
    rotate(numseq+si, numseq+si+idx, numseq+si+idx+1);
    arng(si+1, len-1, (nth-2)%subcnt[len-1]+1);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int n;
    long long m;
    init();

    while(cin>>n>>m){
        for(int i=0; i<=n; ++i)
            numseq[i] = i;
        arng(0, n, m+1);
        for(int i=0; i<n; ++i){
            if(numseq[i] == 0)break;
            if(i>0)cout.put(' ');
            cout<<numseq[i];
        }
        cout.put('\n');
    }
}
