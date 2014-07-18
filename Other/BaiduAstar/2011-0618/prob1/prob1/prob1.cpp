#include<iostream>
#include<cstdio>
using namespace std;

int calc(){
    int n, p, q;
    int rp = 0, rq = 0, s = 0;
    cin >> n;
    while(n--){
        cin >> p >> q;
        rp += p;
        rq += q;
        if(rp > rq){
            s += rp;
            rq = 0;
        } else {
            s += rq;
            rp = 0;
        }
    }
    return s;
}

int main(){
#ifdef LOCAL
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    cout << calc() << '\n';
}
