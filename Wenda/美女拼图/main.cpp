#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>
using namespace std;

queue< pair<vector<int>, vector<int> > > Q; // first -> state; second -> steps; second[0] -> 0 current pos
vector<int> initState(9);
vector<int> ans_steps;
set<int> visited;

void input(){
    Q.push(pair<vector<int>, vector<int> >());
    for(int i=0; i<9; ++i){
        scanf("%d", &initState[i]);
        if(initState[i] == 0) Q.front().second.push_back(i);
    }
    Q.front().first = initState;
    visited.clear();
}

bool test(vector<int> &state){
    for(int i=0; i<8; ++i) if(state[i] != i+1) return false;
    return state[8] == 0;
}

int st2num(const vector<int> &state){
    int ret = 0;
    for(int i=0; i<9; ++i){
        ret = ret * 10 + state[i];
    }
    return ret;
}

bool step(pair<vector<int>, vector<int> > cs, int dir){
    int newpos = cs.second[0] + dir;
    if(newpos < 0 || newpos >= 9) return false;
    swap(cs.first[cs.second[0]], cs.first[newpos]);

    cs.second.push_back(dir);
    cs.second[0] = newpos;
    if(newpos == 8 && test(cs.first)){
        ans_steps.assign(cs.second.begin()+1, cs.second.end());
        return true;
    }
    Q.push(cs);
    return false;
}

bool calc(){
    if(test(initState)){
        ans_steps.clear();
        return true;
    }
    while(!Q.empty()){
        int num = st2num(Q.front().first);
        if(visited.find(num) != visited.end()){
            Q.pop();
            continue;
        }
        visited.insert(num);

        if(step(Q.front(), 1)) return true;
        if(step(Q.front(), -1)) return true;
        if(step(Q.front(), 3)) return true;
        if(step(Q.front(), -3)) return true;
        Q.pop();
    }
    return false;
}

void output(){
    printf("%d", initState[0]);
    for(int i=1; i<9; ++i)printf(" %d", initState[i]);putchar('\n');
    int zpos = 0;
    for(int i=0; i<9; ++i) if(initState[i] == 0){
        zpos = i;
        break;
    }
    for(int i=0; i<ans_steps.size(); ++i){
        int newpos = zpos + ans_steps[i];
        swap(initState[zpos], initState[newpos]);
        zpos = newpos;
        printf("%d", initState[0]);
        for(int j=1; j<9; ++j)printf(" %d", initState[j]);putchar('\n');
    }
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    input();
    if(calc()){
        output();
    }
}
