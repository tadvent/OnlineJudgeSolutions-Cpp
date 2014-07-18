/*
ID: wjl1241
PROG: fence4
LANG: C++
*/

#include<fstream>
#include<vector>
#include<utility>
#include<cmath>
#include<limits>
using namespace std;

const double eps=100.0*numeric_limits<double>::epsilon();
const double Pi=3.141592653589793;

int N;
pair<int,int> person;
vector< pair<int,int> > vCorners;
vector<double> vAngles;
vector< pair<int,int> > vCansee;

template<typename T>
inline T crossproduct(const pair<T,T> &vec1, const pair<T,T> &vec2){
    return vec1.first*vec2.second-vec1.second*vec2.first;
}

template<typename T>
inline pair<T,T> operator-(const pair<T,T> &vec1, const pair<T,T> &vec2){
    return make_pair<T,T>(vec1.first-vec2.first,vec1.second-vec2.second);
}

template<typename T>
inline bool IsOtherside(const pair<T,T> &line_s, const pair<T,T> &line_e,
                const pair<T,T> &point1, const pair<T,T> &point2){
    T pdt1,pdt2;
    pdt1=crossproduct(line_s-point1,line_e-point1);
    pdt2=crossproduct(line_s-point2,line_e-point2);

    if( (pdt1>0 && pdt2<0) || (pdt1<0 && pdt2>0) )return true;
    return false;
}

template<typename T>
inline bool IsSameside(const pair<T,T> &line_s, const pair<T,T> &line_e,
                const pair<T,T> &point1, const pair<T,T> &point2){
    T pdt1,pdt2;
    pdt1=crossproduct(line_s-point1,line_e-point1);
    pdt2=crossproduct(line_s-point2,line_e-point2);

    if( (pdt1>0 && pdt2>0) || (pdt1<0 && pdt2<0) )return true;
    return false;
}

template<typename T>
inline bool IsCrossed(const pair<T,T> &seg1s, const pair<T,T> &seg1e,
               const pair<T,T> &seg2s, const pair<T,T> &seg2e){
   return (IsOtherside(seg1s,seg1e,seg2s,seg2e) && IsOtherside(seg2s,seg2e,seg1s,seg1e));
}

void angle2range(int ang1_idx, int ang2_idx, int &st_idx, int &ed_idx){
    if(vAngles[ang1_idx]<vAngles[ang2_idx]){
        st_idx=ang1_idx;
        ed_idx=ang2_idx;
    }
    else {
        st_idx=ang2_idx;
        ed_idx=ang1_idx;
    }
    if(vAngles[ed_idx]-vAngles[st_idx]>Pi){
        swap(st_idx,ed_idx);
    }
}

