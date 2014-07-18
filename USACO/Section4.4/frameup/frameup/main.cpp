/*
ID: wjl1241
PROG: frameup
LANG: C++
*/

#include<fstream>
#include<vector>
#include<cstring>  // for memset()
#include<set>
using namespace std;

const int maxframesize = 31;
const int maxframenum = 27;
char allframe[maxframesize][maxframesize];
int width, height;

int border[maxframenum][4];  // left top right bottom;
vector<char> sequence;
set<char> firstorder;
ofstream fout;

struct frame{
    int numlower;
    vector<int> upperlayers;
    frame():numlower(-1){   // -1 means this frame is not used.
        upperlayers.reserve(maxframenum);
    }
};

frame graph[maxframenum];

inline char l2idx(char ch){
    return (ch>='A' && ch<='Z')? (ch-'A'+1):0 ;
}
inline char idx2l(char idx){
    return idx+'A'-1;
}

inline void logupper(int layer, int upper){
    graph[layer].upperlayers.push_back(upper);
    ++(graph[upper].numlower);
}

void makegraph(){
    // get borders for each frame
    for(int i=0; i<height; ++i)for(int j=0; j<width; ++j){
        char &ch = allframe[i][j];
        if(ch == 0)continue;
        if(graph[ch].numlower < 0)graph[ch].numlower = 0;  // used
        border[ch][0] = min(border[ch][0], j);  // left
        border[ch][1] = min(border[ch][1], i);  // top
        border[ch][2] = max(border[ch][2], j);  // right
        border[ch][3] = max(border[ch][3], i);  // bottom
    }
    // for each frame, make the down->up graph
    for(int layer=1; layer<maxframenum; ++layer)if(graph[layer].numlower >= 0){
        int isUpper[maxframenum];
        memset(isUpper, 0, sizeof(isUpper));
        isUpper[layer] = 1;

        // for four borders, log the uppers.
        for(int i=border[layer][0]; i<=border[layer][2]; ++i){
            const char &ch1 = allframe[border[layer][1]][i];  // top line
            if(!isUpper[ch1]){
                isUpper[ch1] = 1;
                logupper(layer, ch1);
            }
            const char &ch2 = allframe[border[layer][3]][i]; // bottom line
            if(!isUpper[ch2]){
                isUpper[ch2] = 1;
                logupper(layer, ch2);
            }
        }
        for(int i=border[layer][1]+1; i<border[layer][3]; ++i){
            const char &ch1 = allframe[i][border[layer][0]];  // left row
            if(!isUpper[ch1]){
                isUpper[ch1] = 1;
                logupper(layer, ch1);
            }
            const char &ch2 = allframe[i][border[layer][2]];  // right row
            if(!isUpper[ch2]){
                isUpper[ch2] = 1;
                logupper(layer, ch2);
            }
        }
    }
}

inline void output(){
    fout.rdbuf()->sputn(&sequence[0], sequence.size());
    fout.rdbuf()->sputc('\n');
}

void dfsout(){
    if(firstorder.empty()){
        output();
        return;
    }
    int layer = 0;
    set<char>::iterator itr;
    while((itr = firstorder.upper_bound(layer)) != firstorder.end()){
        layer = *itr;
        sequence.push_back(idx2l(layer));
        firstorder.erase(layer);

        for(vector<int>::iterator i = graph[layer].upperlayers.begin();
            i != graph[layer].upperlayers.end(); ++i){
                if(--graph[*i].numlower == 0){
                    firstorder.insert(*i);
                }
        }

        dfsout();

        for(vector<int>::iterator i = graph[layer].upperlayers.begin();
            i != graph[layer].upperlayers.end(); ++i){
                if(++graph[*i].numlower == 1){
                    firstorder.erase(*i);
                }
        }

        firstorder.insert(layer);
        sequence.pop_back();
    }
}

