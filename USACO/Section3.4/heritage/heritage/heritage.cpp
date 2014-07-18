/*
ID: wjl1241
PROG: heritage
LANG: C++
*/

#include<fstream>
#include<string>
using namespace std;

struct TNode{
    char ch;
    TNode *lchild,*rchild;
    TNode(char Ch):ch(Ch){
        lchild=NULL;
        rchild=NULL;
    }
};

string sPreOrder;
string sInOrder;
ifstream fin("heritage.in");
ofstream fout("heritage.out");

TNode *MakeTree(int inst, int ined, int prst, int pred){
    if(inst >= ined || prst >= pred)return NULL;
    TNode *root=new TNode(sPreOrder[prst]);
    int rootidx=sInOrder.find(root->ch,inst);
    root->lchild=MakeTree(inst,rootidx,prst+1,prst+1+(rootidx-inst));
    root->rchild=MakeTree(rootidx+1,ined,prst+(rootidx-inst)+1,pred);
    return root;
}

void PostOrder(TNode *root){
    if (root==NULL) return;
    PostOrder(root->lchild);
    PostOrder(root->rchild);
    fout<<root->ch;
}

int main(){
    fin>>sInOrder;
    fin>>sPreOrder;

    PostOrder(MakeTree(0,sInOrder.size(),0,sPreOrder.size()));
    fout<<endl;
}