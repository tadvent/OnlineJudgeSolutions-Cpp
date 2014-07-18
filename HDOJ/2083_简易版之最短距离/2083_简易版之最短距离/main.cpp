#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> pos;

int calc(){
    int sum = 0, idx = pos.size()/2;
    sort(pos.begin(), pos.end());
    for(int i=0; i<idx; ++i)
        sum += pos[idx] - pos[i];
    for(int i=idx+1; i<pos.size(); ++i)
        sum += pos[i] - pos[idx];
    return sum;
}

int main(){
    int t, n;
    cin>>t;
    while(t--){
        pos.clear();
        cin>>n;
        pos.resize(n);
        for(int i=0; i<n; ++i)
            cin>>pos[i];
        cout<<calc()<<'\n';
    }
}
