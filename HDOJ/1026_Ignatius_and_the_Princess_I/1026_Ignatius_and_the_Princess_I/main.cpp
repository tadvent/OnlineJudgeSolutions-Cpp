#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn = 104;
char castle[maxn][maxn];
int width, height;

bool input(){
    if(scanf("%d%d", &height, &width) == EOF)return false;
    for(int i=0; i<=width+1; ++i)
        castle[0][i] = castle[height+1][i] = 'X';
    for(int i=0; i<=height+1; ++i)
        castle[i][0] = castle[i][width+1] = 'X';
    for(int i=1; i<=height; ++i)for(int j=1; j<=width; ++j)
        scanf(" %c", &castle[i][j]);
    return true;
}

int minpath(vector<pair<int,int> > &path){
    typedef pair<int, pair<int,int> > TimePos;
    TimePos pre[maxn][maxn];
    for(int i=0; i<maxn; ++i)for(int j=0; j<maxn; ++j){
        const TimePos init(INT_MAX, make_pair(0,0));
        pre[i][j] = init;
    }
    vector<TimePos> pq; pq.reserve(maxn*maxn);
    const greater<TimePos> gt;
    const pair<int,int> des(height, width);
    const int dir[4][2] = {1,0,0,1,-1,0,0,-1};

    pq.push_back(make_pair(0, make_pair(1,1)));
    while(!pq.empty()){
        pop_heap(pq.begin(), pq.end(), gt);
        TimePos top = pq.back();
        pq.pop_back();

        if(top.second == des){
            const pair<int,int> st(1,1);
            path.clear();
            while(top.second != st){
                path.push_back(top.second);
                top = pre[top.second.first][top.second.second];
            }
            return pre[des.first][des.second].first;
        }
        for(int d=0; d<4; ++d){
            int x=top.second.first+dir[d][0], y=top.second.second+dir[d][1];
            int time;
            switch(castle[x][y]){
                case 'X': break;
                case '.':
                    if(top.first + 1 < pre[x][y].first){
                        pre[x][y].first = top.first + 1;
                        pre[x][y].second = top.second;
                        pq.push_back(make_pair(top.first+1, make_pair(x,y)));
                        push_heap(pq.begin(), pq.end(), gt);
                    }
                    break;
                default:  // '1' ~ '9'
                    time = castle[x][y] - '0' + 1;
                    if(top.first+time < pre[x][y].first){
                        pre[x][y].first = top.first+time;
                        pre[x][y].second = top.second;
                        pq.push_back(make_pair(top.first+time, make_pair(x,y)));
                        push_heap(pq.begin(), pq.end(), gt);
                    }
                    break;
            }
        }
    }
    return 0;
}

void outpath(const vector<pair<int,int> > &path){
    int s = 1;
    pair<int,int> last(1,1);
    for(vector<pair<int,int> >::const_reverse_iterator it = path.rbegin();
        it != path.rend(); ++it){
            printf("%ds:(%d,%d)->(%d,%d)\n", s++,
                last.first-1, last.second-1, it->first-1, it->second-1);
            last = *it;
            int ts;
            if(castle[it->first][it->second] == '.'){
                ts = 0;
            } else {
                ts = castle[it->first][it->second] - '0';
            }
            while(ts--){
                printf("%ds:FIGHT AT (%d,%d)\n", s++, it->first-1, it->second-1);
            }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(input()){
        int rst;
        vector<pair<int,int> > path;
        if((rst = minpath(path)) > 0){
            printf("It takes %d seconds to reach the target position, let me show you the way.\n", rst);
            outpath(path);
        } else {
            printf("God please help our poor hero.\n");
        }
        printf("FINISH\n");
    }
}
