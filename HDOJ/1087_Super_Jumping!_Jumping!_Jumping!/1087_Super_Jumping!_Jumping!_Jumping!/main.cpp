#include<cstdio>
#include<map>
using namespace std;

int seq[1000], N;
// map[val] ��ʾĿǰ��֪�Ľ�β�� <= val ��������к�
// �� map[val] ��ǰһ��ֵ + seq[i] ������ seq[i] ��β��������к�
// Ȼ����� map �� > seq[i] ��ֵ��
map<int, int> val_sum;

int calc(){
    int maxsum = 0;
    val_sum.clear();
    val_sum.insert(make_pair(0, 0));

    for(int i=0; i<N; ++i){
        int newsum;
        map<int, int>::iterator it = val_sum.lower_bound(seq[i]), prev;
        prev = it; --prev;
        newsum = prev->second + seq[i];
        if(it != val_sum.end() && it->first == seq[i]){
            if(newsum > it->second){
                it->second = newsum;
            } else continue;
        } else {
            it = val_sum.insert(it, make_pair(seq[i], newsum));
        }
        if(newsum > maxsum) maxsum = newsum;
        if(it != val_sum.end()){
            ++it;
            while(it != val_sum.end() && newsum >= it->second)
                val_sum.erase(it++);
        }
    }
    return maxsum;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(scanf("%d", &N) != EOF && N){
        for(int i=0; i<N; ++i)scanf("%d", seq+i);
        printf("%d\n", calc());
    }
}
