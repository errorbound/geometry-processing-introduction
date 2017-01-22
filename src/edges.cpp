#include "edges.h"
#include <cstdio>

#define DEBUG

Eigen::MatrixXi edges(const Eigen::MatrixXi &F)
{
  Eigen::MatrixXi E;
 
  // There are at most 3*F unique vertices
  // Each vertex has some relatively small number of edges going to it
  // These are undirected edges; it doesn't matter which vertex is listed first
 
  std::vector<int> verte[3*F.rows()];
 
  // For each face (a,b,c)
  int i0, i1, i2; 
  for (int f = 0; f < F.rows(); ++f) {
    // Order the vertices from smallest to largest
    if (F(f, 0) <= F(f, 1)) { // a <= b
      if (F(f, 0) <= F(f, 2)) { // a <= c
        if (F(f, 1) <= F(f, 2)) { // b <= c: abc
          i0 = F(f, 0); 
          i1 = F(f, 1);
          i2 = F(f, 2);
        }
        else { // acb
          i0 = F(f, 0); 
          i1 = F(f, 2);
          i2 = F(f, 1);
        }
      }
      else { // cab
        i0 = F(f, 2);
        i1 = F(f, 0);
        i2 = F(f, 1);
      }   
    }
    else {
      if (F(f, 1) <= F(f, 2)) { // b <= c
        if (F(f, 0) <= F(f, 2)) { // a <= c: bac
          i0 = F(f, 1); 
          i1 = F(f, 0); 
          i2 = F(f, 2); 
        }
        else { // bca
          i0 = F(f, 1);
          i1 = F(f, 2);
          i2 = F(f, 0);
        }
      }
      else { // cba
        i0 = F(f, 2); 
        i1 = F(f, 1);
        i2 = F(f, 0);
      }
    }

  #if defined(DEBUG) 
    if (!(i0 <= i1 && i1 <= i2)) {
      fprintf(stderr, "index ordering failed!\n");
      exit(-1); 
    } 

  #endif

  
  }
  


  return E;
}