int main(){
    ifstream fin("fence4.in");
    ofstream fout("fence4.out");
    fin>>N>>person.first>>person.second;
    vCorners.resize(2*N);
    vAngles.resize(2*N);
    for(int i=0;i<N;++i){
        fin>>vCorners[i].first>>vCorners[i].second;
        vCorners[i+N]=vCorners[i];
    }

    for(int i=0;i<=N;++i){
        for(int j=1;j<i;++j)
            if(IsCrossed(vCorners[j-1],vCorners[j],vCorners[i-1],vCorners[i])){
                fout<<"NOFENCE"<<endl;
                return 0;
            }
    }

    //can produce a fence:
    for(int i=0;i<N;++i){
        vAngles[i]=atan2(double(vCorners[i].second-person.second),double(vCorners[i].first-person.first));
        vAngles[i+N]=vAngles[i];
    }

    for(int i=0;i<N;++i){
        double st,ed;
        int st_idx,ed_idx;
        angle2range(i,i+1,st_idx,ed_idx);
        st=vAngles[st_idx];
        ed=vAngles[ed_idx];
        if(st>ed)ed+=2.0*Pi;
        for(int j=i+1;j<i+N && st<ed;++j){
            double covst,coved;
            int covst_idx,coved_idx;
            angle2range(j,j+1,covst_idx,coved_idx);
            covst=vAngles[covst_idx];
            coved=vAngles[coved_idx];
            if(covst>coved)coved+=2.0*Pi;
            if(coved>st && coved<ed &&  covst<st+eps
&& IsSameside(vCorners[i],vCorners[i+1],vCorners[coved_idx],person)){
                st=coved;
            }
            if(covst>st && covst<ed && coved>ed-eps
&& IsSameside(vCorners[i],vCorners[i+1],vCorners[covst_idx],person)){
                ed=covst;
            }
            if(covst<st+eps && coved>ed-eps
&& (IsOtherside(vCorners[j],vCorners[j+1],vCorners[i],person)
|| IsOtherside(vCorners[j],vCorners[j+1],vCorners[i+1],person)) ){
                st=coved;
                ed=covst;
            }

            if(covst<0){
                coved+=2.0*Pi;
                covst+=2.0*Pi;
                if(coved>st && coved<ed &&  covst<st+eps
&& IsSameside(vCorners[i],vCorners[i+1],vCorners[coved_idx],person)){
                    st=coved;
                }
                if(covst>st && covst<ed && coved>ed-eps
&& IsSameside(vCorners[i],vCorners[i+1],vCorners[covst_idx],person)){
                    ed=covst;
                }
                if(covst<st+eps && coved>ed-eps
&& (IsOtherside(vCorners[j],vCorners[j+1],vCorners[i],person)
|| IsOtherside(vCorners[j],vCorners[j+1],vCorners[i+1],person)) ){
                    st=coved;
                    ed=covst;
                }
            }
        }
        if(st<ed){   // can see the i - i+1 fence
            vCansee.push_back(make_pair<int,int>(i,i+1));
        }
    }

    if(vCansee.back().second == N){
        vCansee.back().second=vCansee.back().first;
        vCansee.back().first=0;
        if(vCansee.size()>1 && vCansee[vCansee.size()-2].second == N-1)
            swap(vCansee[vCansee.size()-1],vCansee[vCansee.size()-2]);
    }

    fout<<vCansee.size()<<'\n';
    for(int i=0;i<(int)vCansee.size();++i){
        fout<<vCorners[vCansee[i].first].first<<' '<<vCorners[vCansee[i].first].second
            <<' '<<vCorners[vCansee[i].second].first<<' '<<vCorners[vCansee[i].second].second<<'\n';
    }
}

//========================================================================
//========================================================================

//standard program

