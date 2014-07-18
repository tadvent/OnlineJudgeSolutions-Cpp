/*
ID: wjl1241
PROG: race3
LANG: C++
*/

// ��һ�ʼ򵥣������ dfs ��һ��·���ȣ�Ȼ������ȥ��·���е�ÿ���㣬���ȥ���������޷������յ㣬��õ㼴Ϊ���ɱ����
// �ڶ��ʣ���ʼʱ��������Ϊ���м�����ܹ��ƻش����ļ�������Ϊ�м�㡣ʵ����ֻҪ�����ܵ�ǰһ��·��ȥ���С�
// �������ȶԵ�һ��·�ܵ�������е�Ⱦɫ��Ȼ����м���������������޷�����Ⱦɫ���ĵ㣬��ô�˵���ܹ���Ϊ�м���㡣���� dfs �����㶨��

#include<fstream>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

vector< list<int> > graph;
vector<int> path;
vector<int> visited;
vector<int> unavoid;
vector<int> split;
int des;

bool dfs(int ver, vector<int> &tmpath){
    // if find tmpath to the last vertex, then return true; else return false.
    if(ver == des)return true;
    tmpath.push_back(ver);
    visited[ver] = 1;

    for(list<int>::iterator itr = graph[ver].begin(); itr != graph[ver].end(); ++itr){
        if(visited[*itr])continue;
        if(dfs(*itr, tmpath))return true;
    }
    tmpath.pop_back();
    return false;
}

int paintdes;
vector<int> painted;
void paint(int ver){
    if(ver == paintdes)return;
    painted[ver] = 1;
    for(list<int>::iterator itr = graph[ver].begin(); itr != graph[ver].end(); ++itr){
        if(painted[*itr])continue;
        paint(*itr);
    }
}

bool arrivepaint(int ver){
    if(painted[ver])return true;
    visited[ver] = 1;
    for(list<int>::iterator itr = graph[ver].begin(); itr != graph[ver].end(); ++itr){
        if(visited[*itr])continue;
        if(arrivepaint(*itr))return true;
    }
    return false;
}

int main(){
    int vertex;
    ifstream fin("race3.in");
    while(fin>>vertex && vertex != -1){
        graph.push_back(list<int>());
        while(vertex != -2){
            graph.back().push_back(vertex);
            fin>>vertex;
        }
    }

    path.reserve(graph.size());
    visited.assign(graph.size(), 0);
    des = graph.size() - 1;
    dfs(0, path);
    vector<int> tmpath;
    tmpath.reserve(graph.size());
    for(vector<int>::iterator itr = ++path.begin(); itr != path.end(); ++itr){
        visited.assign(graph.size(), 0);
        visited[*itr] = 1;
        tmpath.clear();
        if(!dfs(0, tmpath))unavoid.push_back(*itr);
    }
    sort(unavoid.begin(), unavoid.end());
    for(vector<int>::iterator itr = unavoid.begin(); itr != unavoid.end(); ++itr){
        paintdes = *itr;
        painted.assign(graph.size(), 0);
        paint(0);

        visited.assign(graph.size(), 0);
        if(!arrivepaint(*itr))split.push_back(*itr);
    }

    ofstream fout("race3.out");
    fout<<unavoid.size();
    for(vector<int>::iterator itr = unavoid.begin(); itr != unavoid.end(); ++itr)
        fout<<" "<< *itr;
    fout<<"\n"<<split.size();
    for(vector<int>::iterator itr = split.begin(); itr != split.end(); ++itr)
        fout<<" "<< *itr;
    fout<<"\n";
}
