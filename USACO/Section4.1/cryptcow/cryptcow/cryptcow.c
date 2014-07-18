/*
ID: wjl1241
PROG: cryptcow
LANG: C
*/

#include <stdio.h>
#include <assert.h>
#include <ctype.h>

/* for purposes of value a-z are 0-25, A-Z are 26-51, and space is 52 */

#define MAXLEN 100
const char goal[50] = "Begin the Escape execution at the Break of Dawn";

/* represents locations of characters in the goal string */
/* used to get fragment matches (e.g., finding if/where 'e exec' occurs in
   the goal, try all places that start with e) */
int starts[53][10];
int nstart[53];

/* the link list that is the current message */
int next[MAXLEN];
int head;

/* the encrypted message */
char str[MAXLEN];

int lvl; /* how many levels of encryption are left to do */

/* hash table size */
#define HSIZE 502973
typedef struct HASH_T *hash_t;

struct HASH_T
 {
  char str[MAXLEN];
  hash_t next; /* use chaining to resolve conflicts */
 };

/* hash entries */
#define NUMENT 262144
struct HASH_T entries[NUMENT];
int hloc;

/* hash table */
hash_t table[HSIZE];

/* calculate the hash value of the current message */
int hash_chain(void)
 {
  int rv = 0;
  int c;

  for (c = head; c != -1; c = next[c])
    rv = (str[c] + (rv * 2377)) % HSIZE;
  return rv;
 }

/* change the current message into a string (from a linked list) */
void fill(char *dst)
 {
  int lv, c;

  for (lv = 0, c = head; c != -1; c = next[c], lv++)
    dst[lv] = str[c];
  dst[lv] = '\0';
 }

/* is the current message in the hash table? */
int check_hash(void)
 {
  int i;
  hash_t lp;
  hash_t t;

  i = hash_chain(); /* compute hash */

  /* grab an entry (we can throw it away if we don't use it) */
  t = &entries[hloc];
  fill(t->str); /* create the string */

  /* check the hash table */
  for (lp = table[i]; lp; lp = lp->next)
    if (strcmp(lp->str, t->str) == 0) return 1; /* match found */

  /* no match, add it to the table if we have entries left */
  if (hloc < NUMENT-1)
   {
    hloc++;
    t->next = table[i];
    table[i] = t;
   }
  return 0;
 }

/* initialize the start[] & nstart[] arrays */
void fill_start(void)
 {
  int lv;
  int pos;

  for (lv = 0; goal[lv]; lv++)
   { 
    if (goal[lv] >= 'a' && goal[lv] <= 'z') pos = goal[lv] - 'a';
    if (goal[lv] >= 'A' && goal[lv] <= 'Z') pos = goal[lv] - 'A' + 26;
    if (goal[lv] == ' ') pos = 52;
    starts[pos][nstart[pos]++] = lv;
   }
 }

/* output the linked list to stderr (debugging routine) */
void out_str(void)
 {
  int pos;
  for (pos = head; pos != -1; pos = next[pos])
    fprintf (stderr, "%c", str[pos]);
  fprintf (stderr, "\n");
 }

/* make sure the numbers match up */
int check_distrib(char *str)
 {
  int lv;
  char *lp;
  int count[52];
  int rv;

  /* init the counts */
  for (lv = 0; lv < 52; lv++) count[lv] = 0;

  /* add in the encoded string counts */
  for (lp = str; *lp; lp++)
   {
    if (*lp >= 'a' && *lp <= 'z')
      count[*lp - 'a']++;
    if (*lp >= 'A' && *lp <= 'Z')
      count[*lp - 'A'+26]++;
   }

  /* subtract the goal string counts */
  for (lp = goal; *lp; lp++)
   {
    if (*lp >= 'a' && *lp <= 'z')
      count[*lp - 'a']--;
    if (*lp >= 'A' && *lp <= 'Z')
      count[*lp - 'A'+26]--;
   }

  /* make sure encoded string has as many C as O as W's */
  if (count['C' - 'A' + 26] != count['O' - 'A' + 26]) return 0;
  if (count['C' - 'A' + 26] != count['W' - 'A' + 26]) return 0;
  rv = count['C' - 'A' + 26] + 1; /* how many decodings to do + 1 */

  /* we don't expect these counts to match up with original */
  count['C'-'A'+26] = 0;
  count['O'-'A'+26] = 0;
  count['W'-'A'+26] = 0;

  /* make sure frequencies match */
  for (lv = 0; lv < 52; lv++)
    if (count[lv] != 0) return 0; /* not that same number, can't decode */

  /* can decode, return number of encodings + 1 */
  return rv;
 }

