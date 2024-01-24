#include <stdio.h>
#include <stdbool.h>


#include "Graph.h"

static bool CALLED = false;

int curr_source = -1;
int size = 0;//Total number of vertices
int edges = 0;//Number of edges
//Priavte struct
typedef struct GraphObj{
	List *adj; //i'th element contains neighbors of vertex i
	char *color;
	int *parent;
	int *distance;
}GraphObj;
/** Constructors-Destructors **/
Graph newGraph(int n){//Return newly created GraphObj representing a graph having n vertices and no edges
	Graph graph;
	graph = malloc(sizeof(GraphObj));
	for(int i= 0; i < n; i++){//Initialize vertex at i to null adj list
		graph->adj[i] = newList();
	}
	graph->color = malloc(sizeof(char) * n);
	graph->parent = malloc(sizeof(int) * n);
	graph->distance = malloc(sizeof(int) * n );

	size = n;
	return graph;
}
void freeGraph(Graph *pG){ //Frees all heap memory associated with the Graph *pG then sets the handle *pG to NULL
	if(pG != NULL && *pG != NULL){
		for(int i=0; i < *pG->adj->length; i++){
			free(*pG->color[i]);
			free(*pG->parent[i]);
			free(*pG->distance[i]);
		}
		freeList(&pG->adj);
	}
	free(*pG);
	*pG = NULL;
}

/** Access Functions **/
int getOrder(Graph G){
	if(G == NULL){
		fprintf(stder,"Graph Error: calling getOrder with NULL graph\n");
		exit(EXIT_FAILURE);
	}
	return size; // Recheck
} //Return the corresponding field values
int getSize(Graph G){//Num of edges
	if(G == NULL){
                fprintf(stder,"Graph Error: calling getSize with NULL graph\n");
                exit(EXIT_FAILURE);
        }
	return edges;//Recheck
}
int getSource(Graph G){//Returns the source vertex most recently used in function BFS or NIL if BFS has not yet been called
	 if(G == NULL){
                fprintf(stder,"Graph Error: calling getSource with NULL graph\n");
                exit(EXIT_FAILURE);
        }
	if(CALLED == false){
		return NIL;
	}
	return curr_source;
}
int getParent(Graph G, int u){//Return the parent of vertex u in the BFS tree created by BFS() or NIL if BFS() has not yet been called
	if(G == NULL){
                fprintf(stder,"Graph Error: calling getParent with NULL graph\n");
                exit(EXIT_FAILURE);
        }
        if(CALLED == false){
                return NIL;
        }
	if(1 <= u && u <= getOrder(G)){
		return G->parent[u];
	}
	return NIL;
}
int getDist(Graph G, int u){//Returns the distance from the most recent BFS source to vertex u or INF is BFS() has not yet been called
	if(G == NULL){
                fprintf(stder,"Graph Error: calling getParent with NULL graph\n");
                exit(EXIT_FAILURE);
        }
        if(CALLED == false){
                return NIL;
        }
	if(1 <= u && u <= getOrder(G)){
		return G->distance[u];
	}
	return NIL;
}

void getPath(List L, Graph G, int u){
	if(G == NULL){
                fprintf(stder,"Graph Error: calling getParent with NULL graph\n");
                exit(EXIT_FAILURE);
        }
        if(CALLED == false){
                return NIL;
        }
	if(1 <= u && u <= getOrder(G)){
		PrintPath(L,G,curr_source,u);
	}
	return NIL;
}
int PrintPath(L,G,s,u){//Helper method
	if(u == s){
		append(L,s);
	}else if(G->parent[u] == NIL){
		append(L,NIL);
	}else{
		PrintPath(G,s,G->parent[u]);
		append(L,u);
	}
}
//Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the va>
//Pre condition: getSource(G) 1= NIL so BFS must be called before getPath() is called
//getParent, egtDist and getPath->preCondition: 1 <= u <= getOrder(G)

