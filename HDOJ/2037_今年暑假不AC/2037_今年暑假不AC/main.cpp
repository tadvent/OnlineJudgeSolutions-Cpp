#include<cstdlib>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
typedef vector<pair<int,int> > Times;
Times t;
int maxtv(){
    int cnt = 1, next = INT_MAX;
    sort(t.begin(), t.end());
    for(Times::iterator it=t.begin(); it != t.end(); ++it){
        if(it->first >= next){
            ++cnt; next = INT_MAX;
        }
        next = min(next, it->second);
    }
    return cnt;
}
int main(){
    int n, a, b;
    while(scanf("%d", &n) != EOF && n){
        t.clear();
        while(n--){
            scanf("%d%d", &a, &b);
            t.push_back(make_pair(a, b));
        }
        printf("%d\n", maxtv());
    }
}