/* ensure that all frags (sequences between encoding letters) are
   frags of the original string */
/* for a string without a C, O, or W, this routine degenarets to
   checking if the string is the same as the goal string */
int check_frags(void)
 {
  int lv, lv2, lv3;
  int f = 0;
  int pos;
  char *lp, *p;
  int lpos;
  int tp;
  char l = 'W';
  int max;
  static int cnt = 0;

  /* make sure prefix matches */
  for (lpos = head, lv = 0; lpos != -1 && str[lpos] != 'C' && 
                            str[lpos] != 'O' && str[lpos] != 'W'; 
			                            lpos = next[lpos], lv++)
    if (str[lpos] != goal[lv]) 
      return 0;

  /* first encoding character must be a 'C' */
  if (lpos != -1 && str[lpos] != 'C') return 0;

  /* find next non-encoding character */
  for (; str[lpos] == 'C' || str[lpos] == 'O' || str[lpos] == 'W'; 
                lpos = next[lpos])
    if (lpos == -1) break;

  /* while it's not the end of the string */
  for (; lpos != -1; )
   { 
    /* calculate value of first character in fragment */
    if (str[lpos] >= 'a' && str[lpos] <= 'z') pos = str[lpos] - 'a';
    if (str[lpos] >= 'A' && str[lpos] <= 'Z') pos = str[lpos] - 'A' + 26;
    if (str[lpos] == ' ') pos = 52;

    max = nstart[pos];

    for (lv2 = 0; lv2 < max; lv2++)
     { /* go through all the frags */

      /* the prefix of the goal string must occur at the beginning of
         the encoded string if the first character is not an encoding
	 letter */
      if (lv2 == 0 && str[head] == 'B' && str[lpos] == 'B' && lpos != head) 
        continue;

      /* find match length */
      p = goal + starts[pos][lv2];
      tp = lpos;
      for (lv3 = 0; tp != -1 && str[tp] == p[lv3]; lv3++, tp = next[tp])
       ;
      if (tp == -1) /* matches until end of encoded string */
       {
        /* substring must end here as well */
	/* also, last encoding letter must be a 'W' */
        if (p[lv3] == '\0') return (l == 'W'); 
	continue;
       }
      /* if it matches up to an encoding letter */
      if (str[tp] == 'C' || str[tp] == 'O' || str[tp] == 'W')
       {
	lpos = tp; 
	break;
       }
     }
    if (lv2 >= max) 
      return 0; /* no match for string found */
    if (str[lpos] == '\0') break; /* end of string */
    /* find next encoding letter */
    for (; lpos != -1 && (str[lpos] == 'C' || str[lpos] == 'O' || 
                                     str[lpos] == 'W'); lpos = next[lpos])
      l = str[lpos];
   }
  return (l == 'W'); /* last encoding letter must be a 'W' */
 }

/* translate the encoding string */
/* pcloc/poloc/pwloc are the position just BEFORE the C, O, and W */
void do_xform(int pcloc, int poloc, int pwloc)
 {
  int t;
  if (pcloc == -1) t = head;
  else t = next[pcloc];

  /* most of this is dealing with cases where the encoded letters
     selected are adjacent */
  if (t == poloc)
   {
    if (next[poloc] == pwloc)
     {
      if (pcloc == -1) head = next[next[pwloc]];
      else next[pcloc] = next[next[pwloc]];
     }
    else
     {
      if (pcloc == -1) head = next[next[poloc]];
      else next[pcloc] = next[next[poloc]];

      next[pwloc] = next[next[pwloc]];
     }
   } else if (next[poloc] == pwloc) {
    if (pcloc == -1) head = next[head];
    else next[pcloc] = next[next[pcloc]];

    next[poloc] = next[next[pwloc]];
   } else {
    if (pcloc == -1)
     {
      t = next[head];
      head = next[next[poloc]];
     }
    else
     {
      t = next[next[pcloc]];
      next[pcloc] = next[next[poloc]];
     }

    next[poloc] = next[next[pwloc]];
    next[pwloc] = t;
   }
 }

