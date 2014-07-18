#include<cstdio>
#include<vector>
#include<list>
#include<utility>
using namespace std;

class Test{
    struct block{
        int x, y, z; // x<=y  z is height
        list<int> lowers; // block idxs that can be put under this block
        int maxh; // max height this block and the lowers can make (including this)
        block(){}
        block(const block &r):x(r.x), y(r.y), z(r.z){}
        block(int X,int Y, int Z):x(X), y(Y), z(Z){
            if(x>y)swap(x,y);
        }
        bool operator<(const block &r)const{
            return x<r.x && y<r.y;
        }
        bool operator==(const block &r)const{
            return x==r.x && y==r.y && z==r.z;
        }
    };
    vector<block> vblks;
    void connect(){ // fill block::lowers
        for(int i=0; i<(int)vblks.size(); ++i){
            vblks[i].lowers.clear();
            vblks[i].maxh = -1;
            for(int j=0; j<(int)vblks.size(); ++j)
                if(vblks[i] < vblks[j])vblks[i].lowers.push_back(j);
        }
    }
    int height(int idx){
        if(vblks[idx].maxh == -1){
            int maxh = 0;
            for(list<int>::const_iterator it = vblks[idx].lowers.begin();
                it != vblks[idx].lowers.end(); ++it){
                    maxh = max(maxh, height(*it));
            }
            vblks[idx].maxh = vblks[idx].z + maxh;
        }
        return vblks[idx].maxh;
    }
public:
    void reserve(int n){
        vblks.reserve(3*n+1);
    }
    void add(int x, int y, int z){
        vblks.push_back(block(x,y,z));
        if(x == y && y == z)return;
        if(x == y){
            vblks.push_back(block(x,z,y));
        } else if(y == z){
            vblks.push_back(block(y,z,x));
        } else {
            vblks.push_back(block(y,z,x));
            vblks.push_back(block(z,x,y));
        }
    }
    int maxheight(){
        using namespace std::rel_ops;
        if(vblks.back() != block(0,0,0))
            vblks.push_back(block(0,0,0));
        connect();
        return height(vblks.size()-1);
    }
    void clear(){
        vblks.clear();
    }
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    Test t;
    int n, idx = 1;
    while(scanf("%d", &n) != EOF && n){
        t.reserve(n);
        while(n--){
            int x,y,z;
            scanf("%d%d%d", &x,&y,&z);
            t.add(x,y,z);
        }
        printf("Case %d: maximum height = %d\n", idx++, t.maxheight());
        t.clear();
    }
}
