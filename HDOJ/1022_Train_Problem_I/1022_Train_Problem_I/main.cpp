#include<vector>
#include<cstdio>
using namespace std;
vector<char> inseq, outseq, stack;
vector<char> orderseq;  // 1:in, 0:out

bool check(){
    stack.clear();
    orderseq.clear();
    for(int ii=0, oi=0;;){
        if(stack.empty()){
            if(ii == inseq.size())break;
            else {
                stack.push_back(inseq[ii++]);
                orderseq.push_back(1);
            }
        } else {
            if(stack.back() == outseq[oi]){
                stack.pop_back();
                ++oi;
                orderseq.push_back(0);
            } else {
                if(ii == inseq.size())return false;
                stack.push_back(inseq[ii++]);
                orderseq.push_back(1);
            }
        }
    }
    return true;
}

int main(){
    inseq.reserve(10);
    outseq.reserve(10);
    stack.reserve(10);
    orderseq.reserve(10);
    int n;
    while(scanf("%d", &n) != EOF){
        inseq.clear(); outseq.clear();
        char ch;
        getchar();
        for(int i=0; i<n; ++i)
            inseq.push_back(getchar());
        getchar();
        for(int i=0; i<n; ++i)
            outseq.push_back(getchar());
        if(check()){
            printf("Yes.\n");
            for(int i=0; i<(int)orderseq.size(); ++i)
                printf((orderseq[i]?"in\n":"out\n"));
            printf("FINISH\n");
        } else {
            printf("No.\nFINISH\n");
        }
    }
}
