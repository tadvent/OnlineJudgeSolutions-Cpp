#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<vector>
#include<deque>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
#include<utility>

using namespace std;

#define LOCAL

int n, k;
vector<int> a, b;
struct node{
    int s, d;
    pair<int,int> r;
    node(int S, int D, const pair<int,int> &R): s(S), d(D), r(R){}
    bool operator<(const node &rt) const {
        return s > rt.s || s == rt.s && d > rt.d;
    }
};

priority_queue<node> pq;

bool input(){
    if(cin >> n >> k){
        a.clear();
        b.clear();

        for(int i=0; i<n; ++i){
            int aa, ab;
            cin >> aa >> ab;
            a.push_back(aa);
            b.push_back(ab);
        }
        return true;
    }
    return false;
}

int clac(){
    set<pair<int,int> > fn;
    set<int> finish;
    fn.insert(make_pair(0,0));
    finish.insert(0);

    pq.push(node(0, 1, make_pair(0, 0)));
    while(k--){
        node t = pq.top();
        pq.pop();
        if(finish.find(t.s) == finish.end())
            finish.insert(t.s);
        else if(t.s) ++k;

        for(int i=0; i<n; ++i){
            pq.push(node(t.s+a[i]+b[i]*t.d, t.d+1, make_pair(t.s, t.d)));
        }
        if(fn.find(t.r) == fn.end()){
            fn.insert(t.r);
            for(int i=0; i<n; ++i){
                pq.push(node(t.r.first+a[i]+b[i]*t.d, t.d+1, make_pair(t.r.first, t.d)));
            }
        }
    }
    return pq.top().s;
}

int main(){
#ifdef LOCAL
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif

    while(input()){
        cout << clac() << '\n';
    }
}
