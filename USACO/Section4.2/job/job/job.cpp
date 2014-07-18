/*
ID: wjl1241
PROG: job
LANG: C++
*/

#include<fstream>
#include<vector>
#include<queue>
using namespace std;

struct itv_ftime{
    int interval;
    int fintime;
    itv_ftime(){}
    itv_ftime(int Interval, int FinishTime):interval(Interval), fintime(FinishTime){}
    bool operator>(const itv_ftime &comp)const{
        return fintime > comp.fintime;
    }
};

vector<int> A, B, TA, TB;
int nJobs;

void LeastTime(const vector<int> &mac, vector<int> &Tmac){
    Tmac.resize(nJobs + 1);
    priority_queue<itv_ftime, vector<itv_ftime>, greater<itv_ftime> > Q;
    for(vector<int>::const_iterator itr=mac.begin(); itr!=mac.end(); ++itr)
        Q.push(itv_ftime(*itr, *itr));
    int iJob = 1;
    while(iJob <= nJobs){
        itv_ftime obj = Q.top();
        Q.pop();
        Tmac[iJob++] = obj.fintime;
        Q.push(itv_ftime(obj.interval, obj.fintime + obj.interval));
    }
}

int main(){
    ifstream fin("job.in");
    ofstream fout("job.out");
    int m1, m2;
    fin>>nJobs>>m1>>m2;
    A.resize(m1);
    B.resize(m2);
    for(int i=0;i<m1;++i)fin>>A[i];
    for(int i=0;i<m2;++i)fin>>B[i];
    fin.close();

    LeastTime(A,TA);
    LeastTime(B,TB);
    int least = 0;
    for(int i=1; i<=nJobs; ++i)
        least = max(least, TA[i] + TB[nJobs - i + 1]);
    fout<<TA[nJobs]<<' '<<least<<endl;
    fout.close();
    return 0;
}
