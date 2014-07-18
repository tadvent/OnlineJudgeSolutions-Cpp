#include<iostream>
using namespace std;

void output(unsigned num, int base){
    char buffer[32];
    int idx = 0;
    do{
        buffer[idx++] = num%base + '0';
        num /= base;
    }while(num);
    for(int i=idx-1; i>=0; --i)
        cout.put(buffer[i]);
    cout.put('\n');
}

int main(){
    unsigned m, a, b;
    while(cin>>m && m){
        cin>>a>>b;
        output(a+b, m);
    }
}
