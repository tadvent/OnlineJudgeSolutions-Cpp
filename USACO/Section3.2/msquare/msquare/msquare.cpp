/*
ID: wjl1241
PROG: msquare
LANG: C++
*/

#include<fstream>
#include<queue>
using namespace std;

class state{
    static int pn[8];   // 0! - 7!
public:
    int str[8];
    static void init(void){ // pre-calculate 0! ~ 7!
        pn[0]=1;
        for(int i=1;i<8;++i)pn[i]=pn[i-1]*i;
    }
    int hash(void){
        int sum=0;
        for(int i=0;i<8;++i){
            int rev=0;
            for(int j=0;j<i;++j)if(str[j]>str[i])++rev;
            sum+=rev*pn[i];
        }
        return sum;
    }
    bool operator==(const state &comp)const{
        for(int i=0;i<8;++i)if(str[i]!=comp.str[i])return false;
        return true;
    }
    void op(int idx){
        int tmp;
        switch(idx){
            case 0:
                for(int i=0;i<4;++i)swap(str[i],str[7-i]);
                break;
            case 1:
                tmp=str[3];
                for(int i=3;i>0;--i)str[i]=str[i-1];
                str[0]=tmp;
                tmp=str[4];
                for(int i=4;i<7;++i)str[i]=str[i+1];
                str[7]=tmp;
                break;
            case 2:
                tmp=str[6];
                str[6]=str[5];
                str[5]=str[2];
                str[2]=str[1];
                str[1]=tmp;
                break;
        }
    }
};
int state::pn[8];

struct pathnode{
    state s;
    vector<int> ops;
    pathnode(const state &new_state, const vector<int> &new_ops):s(new_state),ops(new_ops){}
    pathnode(const pathnode &pano):s(pano.s),ops(pano.ops){}
    pathnode(void){}
};

state goal;
vector<bool> visit(40320); // 40320 = 8!

int main(){
    ifstream fin("msquare.in");
    ofstream fout("msquare.out");
    state::init();
    for(int i=0;i<8;++i)fin>>goal.str[i];

    state tmpstate;
    for(int i=0;i<8;++i)tmpstate.str[i]=i+1;
    queue<pathnode> solpath;
    solpath.push(pathnode(tmpstate,vector<int>(0)));
    visit[tmpstate.hash()]=true;

    pathnode nownode;
    while(!solpath.empty()){
        nownode=solpath.front();
        solpath.pop();
        if(nownode.s==goal)break;

        for(int newop=0;newop<3;++newop){
            tmpstate=nownode.s;
            tmpstate.op(newop);
            int tmphash=tmpstate.hash();
            if(!visit[tmphash]){
                vector<int> nowops=nownode.ops;
                nowops.push_back(newop);
                solpath.push(pathnode(tmpstate,nowops));
                visit[tmphash]=true;
            }
        }
    }

    fout<<nownode.ops.size()<<'\n';
    if(nownode.ops.size()==0)fout<<endl;
    else {
        int printcnt=0;
        for(vector<int>::iterator itr=nownode.ops.begin();itr!=nownode.ops.end();++itr){
            fout<<char('A'+(*itr));
            ++printcnt;
            if(0==printcnt%60)fout<<'\n';
        }
        if(printcnt%60)fout<<endl;
    }
}