int find_str(void)
 {
  int c, o, w;
  int lc, lo, lw;
  int pc, po, pw;
  int lv;
  
  /* location of encoding letter */
  int cloc[15], oloc[15], wloc[15];

  /* location of characetr before encoding letter */
  int pcloc[15], poloc[15], pwloc[15];

  /* the position within the encoded string of the letter */
  int cord[15], oord[15], word[15];

  int cc, oc, wc;
  int p;

  /* initialize *loc, p*loc, and *ord arrays */
  cc = oc = wc = 0;
  p = -1;
  for (lv = 0, c = head; c != -1; c = next[c], lv++)
   {
    if (str[c] == 'C') 
     {
      cord[cc] = lv;
      pcloc[cc] = p;
      cloc[cc++] = c;
     }
    if (str[c] == 'O') 
     {
      oord[oc] = lv;
      poloc[oc] = p;
      oloc[oc++] = c;
     }
    if (str[c] == 'W') 
     {
      word[wc] = lv;
      pwloc[wc] = p;
      wloc[wc++] = c;
     }
    p = c;
   }

  pc = -1;
  if (lvl == 0) return check_frags(); /* all encodings undone */
  lvl--;
  for (c = 0; c < cc; c++)
   {
    lc = cloc[c];
    pc = pcloc[c];
    for (o = 0; o < oc; o++)
     {
      /* O must be after the C */
      if (cord[c] > oord[o]) continue;
      lo = oloc[o];
      po = poloc[o];
      for (w = 0; w < wc; w++)
       {
        /* W must be after the O */
        if (oord[o] > word[w]) continue;
        lw = wloc[w];
	pw = pwloc[w];
	do_xform(pc, po, pw);

	/* depending on level, perform different checks */
	if (lvl <= 1 || check_frags())
	 {
	  if (lvl < 3 || !check_hash())
	   {
	    if (find_str()) return 1; /* we found a match! */
	   }
	 }

        /* undo the do_xform */
	if (pc == -1) head = lc;
	else next[pc] = lc;
	next[po] = lo;
	next[pw] = lw;
       }
     }
   }
  lvl++;
  return 0;
 }

int main(int argc, char **argv)
 {
  FILE *fout, *fin;
  int len;
  char end[MAXLEN];
  int rv;

  /* initialize fragment arrays (starts/nstart) */
  fill_start();

  if ((fin = fopen("cryptcow.in", "r")) == NULL)
   {
    perror ("fopen fin");
    exit(1);
   }
  if ((fout = fopen("cryptcow.out", "w")) == NULL)
   {
    perror ("fopen fout");
    exit(1);
   }

  fgets(str, sizeof(str)-1, fin);
  len = strlen(str);

  /* eat trailing newlines */
  while (!isalpha(str[len-1])) str[--len] = '\0';

  /* initialize the linked list */
  for (rv = 0; rv < len; rv++) next[rv] = rv+1;
  next[len-1] = -1;
  head = 0;


  /* make sure distribution is correct */
  rv = check_distrib(str);
  if (!rv || !check_frags())
   { /* distribution or frags don't match, can't decode */
    fprintf (fout, "0 0\n");
    return 0;
   }

  lvl = (len - 47) / 3; /* number of decodes to perform */
  if (find_str())
    fprintf (fout, "1 %i\n", rv-1);
  else
    fprintf (fout, "0 0\n");

  return 0;
 }


