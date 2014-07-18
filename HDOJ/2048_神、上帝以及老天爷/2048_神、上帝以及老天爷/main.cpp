#include<iostream>
using namespace std;
long long a[21] = {0};
long long C[21] = {1, 1};
long long jiecheng[21] = {1, 1};
void init(){
    for(int i=2; i<21; ++i){
        long long total = jiecheng[i] = jiecheng[i-1]*i;
        C[i] = 1;
        --total;
        for(int j=i-1; j>0; --j){
            C[j] += C[j-1];
            total -= C[j]*a[i-j];
        }
        a[i] = total;
    }
}
int main(){
    int N, n;
    init();
    cout.setf(ios::fixed);
    cout.precision(2);
    cin>>N;
    while(N--){
        cin>>n;
        cout<<(double)a[n]/jiecheng[n]*100<<"%\n";
    }
}

// better algorithm:
// a[i] = (i-1)*(a[i-1] + a[i-2]);