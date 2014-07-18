#include<iostream>
using namespace std;

class rem{
    static int r[65];
public:
    rem(){
        for(int x = 0; x < 65; ++x){
            int mul = 1;
            // a = x ^ 5 % 65
            for(int i = 0; i < 5; ++i)
                mul *= x;
            int a = mul %= 65;

            // mul = x ^ 13 % 65
            for(int i = 5; i < 13; ++i){
                mul *= x;
                mul %= 65;
            }

            // r[x] = (5 * x^13 + 13 * x^5) % 65
            r[x] = (5 * mul + 13 * a) % 65;
        }
    }
    int operator[](int x)const{
        return r[x%65];
    }
};
int rem::r[65];
rem r;

bool divide(int k, int a){
    int x;
    for(x=0; x<65; ++x)
        if((r[x] + x * k *a) % 65 != 0)
            return false;
    return true;
}

int k2a(int k){
    // return 65 if no a
    int a;
    k %= 65;
    for(a=0; a<65; ++a){
        if(divide(k, a))break;
    }
    return a;
}
int a[65];

int main(){
    int k;
    for(k=0; k<65; ++k)a[k] = k2a(k);
    while(cin>>k){
        k %= 65;
        if(a[k] == 65)
            cout << "no\n";
        else cout << a[k] << '\n';
    }
}