/** Manipulation procedures **/
void makeNull(Graph G){//Deletes al edges of G, restoring it to its original (no edge) state
	if( G == NULL){
		fprintf(stder,"Graph Error: calling makeNull with NULL graph\n");
                exit(EXIT_FAILURE);
	}
	freeList(&G->adj);//Free parent too?
}
void addEdge(Graph G, int u, int v){//Inserts a new edge joining u to v. I.e u is added to the adjancency List of v, and v to the adjencen
	if(G == NULL){
                fprintf(stder,"Graph Error: calling addEdge with NULL graph\n");
                exit(EXIT_FAILURE);
        }
//** Adding v to adjcency list of u **//
	if(length(G->adj[u]) == 0){
		append(G->adj[u], v);
	}else{
		 for (int i = 1; i < G->adj[u]->length; i++) {
        		moveBack(G->adj[u]);
        		while (index(G->adj[u]->length) >= 0 && strcmp(v, get(G->adj[u]) < 0) {
                		movePrev(G->adj[u]);
        		}
        		if (index(G->adj[u]) >= 0) {
                		insertAfter(G->adj[u], i);
        		}else{
                		prepend(G->adj[u], i);
        		}
    		}
	}
//** Adding u to adjency list of v **//
	if(length(G->adj[v]) == 0){
		append(G->adj[v], u);
	}else{
		 for (int i = 1; i < G->adj[v]->length; i++) {
                        moveBack(G->adj[v]);
                        while (index(G->adj[v]->length) >= 0 && strcmp(u, get(G->adj[v]) < 0) {
                                movePrev(G->adj[v]);
                        }
                        if (index(G->adj[v]) >= 0) {
                                insertAfter(G->adj[v], i);
                        }else{
                        	prepend(G->adj[v], i);
                        }
                }
	}
	edges++;
}
void addArc(Graph G, int u, int v){//Insertes a directed edge from u to v
	if(G == NULL){
		fprintf(stder,"Graph Error: calling addArc with NULL graph\n");
                exit(EXIT_FAILURE);
	}
	//** Adding v to adjency list of u **//
	if(length(G->adj[u]) == 0){
                append(G->adj[u], v);
        }else{
                 for (int i = 1; i < G->adj[u]->length; i++) {
                        moveBack(G->adj[u]);
                        while (index(G->adj[u]->length) >= 0 && strcmp(v, get(G->adj[u]) < 0) {
                                movePrev(G->adj[u]);
                        }
                        if (index(G->adj[u]) >= 0) {
                                insertAfter(G->adj[u], i);
                        }else{
                                prepend(G->adj[u], i);
                        }
                }
        }
        edges++;
}
void BFS(Graph G, int s){//runs the BFS algorithm on the Graph G with source s,setting the color, distance, parent, and source fields of G>
	if(G == NULL){
		fprintf(stderr,"Graph Error: calling BFS on NULL graph");
	}

	List Queue = newList();
	curr_source = s;
	//First intialize all vertices to default values
	for(int i= 0; i < size; i++){
		G->color[i] = 'w';
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	//Reinitalize source element
	G->color[s] = 'g';
	G->parent[s] = NIL;
	G->distance[s] = 0;//Trivial path

	//Enqueue source
	append(Queue,s);

	//Start BFS
	while(length(Queue) > 0){
		int vertex = front(Queue);//Dequeue element
		deleteFront(Queue);

		moveFront(G->adj[vertex]);
   		while(index(G->adj[vertex]) >= 0){
			if(strcmp(G->color[get(G->adj[vertex])],'w'){//If undiscovered change: color, parent, distance and add to queue
				G->color[get(G->adj[vertex])] = 'g';
				G->parent[get(G->adj[vertex])] = vertex;
				G->distance[get(G->adj[vertex])] = G->distance[vertex] + 1;
				append(Queue,get(G->adj[vertex]));
			}
       			moveNext(ordered);
   		}
		G->color[vertex] = 'b';
	}
	CALLED = true;
}


/** other operations **/
void printGraph(FILE *out, Graph G){ //prints the adjacency list representation of G to the file pointed to by out
	if(L == NULL){
        	printf("Graph Error: calling printGraph() on NULL List\n");
        	exit(EXIT_FAILURE);
    	}
    	if(out == NULL){
        	printf("Graph Error: calling printGraph() on NULL File\n");
        	exit(EXIT_FAILURE);
    	}
	for(int i=0; i < size; i++){
		fprintf(out,"%d : ",i);
		PrintList(out,G->adj[i]);
		fprintf(out,"\n");
	}
}

