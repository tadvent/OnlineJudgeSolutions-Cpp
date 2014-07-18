/*
ID: wjl1241
LANG: C++
TASK: schlnet
*/

#include<cstdio>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

struct idlist: list<int>{
    int in, out;
    idlist():in(0), out(0){}
};
vector<list<int> > onet;
vector<idlist> net;
int in0, out0;

void input(){
    int n, id;
    FILE *fin = fopen("schlnet.in", "r");
    fscanf(fin, "%d", &n);
    onet.resize(n);
    for(int i=0; i<n; ++i){
        while(fscanf(fin, "%d", &id)!= EOF && id != 0){
            onet[i].push_back(id-1);
        }
    }
    fclose(fin);
}

int dfidx, setidx;
vector<int> belong, low, dfn, state; // state: 0: unvisited; 1: instack 2:finished
vector<int> stack;
void dfs(int u){
    stack.push_back(u);
    dfn[u] = low[u] = dfidx++;
    state[u] = 1;
    for(list<int>::const_iterator it = onet[u].begin();
        it != onet[u].end(); ++it){
            if(state[*it] == 2)continue;
            if(!state[*it])dfs(*it);
            low[u] = min(low[u], low[*it]);
    }

    if(dfn[u] == low[u]){
        int v;
        do {
            v = stack.back();
            stack.pop_back();
            belong[v] = setidx;
        }while(v != u);
        ++setidx;
    }
    state[u] = 2;
}
void reduce(){
    dfidx = 0;
    setidx = 0;
    belong.assign(onet.size(), -1);
    low.assign(onet.size(), 0);
    dfn = state = low;
    stack.reserve(onet.size());
    for(int i=0; i<(int)onet.size(); ++i)
        if(!state[i])dfs(i);
}

void cnt(){
    net.resize(setidx);
    for(int i=0; i<(int)onet.size(); ++i){
        for(list<int>::const_iterator it = onet[i].begin();
            it != onet[i].end(); ++it){
                if(belong[i] != belong[*it] &&
                    find(net[belong[i]].begin(), net[belong[i]].end(), belong[*it])
                    == net[belong[i]].end()){
                        net[belong[i]].push_back(belong[*it]);
                        ++net[belong[i]].out;
                        ++net[belong[*it]].in;
                }
        }
    }
    in0 = out0 = 0;
    for(int i=0; i<(int)net.size(); ++i){
        if(net[i].in == 0)++in0;
        if(net[i].out == 0)++out0;
    }
}

void output(){
    FILE *fout = fopen("schlnet.out", "w");
    fprintf(fout, "%d\n%d\n", in0, (net.size() == 1)?0:max(in0, out0));
    fclose(fout);
}

int main(){
    input();
    reduce();
    cnt();
    output();
}



////////////////////////////////////////////////////////////////
// standard program
//#include <stdio.h>
//
//#define MAX_N 100
//
//int n;
//int conn[MAX_N][MAX_N]; //[from][to]
//
//int is_top[MAX_N];
//int has_top[MAX_N];
//int touched[MAX_N];
//int reachable[MAX_N];
//
//int max(int a, int b)
//{
//    return a>b?a:b;
//}
//
//void fill_from(int x)
//{
//    if(touched[x])
//        return;
//  
//    is_top[x] = 0;
//    has_top[x] = 1;
//    touched[x] = 1;
//  
//    for(int i=0; i<n; i++)
//        if(conn[x][i])
//            fill_from(i);
//}
//
//int count_tops()
//{
//    for(int i=0; i<n; i++) {
//        has_top[i] = 0;
//        is_top[i] = 0;
//    }
//  
//    while(1) {
//    
//    // find one that has no top
//      int i;
//    
//      for(i=0; i<n; i++)
//          if(!has_top[i])
//              break;
//    
//      if(i == n)
//          break;
//    
//      for(int j=0; j<n; j++)
//          touched[j] = 0;
//    
//      // flood-fill all descendents of it to have a top, and not be a top
//      fill_from(i);
//    
//      is_top[i] = 1;
//    }
//  
//    int count = 0;
//  
//    for(int i=0; i<n; i++)
//        if(is_top[i])
//            count++;
//  
//    return count;
//}
//
//void fill_reachable(int x)
//{
//    if(reachable[x])
//        return;
//  
//    reachable[x] = 1;
//  
//    for(int i=0; i<n; i++)
//        if(conn[x][i])
//            fill_reachable(i);
//}
//
//// check to see if the graph is already fully connected
//int none_needed()
//{
//    for(int i=0; i<n; i++) {
//      for(int j=0; j<n; j++)
//          reachable[j] = 0;
//      fill_reachable(i);
//    
//      for(int j=0; j<n; j++)
//          if(!reachable[j])
//              return 0;
//    }
//    return 1;
//}
//      
//
//int main()
//{
//    FILE *in;
//  
//    in = fopen("schlnet.in", "r");
//  
//    fscanf(in, "%d", &n);
//  
//    for(int i=0; i<n; i++) {
//        while(1) {
//            int to;
//            fscanf(in, "%d", &to);
//            if(to == 0)
//                break;
//            conn[i][to-1] = 1;
//        }
//    }
//    fclose(in);
//  
//    int tops = count_tops();
//  
//    // reverse the graph
//    for(int i=0; i<n; i++)
//        for(int j=i+1; j<n; j++) {
//            int temp = conn[i][j];
//            conn[i][j] = conn[j][i];
//            conn[j][i] = temp;
//        }
//  
//    int bottoms = count_tops();
//    int b;
//  
//    if(none_needed())
//        b = 0;
//    else
//        b = max(tops, bottoms);
//  
//    FILE *out;
//    out = fopen("schlnet.out", "w");
//    fprintf(out, "%d\n%d\n", tops, b);
//    fclose(out);
//    return 0;
//}

