#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int div_n = 7;  // div > 1
vector<int> seq;

int f(int a, int b, int n){
    if(n < 3)return 1;
    seq.assign(1, 1);
    int fn[2] = {1};
    int idx = 2;
    fn[1] = (a*fn[0] + b*seq.back()) % div_n;
    vector<int>::iterator itr;
    while((itr = search(seq.begin(), seq.end(), fn, fn+2)) == seq.end()){
        if(++idx == n)return fn[1];
        seq.push_back(fn[0]);
        fn[0] = fn[1];
        fn[1] = (a*fn[0] + b*seq.back()) % div_n;
    }
    return *(((n-1) - (itr-seq.begin())) % (seq.end() - itr) + itr);
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int a, b, n;
    seq.reserve(50);
    while(cin>>a>>b>>n && (a || b || n)){
        cout << f(a, b, n) << '\n';
    }
    cout.flush();
}
