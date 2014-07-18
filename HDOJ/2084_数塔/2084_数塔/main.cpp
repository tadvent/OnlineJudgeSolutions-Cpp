#include<cstring>
#include<iostream>
using namespace std;
int layer[100], n;
int calc(){
    int num;
    memset(layer, 0, sizeof(layer));
    cin>>n;
    for(int i=1; i<=n; ++i){
        int last = 0;
        for(int j=0; j<i; ++j){
            int tmp = layer[j];
            cin>>num;
            layer[j] = num + max(last, tmp);
            last = tmp;
        }
    }
    int maxlen = 0;
    for(int i=0; i<n; ++i)if(layer[i]>maxlen)
        maxlen = layer[i];
    return maxlen;
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int t;
    cin>>t;
    while(t--)
        cout<<calc()<<'\n';
}
