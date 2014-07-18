#include<cstdio>
#include<complex>
#include<vector>
#include<algorithm>
using namespace std;

struct lessX{
    bool operator()(const complex<double> &l, const complex<double> &r)const{
        return l.real() < r.real();
    }
};
template<class Iter>
struct lessY{
    bool operator()(Iter l, Iter r)const{
        return l->imag() < r->imag();
    }
};

template<class Iter> double mindist(Iter beg, Iter end){
    double mind;
    int n = end - beg;
    if(n < 2)return 1e100;
    if(n == 2)return abs(*beg - *(beg+1));
    if(n == 3){
        mind = min(abs(*beg - *(beg+1)), abs(*beg - *(beg+2)));
        return min(mind, abs(*(beg+1) - *(beg+2)));
    }
    Iter mid = beg + n/2;
    mind = min(mindist(beg, mid), mindist(mid, end));
    Iter itlt = upper_bound(beg, mid, *mid-mind+1e-8, lessX());
    Iter itrt = lower_bound(mid, end, *mid+mind-1e-8, lessX());
    static vector<Iter> idxs; idxs.clear();
    for(Iter it=itlt; it!= itrt; ++it)idxs.push_back(it);
    sort(idxs.begin(), idxs.end(), lessY<Iter>());
    for(typename vector<Iter>::iterator it1=idxs.begin(); it1!=idxs.end(); ++it1)
        for(typename vector<Iter>::iterator it2=it1+1;
            it2!=idxs.end() && (*it1)->imag()+mind > (*it2)->imag()+1e-8; ++it2){
            double td;
            if((td = abs(**it1 - **it2)) + 1e-8 < mind)mind = td;
        }
    return mind;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int n;
    vector< complex<double> > pts;
    pts.reserve(100000);
    while(scanf("%d",&n)!=EOF && n){
        double x,y;
        pts.clear();
        while(n-- && scanf("%lf%lf",&x,&y) != EOF)
            pts.push_back(complex<double>(x,y));
        sort(pts.begin(), pts.end(), lessX());
        printf("%.2lf\n", mindist(pts.begin(), pts.end())/2.0);
    }
}
