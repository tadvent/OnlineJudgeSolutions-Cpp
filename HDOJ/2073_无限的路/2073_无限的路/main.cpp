#include<iostream>
#include<cmath>
using namespace std;

double seg[201] = {0.0};
void init(){
    for(int y = 1; y < 201; ++y)
        seg[y] = seg[y-1] + sqrt(double(2*(y-1)*(y-1))) + sqrt(double((y-1)*(y-1)+y*y));
}
inline double len(int x, int y){
    int idx = x + y;
    if(idx <= 0)return 0.0;
    return seg[idx] + sqrt(double(2*idx*idx))*x/idx;
}
inline double dis(int x1, int y1, int x2, int y2){
    return abs(len(x1,y1) - len(x2,y2));
}

int main(){
    int n, x1, y1, x2, y2;
    init();
    cin>>n;
    cout.setf(ios::fixed);
    cout.precision(3);

    while(n--){
        cin>>x1>>y1>>x2>>y2;
        cout<<dis(x1,y1,x2,y2)<<'\n';
    }
}