//#include <iostream>
//#include <string>
//#include <algorithm>
//using namespace std ;
//#define llong unsigned long long 
//#define unint unsigned int
//#define printline  printf( "\n" ) 
//
//const int INF = 1000000 ;
//const int size = 155 ;
//const int hashsize = 551071 ;
//
//bool hasHashed[hashsize] = { false } ;
//const string dest = "Begin the Escape execution at the Break of Dawn" ;
//string text ; string trans ;
//
//unsigned int ELFHash( string str )
//{
//    unsigned int hash = 0 ;
//    unsigned int x = 0 ;
//
//    for( int i=0; i<str.length(); i++ ) {
//        hash = ( hash << 4 ) + ( str[i] ) ;
//        if( ( x = hash & 0xF0000000L ) != 0 ) {
//            hash ^= ( x >> 24 ) ;
//            hash &= ~x ;
//        }
//    }
//
//    return ( hash & 0x7FFFFFFF ) ;
//}
//
//bool substr_in_dest( string &sour)
//{//判断夹在COW之间的字符串是否存在dest中
//    for( int i=0; i<sour.size(); i++ ) {
//
//        if( sour[i]=='C' || sour[i]=='O' || sour[i]=='W' )    continue ;
//
//        int j = i + 1 ;
//        for( j=i+1; j<sour.size(); j++ ) {
//            if( 'C'==sour[j] || 'O'==sour[j] || 'W'==sour[j] )    break ;
//        }
//        if( dest.find( sour.substr( i, j-i ) ) == string::npos )    return false ;
//
//        i = j ;
//    }
//
//    return true ;
//}
//
//string Transform( string &sour, int c, int o, int w )
//{
//    trans = "" ;
//    for( int i=0; i<c; i++ )        trans += sour[i] ;
//    for( int i=o+1; i<w; i++ )    trans += sour[i] ;
//    for( int i=c+1; i<o; i++ )    trans += sour[i] ;
//    for( int i=w+1; i<sour.size(); i++ )    trans += sour[i] ;
//
//    //trans += '\0' ;//trans != trans + '\0'
//    //cout << trans << endl ;
//    return trans ;
//}
//
//bool IsEncrypted( string sour )
//{
//    unsigned int hashval = ELFHash( sour ) % hashsize ;
//    if( hasHashed[hashval] )        return false ;
//    hasHashed[hashval] = true ;
//
//    if( sour == dest )    return true ;
//
//    if( false == substr_in_dest( sour ) )    return false ;
//
//    for( int o=1; o<sour.size(); o++ ) {//枚举－－然后深度优先搜索
//        if( 'O' == sour[o] ) {
//            for( int c=0; c<o; c++ ) {
//                if( 'C' == sour[c] ) {
//                    for( int w=sour.size()-1; w>o; w-- ) {
//                        if( 'W' == sour[w] ) 
//                            if( IsEncrypted( Transform( sour, c, o, w ) ) )    return true ;
//                    }//递归判断是否有一个合理的转换解，如果有直接return true; 相当于深度优先搜索
//                }
//            }
//        }
//    }
//
//    return false ;
//}
//
//int main()
//{
//    //freopen( "in.txt", "r", stdin ) ;
//    freopen( "cryptcow.in", "r", stdin ) ;
//    freopen( "cryptcow.out","w",stdout ) ;
//    
//    getline( cin, text ) ;    //cout << text << endl ;
//
//    if( ( text.size()-dest.size() ) % 3 != 0 )
//    { printf( "0 0\n" ) ; return 0 ; }
//
//    int numc, numo, numw ; numc = numo = numw = 0 ;
//    for( int i=0; i<text.size(); i++ ) {
//        if( 'C' == text[i] )    numc++ ;
//        if( 'O' == text[i] )    numo++ ;
//        if( 'W' == text[i] )    numw++ ;
//    }
//    if( numc!=numo || numc != numw || numo != numw )    
//    { printf( "0 0\n" ) ; return 0 ; }
//
//    if( IsEncrypted( text ) ) {
//        cout << "1 " << count( text.begin(),text.end(),'C' ) << endl ;
//    }
//    else {
//        printf( "0 0\n" ) ;
//    }
//    return 0 ;
//}

