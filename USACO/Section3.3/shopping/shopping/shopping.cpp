/*
ID: wjl1241
PROG: shopping
LANG: C++
*/

#include<fstream>
#include<vector>
using namespace std;
const int infinite=1000000000;

struct offer{
    vector< pair<int,int> > vProducts;  //first int of the pair is the product code
                                        //second int is the quantity
    int nPrice;
};

struct item{
    int iCode;
    int nNum;
    int iPrice;
};

int nOffer,nItem;   //item: the items to buy
vector<offer> vOffers,vValOffers;
vector<item> vItems;
int dp[6][6][6][6][6];
int Code2Idx[1000];

// DP recuision:
int getprice(vector<int> n){
    int price;
    if(-1 != (price=dp[n[0]][n[1]][n[2]][n[3]][n[4]]))return price;
    price=infinite;
    for(vector<offer>::iterator itr=vValOffers.begin();itr!=vValOffers.end();++itr){
        vector<int> nextn(n);
        vector< pair<int,int> >::iterator itrj;
        for(itrj=itr->vProducts.begin();itrj!=itr->vProducts.end();++itrj){
            int idx=Code2Idx[itrj->first];
            nextn[idx]-=itrj->second;
            if(nextn[idx]<0)break;
        }
        if(itrj == itr->vProducts.end()){
            price=min(price,getprice(nextn)+itr->nPrice);
        }
    }
    if(price == infinite){
        price=0;
        for(int i=0;i<nItem;++i)price+=vItems[i].iPrice*n[i];
    }
    dp[n[0]][n[1]][n[2]][n[3]][n[4]]=price;
    return price;
}

int main(){
    ifstream fin("shopping.in");
    ofstream fout("shopping.out");

    //Initialize:
    for(int i=0;i<6*6*6*6*6;++i){
        ((int *)dp)[i]=-1;
    }
    for(int i=0;i<1000;++i)Code2Idx[i]=-1;

    //Read data:
    fin>>nOffer;
    vOffers.resize(nOffer);
    for(int i=0;i<nOffer;++i){
        int nPrdt;
        fin>>nPrdt;
        vOffers[i].vProducts.resize(nPrdt);
        for(int j=0;j<nPrdt;++j)
            fin>>vOffers[i].vProducts[j].first>>vOffers[i].vProducts[j].second;
        fin>>vOffers[i].nPrice;
    }
    fin>>nItem;
    vItems.resize(nItem);
    for(int i=0;i<nItem;++i){
        fin>>vItems[i].iCode>>vItems[i].nNum>>vItems[i].iPrice;
        Code2Idx[vItems[i].iCode]=i;
    }

    //Construct vValOffers:
    for(vector<offer>::iterator itr=vOffers.begin();itr!=vOffers.end();++itr){
        vector< pair<int,int> >::iterator j=itr->vProducts.begin();
        for(;j!=itr->vProducts.end();++j){
            if(Code2Idx[j->first] == -1)break;
        }
        if(j == itr->vProducts.end())vValOffers.push_back(*itr);
    }

    //Do Calculation:
    vector<int> parameter(5,0);
    for(int i=0;i<nItem;++i)parameter[i]=vItems[i].nNum;
    fout<<getprice(parameter)<<endl;
}