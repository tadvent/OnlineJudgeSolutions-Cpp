#include<cstdio>

int n, teamid;
double d, h, m, s;

bool teamin(){
    if(scanf("%d", &teamid) == EOF)return false;
    int i;
    h = m = s = 0.0;
    for(i=0; i<n; ++i){
        int th, tm, ts;
        if(scanf("%d:%d:%d", &th, &tm, &ts) < 3)break;
        h += th;
        m += tm;
        s += ts;
    }
    scanf("%*[^\n]%*c");
    if(i < n){
        h = -1.0;
    }
    return true;
}
void teamout(){
    printf("%3d: ", teamid);
    if(h < 0){
        puts("-");
        return;
    }
    s += h*60.0*60.0 + m*60.0;
    s /= d;

    int im, is;
    is = (int)(s + 0.5);
    im = is/60;
    is %= 60;
    printf("%d:%02d min/km\n", im, is);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    scanf("%d%lf", &n, &d);
    while(teamin())teamout();
}