//#include<fstream>
//#include<string>
//#include<vector>
//#include<cassert>
//using namespace std;
//
//const string desStr("Begin the Escape execution at the Break of Dawn");
//vector<bool> hashtb(0xFFFF + 1);//,vector<string>()); // strlength + 1 or 0 : true or false
//
////unsigned strhash(const char *s){
////    unsigned hash = 0;
////    while(*s)
////        hash += (hash<<7) + (hash<<1) + (*s++);
////
////    return (hash & 0x7FFFF);
////}
//
//unsigned int strhash(const char* str){
//    unsigned int hash = 0;
//    unsigned int x    = 0;
//
//    while (*str){
//        hash = (hash << 4) + (*str++);
//        if ((x = hash & 0xF0000000L) != 0){
//            hash ^= (x >> 24);
//            hash &= ~x;
//        }
//    }
//    return (hash & 0xFFFF);
//}
//
//int FirstCheck(const string &srcStr){
//// assert the srcStr != desStr in advance
//// return encryption times if can check false
//// return 0 otherwise
//    assert(srcStr != desStr);
//
//    int cryptcnt = 0;
//    if(0 != (srcStr.size() - desStr.size()) % 3)return 0;
//    cryptcnt = (srcStr.size() - desStr.size()) / 3;
//
//    int Ccnt = 0, Ocnt = 0, Wcnt = 0;
//    for(string::const_iterator itr = srcStr.begin(); itr != srcStr.end(); ++itr){
//        switch(*itr){
//            case 'C':
//                ++ Ccnt;
//                break;
//            case 'O':
//                ++ Ocnt;
//                break;
//            case 'W':
//                ++ Wcnt;
//                break;
//        }
//    }
//    if(Ccnt != cryptcnt || Ocnt != cryptcnt || Wcnt != cryptcnt)return 0;
//
//    string curstr;
//    for(string::const_iterator itr=srcStr.begin(); itr!=srcStr.end(); ++itr){
//        if(*itr == 'C' || *itr == 'O' || *itr == 'W'){  // delim
//            if(!curstr.empty() && desStr.find(curstr) == string::npos)return 0;
//            curstr.clear();
//        } else {
//            curstr += *itr;
//        }
//    }
//    return cryptcnt;
//}
//
//bool CheckClip(const string &str, int pos){
//    string::size_type pos1, pos2;
//    pos1 = str.find_last_of("COW", pos) + 1;
//    if(pos1 == pos)return true;
//    pos2 = str.find_first_of("COW",pos);
//    if(pos2 == pos)return true;
//    if(desStr.find(str.substr(pos1,pos2-pos1)) == string::npos)return false;
//    else return true;
//}
//
//bool dfs(const string &srcstr){
//    unsigned hash = strhash(srcstr.c_str());
//    if(hashtb[hash])return false;
//    hashtb[hash] = true;
//    //while(hashtb[hash]){
//    //    if(hashtb[hash]->length() == srcstr.length()){
//    //        if(*(hashtb[hash]) == srcstr)return false;
//    //    }
//    //    hash = (hash+1)%0x7FFFF;
//    //}
//
//    vector<int> Cpos;
//    vector<int> Opos;
//    vector<int> Wpos;
//    for(string::const_iterator itr=srcstr.begin(); itr!=srcstr.end(); ++itr){
//        switch(*itr){
//            case 'C':
//                Cpos.push_back(itr-srcstr.begin());
//                break;
//            case 'O':
//                Opos.push_back(itr-srcstr.begin());
//                break;
//            case 'W':
//                Wpos.push_back(itr-srcstr.begin());
//                break;
//        }
//    }
//    if(Cpos[0] > Opos[0] || Cpos[0] > Wpos[0]){
//        //hashtb[hash] = true;
//        return false;
//    }
//    if(Wpos[Wpos.size()-1] < Opos[Opos.size()-1] || Wpos[Wpos.size()-1] < Cpos[Cpos.size()-1]){
//        //hashtb[hash] = true;
//        return false;
//    }
//
//    for(vector<int>::iterator oitr=Opos.begin(); oitr!=Opos.end(); ++oitr)
//        for(vector<int>::iterator citr=Cpos.begin(); citr!=Cpos.end() && *citr < *oitr; ++citr)
//            for(vector<int>::reverse_iterator witr=Wpos.rbegin(); witr!=Wpos.rend() && *oitr < *witr; ++witr){
//                string tmpstr = srcstr.substr(0,*citr)
//                    + srcstr.substr(*oitr+1, *witr-*oitr-1)
//                    + srcstr.substr(*citr+1, *oitr-*citr-1)
//                    + srcstr.substr(*witr+1, srcstr.size()-*witr-1);
//                if(tmpstr.length() == desStr.length()){
//                    if(tmpstr == desStr){
//                        return true;
//                    }
//                    else continue;
//                }
//                if(!CheckClip(tmpstr,*citr))continue;
//                if(!CheckClip(tmpstr,*citr+*witr-*oitr-1))continue;
//                if(!CheckClip(tmpstr,*witr-2))continue;
//                if(dfs(tmpstr)){
//                    return true;
//                }
//            }
//
//    //hashtb[hash] = new string(srcstr);
//    return false;
//}
//
//int main(){
//    string srcStr;
//    ifstream fin("cryptcow.in");
//    ofstream fout("cryptcow.out");
//    getline(fin, srcStr);
//    fin.close();
//    //srcStr.resize(srcStr.size() - 1);
//
//    if(srcStr == desStr){
//        fout<<"1 0"<<endl;
//        fout.close();
//        return 0;
//    }
//
//    int cryptcnt;
//    if((cryptcnt = FirstCheck(srcStr)) == 0){
//        fout<<"0 0"<<endl;
//        fout.close();
//        return 0;
//    }
//
//    if(dfs(srcStr)){
//        fout<<"1 "<<cryptcnt<<endl;
//    }else {
//        fout<<"0 0"<<endl;
//    }
//    fout.close();
//    return 0;
//}

