#include<cstdio>
#include<utility>
#include<map>
using namespace std;

class Moves{
    multimap<int, int> movs;
    void one_move(){
        int st = 0;
        multimap<int, int>::iterator it;
        while((it = movs.lower_bound(st)) != movs.end()){
            st = it->second;
            movs.erase(it);
        }
    }
public:
    void add(int from, int to){
        if(from > to)swap(from, to);
        movs.insert(make_pair((from-1)/2, (to-1)/2+1));
    }
    int calc(){
        int time = 0;
        while(!movs.empty()){
            one_move();
            time += 10;
        }
        return time;
    }
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int t, n;
    Moves obj;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        while(n--){
            int from, to;
            scanf("%d %d", &from, &to);
            obj.add(from, to);
        }
        printf("%d\n", obj.calc());
    }
}
