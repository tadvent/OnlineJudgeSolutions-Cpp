/*
ID: wjl1241
PROG: fence6
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;

const int infinity = 100000000;

struct edge {
    int len;
    vector<int> end1;
    vector<int> end2;

    bool IsOnePoint(int idx1, int idx2){
        int cnt = 0;
        for(vector<int>::iterator itr=end1.begin();itr!=end1.end();++itr){
            if(*itr == idx1)++cnt;
            else if(*itr == idx2)++cnt;
            if(cnt>=2)return true;
        }
        if(cnt == 1)return false;
        for(vector<int>::iterator itr=end2.begin();itr!=end2.end();++itr){
            if(*itr == idx1)++cnt;
            else if(*itr == idx2)++cnt;
            if(cnt>=2)return true;
        }
        return false;
    }
};

vector<edge> vEdges;
vector< vector<int> > matrix;
vector< vector<int> > graph;

int main(){
    ifstream fin("fence6.in");
    ofstream fout("fence6.out");

    int nEdge;
    fin>>nEdge;
    vector<bool> flag(nEdge+1,false);
    vEdges.resize(nEdge+1);
    matrix.resize(nEdge+1,vector<int>(nEdge+1,infinity));
    graph.resize(nEdge+1,vector<int>(nEdge+1,infinity));
    for(int i=0;i<nEdge;++i){
        int idx,len,nend1,nend2;
        fin>>idx>>len>>nend1>>nend2;
        vEdges[idx].len = len;
        flag[idx] = true;
        for(int j=0;j<nend1;++j){
            int joint;
            fin>>joint;
            vEdges[idx].end1.push_back(joint);
            if(flag[joint])
                matrix[joint][idx]=matrix[idx][joint]=vEdges[idx].len + vEdges[joint].len;
        }
        for(int j=0;j<nend2;++j){
            int joint;
            fin>>joint;
            vEdges[idx].end2.push_back(joint);
            if(flag[joint])
                matrix[joint][idx]=matrix[idx][joint]=vEdges[idx].len + vEdges[joint].len;
        }
    }

    for(int i=1;i<=nEdge;++i)for(int j=1;j<=nEdge;++j)graph[i][j]=matrix[i][j];

    int mincircle = infinity;
    for(int k=1;k<=nEdge;++k){
        for(int i=1;i<k;++i)
            for(int j=1;j<i;++j){
                if(vEdges[i].IsOnePoint(j,k))continue;
                mincircle = min(mincircle,matrix[i][j]+graph[j][k]+graph[k][i]);
            }
        for(int i=1;i<=nEdge;++i)
            for(int j=1;j<i;++j){
                int temp = matrix[i][k] + matrix[k][j];
                if(matrix[i][j] > temp)
                    matrix[j][i]=matrix[i][j]=temp;
            }
    }

    fout<< mincircle/2 <<endl;
    return 0;
}
