#include<fstream>
#include<math.h>
using namespace std;

int space[200][200];
int lena[4],lenb[4];
int rotlena[4],rotlenb[4];
//int shtlen,longlen;
ofstream fout("packrec.out");

bool fillblock(int shtlen, int longlen, int index, int posi, int posj){
//�����(posi,posj)λ���ܷ��µ�index�����������������򲢷���true��������䲢����false
    if((posi+rotlena[index]) > shtlen)return false;
    if((posj+rotlenb[index]) > longlen)return false;
    for(int i=posi;i<(posi+rotlena[index]);++i)
        for(int j=posj;j<(posj+rotlenb[index]);++j)
            if(space[i][j]!=0)return false;
    for(int i=posi;i<(posi+rotlena[index]);++i)
        for(int j=posj;j<(posj+rotlenb[index]);++j)
            space[i][j]=index+1;
    return true;
}

void unfillblock(int index, int posi, int posj){
    for(int i=posi;i<(posi+rotlena[index]);++i)
        for(int j=posj;j<(posj+rotlenb[index]);++j)
            space[i][j]=0;
}

bool fillrec(int shtlen, int longlen, int index){//�ж��ܷ���µ�index�Լ��Ժ����о���
    if(index>=4){
        for(int i=0;i<shtlen;++i){
            for(int j=0;j<longlen;++j)
                fout<<space[i][j]<<' ';
            fout<<endl;
        }
        fout<<endl;
        return true;
    }
    for(int posi=0;posi<shtlen;++posi)for(int posj=0;posj<longlen;++posj){
        if(fillblock(shtlen,longlen,index,posi,posj)){//�����(posi,posj)λ���ܷ��µ�index�����������������򲢷���true
            if(fillrec(shtlen,longlen,index+1))return true;
            unfillblock(index,posi,posj);//������������
        }
        //�Ų��������
    }
    return false;
}

bool fillwithrot(int shtlen, int longlen){//�ж���shtlen,longlen��Χ���ܷ������4������
    for(int i=0;i<shtlen;++i)for(int j=0;j<longlen;++j)space[i][j]=0;
    return fillrec(shtlen,longlen,0);
    
    //for(int i=0;i<4;++i){//.............................................................
    //    fillrec(shtlen,longlen,i);
    //}
}

bool fillthissize(int shtlen, int longlen){//��4�����ν�����ת90�ȱ任
    //int rotlena[4],rotlenb[4];
    for(int direction=0;direction<16;++direction){
        int tmpd=direction;
        for(int i=0;i<4;++i){
            if(tmpd&0x0001){
                rotlena[i]=lenb[i];
                rotlenb[i]=lena[i];
            }
            else {
                rotlena[i]=lena[i];
                rotlenb[i]=lenb[i];
            }
            tmpd>>=1;
        }
        if(fillwithrot(shtlen,longlen))return true;
    }
    return false;
}

int main(){
    ifstream fin("packrec.in");
    //ofstream fout("packrec.out");
    for(int i=0;i<4;++i){
        fin>>lena[i]>>lenb[i];
    }
    int area[4];
    for(int i=0;i<4;++i)area[i]=lena[i]*lenb[i];
    for(int i=0;i<4;++i)for(int j=0;j<3-i;++j)
        if(area[j]<area[j+1]){
            swap(lena[j],lena[j+1]);
            swap(lenb[j],lenb[j+1]);
            swap(area[j],area[j+1]);
        }
    //for(int i=4;i<8;++i){
    //    lena[i]=lenb[i-4];
    //    lenb[i]=lena[i-4];
    //}
    int minarea=0;
    bool nfound=true;
    for(int i=0;i<4;++i)minarea+=lena[i]*lenb[i];
    for(;nfound;++minarea){
        int sqtarea=static_cast<int>(sqrt(static_cast<float>(minarea)));
        for(int shtlen=1;shtlen<=sqtarea;++shtlen){
            if(minarea%shtlen==0){
                int longlen=minarea/shtlen;
                if(fillthissize(shtlen,longlen)){
                    if(nfound){fout<<minarea<<endl;nfound=false;}
                    fout<<shtlen<<' '<<longlen<<endl;
                }
            }
        }
    }

    return 0;
}