#include<iostream>
using namespace std;
int main(){
    int m, n;
    double sum, score, max, min;
    cout.setf(ios::fixed);
    cout.precision(2);
    while(cin>>n){
        m = n;
        sum = 0.0;
        max = -1e10;
        min = 1e10;
        while(m--){
            cin>>score;
            sum += score;
            if(score>max)max=score;
            if(score<min)min=score;
        }
        cout<<(sum-max-min)/(n-2)<<'\n';
    }
}