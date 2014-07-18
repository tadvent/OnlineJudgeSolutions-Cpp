#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

unsigned strhash(const string &s){
    unsigned h = 0;
    string::const_iterator it = s.begin();
    while(it != s.end())
        h = h * 131 + *it++;
    return h;
}

template<class Type>
class hash{
    struct node{
        Type val;
        node *next;
        node(const Type &w, node *Next):val(w), next(Next){}
    };
    vector<node*> hashtable;
public:
    hash(int initsize): hashtable(initsize, (node*)NULL){}
    bool add(const Type &w){
        unsigned h = strhash(w) % hashtable.size();
        node *p = hashtable[h];
        while(p){
            if(p->val == w)return false;
            p = p->next;
        }
        p = new node(w, hashtable[h]);
        hashtable[h] = p;
        return true;
    }
    void clear(){
        for(vector<node*>::iterator it = hashtable.begin();
            it != hashtable.end(); ++it){
                node *p = *it, *q;
                *it = (node*)NULL;
                while(p){
                    q = p;
                    p = p->next;
                    delete q;
                }
        }
    }
};

int main(){
    int count;
    string word;
    istringstream iss;
    hash<string> table(3000);

    while(getline(cin, word) && word != "#"){
        count = 0;
        iss.clear();
        iss.str(word);
        while(iss>>word)
            if(table.add(word))++count;
        cout<<count<<'\n';
        table.clear();
    }
}
