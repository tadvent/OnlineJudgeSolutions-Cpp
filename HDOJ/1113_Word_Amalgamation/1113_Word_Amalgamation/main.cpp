#include<cstdio>
#include<string>
#include<map>
#include<deque>
#include<algorithm>
using namespace std;

typedef map<string, deque<string> > Dic;
Dic dic;
char word[10], tmp[10];

bool dicin(){
    char c;
    if((c=getchar()) == EOF)return false;
    ungetc(c, stdin);
    while(gets(word) && strcmp(word, "XXXXXX")){
        strcpy(tmp, word);
        sort(tmp, tmp+strlen(tmp));
        dic[tmp].push_back(word);
    }
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    while(dicin()){
        Dic::iterator it;
        for(it=dic.begin(); it!=dic.end(); ++it)
            sort(it->second.begin(), it->second.end());
        while(gets(word) && strcmp(word, "XXXXXX")){
            sort(word, word+strlen(word));
            if((it = dic.find(word)) != dic.end()){
                for(deque<string>::const_iterator cit=it->second.begin();
                    cit != it->second.end(); ++cit)
                    printf("%s\n", cit->c_str());
            } else { puts("NOT A VALID WORD"); }
            puts("******");
        }
    }
}
