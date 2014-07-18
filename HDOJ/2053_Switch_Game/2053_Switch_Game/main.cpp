#include<iostream>
#include<cmath>
using namespace std;
bool is_square(int n){
    int root = (int)(sqrt((double)n) + 0.5);
    return root*root == n;
}
int main(){
    int n;
    while(cin>>n && n>0){
        cout << is_square(n) << '\n';
    }
}