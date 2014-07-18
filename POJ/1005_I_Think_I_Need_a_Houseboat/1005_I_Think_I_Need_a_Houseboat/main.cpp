#include<fstream>
#include<iostream>
using namespace std;

inline int point2year(double x, double y){
    double rr = x*x + y*y;
    return static_cast<int>(rr * 3.1415926536 / 100.0) + 1;
}

int main(){
    ifstream cin("in.txt");
    ofstream cout("out.txt");
    int n, cnt = 1;
    double x,y;
    cin>>n;
    while(n--){
        cin>>x>>y;
        cout<<"Property "<< cnt++ <<": This property will begin eroding in year "
            <<point2year(x, y)<<".\n";
    }
    cout<<"END OF OUTPUT.\n";
}