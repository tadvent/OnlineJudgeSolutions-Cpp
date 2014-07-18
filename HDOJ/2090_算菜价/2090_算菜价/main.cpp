#include<cstdio>
int main(){
double n,p,s=0.0;
while(scanf("%*s%lf%lf",&n,&p)!=EOF){
s+=n*p;
}
printf("%.1lf\n",s);
}
