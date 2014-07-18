/*
ID: wjl1241
PROG: milk2
LANG: C++
*/

#include<iostream>
#include<fstream>
using namespace std;

typedef struct mytime {
    int start;
    int end;
    struct mytime *pre;
    struct mytime *next;
}mytime;

class tlist{
    mytime *head;
    bool tdelete(mytime *p);
public:
    tlist(){head=NULL;}
    void push(int a,int b);
    mytime *earlystart(void);
    void maxend(int &etime);
    inline bool isempty(void);
};

bool tlist::tdelete(mytime *p){
    if(p==NULL)return false;
    if(p==head){
        if(p->next==NULL)head=NULL;
        else{
            head=p->next;
            head->pre=p->pre;
        }
    }
    else if(p==head->pre){
        p->pre->next=NULL;
        head->pre=p->pre;
    }
    else {
        p->pre->next=p->next;
        p->next->pre=p->pre;
    }
    delete p;
    return true;
}

void tlist::push(int a,int b){
    mytime *p=new mytime;
    p->start=a;
    p->end=b;
    if(head!=NULL){
        p->next=NULL;
        p->pre=head->pre;
        head->pre->next=p;
        head->pre=p;
    }
    else {
        head=p;
        head->next=NULL;
        head->pre=head;
    }
}

mytime* tlist::earlystart(void){    //在tlist中查找start最小的项，返回指向该项的指针
    mytime* r=NULL;
    int early=2147483647;
    for(mytime *p=head;p!=NULL;p=p->next)
        if(p->start<early){
            early=p->start;
            r=p;
        }
    return r;
}

void tlist::maxend(int &etime){ //在tlist中查找满足条件start<=etime的项，如果该项的end>etime，则更新etime为end;同时删除满足条件的所有项
    bool find=true;
    while(find){
        find=false;
        for(mytime *p=head;p!=NULL;){
            if(p->start<=etime){
                find=true;
                if(p->end>etime)etime=p->end;
                mytime *t=p;
                p=p->next;
                tdelete(t);
            }
            else {p=p->next;}
        }
    }
}

bool tlist::isempty(void){
    return head==NULL;
}

int main(){
    ifstream fin("milk2.in");
    ofstream fout("milk2.out");
    tlist farmer;
    int nf;
    fin>>nf;
    for(int i=0;i<nf;i++){
        int start,end;
        fin>>start>>end;
        farmer.push(start,end);
    }

    int milktime=0,idletime=0,stime=0,etime=0,lastetime=2147483647;
    while(!farmer.isempty()){
        mytime *p=farmer.earlystart();
        stime=p->start;
        etime=p->end;
        farmer.maxend(etime);
        if(etime-stime>milktime)milktime=etime-stime;
        if(stime-lastetime>idletime)idletime=stime-lastetime;
        lastetime=etime;
    }
    fout<<milktime<<' '<<idletime<<endl;
    return 0;
}