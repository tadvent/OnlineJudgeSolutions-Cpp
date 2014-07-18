#include<fstream>
#include<iostream>
#include<numeric>
#include<vector>
#include<algorithm>
using namespace std;

vector<double> len;
void init(){
    len.reserve(300);
    len.push_back(0.0);
    for(int i=2; i<300; ++i)
        len.push_back(1.0/i);
    partial_sum(len.begin(), len.end(), len.begin());
}

int main(){
    ifstream cin("in.txt");
    ofstream cout("out.txt");
    init();

    double des;
    cin>>des;
    while(des != 0.0){
        cout<<(lower_bound(len.begin(), len.end(), des) - len.begin())
            <<" card(s)\n";
        cin>>des;
    }
}