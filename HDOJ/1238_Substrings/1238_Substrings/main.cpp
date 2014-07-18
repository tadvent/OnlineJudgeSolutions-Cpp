#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

const int maxn = 105;

//void build_sa(char line[], int len, int sa[]){
//    int i, j, k;
//    int acc[maxn]; // �ۼӣ�������������
//    int rnk[maxn]; // rank, ��Χ[0, len-1]
//}

class sub_less{
    char *p;
public:
    sub_less(char *Arr):p(Arr){}
    bool operator()(int i, int j) const {
        return p[i] < p[j];
    }
};

void build_sa(char line[], int n, int sa[]){
    int i, j, k, cl; // cl: cmp len
    int rnk[maxn];

    // init
    for(i=0; i<n; ++i)sa[i] = i;
    std::sort(sa, sa+n, sub_less(line));
    rnk[sa[0]] = 1;
    for(k=1, i=1; i<n; ++i)rnk[i] = (line[sa[i]] == line[sa[i-1]])? k: ++k;

    // sa Ϊ��һ�˵���������ȡֵ��Χ�� 0 ~ n-1
    // rnk ��ȡֵ��Χ�� 1 ~ n
    for(cl=1; rnk[sa[n-1]] < n; cl<<=1){
    }

    // sa Ϊ��һ�˵���������ȡֵ��Χ�� 0 ~ len-1
    // rank ��ȡֵ��Χ�� 1 ~ len
    do{
        int y[maxn]; // �������� ���������ý��
        int acc[maxn]; // �ۼƣ�������ǰ��εĻ�������

        // �����λ������������ϴ� sa[] �Ľ��
        for(j=0, i=n-cl; i<len; ++i)y[j++] = i;
        for(i=0; i<n; ++i)if(sa[i]>=cl)y[j++] = sa[i] - cl;

        // ��ǰ��λ�������
        memset(acc, 0, sizeof(acc));
        for(i=0; i<n; ++i)++acc[rnk[i]];
        for(i=1; i<n; ++i)acc[i] += acc[i-1];
        for(i=n-1; i>=0; --i)sa[--acc[y[i]]] = i;
    }while(rank[sa[n-1]] < n);
    // �� rank ���ֵ�ﵽ len ʱ��˵������ rank ֵ���ظ�
    // ��ô��������ıȽ��������ٽ����ˡ�
}

int main(){
    char line[maxn];
    int sfx_array[maxn], n;

    while(*gets(line)){
        n = strlen(line);
        build_sa(line, n, sfx_array);
        for(int i=0; i<n; ++i)
            printf("%d ", sfx_array[i]);
        puts("\n");
    }

    system("pause");
}
