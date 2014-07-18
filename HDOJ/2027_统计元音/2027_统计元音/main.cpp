#include<cstdio>
int main(){
    int n,a,e,i,o,u,c;
    scanf("%d\n",&n);
    while(n--){
        a=e=i=o=u=0;
        while((c=getchar())!=EOF){
            if(c=='\n')break;
            if(c=='a')++a;
            else if(c=='e')++e;
            else if(c=='i')++i;
            else if(c=='o')++o;
            else if(c=='u')++u;
        }
        printf("a:%d\ne:%d\ni:%d\no:%d\nu:%d\n",a,e,i,o,u);
        if(n)putchar('\n');
    }
}