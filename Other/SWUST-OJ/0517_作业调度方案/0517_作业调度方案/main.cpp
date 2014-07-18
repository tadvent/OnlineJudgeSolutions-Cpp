#define MY

#ifdef MY

#include<cstdio>
#include<vector>
#include<map>
#include<cstring>
#include<climits>
using namespace std;

const int n_max = 20;
const int m_max = 20;

int nPart, mCourse;
int partSeq[n_max * m_max];
int ps_size;

int workOn[n_max][m_max];   // part i seq j work on workOn[i][j] machine
int wTime[n_max][m_max];    // part i seq j work consume wTime[i][j] time

map<int, int> timeMap[m_max];
int beginTime[n_max];
int seqIdx[n_max];  // part i's next step is seq seqIdx[i]

bool input(){
    int i, j;
    if(scanf("%d%d", &mCourse, &nPart) != 2)
        return false;
    ps_size = nPart * mCourse;
    for(i=0; i<ps_size; ++i){
        scanf("%d", &partSeq[i]);
        --partSeq[i];
    }
    for(i=0; i<nPart; ++i)for(j=0; j<mCourse; ++j){
        scanf("%d", &workOn[i][j]);
        --workOn[i][j];
    }
    for(i=0; i<nPart; ++i)for(j=0; j<mCourse; ++j){
        scanf("%d", &wTime[i][j]);
    }

    // initialization
    for(i=0; i<mCourse; ++i)
        timeMap[i].insert(make_pair(0, INT_MAX));
    memset(beginTime, 0, sizeof(beginTime));
    memset(seqIdx, 0, sizeof(seqIdx));

    return true;
}

int calc(){
    for(int idx=0; idx<ps_size; ++idx){
        int iPart = partSeq[idx];
        int workTime = wTime[iPart][seqIdx[iPart]];
        map<int, int> &machine = timeMap[workOn[iPart][seqIdx[iPart]++]];
        map<int, int>::iterator itr = machine.upper_bound(beginTime[iPart]);
        if(itr != machine.begin())
            --itr;
        else {
            beginTime[iPart] = itr->first;
        }

        if(itr->first + itr->second >= beginTime[iPart] + workTime){
            int clip = itr->first + itr->second - (beginTime[iPart] + workTime);
            if(beginTime[iPart] > itr->first){
                itr->second = beginTime[iPart] - itr->first;
                if(clip > 0)
                    machine.insert(itr,
                        make_pair(beginTime[iPart] + workTime, clip)
                );
            }
            else if(clip > 0){
                *(const_cast<int *>(&itr->first)) += workTime;
                itr->second = clip;
            }
            else machine.erase(itr);
            beginTime[iPart] += workTime;
            continue;
        }

        for(++itr; itr != machine.end(); ++itr)
            if(itr->second >= workTime)break;
        beginTime[iPart] = itr->first + workTime;
        if(itr->second > workTime){
            *(const_cast<int *>(&itr->first)) += workTime;
            itr->second -= workTime;
        } else {
            machine.erase(itr);
        }
    }

    int minTime = 0;
    for(int i=0; i<nPart; ++i)
        if(beginTime[i] > minTime)minTime = beginTime[i];
    return minTime;
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    while(input())
        printf("%d\n", calc());
}

#else

#include <fstream>

using namespace std;

bool busy[20][400];

bool check(int,int,int);

int main() {
    ifstream fin ("i.txt");
    ofstream fout ("o.txt");
    int m,n,order[400],use[20][20],times[20][20],end[20],pro[20],ans=0;
    fin >> m >> n;
    for (int i=1;i<=m*n;i++) fin >> order[i];
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) fin >> use[i][j];
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) fin >> times[i][j];
    memset(end,0,sizeof(end));
    memset(pro,0,sizeof(pro));
    for (int i=1;i<=m*n;i++) {
        int cur=order[i],mac=use[cur][++pro[cur]],t=times[cur][pro[cur]];
        for (int j=end[cur];;j++) if (check(mac,j,j+t-1)) {
            memset(&busy[mac][j],1,sizeof(busy[0][0])*t);
            if (j+t-1>=ans) ans=j+t;
            end[cur]=j+t;
            break;
        }
    }
    fout << ans << endl;
    fin.close();
    fout.close();
    return 0;
}

bool check(int mac,int s,int t) {
    for (int i=s;i<=t;i++) if (busy[mac][i]) return false;
    return true;
}

#endif