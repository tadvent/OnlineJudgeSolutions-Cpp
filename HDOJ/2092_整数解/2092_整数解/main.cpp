#include<cmath>
#include<iostream>
using namespace std;
bool HasResult(int m, int n){
    int root = int(sqrt(abs(double(n))) + 0.5);
    for(int i=1; i<=root; ++i)if(n%i==0){
        int j=n/i;
        if(i+j == m || -i-j == m)return true;
    }
    return false;
}

int main(){
    int m,n;
    while(cin>>m>>n && (m||n)){
        cout<<(HasResult(m,n)? "Yes\n":"No\n");
    }
}