//---------------------------------------------------

//#include<fstream>
//#include<string>
//#include<vector>
////#include<algorithm>
//#include<cassert>
//using namespace std;
//
//const string desStr("Begin the Escape execution at the Break of Dawn");
//vector<int> hashtb1(0xFFFFF,0); // strlength + 1 or 0 : true or false
//vector<int> hashtb2(0xFFFFF,0);
//
////inline bool longer(const string &str1, const string &str2){
////    return str1.length() > str2.length();
////}
//
//void strhash(const char *s, unsigned &hash1, unsigned &hash2){
//    hash1 = hash2 = 0;
//    while(*s){
//        hash1 += (hash1<<7) + (hash1<<1) + (*s);
//        hash2 = (hash2<<5) - hash2 + (*s++);
//    }
//    hash1 &= 0xFFFFF;
//    hash2 &= 0xFFFFF;
//}
//
//int FirstCheck(const string &srcStr){
//// assert the srcStr != desStr in advance
//// return encryption times if can check false
//// return 0 otherwise
//    assert(srcStr != desStr);
//
//    int cryptcnt = 0;
//    if(0 != (srcStr.size() - desStr.size()) % 3)return 0;
//    cryptcnt = (srcStr.size() - desStr.size()) / 3;
//
//    int Ccnt = 0, Ocnt = 0, Wcnt = 0;
//    for(string::const_iterator itr = srcStr.begin(); itr != srcStr.end(); ++itr){
//        switch(*itr){
//            case 'C':
//                ++ Ccnt;
//                break;
//            case 'O':
//                ++ Ocnt;
//                break;
//            case 'W':
//                ++ Wcnt;
//                break;
//        }
//    }
//    if(Ccnt != cryptcnt || Ocnt != cryptcnt || Wcnt != cryptcnt)return 0;
//
//    vector<string> clips;
//    string curstr;
//    for(string::const_iterator itr=srcStr.begin(); itr!=srcStr.end(); ++itr){
//        if(*itr == 'C' || *itr == 'O' || *itr == 'W'){  // delim
//            if(!curstr.empty()) clips.push_back(curstr);
//            curstr.clear();
//        } else {
//            curstr += *itr;
//        }
//    }
//    clips.push_back(curstr);
//    for(vector<string>::iterator itr=clips.begin(); itr!=clips.end(); ++itr){
//        if(desStr.find(*itr) == string::npos)return 0;
//    }
//    return cryptcnt;
//}
//
//bool CheckClip(const string &str, int pos){
//    string::size_type pos1, pos2;
//    pos1 = str.find_last_of("COW", pos) + 1;
//    if(pos1 == pos)return true;
//    pos2 = str.find_first_of("COW",pos);
//    if(pos2 == pos)return true;
//    if(desStr.find(str.substr(pos1,pos2-pos1)) == string::npos)return false;
//    else return true;
//}
//
//bool dfs(const string &srcstr){
//    //if(srcstr.length() == desStr.length()){
//    //    if(srcstr == desStr)return true;
//    //    else return false;
//    //}
//    //if(!CheckClip(srcstr))return false;
//    unsigned hash1, hash2;
//    strhash(srcstr.c_str(),hash1,hash2);
//    if(hashtb1[hash1] && hashtb1[hash1] == hashtb2[hash2])
//        return ((hashtb1[hash1]%3) == 1);
//
//    vector<int> Cpos;
//    vector<int> Opos;
//    vector<int> Wpos;
//    for(string::const_iterator itr=srcstr.begin(); itr!=srcstr.end(); ++itr){
//        switch(*itr){
//            case 'C':
//                Cpos.push_back(itr-srcstr.begin());
//                break;
//            case 'O':
//                Opos.push_back(itr-srcstr.begin());
//                break;
//            case 'W':
//                Wpos.push_back(itr-srcstr.begin());
//                break;
//        }
//    }
//    if(Cpos[0] > Opos[0] || Cpos[0] > Wpos[0]){
//        hashtb1[hash1]=hashtb2[hash2]=srcstr.length();
//        return false;
//    }
//    if(Wpos[Wpos.size()-1] < Opos[Opos.size()-1] || Wpos[Wpos.size()-1] < Cpos[Cpos.size()-1]){
//        hashtb1[hash1]=hashtb2[hash2]=srcstr.length();
//        return false;
//    }
//
//    for(vector<int>::iterator oitr=Opos.begin(); oitr!=Opos.end(); ++oitr)
//        for(vector<int>::iterator citr=Cpos.begin(); citr!=Cpos.end() && *citr < *oitr; ++citr)
//            for(vector<int>::reverse_iterator witr=Wpos.rbegin(); witr!=Wpos.rend() && *oitr < *witr; ++witr){
//                string tmpstr = srcstr.substr(0,*citr)
//                    + srcstr.substr(*oitr+1, *witr-*oitr-1)
//                    + srcstr.substr(*citr+1, *oitr-*citr-1)
//                    + srcstr.substr(*witr+1, srcstr.size()-*witr-1);
//                if(tmpstr.length() == desStr.length()){
//                    if(tmpstr == desStr){
//                        hashtb1[hash1]=hashtb2[hash2]=srcstr.length()+1;
//                        return true;
//                    }
//                    else continue;
//                }
//                if(!CheckClip(tmpstr,*citr))continue;
//                if(!CheckClip(tmpstr,*citr+*witr-*oitr-1))continue;
//                if(!CheckClip(tmpstr,*witr-2))continue;
//                if(dfs(tmpstr)){
//                    hashtb1[hash1]=hashtb2[hash2]=srcstr.length()+1;
//                    return true;
//                }
//            }
//
//    hashtb1[hash1]=hashtb2[hash2]=srcstr.length();
//    return false;
//}
//
//int main(){
//    string srcStr;
//    ifstream fin("cryptcow.in");
//    ofstream fout("cryptcow.out");
//    getline(fin, srcStr);
//    fin.close();
//    //srcStr.resize(srcStr.size() - 1);
//
//    if(srcStr == desStr){
//        fout<<"1 0"<<endl;
//        fout.close();
//        return 0;
//    }
//
//    int cryptcnt;
//    if((cryptcnt = FirstCheck(srcStr)) == 0){
//        fout<<"0 0"<<endl;
//        fout.close();
//        return 0;
//    }
//
//    if(dfs(srcStr)){
//        fout<<"1 "<<cryptcnt<<endl;
//    }else {
//        fout<<"0 0"<<endl;
//    }
//    fout.close();
//    return 0;
//}