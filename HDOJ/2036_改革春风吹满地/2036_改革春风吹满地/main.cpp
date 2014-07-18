#include<iostream>
#include<vector>
#include<complex>
using namespace std;
vector<complex<double> > pts;
inline double crossp(const complex<double> c1, const complex<double> c2){
    return c1.real()*c2.imag() - c1.imag()*c2.real();
}
double Spts(){
    if(pts.size()<3)return 0.0;
    double s = crossp(pts.back(), pts.front());
    for(vector<complex<double> >::iterator it=pts.begin()+1;it!=pts.end();++it)
        s+=crossp(*(it-1), *it);
    return s/2.0;
}
int main(){
    int n;
    cout.setf(ios::fixed);
    cout.precision(1);
    while(cin>>n && n){
        double x,y;
        pts.clear();
        while(n--){
            cin>>x>>y;
            pts.push_back(complex<double>(x,y));
        }
        cout<<Spts()<<'\n';
    }
}