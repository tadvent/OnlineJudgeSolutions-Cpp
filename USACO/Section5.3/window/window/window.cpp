/*
ID: wjl1241
LANG: C++
TASK: window
*/

/*
   (0, 0) left ------> right
    top
     |
     |
     V
   bottom
*/

#include<cstdio>
#include<list>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

struct window{
    int left, top, right, bottom;
    window(){}
    window(int l, int t, int r, int b)
        :left(l), top(t), right(r), bottom(b){
#ifdef _DEBUG
            assert(left <= right && top <= bottom);
#endif
    }
    int area()const{
        return (right-left)*(bottom-top);
    }
};

class CWnds{
    int id2idx(char id){
        if(id >= 'a' && id <= 'z')
            return id - 'a';
        if(id >= 'A' && id <= 'Z')
            return id - 'A' + 26;
        if(id >= '0' && id <= '9')
            return id - '0' + 52;
        return -1;
    }

    list<window> wnds;
    vector<list<window>::iterator> iters;

    void split(list<window> &pieces, const window &win){
        list<window> newpcs;
        for(list<window>::const_iterator it = pieces.begin();
            it != pieces.end(); ++it){
                int l = it->left, r = it->right, t = it->top, b = it->bottom;
                if(l >= win.right || r <= win.left || t >= win.bottom || b <= win.top){
                    newpcs.push_back(window(l, t, r, b));
                    continue;
                }
                if(l < win.left){
                    newpcs.push_back(window(l, t, win.left, b));
                    l = win.left;
                }
                if(r > win.right){
                    newpcs.push_back(window(win.right, t, r, b));
                    r = win.right;
                }
                if(t < win.top){
                    newpcs.push_back(window(l, t, r, win.top));
                    t = win.top;
                }
                if(b > win.bottom){
                    newpcs.push_back(window(l, win.bottom, r, b));
                    b = win.bottom;
                }
        }
        pieces.swap(newpcs);
    }
public:
    CWnds(){
        iters.assign(62, wnds.end());
    }
    void w(char id, int x, int y, int X, int Y){
        if(x > X)swap(x, X);
        if(y > Y)swap(y, Y);
        wnds.push_front(window(x, y, X, Y));
        iters[id2idx(id)] = wnds.begin();
    }
    void t(char id){ // top
        wnds.splice(wnds.begin(), wnds, iters[id2idx(id)]);
        iters[id2idx(id)] = wnds.begin();
    }
    void b(char id){ // bottom
        wnds.splice(wnds.end(), wnds, iters[id2idx(id)]);
        iters[id2idx(id)] = --wnds.end();
    }
    void d(char id){ // destroy
        wnds.erase(iters[id2idx(id)]);
        iters[id2idx(id)] = wnds.end();
    }
    double s(char id){ // percentage visible
        list<window>::const_iterator end = iters[id2idx(id)];
        list<window> pieces(1, *end);
        for(list<window>::const_iterator it = wnds.begin();
            it != end; ++it){
                split(pieces, *it);
        }
        int sum = 0.0;
        for(list<window>::const_iterator it = pieces.begin();
            it != pieces.end(); ++it){
                sum += it->area();
        }
        return double(sum)/(end->area())*100.0;
    }
};

int main(){
    FILE *fin, *fout;
    CWnds wnds;
    char id, inst;
    int x, y, X, Y;
    fin = fopen("window.in", "r");
    fout = fopen("window.out", "w");
    while(fscanf(fin, " %c", &inst) != EOF){
        switch(inst){
            case 'w':
                fscanf(fin, "(%c,%d,%d,%d,%d)", &id, &x, &y, &X, &Y);
                wnds.w(id, x, y, X, Y);
                break;
            case 't':
                fscanf(fin, "(%c)", &id);
                wnds.t(id);
                break;
            case 'b':
                fscanf(fin, "(%c)", &id);
                wnds.b(id);
                break;
            case 'd':
                fscanf(fin, "(%c)", &id);
                wnds.d(id);
                break;
            case 's':
                fscanf(fin, "(%c)", &id);
                fprintf(fout, "%.3f\n", wnds.s(id));
                break;
        }
    }

    fclose(fin);
    fclose(fout);
}
