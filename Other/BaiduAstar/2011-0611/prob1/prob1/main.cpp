#include<iostream>

using namespace std;

int n, m, ge2;

bool input(){
    int tmp;
    ge2 = 0;
    if(cin>>n>>m){
        while(m--){
            cin >> tmp;
            if(tmp > 1)++ge2;
        }
        return true;
    }
    return false;
}

int main(){
    while(input()){
        cout << ge2*(n-ge2) << '\n';
    }
}
