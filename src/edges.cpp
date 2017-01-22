#include "edges.h"
#include <cstdio>
#include <list>
#include <algorithm>

// Order the vertices from smallest to largest 
void orderIndices(int a, int b, int c, int &i0, int &i1, int &i2) 
{
     // Order the vertices from smallest to largest
    if (a <= b) {
      if (a <= c) { 
        if (b <= c) { //abc
          i0 = a; 
          i1 = b;
          i2 = c;
        }
        else { // acb
          i0 = a; 
          i1 = c;
          i2 = b;
        }
      }
      else { // cab
        i0 = c;
        i1 = a;
        i2 = b;
      }   
    }
    else {
      if (b <= c) { 
        if (a <= c) { // bac
          i0 = b; 
          i1 = a; 
          i2 = c; 
        }
        else { // bca
          i0 = b;
          i1 = c;
          i2 = a;
        }
      }
      else { // cba
        i0 = c; 
        i1 = b;
        i2 = a;
      }
    }
}

Eigen::MatrixXi edges(const Eigen::MatrixXi &F)
{
  Eigen::MatrixXi E(3*F.rows(), 2); 
 
  // There are at most 3*F unique vertices
  std::list<int> verte[3*F.rows()];
 
  // For each face (a,b,c)
  int i0, i1, i2;
  for (int f = 0; f < F.rows(); ++f) {
    orderIndices(F(f, 0), F(f, 1), F(f, 2), i0, i1, i2);
    verte[i0].push_front(i1); 
    verte[i0].push_front(i2);
    verte[i1].push_front(i2);
  }

  int laste = -1; // use to check for duplicates
  int edges = 0; // number of unique edges

  for (int vi = 0; vi < 3*F.rows(); ++vi) {
    if (verte[vi].size() < 1)
      continue; 
    
    verte[vi].sort();
    
    for (std::list<int>::iterator vit = verte[vi].begin(); vit != verte[vi].end(); ++vit) { 
      if (laste != *vit) { // not a duplicate
        E(edges, 0) = vi; 
        E(edges, 1) = *vit; 
        ++edges; 
        laste = *vit;       
      } 
    }
    laste = -1; 
  }
  
  E.resize(edges, 2);
 
  return E;
}
