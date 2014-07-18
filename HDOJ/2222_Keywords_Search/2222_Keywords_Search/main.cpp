// trie tree + KMP ==> AC automation machine!

/* wrong answer, the counting method is wrong ...

#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

template<class DataType>
class Trie{
public:
    struct node{
        char ch;
        int fchild;
        int brother;
        int parent;
        mutable DataType data;
        node():ch(0), fchild(-1), brother(-1), parent(-1), data(){}
    };

    void init(int size) {
        assert(size > 0);
        table.assign(size, node());
        table[0].parent = 0;
    }
    DataType &operator[](int idx) const {
        return table[idx].data;
    }
    int insert(const char *str) {
        assert(str != NULL);
        int s = 0, p;
        while(*str && (p = getpos(s, *str)) > 0){
            if(table[p].parent != s){
                table[p].ch = *str;
                // table[p].fchild = -1;
                table[p].parent = s;
                table[p].brother = table[s].fchild;
                table[s].fchild = p;
            }
            s = p;
            ++str;
        }
        return s;
    }
    char getchar(int s) const {
        return table[s].ch;
    }
    int getparent(int s) const {
        return table[s].parent;
    }
    int getfchild(int s) const {
        return table[s].fchild;
    }
    int getbrother(int s) const {
        return table[s].brother;
    }
    int getchild(int s, char c) const {
        unsigned p = hash(s, c) % table.size();
        if(table[p].parent != s || table[p].ch != c){
            for(int i=1; i<15; ++i){
                p = (p + i*i) % table.size();
                if(table[p].parent == s){
                    if(table[p].ch == c)
                    return p;
                } else if(table[p].parent == -1)
                    return -1;
            }
            return -1;
        } else return p;
    }
private:
    unsigned hash(int s, char c) const {
        return unsigned(((((c<<13)^s)<<15) + ((s*c)<<5) + s^c) & (~(1 << (sizeof(int) * 8 - 1))));
    }

    int getpos(int s, char c) const {   // get exist node's idx or new pos to insert
        unsigned p = hash(s, c) % table.size();
        if(table[p].parent != s || table[p].ch != c){
            for(int i=1; i<15; ++i){
                p = (p + i*i) % table.size();
                if(table[p].parent == s){
                    if(table[p].ch == c)
                    return p;
                } else if(table[p].parent == -1)
                    return p;
            }
            return -1;
        } else return p;
    }
    vector<node> table;
};

class ACtree{
public:
    struct node{
        int str_count;
        int fail_state;
        node(): str_count(0), fail_state(-1){}
    };

    void init(int size = 500001){
        tree.init(size);
    }
    bool insert(const char *str){
        assert(str != NULL);
        int s = tree.insert(str);   // insert return the final state number or -1 if failed
        if(s == -1) return false;
        ++tree[s].str_count;
        return true;
    }
    void compile(){
        queue<int> q;
        for(int i=tree.getfchild(0); i >= 0; i = tree.getbrother(i)){
            q.push(i);
        }
        while(!q.empty()){
            int s = q.front();
            q.pop();

            int pf = tree[tree.getparent(s)].fail_state;
            char ch = tree.getchar(s);
            while(pf >= 0 && tree.getchild(pf, ch) < 0) pf = tree[pf].fail_state;
            int pfc = (pf < 0)? 0:tree.getchild(pf, ch);
            tree[s].fail_state = pfc;
            tree[s].str_count += tree[pfc].str_count;

            for(int i=tree.getfchild(s); i >= 0; i = tree.getbrother(i)){
                q.push(i);
            }
        }
    }
    int matchall(const char *str) const {
        int sum = 0, s = 0, t;
        const char *p = str;
        while(*p){
            while(s >= 0 && (t = tree.getchild(s, *p)) < 0){
                s = tree[s].fail_state;
            }
            s = (s < 0)? 0:t;
            sum += tree[s].str_count;
            tree[s].str_count = 0;
            ++p;
        }
        return sum;
    }
private:
    Trie<node> tree;
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif

    ACtree ac;
    int n;
    char buffer[1000005];

    scanf("%d", &n);
    while(n--){
        int m;

        ac.init();
        scanf("%d", &m);
        while(m--){
            scanf("%s", buffer);
            ac.insert(buffer);
        }
        ac.compile();

        scanf("%s", buffer);
        printf("%d\n", ac.matchall(buffer));
    }

    return 0;
}

/* */

//////////////////////////////////////////////////////////////
// double array trie
//*

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cassert>

const int MAXNODE = 500005;

class ac{
public:
    struct node{
        int cnt;
        node *key[26];
        node *fail;
    };

    ac(){
        root = (node*)malloc(MEMSIZE);
    }
    ~ac(){
        free(root);
        root = NULL;
    }
    void init(){
        memset(root, 0, MEMSIZE);
        root->cnt = -1;
        empos = root + 1;
    }
    void insert(const char *s){
        assert(s != NULL);
        node *u = root;
        for(; *s; ++s){
            const int i = *s - 'a';
            if(u->key[i] == NULL)
                u->key[i] = empos++;
            u = u->key[i];
        }
        ++u->cnt;
    }
    void compile(){
        static node *Q[MAXNODE];
        int head = 0, tail = 0;
        Q[tail++] = root;

        while(head < tail){
            node *u = Q[head++];
            for(int i = 0; i < 26; ++i){
                if(u->key[i] == NULL) continue;
                Q[tail++] = u->key[i];
                for(const node *uf = u->fail; ; uf = uf->fail){
                    if(uf == NULL){
                        u->key[i]->fail = root;
                        break;
                    } else if(uf->key[i] != NULL){
                        u->key[i]->fail = uf->key[i];
                        break;
                    }
                }
            }
        }
    }
    int match(){
        scanf(" ");
        char c;
        node *u = root;
        int sum = 0;
        while((c = getchar()) != '\n'){
            const int i = c - 'a';
            while(u->key[i] == NULL)
                if((u = u->fail) == NULL) break;
            if(u == NULL){
                u = root;
            } else {
                u = u->key[i];
                for(node *v = u; v->cnt >= 0; v = v->fail){
                    sum += v->cnt;
                    v->cnt = -1;
                }
            }
        }
        return sum;
    }
private:
    static const int MEMSIZE = MAXNODE * sizeof(node) / 2;
    node *root, *empos;
};

int main(){
#ifndef ONLINE_JUDGE
    freopen("i.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    int n, m;
    char buf[55];
    ac a;

    scanf("%d", &n);
    while(n--){
        a.init();
        scanf("%d", &m);
        while(m--){
            scanf("%s", buf);
            a.insert(buf);
        }
        a.compile();

        printf("%d\n", a.match());
    }

    return 0;
}

/* */