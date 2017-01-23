Eszter Offertaler, eo2309
Digital Geometry Processing
Spring 2017
Homework 0: An Introduction

///////////////////////////////////////////////////////////
edges.cpp

The complex part of the problem is finding and removing edge duplicates: 
you can't just iterate through all of the faces and add their edges.
 
You could potentially have an adjacency matrix for the mesh to store whether 
you've already seen an edge, but that would take a huge amount of space (O(V^2)).  

You could also just add all edges as you go, and then find/remove duplicates by
sorting them (under the restriction that for each edge (i,j), i <= j). But 
sorting all of the edges would be O((3*F)lg(3*F)). 

Instead, again with the restriction that for each edge (i,j), i <= j, I stored 
edges in an adjacency list, indexed by the smaller vertex index in the edge pair. 
If the max number of edges / vertex is K, space taken is O(V*K), and the initial 
traversal is O(3*F). 
Then, I sort each edge list (O(V*K*lg(K)) and again traverse the whole thing to 
collect the unique edges, skipping over edge pairs that are the same as the last 
one processed. This is again O(V*K). 


///////////////////////////////////////////////////////////
euler_characteristic.cpp

I made the assumption that all inputs will be well-behaved, polyhedral 
surfaces with no unreferenced vertices or repeated faces.

The Euler characteristic  was calculated via the following formula: 
  Chi = |V| - |E| + |F|

The number of faces, |F|, was obtained by taking the number of rows of F. 
Similarly, the number of edges, |E|, was obtained by calling the edges()
function and taking the number of rows of the resulting matrix. 

Because we can't make any assumptions about how many edges actually go 
to a vertex, or how many faces reuse vertices, the number of vertices 
can't necessarily be obtained from the number of faces and edges (although 
for convex polyhedra the euler characteristic will just be 2). 
So to find the number of vertices, I did a linear search over the face indices
for the largest vertex index, under the reasonable assumption that vertex indices 
are contiguous. 

