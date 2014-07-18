#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

string name[30];
double change[30][30];
int n;

int name2id(const string &str){
    int i=0;
    while(str != name[i])++i;
    return i;
}

bool input(){
    if(!(cin>>n) || !n)return false;
    for(int i=0; i<n; ++i)cin>>name[i];

    memset(change, 0, sizeof(change));
    int m;
    cin>>m;
    while(m--){
        string c1, c2;
        double r;
        cin >> c1 >> r >> c2;
        change[name2id(c1)][name2id(c2)] = r;
    }
    for(int i=0; i<n; ++i)
        change[i][i] = max(change[i][i], 1.0);
    return true;
}

// just like a floyd
bool arbitrage(){
    for(int k=0; k<n; ++k)
        for(int i=0; i<n; ++i)
            for(int j=0; j<n; ++j){
                change[i][j] = max(change[i][j], change[i][k]*change[k][j]);
            }
    for(int i=0; i<n; ++i)
        if(change[i][i] > 1.0)return true;
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    for(int nCase=1; input(); ++nCase){
        cout << "Case " << nCase << (arbitrage()? ": Yes\n":": No\n");
    }
}