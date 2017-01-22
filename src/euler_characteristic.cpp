#include "euler_characteristic.h"
#include "edges.h"

int euler_characteristic(const Eigen::MatrixXi &F)
{
  int Chi;
  int nfaces, nedges, nverts; 

  nfaces = F.rows(); 

  Eigen::MatrixXi E = edges(F);
  nedges = E.rows(); 

  // Still need to find the number of vertices; don't know how many edges go to each vertex
  int maxv = 0; 
  for (int f = 0; f < F.rows(); ++f) {
    if (F(f, 0) > maxv)
      maxv = F(f, 0); 
    if (F(f, 1) > maxv) 
      maxv = F(f, 1); 
    if (F(f, 2) > maxv)
      maxv = F(f, 2); 
  }
  nverts = maxv + 1; 

  Chi = nverts - nedges + nfaces; 

  return Chi;
}
