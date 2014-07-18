/*
ID: wjl1241
LANG: C++
TASK: fence3
*/

#include<fstream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

struct fence{
    double beg, end, z;
    fence(double Beg, double End, double Z):beg(Beg), end(End), z(Z){}
    bool operator< (const fence &r) const {
        return beg < r.beg;
    }
};

vector<fence> hfences;
vector<fence> vfences;
double minlength;

double totalength(double x, double y){
    double total = 0.0;
    vector<fence>::iterator it;
    for(it = hfences.begin(); it != hfences.end() && it->beg <= x; ++it)
        total += (it->end >= x)? abs(it->z - y)
            : sqrt((it->z - y) * (it->z - y) + (x - it->end) * (x - it->end));
    while(it != hfences.end()){
        total += sqrt((it->beg - x) * (it->beg - x) + (it->z - y) * (it->z - y));
        ++it;
    }
    for(it = vfences.begin(); it != vfences.end() && it->beg <= y; ++it)
        total += (it->end >= y)? abs(it->z - x)
            : sqrt((it->z - x) * (it->z - x) + (y - it->end) * (y - it->end));
    while(it != vfences.end()){
        total += sqrt((it->beg - y) * (it->beg - y) + (it->z - x) * (it->z - x));
        ++it;
    }
    return total;
}

void walkToEnd(double &x, double &y, double step){
    // get the smallest total lens to every fence by step
    // point is returned by x and y
    double ttlen;
    for(;;){
        if(x+step <= 100.0 && (ttlen = totalength(x+step, y)) < minlength - 1e-4){
            minlength = ttlen;
            x += step;
        } else if(x-step >=0.0 && (ttlen = totalength(x-step, y)) < minlength - 1e-4){
            minlength = ttlen;
            x -= step;
        } else if(y+step <= 100.0 && (ttlen = totalength(x, y+step)) < minlength - 1e-4){
            minlength = ttlen;
            y += step;
        } else if(y-step >= 0.0 && (ttlen = totalength(x, y-step)) < minlength - 1e-4){
            minlength = ttlen;
            y -= step;
        } else break;
    }
}

int main(){
    int n;
    double x1, y1, x2, y2;
    ifstream fin("fence3.in");
    if(!fin)return -1;
    fin >> n;
    hfences.reserve(n);
    vfences.reserve(n);
    while(n-- && fin>>x1>>y1>>x2>>y2){
        if(y1 == y2){
            if(x1 > x2)swap(x1, x2);
            hfences.push_back(fence(x1, x2, y1));
        }
        else if(x1 == x2){
            if(y1 > y2)swap(y1, y2);
            vfences.push_back(fence(y1, y2, x1));
        } else
            return -2;
    }
    fin.close();
    sort(hfences.begin(), hfences.end());
    sort(vfences.begin(), vfences.end());

    double step = 25.0, minx = 50.0, miny = 50.0;
    minlength = totalength(minx, miny);
    while(step > 0.02){
        walkToEnd(minx, miny, step);
        step /= 2.0;
    }

    ofstream fout("fence3.out");
    fout.setf(ios::fixed);
    fout.precision(1);
    fout << minx << ' ' << miny << ' ' << minlength << '\n';
    fout.close();
}
