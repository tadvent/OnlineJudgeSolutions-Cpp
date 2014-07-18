/* 
 * File:   main.cpp
 * Author: tadvent
 *
 * Created on May 31, 2012, 1:46 AM
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

char buf[210];
int pos;
inline char toup(const char c){
    return c + 'A' - 'a';
}
inline char tolo(const char c){
    return c + 'a' - 'A';
}
inline bool islo(const char c){
    return c >= 'a' && c <= 'z';
}
inline bool isup(const char c){
    return c >= 'A' && c <= 'Z';
}
inline void pt(const char c){
    buf[pos++] = c;
}

int tr(int s, char ch){
    switch(s){
        case 0:
            if(islo(ch)){
                s = 1;
                pt(ch);
            } else s = -1;
            break;
        case 1:
            if(ch >= 'a' && ch <= 'z'){
                pt(ch);
            } else if(ch >= 'A' && ch <= 'Z'){
                s = 2;
                pt('_');
                pt(tolo(ch));
            } else if(ch == '_'){
                s = 3;
            } else s = -1;
            break;
        case 2:
            if(islo(ch)){
                pt(ch);;
            } else if(isup(ch)){
                pt('_');
                pt(tolo(ch));
            } else s = -1;
            break;
        case 3:
            if(islo(ch)){
                s = 4;
                pt(toup(ch));
            } else s = -1;
            break;
        case 4:
            if(islo(ch)){
                pt(ch);
            } else if(ch == '_'){
                s = 3;
            } else s = -1;
            break;
        default:
            s = -1;
            break;
    }
    return s;
}

/*
 * 
 */
int main(int argc, char** argv) {
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
    pos = 0;
    int s = 0;
    int c;
    while((c = getchar()) != '\n' && c != EOF && s >= 0){
        s = tr(s, c);
    }
    if(s < 0 || s == 3){
        printf("Error!\n");
    } else {
        buf[pos] = 0;
        printf("%s\n", buf);
    }
    
    return 0;
}

