#include<iostream>
using namespace std;

bool isSky(int num){
    int sum10 = 0, sum16 = 0, sum12 = 0;
    div_t d;
    d.quot = num;
    while(d.quot){
        d = div(d.quot, 10);
        sum10 += d.rem;
    }
    d.quot = num;
    while(d.quot){
        d = div(d.quot, 16);
        sum16 += d.rem;
    }
    if(sum10 != sum16)return false;
    d.quot = num;
    while(d.quot){
        d = div(d.quot, 12);
        sum12 += d.rem;
    }
    if(sum10 != sum12)return false;
    else return true;
}

int main(){
    int num;
    while(cin>>num && num){
        cout<< num << " is ";
        if(!isSky(num))cout<<"not ";
        cout<< "a Sky Number.\n";
    }
}
