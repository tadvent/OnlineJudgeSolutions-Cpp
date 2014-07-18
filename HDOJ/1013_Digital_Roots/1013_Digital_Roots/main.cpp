#include<iostream>
#include<string>
#include<cstdlib>
#include<algorithm>
using namespace std;

int root(int num){
    div_t r = div(num, 10);
    int sum = r.rem;
    while(r.quot){
        r = div(r.quot, 10);
        sum += r.rem;
    }
    return sum;
}
class charsum{
    int &sum;
public:
    charsum(int &N):sum(N){}
    void operator()(char ch){
        sum += ch - '0';
    }
};

int main(){
    string s;
    while(cin>>s && s != "0"){
        int n = 0;
        for_each(s.begin(), s.end(), charsum(n));
        while(n > 9)n = root(n);
        cout << n << '\n';
    }
}
