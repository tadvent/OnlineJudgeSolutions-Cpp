#ifndef ONLINE_JUDGE
#include<cstdio>
#endif

#include<iostream>
#include<cmath>
#include<utility>
#include<queue>
using namespace std;

#ifdef _DEBUG
int runcnt = 0;
#endif

class range{
    static double inv;
    double v;
    int idx;
public:
    static void setD(double d){
        inv = 30.0 - d*60.0/360;
    }
    range(double V):v(V), idx(0){}
    pair<double, double> nextrange(){
        ++idx;
        return make_pair((60.0*idx-30.0-inv)/v, (60.0*idx-30.0+inv)/v);
    }
};
double range::inv = 0.0;

struct point{
    int idx;
    double time;
    bool start;
    point(int Idx, double Time, bool Start):idx(Idx), time(Time), start(Start){}
    bool operator>(const point &r)const{
        return (time > r.time || (time ==r.time && idx > r.idx));
    }
};

double percent(double D){
    unsigned char flag = 0;
    range::setD(D);
    range dv[3] = {1.0 - 1.0/60, 1.0 - 1.0/720, 1.0/60 - 1.0/720};
    pair<double, double> pt;
    priority_queue<point, vector<point>, greater<point> > pq;
    for(int i=0; i<3; ++i){
        pt = dv[i].nextrange();
        pq.push(point(i, pt.first, true));
        pq.push(point(i, pt.second, false));
    }

    double last = 0.0, happy = 0.0;
    while(pq.top().time < 12.0*60*60 + 1e-8){
#ifdef _DEBUG
        ++runcnt;
#endif
        point &top = pq.top();
        if(!top.start){ // end
            if(flag == 0x07){
                happy += top.time - last;
            }
            flag &= ~(0x01 << top.idx);
            pt = dv[top.idx].nextrange();
            pq.push(point(top.idx, pt.first, true));
            pq.push(point(top.idx, pt.second, false));
        } else {    // start
            flag |= 0x01 << top.idx;
        }
        last = top.time;
        pq.pop();
    }
    if(flag == 0x07){
        happy += 12.0*60*60 - last;
    }
    return happy*100/(12.0*60*60);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    double D;
    cout.setf(ios::fixed);
    cout.precision(3);
    while(cin>>D && abs(D+1) > 1e-8){
#ifdef _DEBUG
        double result = percent(D);
        cout << result << ' ' << runcnt << '\n';
        runcnt = 0;
#else
        cout << percent(D) << '\n';
#endif
    }
}
