#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include<map>
#include<queue>
using namespace std;

vector<string> strs;

bool inputStrs(){
    int n;
    if(!(cin >> n)) return false;
    cin.ignore(1024, '\n');
    strs.resize(n);
    for(int i=0; i<n; ++i){
        if(!getline(cin, strs[i]))
            return false;
    }
    return true;
}

class ac{
public:
    struct node{
        int strIdx;
        map<char, node*> key;
        node *fail;
        node():strIdx(-1), fail(NULL){}
    };

    void init(){
        root = new node();
    }
    void unInit(){
        nodeDelete(root);
    }
    void insert(int strIdx){
        node *u = root;
        for(int i=0; i<strs[strIdx].length(); ++i){
            char c = strs[strIdx][i];
            if(u->key.find(c) == u->key.end())
                u->key.insert(pair<char, node*>(c, new node()));
            u = u->key[c];
        }
        u->strIdx = strIdx;
    }
    void compile(){
        queue<node*> Q;
        Q.push(root);

        while(!Q.empty()){
            node *u = Q.front();
            Q.pop();
            for(map<char,node*>::iterator i=u->key.begin(); i != u->key.end(); ++i){
                Q.push(i->second);
                for(node *uf = u->fail;; uf = uf->fail){
                    if(uf == NULL){
                        i->second->fail = root;
                        break;
                    } else if(uf->key[i->first] != NULL){
                        i->second->fail = uf->key[i->first];
                        break;
                    }
                }
            }
        }
    }
    void match(const string & s, vector<int> &matchIdxs){
        node *u = root;
        for(string::const_iterator i = s.begin(); i != s.end(); ++i){
            while(u->key[*i] == NULL)
                if((u = u->fail) == NULL) break;
            if(u == NULL){
                u = root;
            } else {
                u = u->key[*i];
                if(u->strIdx >= 0)
                    matchIdxs.push_back(u->strIdx);
            }
        }
    }
private:
    void nodeDelete(node *p){
        if(p == NULL) return;
        for(map<char, node*>::iterator i = p->key.begin(); i != p->key.end(); ++i){
            nodeDelete(i->second);
        }
        delete p;
    }
    node *root;
};

struct lenless{
    bool operator()(int i, int j) const {
        return strs[i].length() < strs[j].length();
    }
};

int main(){
    //freopen("i.txt", "r", stdin);
    //freopen("o.txt", "w", stdout);

    ac a;
    while(inputStrs()){
        a.init();
        for(int i=0; i<strs.size(); ++i){
            a.insert(i);
        }
        a.compile();

        int m;
        string s;
        vector<int> matchIdxs;
        cin >> m;
        cin.ignore(1024, '\n');
        while(m--){
            matchIdxs.clear();
            getline(cin, s);
            a.match(s, matchIdxs);
            sort(matchIdxs.begin(), matchIdxs.end(), lenless());
            for(int i=matchIdxs.size()-1; i>=0; --i){
                size_t p;
                string &ss = strs[matchIdxs[i]];
                while((p = s.find(ss)) != string::npos){
                    s.replace(p, ss.length(), ss.length(), '*');
                }
            }
            cout << s << '\n';
        }
        a.unInit();
    }
}
