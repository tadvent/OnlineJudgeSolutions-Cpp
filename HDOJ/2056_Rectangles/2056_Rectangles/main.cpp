#include<iostream>
using namespace std;

int main(){
    cout.setf(ios::fixed);
    cout.precision(2);
    double x[4],y[4];
    for(;;){
        for(int i=0; i<4; ++i)
            cin >> x[i] >> y[i];
        if(!cin)break;
        if(x[0] > x[1])swap(x[0], x[1]);
        if(y[0] > y[1])swap(y[0], y[1]);
        if(x[2] > x[3])swap(x[2], x[3]);
        if(y[2] > y[3])swap(y[2], y[3]);

        x[0] = max(x[0], x[2]);
        y[0] = max(y[0], y[2]);
        x[1] = min(x[1], x[3]);
        y[1] = min(y[1], y[3]);

        if(x[0] < x[1] && y[0] < y[1])
            cout << (x[1]-x[0])*(y[1]-y[0]) << '\n';
        else cout << 0.0 << '\n';
    }
}
