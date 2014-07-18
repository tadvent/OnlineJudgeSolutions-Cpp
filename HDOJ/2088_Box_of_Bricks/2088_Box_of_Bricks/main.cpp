#include<iostream>
#include<vector>
using namespace std;

int main(){
    bool first = true;
    int n, avg, sum;
    vector<int> h;
    while(cin>>n && n>0){
        if(first)first = false;
        else cout<<'\n';
        sum = 0;
        h.resize(n);
        for(int i=0; i<n; ++i){
            cin>>h[i];
            sum += h[i];
        }
        avg = sum / n;
        sum = 0;
        for(int i=0; i<n; ++i)if(h[i] > avg)
            sum += h[i] - avg;
        cout<<sum<<'\n';
    }
}
