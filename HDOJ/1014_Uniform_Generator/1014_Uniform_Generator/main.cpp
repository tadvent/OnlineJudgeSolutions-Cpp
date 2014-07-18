#include<iostream>
#include<iomanip>
using namespace std;
int gcd(int a, int b){ // a >= b
    int c;
    while(b){
        c = a%b;
        a = b;
        b = c;
    }
    return a;
}
int main(){
    int step, mod;
    while(cin >> step >> mod){
        cout << setw(10) << step << setw(10) << mod << "    ";
        if(step < mod)swap(step, mod);
        if(gcd(step, mod) == 1)
            cout << "Good Choice";
        else
            cout << "Bad Choice";
        cout << "\n\n";
    }
}
