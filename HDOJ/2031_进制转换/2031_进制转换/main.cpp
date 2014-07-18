#include<iostream>
#include<cstdlib>
#include<list>
#include<iterator>
#include<algorithm>
using namespace std;
list<char> digits;
bool num2digit(long num, long R){
    bool minus=false;
    digits.clear();
    if(num<0){num=-num;minus=true;}
    ldiv_t d = ldiv(num, R);
    for(;;){
        if(d.rem<10)d.rem+='0';
        else d.rem+='A'-10;
        digits.push_front((char)d.rem);
        if(d.quot==0)break;
        d = ldiv(d.quot,R);
    }
    if(minus)digits.push_front('-');
    return true;
}
int main(){
    long N, R;
    while(cin>>N>>R){
        num2digit(N,R);
        copy(digits.begin(), digits.end(), ostreambuf_iterator<char>(cout));
        cout.put('\n');
    }
}