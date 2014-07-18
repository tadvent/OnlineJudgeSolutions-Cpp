// standard disjoin set

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

class diset{
	struct node{
		int parent;
		int height;
	};
	vector<node> v;
	int nDiset;
public:
	diset(){}
	diset(int N){
		reset(N);
	}
	void reset(int N){
		v.resize(N);
		for(int i=0; i<N; ++i){
			v[i].parent = i;
			v[i].height = 1;
		}
		nDiset = N;
	}
	int getid(int idx){
		if(v[idx].parent == idx) return idx;
		else return v[idx].parent = getid(v[idx].parent);
	}
	int getsize() const {
		return nDiset;
	}
	void merge(int id1, int id2){
		id1 = getid(id1);
		id2 = getid(id2);
		if(id1 == id2) return;
		else --nDiset;
		if(v[id1].height < v[id2].height){
			v[id1].parent = id2;	
		} else {
			v[id2].parent = id1;
			if(v[id1].height == v[id2].height)
				++v[id1].height;
		}
	}
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
	int nTown, nRoad, x, y;
	diset d;
	while(scanf("%d%d", &nTown, &nRoad) != EOF && nTown > 0){
		d.reset(nTown);
		while(nRoad--){
			scanf("%d%d", &x, &y);
			d.merge(x-1, y-1);
		}
		printf("%d\n", d.getsize() - 1);
	}
}

/////////////////////////////////////////////////////////////////////////////
// low performance ....
//#include<cstdio>
//#include<algorithm>
//using namespace std;
//
//int calc(){ // return -1 if finished
//    static int group[1000];
//    int nTown, nEdge, nGroup;
//
//    if(scanf("%d", &nTown) == EOF || nTown == 0)return -1;
//    for(int i=0; i<nTown; ++i)group[i] = i;
//    nGroup = nTown;
//    scanf("%d", &nEdge);
//    while(nEdge--){
//        int x, y, idx, idy, idm;
//        scanf("%d%d", &x,&y); --x,--y;
//        idx = x; idy = y;
//        while(idx != group[idx])idx = group[idx];
//        while(idy != group[idy])idy = group[idy];
//        if(idx == idy)continue;
//        --nGroup;
//        idm = min(idx, idy);
//        for(idx = group[x]; idx != idm; x = group[idx], idx = group[x])group[x] = idm;
//        for(idy = group[y]; idy != idm; y = group[idy], idy = group[y])group[y] = idm;
//    }
//    return nGroup - 1;
//}
//
//int main(){
//#ifndef ONLINE_JUDGE
//    freopen("i.txt", "r", stdin);
//    freopen("o.txt", "w", stdout);
//#endif
//    int rst;
//    while((rst = calc()) != -1)
//        printf("%d\n", rst);
//}
