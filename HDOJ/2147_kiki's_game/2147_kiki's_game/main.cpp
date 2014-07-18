#include<iostream>
using namespace std;

int main(){
    int m, n;
    while(cin>>m>>n && (m||n)){
        if(m%2 == 0 || n%2 == 0){
            cout << "Wonderful!\n";
        } else {
            cout << "What a pity!\n";
        }
    }
}
