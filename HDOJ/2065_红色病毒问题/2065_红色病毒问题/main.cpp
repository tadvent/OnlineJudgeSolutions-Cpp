#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;

vector< pair<int, int> > seq;

void init(){
    seq.push_back(make_pair(1, 0));
    seq.push_back(make_pair(2, 1));
    for(;;){
        pair<int, int> val;
        val.first = (2*(seq.back().first + seq.back().second))%100;
        val.second = (4*seq.back().second)%100;
        if(find(seq.begin(), seq.end(), val) != seq.end())
            break;
        else seq.push_back(val);
    }
}
inline int vircnt(long long n){
    if(n<=3)return seq[n].first;
    return seq[(n-3)%20+3].first;
}

int main(){
    int t;
    long long n;
    init();

    while(cin>>t && t>0){
        for(int i=1; i<=t; ++i){
            cin>>n;
            cout<<"Case "<<i<<": "<<vircnt(n)<<'\n';
        }
        cout.put('\n');
    }
}