int main(){
    ios::sync_with_stdio(false);
    ifstream fin("frameup.in");
    fin>>height>>width;
    fin.ignore(width, '\n');
    for(int i=0; i<height; ++i)
        fin.getline(allframe[i], maxframesize);
    fin.close();

    // init allframe & border
    for(int i=0; i<height; ++i)for(int j=0; j<width; ++j)
        allframe[i][j] = l2idx(allframe[i][j]);
    for(int i=1; i<maxframenum; ++i){
        border[i][0] = maxframesize;
        border[i][1] = maxframesize;
        border[i][2] = 0;
        border[i][3] = 0;
    }
    sequence.reserve(maxframenum);

    makegraph();
    for(int i=0; i<maxframenum; ++i)if(graph[i].numlower == 0)
        firstorder.insert(i);

    fout.open("frameup.out");
    dfsout();
    fout.close();
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <assert.h>

FILE *fout, *fin;

/* the picture */
char board[30][32];
int h, w; /* height and width of the picture */

/* for each letter, miny, minx, maxy, and maxy of the frame */
int pos[26][4];
int in[26]; /* is this frame in the picture? */
int cnt; /* number of frames in picture */

/* above[a][b] = 1 if frame a is known to be above frame b in the picture */
int above[26][26];

/* a possible ordering */
char answer[27]; /* one extra for the terminating null */

void find_answers(int pos)
 {
  int lv, lv2;

  if (pos == cnt)
   { /* an ordering has been found, output it */
    answer[pos] = '\0';
    fprintf (fout, "%s\n", answer);
    return;
   }

  for (lv = 0; lv < 26; lv++)
    if (in[lv])
     {
      /* determine if there is a frame that hasn't been place in answer
         yet, but must be below this one */
      for (lv2 = 0; lv2 < 26; lv2++)
        if (in[lv2] && above[lv][lv2]) break;

      if (lv2 >= 26)
       { /* no such frame, so this COULD be the next one */
        answer[pos] = 'A' + lv;
	in[lv] = 0; /* mark as in answer */
	find_answers(pos+1);
	in[lv] = 1; /* clear mark */
       }
     }
 }

int main(int argc, char **argv)
 {
  int lv, lv2;
  int loc;

  if ((fin = fopen("frameup.in", "r")) == NULL)
   {
    perror ("fopen fin");
    exit(1);
   }
  if ((fout = fopen("frameup.out", "w")) == NULL)
   {
    perror ("fopen fout");
    exit(1);
   }

  fscanf (fin, "%d %d", &h, &w);
  for (lv = 0; lv < h; lv++)
    fscanf (fin, "%s", board[lv]);

  for (lv = 0; lv < h; lv++)
    for (lv2 = 0; lv2 < w; lv2++)
     {
      if (board[lv][lv2] != '.')
       {
        loc = board[lv][lv2] - 'A';
	if (!in[loc])
	 { /* first time we've seen this board */
	  in[loc] = 1;
	  cnt++;
	  pos[loc][0] = pos[loc][2] = lv;
	  pos[loc][1] = pos[loc][3] = lv2;
	 } else { /* update the boundary of the frame, if necessary */
	  if (lv < pos[loc][0]) pos[loc][0] = lv;
	  if (lv > pos[loc][2]) pos[loc][2] = lv;
	  if (lv2 < pos[loc][1]) pos[loc][1] = lv2;
	  if (lv2 > pos[loc][3]) pos[loc][3] = lv2;
	 }
       }
     }

  for (lv = 0; lv < 26; lv++)
   if (in[lv])
    { /* for each frame */
     for (lv2 = pos[lv][0]; lv2 <= pos[lv][2]; lv2++)
      { /* check left and right borders */

       /* left */
       loc = board[lv2][pos[lv][1]] - 'A';
       assert(loc >= 0 && loc < 26); /* there must be SOME frame here */
       if (loc != lv) /* there's a different frame where this one should be */
         above[loc][lv] = 1; /* that different frame must be above this one */

       /* right */
       loc = board[lv2][pos[lv][3]] - 'A';
       assert(loc >= 0 && loc < 26);
       if (loc != lv) /* same as left */
         above[loc][lv] = 1;
      }
     for (lv2 = pos[lv][1]; lv2 <= pos[lv][3]; lv2++)
      { /* check top and bottom */

       /* top */
       loc = board[pos[lv][0]][lv2] - 'A';
       assert(loc >= 0 && loc < 26);
       if (loc != lv)
         above[loc][lv] = 1;

       /* bottom */
       loc = board[pos[lv][2]][lv2] - 'A';
       if (loc < 0 || loc >= 26) 
         fprintf (stderr, "%i %i (%c)\n", lv2, pos[lv][2], lv + 'A');
       assert(loc >= 0 && loc < 26);
       if (loc != lv)
         above[loc][lv] = 1;
      }
    }

  /* graph is set up, now just find all answers */
  find_answers(0);
  return 0;
 }

