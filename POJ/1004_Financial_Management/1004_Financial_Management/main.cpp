#include<iostream>
#include<fstream>
using namespace std;
int main(){
    ifstream cin("in.txt");
    ofstream cout("out.txt");
    double num, sum = 0.0;
    while(cin>>num)sum+=num;
    cout.setf(ios::fixed);
    cout.precision(2);
    cout<<'$'<<sum/12<<endl;
}