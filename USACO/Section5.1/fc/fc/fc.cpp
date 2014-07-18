/*
ID: wjl1241
PROG: fc
LANG: C++
*/

#include<cmath>
#include<cstdio>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;

inline
double crossproduct(const pair<double, double> &v1, const pair<double, double> &v2){
    return v1.first*v2.second - v1.second*v2.first;
}
inline
pair<double, double> operator-(const pair<double, double> &v1, const pair<double, double> &v2){
    return make_pair(v1.first - v2.first, v1.second - v2.second);
}
inline
double abs(const pair<double, double> &v){
    return sqrt(v.first*v.first + v.second*v.second);
}

class graph{
    typedef vector< pair<double, double> > ptvec;
    ptvec points;

    pair<double, double> avgpoint(){
        double sumx = 0.0, sumy = 0.0;
        for(ptvec::iterator i = points.begin(); i != points.end(); ++i){
            sumx += i->first;
            sumy += i->second;
        }
        return make_pair(sumx / points.size(), sumy / points.size());
    }
    class idxcompare{
        const vector<double> &values;
    public:
        idxcompare(const vector<double> &Vec):values(Vec){}
        bool operator()(int idx1, int idx2) const {
            return values[idx1] < values[idx2];
        }
    };
public:
    graph(int size_reserve){
        points.reserve(size_reserve);
    }
    void addpoint(double x, double y){
        points.push_back(make_pair(x, y));
    }
    double circum(){
        if(points.empty() || points.size() == 1)return 0.0;
        if(points.size() == 2){
            return 2*abs(points[0] - points[1]);
        }
        vector<double> ptargs;
        pair<double, double> innerpt(avgpoint());

        // calculate each arg of the points
        ptargs.reserve(points.size());
        for(ptvec::iterator it=points.begin(); it!=points.end(); ++it)
            ptargs.push_back(atan2(it->second - innerpt.second, it->first - innerpt.first));

        // sort points by their args
        vector<int> ptidxs;
        ptidxs.reserve(points.size());
        for(int i = 0; i < (int)points.size(); ++i)
            ptidxs.push_back(i);
        sort(ptidxs.begin(), ptidxs.end(), idxcompare(ptargs));

        // remove middle points
        vector<int>::iterator it0 = ptidxs.begin(), it1;
        it1 = it0 + 1;
        while(it1+1 != ptidxs.end()){
            if(crossproduct(points[*it0] - points[*it1],
                points[*it1] - points[*(it1+1)]) < 0){
                    ++it1;
                    while(it0 > ptidxs.begin() && crossproduct(points[*(it0-1)] - points[*it0],
                        points[*it0] - points[*it1]) < 0)
                        --it0;
            } else {
                *++it0 = *it1++;
            }
        }
        *++it0 = *it1;
        ptidxs.erase(it0+1, ptidxs.end());

        // remove leading and ending points
        it0 = ptidxs.begin();
        it1 = ptidxs.end() - 1;
        for(bool flag = true; flag;){
            flag = false;
            while(crossproduct(points[*it1] - points[*it0],
                points[*it0] - points[*(it0+1)]) < 0){
                    ++it0;
                    flag = true;
            }
            while(crossproduct(points[*(it1-1)] - points[*it1],
                points[*it1] - points[*it0]) < 0){
                    --it1;
                    flag = true;
            }
        }

        // calculate circum
        double c = abs(points[*it0] - points[*it1]);
        while(it0 != it1){
            c += abs(points[*it0] - points[*(it0+1)]);
            ++it0;
        }
        return c;
    }
};

int main(){
    FILE *fin = fopen("fc.in", "r");
    if(!fin){
        fprintf(stderr, "Can't open input file...\n");
        exit(EXIT_FAILURE);
    }

    int N;
    double x, y;
    fscanf(fin, "%d", &N);
    graph hull(N);
    while(N--){
        fscanf(fin, "%lf%lf", &x, &y);
        hull.addpoint(x, y);
    }
    fclose(fin);

    FILE *fout = fopen("fc.out", "w");
    if(!fout){
        fprintf(stderr, "Can't open output file...\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fout, "%.2lf\n", hull.circum());
    fclose(fout);
}
