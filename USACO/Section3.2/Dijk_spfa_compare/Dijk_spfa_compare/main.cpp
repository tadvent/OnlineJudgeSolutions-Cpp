#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<deque>
using namespace std;
 
const int infinity=1000000000;
int N;
vector< vector<int> > vAdjMatrix;
vector< vector<int> > dijkstra;
vector< vector<int> > spfa;
vector< vector<int> > spfa_opt1;
vector< vector<int> > spfa_opt2;
vector< vector<int> > floyd;
 
inline bool relax(int u, int v, vector<int> &d){
    int nlen=d[u]+vAdjMatrix[u][v];
    if(nlen<d[v]){
        d[v]=nlen;
        return true;
    }
    return false;
}
 
void DoFloyd(){
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)
        floyd[i][j]=vAdjMatrix[i][j];
 
    int newlen;
    for(int k=0;k<N;++k)
        for(int u=0;u<N;++u)
            for(int v=0;v<N;++v)
                if((newlen=floyd[u][k]+floyd[k][v])<floyd[u][v])
                    floyd[u][v]=floyd[v][u]=newlen;
}
 
void DoSPFA(){
    for(int iSource=0;iSource<N;++iSource){
        queue<int> Q;
        vector<bool> IsInQ(N,false);
 
        //optimizing begin:
        //if(iSource>0){
        //    int iShort=0;
        //    for(int k=1;k<iSource;++k)if(spfa[k][iSource]<spfa[iShort][iSource])
        //        iShort=k;
        //    for(int iDes=0;iDes<N;++iDes)
        //        spfa[iSource][iDes]=spfa[iShort][iSource]+spfa[iShort][iDes];
        //}
        //optimizing end.
 
        Q.push(iSource);
        IsInQ[iSource]=true;
        spfa[iSource][iSource]=0;
        while(!Q.empty()){
            int u=Q.front();
            Q.pop();
            IsInQ[u]=false;
            for(int v=0;v<N;++v)
                if(relax(u,v,spfa[iSource]) && !IsInQ[v]){
                    Q.push(v);
                    IsInQ[v]=true;
                }
        }
    }
}

void DoSPFA_opt1(){
    for(int iSource=0;iSource<N;++iSource){
        deque<int> Q;
        vector<bool> IsInQ(N,false);
 
        //optimizing begin:
        //if(iSource>0){
        //    int iShort=0;
        //    for(int k=1;k<iSource;++k)if(spfa_opt1[k][iSource]<spfa_opt1[iShort][iSource])
        //        iShort=k;
        //    for(int iDes=0;iDes<N;++iDes)
        //        spfa_opt1[iSource][iDes]=spfa_opt1[iShort][iSource]+spfa_opt1[iShort][iDes];
        //}
        //optimizing end.
 
        Q.push_back(iSource);
        IsInQ[iSource]=true;
        spfa_opt1[iSource][iSource]=0;
        while(!Q.empty()){
            int u=Q.front();
            Q.pop_front();
            IsInQ[u]=false;
            for(int v=0;v<N;++v)
                if(relax(u,v,spfa_opt1[iSource]) && !IsInQ[v]){
                    if(!Q.empty() && spfa_opt1[iSource][v] <= spfa_opt1[iSource][Q.front()])
                        Q.push_front(v);
                    else Q.push_back(v);
                    IsInQ[v]=true;
                }
        }
    }
}

inline int relax2(int u, int v, vector<int> &d){
    int sub, nlen=d[u]+vAdjMatrix[u][v];
    if((sub = nlen-d[v]) < 0){
        d[v]=nlen;
        return sub;
    }
    else return 0;
}
 //使用 LLL 优化的话得跟踪队列中所有终点的距离和，这恐怕得改写 relax 函数，使之能返回
 //本次松弛操作缩短了多少距离 ...
void DoSPFA_opt2(){
    for(int iSource=0;iSource<N;++iSource){
        deque<int> Q;
        vector<bool> IsInQ(N,false);
        int sum = 0;
 
        //optimizing begin:
        //if(iSource>0){
        //    int iShort=0;
        //    for(int k=1;k<iSource;++k)if(spfa_opt2[k][iSource]<spfa_opt2[iShort][iSource])
        //        iShort=k;
        //    for(int iDes=0;iDes<N;++iDes)
        //        spfa_opt2[iSource][iDes]=spfa_opt2[iShort][iSource]+spfa_opt2[iShort][iDes];
        //}
        //optimizing end.
 
        Q.push_back(iSource);
        IsInQ[iSource]=true;
        spfa_opt2[iSource][iSource]=0;
        while(!Q.empty()){
            int u;
            while(spfa_opt2[iSource][u=Q.front()] * int(Q.size()) > sum){
                Q.pop_front();
                Q.push_back(u);
            }
            sum -= spfa_opt2[iSource][u];
            Q.pop_front();
            IsInQ[u]=false;
            for(int v=0;v<N;++v){
                int sub;
                if(sub = relax2(u,v,spfa_opt2[iSource])){
                    if(IsInQ[v])
                        sum += sub;
                    else {
                        if(!Q.empty() && spfa_opt2[iSource][v] <= spfa_opt2[iSource][Q.front()])
                            Q.push_front(v);
                        else Q.push_back(v);
                        sum += spfa_opt2[iSource][v];
                        IsInQ[v]=true;
                    }
                }
            }
        }
    }
}
 