//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//
//#define SQR(A) ((A)*(A))
//
///* maximum number of points */
//#define MAXN 201
//
///* number of points */
//int npos;
//
///* the points, where pos[npos] == pos[0] */
//double pos[MAXN][2];
//
///* observer's location */
//double obsx, obsy;
//
///* cansee[x] = can we see the segment (x,x+1)? */
//int cansee[MAXN];
//
//int side(double sx, double sy, double ex, double ey, int p)
// { /* determine the side that the points lie on */
//  double dx, dy;
//  double px, py;
//  double t;
//
//  dx = ex - sx;
//  dy = ey - sy;
//
//  px = pos[p][0] - sx;
//  py = pos[p][1] - sy;
//
//  /* take cross-product */
//  t = dx * py - dy * px;
//
//  if (t > 0.00001) return 0; /* "left" side */
//  if (t < -0.00001) return 1; /* "right" side */
//  return 2; /* on the line */
// }
//
//int first_inter(double sx, double sy, double ex, double ey)
// { /* what is the first segment intersected by the ray s->e */
//  int lv; /* loop variable */
//  int t1, t2;
//  int s1, s2;
//  double ax, ay, bx, by;
//  double t;
//  double coeff, cnst;
//  double i, j;
//  double x, y;
//  double mlbrush, mrbrush; /* when is the earliest brush on a side? */
//
//  /* min = distance to nearest intersection point */
//  /* mloc = edge where this occurs */
//  double min = 1e10; /* ~= infinity */
//  int mloc = npos; /* unused location */
//
//  mlbrush = mrbrush = 1e10; /* infinity */
//
//  for (lv = 0; lv < npos; lv++)
//   { /* for each segment, determine length along */
//    ax = pos[lv][0];
//    ay = pos[lv][1];
//    bx = pos[lv+1][0];
//    by = pos[lv+1][1];
//
//    /* take cross product */
//    t = (ex - sx) * (ay - by) - (ey - sy) * (ax - bx);
//    if (t > -0.00001 && t < 0.00001) /* parallel */
//      continue; /* not considered visible */
//
//    /* not parallel */
//    /* we are now solving the following equations:
//     (ex - sx) j + sx = (bx - ax) i + ax
//     (ey - sy) j + sy = (by - ay) i + ay
//    */
//
//    /* solves for alpha by multiple first by (by - ay) and
//       the second by (bx - ax) and subtracting equations */
//    cnst = (ax - sx)*(by - ay) - (ay - sy)*(bx - ax);
//    coeff = (ex - sx) * (by - ay) - (ey - sy) * (bx - ax);
//    if (coeff > -0.00001 && coeff < .00001)
//     { /* degenerate, one of bx - ax and by - ay is about zero */
//      if (bx - ax > -.00001 && bx - ax < 0.00001)
//       { /* bx - ax == 0, can solve first eqn directly */
//        cnst = ax - sx;
//        coeff = ex - sx;
//       } else { /* by - ay == 0, can solve second eqn directly */
//        cnst = ay - sy;
//        coeff = ey - sy;
//       }
//     }
//    j = cnst / coeff;
//
//    /* if intersection occurs before starting point, no intersection */
//    if (j < -.00001) continue;
//
//    /* determine beta */
//    cnst = sx + (ex - sx) * j - ax;
//    coeff = bx - ax;
//    if (coeff > -0.00001 && coeff < .00001)
//     { /* handle degeneracy */
//      cnst = sy + (ey - sy) * j - ay;
//      coeff = by - ay;
//     }
//    i = cnst / coeff;
//
//    /* if the interesection occurs with i < 0 | i > 1, the
//       intersection is not within the confines of the segment */
//    if (i < -.00001 || i > 1.00001) continue;
//
//    /* calculate intersection point */
//    x = ax + (bx - ax) * i;
//    y = ay + (by - ay) * i;
//
//    /* determine distance along line that intersection occurs */
//    t = (x - sx) * (ex - sx) + (y - sy) * (ey - sy);
//
//    /* make sure it's in bounds, and better than what we have */
//    if (t < -0.00001 || t > min) continue;
//    
//    /* if it occurs at an end point */
//    if (i < .00001 || i > 0.99999) 
//     {
//      /* find the endpoints that are incident to the intersected endpoint */
//      if (i < .00001)
//       {
//        t1 = lv-1;
//        if (t1 < 0) t1 += npos;
//        t2 = lv+1;
//       } else {
//        t1 = lv;
//        t2 = lv+2;
//        if (t2 >= npos) t2 -= npos;
//       }
//
//      /* if they lie on the same side of the line, then ray 'brushes'
//         endpoint, which is not considered to an intersection */
//
//      s1 = side(sx,sy,ex,ey,t1);
//      s2 = side(sx,sy,ex,ey,t2);
//      if (s1 == s2) {
//	if (s1 == 0 && t < mlbrush) mlbrush = t;
//	if (s1 == 1 && t < mrbrush) mrbrush = t;
//        continue;
//      }
//     }
//    /* found a better edge! */
//    min = t;
//    mloc = lv;
//   }
///* if it brushes on both sides, it cannot be seen */
//  if (min > mlbrush && min > mrbrush) return npos;
//  return mloc;
// }
//
//int check_intersect(int f1, int f2) 
// { /* do (f1,f1+1) and (f2,f2+1) intersect? */
//  double sx, sy;
//  double ex, ey;
//  
//  sx = pos[f1][0];
//  sy = pos[f1][1];
//  ex = pos[f1+1][0];
//  ey = pos[f1+1][1];
//
//  if (side(sx, sy, ex, ey, f2) == side(sx, sy, ex, ey, f2+1))
//  /* are the f2 and f2+1 on the same side of (f1,f1+1)? */
//    return 0; /* if so, the segments don't intersect */
//
//  sx = pos[f2][0];
//  sy = pos[f2][1];
//  ex = pos[f2+1][0];
//  ey = pos[f2+1][1];
//
//  if (side(sx, sy, ex, ey, f1) == side(sx, sy, ex, ey, f1+1))
//  /* are f1 & f1+1 on the same side of (f2,f2+1) */
//    return 0; /* if so, the segments don't intersect */
//
//  /* the endpoints of each segment are on opposite sides of
//     the other segment.  Therefore, they intersect */
//  return 1; 
// }
//
//int main(int argc, char **argv)
// {
//  FILE *fout, *fin;
//  int lv, lv2;
//  int cnt;
//  int t;
//  double dx, dy;
//
//  if ((fin = fopen("fence4.in", "r")) == NULL)
//   {
//    perror ("fopen fin");
//    exit(1);
//   }
//  if ((fout = fopen("fence4.out", "w")) == NULL)
//   {
//    perror ("fopen fout");
//    exit(1);
//   }
//
//  fscanf (fin, "%d", &npos);
//  fscanf (fin, "%lf %lf", &obsx, &obsy);
//  for (lv = 0; lv < npos; lv++)
//    fscanf (fin, "%lf %lf", &pos[lv][0], &pos[lv][1]);
//  pos[npos][0] = pos[0][0];
//  pos[npos][1] = pos[0][1];
//
///* for each pair of segments that don't share a vertex */
//  for (lv = 0; lv < npos; lv++)
//    for (lv2 = lv+2; lv2 < npos; lv2++)
//      if (check_intersect(lv, lv2))
//       { /* if they intersect */
//
//        /* and don't share a vertex */
//        if (lv == 0 && lv2 == npos-1) continue; 
//
//        /* then the fence is invalid */
//        fprintf (fout, "NOFENCE\n"); 
//        return 0;
//       }
//
//  for (lv = 0; lv < npos; lv++)
//   {
//    /* check endpoint */
//    cansee[first_inter(obsx, obsy, pos[lv][0], pos[lv][1])] = 1;
//
//    /* check midpoint of segment (lv, lv+1) */
//    cansee[first_inter(obsx, obsy, 
//               (pos[lv][0] + pos[lv+1][0])*0.5, 
//               (pos[lv][1] + pos[lv+1][1])*0.5)] = 1;
//   }
//
//  /* count number of visible segments */
//  cnt = 0;
//  for (lv = 0; lv < npos; lv++)
//    if (cansee[lv]) cnt++;
//
//  fprintf (fout, "%i\n", cnt);
//
//  /* list visible segments */
//  for (lv = 0; lv < npos-2; lv++)
//    if (cansee[lv])
//     {
//      fprintf (fout, "%.0f %.0f %.0f %.0f\n", pos[lv][0], pos[lv][1], 
//            pos[lv+1][0], pos[lv+1][1]);
//     }
//  /* because of the way the ordering is defined, these two must be
//     checked separately */
//  if (cansee[npos-1])
//   {
//    fprintf (fout, "%.0f %.0f %.0f %.0f\n", pos[0][0], pos[0][1], 
//          pos[npos-1][0], pos[npos-1][1]);
//   }
//  if (cansee[npos-2])
//   {
//      fprintf (fout, "%.0f %.0f %.0f %.0f\n", pos[npos-2][0], pos[npos-2][1], 
//            pos[npos-2+1][0], pos[npos-2+1][1]);
//   }
//   
//  return 0;
// }
//
