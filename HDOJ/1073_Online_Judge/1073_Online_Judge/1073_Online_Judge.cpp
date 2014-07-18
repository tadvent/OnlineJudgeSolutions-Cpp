#include<cstdio>
#include<cstring>
#include<cctype>
const int bufsize = 32 * 1024;
char buf[bufsize+1], *st1, *ed1, *st2, *ed2;

bool getnext(){
    const char ststr[] = "\nSTART\n";
    const char edstr[] = "\nEND\n";
    char *cur = ed2;
    size_t len;
    if(!(st1 = strstr(ed2, ststr))
        || !(ed1 = strstr(st1, edstr))
        || !(st2 = strstr(ed1, ststr))
        || !(ed2 = strstr(st2, edstr))){
            memmove(buf, cur, len = bufsize - (cur-buf));
            buf[len += fread(buf+len, 1, bufsize-len, stdin)] = 0;
            ed2 = buf;
            if(!(st1 = strstr(ed2, ststr))
                || !(ed1 = strstr(st1, edstr))
                || !(st2 = strstr(ed1, ststr))
                || !(ed2 = strstr(st2, edstr)))return false;
    }
    st1 += 7;
    st2 += 7;
    return true;
}

bool PE(){
    const char sp[] = " \n\t";
    char *p1 = st1, *p2 = st2;
    for(;;){
        if(isspace(*p1)) p1 += strspn(p1, sp);
        if(isspace(*p2)) p2 += strspn(p2, sp);
        if(p1 >= ed1){
            if(p2 >= ed2)return true;
            else return false;
        } else if(p2 >= ed2)return false;
        if(*p1 == *p2){
            ++p1; ++p2;
        } else return false;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int t;
    scanf("%d", &t);
    buf[fread(buf, 1, bufsize, stdin)] = 0;
    ed2 = buf;
    while(t--){
        if(!getnext())break;
        if(ed1 - st1 == ed2 - st2 && !memcmp(st1, st2, ed1-st1)){
            puts("Accepted");
        } else if(PE()){
            puts("Presentation Error");
        } else {
            puts("Wrong Answer");
        }
    }
}

