#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    int N, M;
    while(scanf("%d%d", &N, &M) != EOF){
        vector<int> vec(N);
        for(int i=0; i<N; ++i)vec[i] = i+1;
        while(--M)
            next_permutation(vec.begin(), vec.end());
        printf("%d", vec.front());
        for(vector<int>::const_iterator it=++vec.begin();
            it != vec.end(); ++it)
            printf(" %d", *it);
        putchar('\n');
    }
}
