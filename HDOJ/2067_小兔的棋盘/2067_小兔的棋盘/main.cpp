#include<iostream>
using namespace std;
unsigned long long bd[36][36] = {1, 0};
void init(){
    for(int i=1; i<36; ++i){
        for(int j=0; j<=i; ++j)
            bd[i][j] = bd[i-1][j] + bd[i][j-1];
    }
}
int main(){
    int n, idx=1;
    init();
    while(cin>>n && n>0){
        cout<< idx++ <<' '<< n <<' '<< 2*bd[n][n] << '\n';
    }
}
