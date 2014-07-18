#include<iostream>
using namespace std;

int gcd(int a, int b){
    if(a<b)swap(a,b);
    while(b){
        int rem = a%b;
        a = b;
        b = rem;
    }
    return a;
}

inline void yuefen(int &a, int &b){
    int g = gcd(a, b);
    if(g){
        a /= g;
        b /= g;
    }
}

int main(){
    int t, a, b, c, d;
    cin>>t;
    while(t--){
        cin>>a>>b>>c>>d;
        int m = a*d + b*c;
        int n = b*d;
        yuefen(m, n);
        cout<<m<<' '<<n<<'\n';
    }
}
