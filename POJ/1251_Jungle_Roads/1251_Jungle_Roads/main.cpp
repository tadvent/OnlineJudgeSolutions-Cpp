#include<stdio.h>
int roads[1000][1000];
int lowcost[1000];
#define MAX 65535
void init(){//��ʼ������
    int i,j;
    for (i=0;i<1000;++i) {
        for (j=0;j<1000;++j) {
            if(i==j)
                roads[i][j]=0;
            else
                roads[i][j]=MAX;
        }
    }
}
void input(int num){//����
    char a,b;
    char t;
    int x,y;
    int i,j;
    for(i=1;i<=num-1;i++){
        //getchar();
        scanf(" %c %d",&a,&x);
        for(j=1;j<=x;j++){
            //getchar();
            scanf(" %c %d",&t,&y);
            roads[a-'A'][t-'A']=y;
            roads[t-'A'][a-'A']=y;//
        }
    }
}


int findmin(int num){
    int j;
    int e=MAX;
    int minpostion;
    for(j=0;j<num;j++){
        if(lowcost[j]!=0 && lowcost[j]<e){
            e=lowcost[j];
            minpostion =j;
        }
    }
    return minpostion; 
}

int prime(int num){
    int totalcost=0;
    int t,i;
    int minpostion=-1;
    for (t=0;t<num;t++)
        lowcost[t]=roads[0][t];//��lowcost[]��ʼ��
    for (i=1;i<num;++i) { 
        minpostion=findmin(num);//////////

        if (minpostion!=-1) {
            totalcost+=lowcost[minpostion];
            lowcost[minpostion]=0;
            for (t=0;t<num;++t) {
                if (lowcost[t]>roads[minpostion][t]) {
                    lowcost[t]=roads[minpostion][t];
                }
            }

        }
    }
    return totalcost;
}

int main(){
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    int totalcost;
    int num;//��ׯ��
    while (scanf("%d",&num)&&num) {
        init();//��ʼ��
        input(num);//����

        totalcost=prime(num);//������С�ɱ�
        printf("%d\n",totalcost);//������
    }
}
