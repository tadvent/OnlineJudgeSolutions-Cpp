/*
ID: wjl1241
PROG: comehome
LANG: C++
*/

//======================================================================
//...Version 1....using Dijkstra's Algorithm

//#include<fstream>
//#include<vector>
//#include<queue>
//using namespace std;
//
//int dist[52][52];
//bool hascow[52];
//const int infinite=1000000000;
//
//class dist_sum{
//public:
//    int to;
//    dist_sum(int v):to(v){}
//    bool operator<(const dist_sum &comp)const{
//        return dist[25][to]<dist[25][comp.to];
//    }
//    bool operator>(const dist_sum &comp)const{
//        return dist[25][to]>dist[25][comp.to];
//    }
//};
//
//int main(){
//    ifstream fin("comehome.in");
//    ofstream fout("comehome.out");
//    int p;
//    fin>>p;
//    for(int i=0;i<52;++i){
//        hascow[i]=false;
//        for(int j=0;j<52;++j)dist[i][j]=infinite;
//    }
//    for(int i=0;i<p;++i){
//        char barn1,barn2;
//        int distance;
//        fin>>barn1>>barn2>>distance;
//        if(barn1<'a'){
//            barn1-='A';
//            hascow[barn1]=true;
//        }
//        else barn1=barn1-'a'+26;
//        if(barn2<'a'){
//            barn2-='A';
//            hascow[barn2]=true;
//        }
//        else barn2=barn2-'a'+26;
//        if(distance<dist[barn1][barn2])
//            dist[barn1][barn2]=dist[barn2][barn1]=distance;
//    }
//    hascow[25]=false;
//
//    bool final[52];
//    priority_queue<dist_sum,vector<dist_sum>,greater<dist_sum> > pq;
//    for(int i=0;i<52;++i){
//        final[i]=false;
//    }
//    final[25]=true;
//    for(int i=0;i<52;++i)if(dist[25][i]<infinite){
//        pq.push(dist_sum(i));
//    }
//    while(!pq.empty()){
//        int from=pq.top().to;
//        pq.pop();
//        if(final[from])continue;
//        if(hascow[from]){
//            fout<<char('A'+from)<<' '<<dist[25][from]<<endl;
//            return 0;
//        }
//        final[from]=true;
//        for(int to=0;to<52;++to){
//            if(!final[to])if(dist[25][from]+dist[from][to]<dist[25][to]){
//                dist[25][to]=dist[25][from]+dist[from][to];
//                pq.push(dist_sum(to));
//            }
//        }
//    }
//
//    return 0;
//}

//==============================================================================
//...Version 2....using SPFA. To compare with Dijkstra's Algorithm, most of the code is a copy of ver1

#include<fstream>
#include<vector>
#include<queue>
using namespace std;

int dist[52][52];
bool hascow[52];
const int infinite=1000000000;
int d[52];

bool relax(int u, int v){
    int tmp=d[u]+dist[u][v];
    if(tmp<d[v]){
        d[v]=tmp;
        return true;
    }
    else return false;
}

int main(){
    ifstream fin("comehome.in");
    ofstream fout("comehome.out");
    int p;
    fin>>p;
    for(int i=0;i<52;++i){
        hascow[i]=false;
        for(int j=0;j<52;++j)dist[i][j]=infinite;
    }
    for(int i=0;i<p;++i){
        char barn1,barn2;
        int distance;
        fin>>barn1>>barn2>>distance;
        if(barn1<'a'){
            barn1-='A';
            hascow[barn1]=true;
        }
        else barn1=barn1-'a'+26;
        if(barn2<'a'){
            barn2-='A';
            hascow[barn2]=true;
        }
        else barn2=barn2-'a'+26;
        if(distance<dist[barn1][barn2])
            dist[barn1][barn2]=dist[barn2][barn1]=distance;
    }
    hascow[25]=false;

    bool inqueue[52];
    for(int i=0;i<52;++i){
        inqueue[i]=false;
        d[i]=infinite;
    }
    d[25]=0;
    queue<int> qu;
    qu.push(25);
    inqueue[25]=true;
    while(!qu.empty()){
        int u=qu.front();
        qu.pop();
        inqueue[u]=false;
        for(int v=0;v<52;++v){
            if(relax(u,v) && !inqueue[v]){
                qu.push(v);
                inqueue[v]=true;
            }
        }
    }
    int min=infinite;
    char pas;
    for(int i=0;i<25;++i){
        if(hascow[i] && d[i]<min){
            min=d[i];
            pas=i;
        }
    }
    fout<<char(pas+'A')<<' '<<d[pas]<<endl;

    return 0;
}