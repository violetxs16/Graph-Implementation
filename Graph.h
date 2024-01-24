#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include "List.h"

#define INF -1
#define NIL -2

typedef struct GraphObj *Graph;
/** Constructors-Destructors **/
Graph newGraph(int n); //Return newly created GraphObj representing a graph having n vertices and no edges
Graph freeGraph(Graph *pG); //Frees all heap memory associated with the Graph *pG then sets the handle *pG to NULL

/** Access Functions **/
int getOrder(Graph G); //Return the corresponding field values
int getSize(Graph G);
int getSource(Graph G); //Returns the source vertex most recently used in function BFS or NIL if BFS has not yet been called
int getParent(Graph G, int u); //Return the parent of vertex u in the BFS tree created by BFS() or NIL if BFS() has not yet been called
int getDist(Graph G, int u); //Returns the distance from the most recent BFS source to vertex u or INF is BFS() has not yet been called
void getPath(List L, Graph G, int u); //Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value of NIL if no such path exists
//Pre condition: getSource(G) 1= NIL so BFS must be called before getPath() is called
//getParent, egtDist and getPath->preCondition: 1 <= u <= getOrder(G)
int PrintPath(List L, Graph G, int s, int u);


/** Manipulation procedures **/
void makeNull(Graph G); //Deletes al edges of G, restoring it to its original (no edge) state
void addEdge(Graph G, int u, int v); //Inserts a new edge joining u to v. I.e u is added to the adjancency List of v, and v to the adjencency List of u(Increasing order labels)
void addArc(Graph G, int u, int v); //Inserts a new directed edge from u to v. i.e v is added to the adjency List of u(but no u to the adjencency List of V)
//Pre-Cond(edge,arv): two int aargs must lie in the range 1 to getOrder(G)
void BFS(Graph G, int s); //runs the BFS algorithm on the Graph G with source s,setting the color, distance, parent, and source fields of G accordingly

/** other operations **/
void printGraph(FILE *out, Graph G); //prints the adjacency list representation of G to the file pointed to by out

#endif