void DoDijkstra(){
    struct ver_weight{
        int vertex;
        int weight;
        ver_weight(int Vertex, int Weight):vertex(Vertex),weight(Weight){}
        bool operator>(const ver_weight &comp)const{
            return weight>comp.weight;
        }
    };
 
    for(int iSource=0;iSource<N;++iSource){
        vector<bool> IsInset(N,false);
        int setcount=0;
        priority_queue< ver_weight,vector<ver_weight>,greater<ver_weight> > pq;
 
        IsInset[iSource]=true;
        ++setcount;
        for(int v=0;v<N;++v)if(vAdjMatrix[iSource][v]<infinity){
            dijkstra[iSource][v]=vAdjMatrix[iSource][v];
            pq.push(ver_weight(v,dijkstra[iSource][v]));
        }

        while(setcount<N){
            ver_weight uw=pq.top();
            pq.pop();
            if(IsInset[uw.vertex])continue;
            IsInset[uw.vertex]=true;
            ++setcount;
            for(int v=0;v<N;++v)if(relax(uw.vertex,v,dijkstra[iSource]))
                pq.push(ver_weight(v,dijkstra[iSource][v]));
        }
    }
}
 
int main(){
    ofstream fout("out.txt");
    cout<<"Input the number of vertexes: ";
    cin>>N;
    vAdjMatrix.resize(N,vector<int>(N,infinity));
    floyd.resize(N,vector<int>(N,infinity));
    spfa.resize(N,vector<int>(N,infinity));
    spfa_opt1.resize(N,vector<int>(N,infinity));
    spfa_opt2.resize(N,vector<int>(N,infinity));
    dijkstra.resize(N,vector<int>(N,infinity));

    fout<<"Number of vertexes: "<<N<<'\n'<<endl;
 
    //create the graph
    srand(unsigned(time(NULL)));
    for(int i=0;i<N;++i)for(int j=0;j<i;++j)
        vAdjMatrix[i][j]=vAdjMatrix[j][i]=rand();
    fout.precision(3);
    fout.setf(ios::fixed);
    clock_t start,finish;
 
    //floyd
    cout<<"Floyd start ... \n";
    start=clock();
    DoFloyd();
    finish=clock();
    cout<<"Floyd end.\n\n";
    fout<<"Floyd consumed:     "<<(double)(finish-start)/CLOCKS_PER_SEC<<" secs\n";
 
    //SPFA
    cout<<"SPFA start ... \n";
    start=clock();
    DoSPFA();
    finish=clock();
    cout<<"SPFA end.\n\n";
    fout<<"SPFA consumed:      "<<(double)(finish-start)/CLOCKS_PER_SEC<<" secs\n";
 
    for(int i=0;i<N;++i)for(int j=0;j<i;++j)
        if(floyd[i][j]!=spfa[i][j]){
            fout<<"SPFA worked wrong!\n";
            goto SPFA_end;
        }
 
SPFA_end:

    //SPFA opt1 (SLF)
    cout<<"SPFA opt1 start ... \n";
    start=clock();
    DoSPFA_opt1();
    finish=clock();
    cout<<"SPFA op1 end.\n\n";
    fout<<"SPFA(opt1) consumed: "<<(double)(finish-start)/CLOCKS_PER_SEC<<" secs\n";
 
    for(int i=0;i<N;++i)for(int j=0;j<i;++j)
        if(floyd[i][j]!=spfa_opt1[i][j]){
            fout<<"SPFA opt1 worked wrong!\n";
            goto SPFAopt1_end;
        }
 
SPFAopt1_end:

    //SPFA opt2 (SLF/LLL)
    cout<<"SPFA opt2 start ... \n";
    start=clock();
    DoSPFA_opt2();
    finish=clock();
    cout<<"SPFA op2 end.\n\n";
    fout<<"SPFA(opt2) consumed: "<<(double)(finish-start)/CLOCKS_PER_SEC<<" secs\n";
 
    for(int i=0;i<N;++i)for(int j=0;j<i;++j)
        if(floyd[i][j]!=spfa_opt2[i][j]){
            fout<<"SPFA opt2 worked wrong!\n";
            goto SPFAopt2_end;
        }
 
SPFAopt2_end:
 
    //Dijkstra
    cout<<"Dijkstra start ... \n";
    start=clock();
    DoDijkstra();
    finish=clock();
    cout<<"Dijkstra end.\n";
    fout<<"Dijkstra consumed:  "<<(double)(finish-start)/CLOCKS_PER_SEC<<" secs\n";
 
    for(int i=0;i<N;++i)for(int j=0;j<i;++j)
        if(floyd[i][j]!=dijkstra[i][j]){
            fout<<"Dijkstra worked wrong!\n";
            goto Dijk_end;
        }
 
Dijk_end:
 
    //system("pause");
    return 0;
}