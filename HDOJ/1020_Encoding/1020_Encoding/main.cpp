#include<cstdio>
using namespace std;
int main(){
    int N, nlast = 0, cur, last = 'A';
    scanf("%d", &N);
    while(N--){
        bool end = false;
        scanf("%*[^A-Z]");
        for(;!end;){
            if(last < 'A' || last > 'Z'){
                last = 'A';
                nlast = 0;
                end = true;
                continue;
            }
            while((cur = getchar()) == last)++nlast;
            if(nlast > 1)printf("%d", nlast);
            if(nlast > 0)putchar(last);
            last = cur;
            nlast = 1;
        }
        putchar('\n');
    }
}
