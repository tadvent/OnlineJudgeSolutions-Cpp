/*
ID: wjl1241
PROG: butter
LANG: C++
*/

//#include<fstream>
//#include<vector>
//#include<list>
//#include<queue>
//using namespace std;
//
//const int infinite=1000000000;
//int nCow,nPasture,nConnect;
//vector<int> vCowsAt;
//vector< list< pair<int,int> > > vPasAjt;
//
//inline bool relax(int u, int v, int weight, vector<int> &d){
//    int newlength=d[u]+weight;
//    if(newlength<d[v]){
//        d[v]=newlength;
//        return true;
//    }
//    return false;
//}
//
//int CalPathSum(int iSource){
//    queue<int> Q;
//    vector<bool> IsInQ(nPasture);
//    vector<int> d(nPasture,infinite);
//
//    d[iSource]=0;
//    Q.push(iSource);
//    IsInQ[iSource]=true;
//
//    while(!Q.empty()){
//        int u=Q.front();
//        Q.pop();
//        IsInQ[u]=false;
//        for(list< pair<int,int> >::iterator itr=vPasAjt[u].begin();itr!=vPasAjt[u].end();++itr){
//            int v=itr->first;
//            if(relax(u,v,itr->second,d) && !IsInQ[v]){
//                Q.push(v);
//                IsInQ[v]=true;
//            }
//        }
//    }
//
//    int sum=0;
//    for(int i=0;i<nCow;++i)sum+=d[vCowsAt[i]];
//    return sum;
//}
//
//int main(){
//    ifstream fin("butter.in");
//    ofstream fout("butter.out");
//    fin>>nCow>>nPasture>>nConnect;
//    vCowsAt.resize(nCow);
//    vPasAjt.resize(nPasture);
//
//    for(int i=0;i<nCow;++i){
//        int iPasture;
//        fin>>iPasture;
//        vCowsAt[i]=iPasture-1;
//    }
//    for(int i=0;i<nConnect;++i){
//        int u,v,distance;
//        fin>>u>>v>>distance;
//        vPasAjt[u-1].push_back(pair<int,int>(v-1,distance));
//        vPasAjt[v-1].push_back(pair<int,int>(u-1,distance));
//    }
//
//    int minpath=infinite;
//    for(int i=0;i<nPasture;++i)
//        minpath=min(minpath,CalPathSum(i));
//
//    fout<<minpath<<endl;
//}


//===========================================================================
//===========================================================================
// Version 2..........SPFA with optimized

#include<fstream>
#include<vector>
#include<list>
#include<queue>
using namespace std;

const int infinite=1000000000;
int nCow,nPasture,nConnect;
vector<int> vCowsAt;
vector< list< pair<int,int> > > vPasAjt;
vector< vector<int> > vDistMatrix;

inline bool relax(int u, int v, int weight, vector<int> &d){
    int newlength=d[u]+weight;
    if(newlength<d[v]){
        d[v]=newlength;
        return true;
    }
    return false;
}

int CalPathSum(int iSource){
    queue<int> Q;
    vector<bool> IsInQ(nPasture);

// optimizing begin:
    if(iSource>0){
        int iShort=0;
        for(int k=1;k<iSource;++k)if(vDistMatrix[k][iSource]<vDistMatrix[iShort][iSource])
            iShort=k;
        for(int iDes=0;iDes<nPasture;++iDes)
            vDistMatrix[iSource][iDes]=vDistMatrix[iShort][iSource]+vDistMatrix[iShort][iDes];
    }
// optimizing end.

    vDistMatrix[iSource][iSource]=0;
    Q.push(iSource);
    IsInQ[iSource]=true;

    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        IsInQ[u]=false;
        for(list< pair<int,int> >::iterator itr=vPasAjt[u].begin();itr!=vPasAjt[u].end();++itr){
            int v=itr->first;
            if(relax(u,v,itr->second,vDistMatrix[iSource]) && !IsInQ[v]){
                Q.push(v);
                IsInQ[v]=true;
            }
        }
    }

    int sum=0;
    for(int i=0;i<nCow;++i)sum+=vDistMatrix[iSource][vCowsAt[i]];
    return sum;
}

int main(){
    ifstream fin("butter.in");
    ofstream fout("butter.out");
    fin>>nCow>>nPasture>>nConnect;
    vCowsAt.resize(nCow);
    vPasAjt.resize(nPasture);
    vDistMatrix.resize(nPasture);
    for(int i=0;i<nPasture;++i)
        vDistMatrix[i].resize(nPasture,infinite);

    for(int i=0;i<nCow;++i){
        int iPasture;
        fin>>iPasture;
        vCowsAt[i]=iPasture-1;
    }
    for(int i=0;i<nConnect;++i){
        int u,v,distance;
        fin>>u>>v>>distance;
        vPasAjt[u-1].push_back(pair<int,int>(v-1,distance));
        vPasAjt[v-1].push_back(pair<int,int>(u-1,distance));
    }

    int minpath=infinite;
    for(int i=0;i<nPasture;++i)
        minpath=min(minpath,CalPathSum(i));

    fout<<minpath<<endl;
}