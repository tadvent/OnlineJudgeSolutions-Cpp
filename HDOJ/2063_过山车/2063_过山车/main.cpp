#include<vector>
#include<list>
#include<iostream>
using namespace std;

typedef vector<list<int> > CNet;
typedef vector<int> CArr;
CNet girl;
CArr boy;
CArr visited;

bool dfs(CNet::const_iterator it){
    for(list<int>::const_iterator cit = it->begin();
        cit != it->end(); ++cit){
            if(visited[*cit])continue;
            visited[*cit] = true;
            int t = boy[*cit];
            boy[*cit] = it-girl.begin();
            if(t==-1 || dfs(girl.begin() + t))
                return true;
            else
                boy[*cit] = t;
    }
    return false;
}

int match(){
    int num = 0;
    for(CNet::const_iterator it = girl.begin();
        it != girl.end(); ++it){
            visited.assign(boy.size(), 0);
            if(dfs(it))
                ++num;
    }
    return num;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int k, gn, bn;
    while(cin>>k && k){
        cin>>gn>>bn;
        girl.assign(gn, list<int>());
        boy.assign(bn, -1);
        while(k--){
            int gi, bi;
            cin>>gi>>bi;
            girl[gi-1].push_back(bi-1);
        }
        cout<<match()<<'\n';
    }
}
