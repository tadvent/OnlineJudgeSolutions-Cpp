// when iterate through a big list, it is much slower than vector or deque !!
#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

class Graph{
    struct Node{
        int dfsid; // 0: unvisited; -1: finished; >0: instack
        int lowid; // lowest dfsid that can reach from this node
        int setid; // belong to set[setid]
        vector<vector<Node>::iterator> out;
    };
    int dfsid, setid;
    vector<Node> nodes;
    vector<vector<Node>::iterator> stack;

    void dfs(vector<Node>::iterator it){
        stack.push_back(it);
        it->dfsid = it->lowid = ++dfsid;
        for(vector<vector<Node>::iterator>::const_iterator itr = it->out.begin();
            itr != it->out.end(); ++itr){
                if((*itr)->dfsid == -1)continue;
                if((*itr)->dfsid == 0)dfs(*itr);
                it->lowid = min(it->lowid, (*itr)->lowid);
        }
        if(it->dfsid == it->lowid){
            vector<Node>::iterator itr;
            do{
                itr = stack.back();
                stack.pop_back();
                itr->setid = setid;
            }while(itr != it);
            ++setid;
        }
        it->dfsid = -1;
    }
public:
    int calc(){
        // init
        for(vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){
            it->dfsid = 0;
        }
        dfsid = 0;
        setid = 0;

        // dfs
        for(vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){
            if(it->dfsid == 0)dfs(it);
        }

        if(setid == 1)return 0;

        // construct new graph
        vector<set<int> > net(setid);
        vector<int> in(setid, 0);
        for(vector<Node>::const_iterator it = nodes.begin(); it != nodes.end(); ++it){
            int u = it->setid;
            for(vector<vector<Node>::iterator>::const_iterator it2 = it->out.begin();
                it2 != it->out.end(); ++it2){
                    int v = (*it2)->setid;
                    if(u != v && net[u].insert(v).second){
                        ++in[v];
                    }
            }
        }

        // count
        int in0 = 0, out0 = 0;
        for(int i=0; i<(int)in.size(); ++i){
            if(in[i] == 0)++in0;
            if(net[i].empty())++out0;
        }
        return max(in0, out0);
    }
    void reset(int n){
        nodes.resize(n);
        stack.clear();
        stack.reserve(n);
    }
    void add(int from, int to){
        nodes[from-1].out.push_back(nodes.begin() + to-1);
    }
    void clear(){
        nodes.clear();
    }
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int t, n, m, x, y;
    Graph g;
    scanf("%d", &t);
    while(t--){
        scanf("%d%d", &n, &m);
        g.reset(n);
        while(m--){
            scanf("%d%d", &x, &y);
            g.add(x, y);
        }
        printf("%d\n", g.calc());
        g.clear();
    }
}
