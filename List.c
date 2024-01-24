#include<stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

//Structs
//Private node type
typedef struct NodeObj *Node;

//private ListObj type
typedef struct NodeObj{
    ListElement data; //Declared in .h
    struct NodeObj *next;
    struct NodeObj *prev;
}NodeObj;

//Private ListObj type
typedef struct ListObj{
    Node front;
    Node cursor;
    Node back;
    int index;
    int length;
}ListObj;


//Constructors-Deconstructors
Node newNode(ListElement data){
    Node N = malloc(sizeof(NodeObj));
    assert(N!= NULL);
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return(N);

}
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN){
    if(pN != NULL && *pN!= NULL){
        free(*pN);
        *pN = NULL;
    }
}
//Returns a new empty List object
List newList(){
    List L;
    L = malloc(sizeof(ListObj));
    assert(L != NULL);
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}

//Frees all heap memory associated with List *pL and sets *pL to NULL
void freeList(List *pL){
    if(pL != NULL && *pL != NULL){
        while(length(*pL) > 0){
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

//Access functions
int length(List L){//Returns the number of elements in L
    if(L == NULL){
        printf("List Error: calling length() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}
int index(List L){//Returns the index of cursor element if defined, -1 otherwise
    if(L == NULL){
        printf("List Error: calling index() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL){
        return L->index;
    }
    return -1;
} 
int front(List L){//Return front elemnt of L. Pre: Length() > 0
    if(L == NULL){
        printf("List Error: calling front() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) > 0){
        return L->front->data;
    }else{
	return -1;
   }
}
int back(List L){// Returns back element of L. Pre: Length() > 0
    if(L == NULL){
        printf("List Error: calling back() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) > 0){
        return L->back->data;
    }else{
	return -1;
	}
}
int get(List L){// Returns cursor element of L. Pre: Length() > 0, index()>=0
    if(L == NULL){
        printf("List Error: calling get() on NULL List\n");
    }
    if(length(L) > 0 && index(L) >=0){
        return L->cursor->data;
    }else{
	return -1;
	}
}

//Manipulation Procedures
void clear(List L){//Resets L to its original empty state
    if(L != NULL){
        while(L->length != 0){
            deleteFront(L);
        }
	L->front = L->back = L->cursor = NULL;
        L->length = 0;
	L->index = -1;
    }
	if(L->front != NULL)L->front = NULL;
	if(L->back != NULL)L->back = NULL;
	if(L->index != -1)L->index = -1;
	if(L->cursor != NULL)L->cursor = NULL;
	if(L->length != 0)L->length = 0;
}
void set(List L, int x){  // Overwrites the cursor element's data with x. Pre: length() > 0, index()>=0
    if(L == NULL){
        printf("List Error: calling set() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) > 0 && index(L) >=0){
        L->cursor->data = x;
    }
}
void moveFront(List L){// If L is non-empty, sets cursor under the front element, otherwise does nothing
    if(L == NULL){
        printf("List Error: calling moveFront() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(L->length > 0){
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List L){//If L is non-empty, sets the cursor under the back element, otherwise does nothing
    if(L == NULL){
        printf("List Error: calling moveBack() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(L->length > 0){
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

void movePrev(List L){//If cursor is defined and not at front, move cursor one step toward the front of L. If cursor is defined at front, cursor becomes undefined. If cursor is undefined do nothing
    if(L == NULL){
        printf("List Error: calling movePrev() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor != NULL && L->cursor != L->front){
        L->cursor = L->cursor->prev;
        L->index--;
    }else{
        L->cursor = NULL;
        L->index = -1;
    }
    
}

void moveNext(List L){//If cursor is defined and not at back, move cursor one step toward the back of L. If cursor is defiend and at back, cursor becomes undefined. if cursor is undefiend do nothing
    if(L == NULL){
        printf("List Error: calling moveNext() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor != NULL && L->cursor != L->back){
        L->cursor = L->cursor->next;
        L->index++;
    }else{
        L->cursor = NULL;
        L->index = -1;
    }
}

void prepend(List L, int x){//Insert new element int L. If L is non-empty, insertion takes place before front element
     if(L == NULL){
        printf("List Error: calling prepend() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    Node n = newNode(x);
    if(L->length == 0){
        L->front = L->back = L->cursor = n;
	L->index = 0;
    }else{

        n->next = L->front;
	L->front->prev = n;
	L->front = n;
	L->index = L->index + 1;
	}
   	 L->length++;
}

void append(List L, int x){//Inset new element in L. If L is non-emptu, insertaion takes place after back element
     if(L == NULL){
        printf("List Error: calling append() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    Node n = newNode(x);

    if(L->length == 0){
        L->front = L->back = L->cursor = n;
	L->index = 0;
    }else{
        n->prev = L->back;
        L->back->next = n;
        L->back = n; // New back is n
    }
    L->length++;
}

void insertBefore(List L, int x){// Insert new element before cursor. Pre: length()>0, index()>=0
    if (L == NULL) {
        printf("List Error: calling insertBefore() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0 && index(L) >= 0){
        Node n = newNode(x);
	if(L->cursor != NULL){
        	n->prev = L->cursor->prev;

		L->cursor->prev = n;

        	n->next = L->cursor;
		L->index = L->index + 1;
	}
        if (n->prev != NULL) {
            Node temp = n->prev;
            temp->next = n;
        } else {
            L->front = n; // update front when cursor is at the front
        }
        L->length++;
    }
}
void insertAfter(List L, int x){//Insert new element after cursor. Pre: length > 0, index()>=0
    if(L == NULL){
        printf("List Error: calling insertAfter() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0 && index(L) >= 0) {
        Node n = newNode(x);

        n->next = L->cursor->next;


        L->cursor->next = n;

        n->prev = L->cursor;

        if (n->next != NULL) {
            Node temp = n->next;
            temp->prev = n;
        } else {
            L->back = n; // update back when cursor is at the back
        }
        L->length++;
    }
}

void deleteFront(List L){// Delete the front element. Pre: Length()>0
    if(L == NULL){
        printf("List Error: calling deleteFront() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) > 0){
        Node temp = L->front;
        L->front = L->front->next;//Moves front to next
        if(L->front != NULL){
		if(L->cursor == L->front){
			L->cursor = NULL;
			L->index = -1;
		}
		//L->front = L->front->next;//Moves front to next
		L->front->prev = NULL;
		L->index = L->index - 1;
	}else{
		L->back = NULL;
	}
        L->length--;

        freeNode(&temp);
    }
}

void deleteBack(List L){//Delete the back element. Pre: length()>0
    if(L == NULL || L->back == NULL){
        printf("List Error: calling deleteBack() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) > 0){
        Node temp = L->back;
        L->back = L->back->prev;//Moves back to prev
        if(L->back != NULL){
		L->back->next = NULL;
	}else{
		L->front = NULL;
	}
        L->length--;

        freeNode(&temp);
    }
}

void delete(List L){ //Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
    if(L == NULL){
        printf("List Error: calling delete() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) > 0 && index(L) >= 0){
	Node temp = L->cursor;

        Node prev = L->cursor->prev;
        Node next = L->cursor->next;

	if(L->cursor == L->front){
		L->front = next;
	}else{
		prev->next = next;
	}
	if(L->cursor == L->back){
		L->back = prev;
	}else{
		next->prev = prev;
	}
        L->cursor = NULL;
        freeNode(&temp);
        L->length--;
    }
}

//Other operations
void printList(FILE *out, List L){// Prints to the file pointed to by out, a string representation of L consisting of a space separated sequence of integers, with front on left.
    if(L == NULL){
        printf("List Error: calling printList() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(out == NULL){
        printf("List Error: calling printList() on NULL File\n");
        exit(EXIT_FAILURE);
    }
    Node n = NULL;
    for(n = L->front; n != NULL; n = n->next){
        fprintf(out,"%d ", n->data);
    }
    
}

List copyList(List L){// Returns a new List representing the same integer // sequence as L. The cursor in the new list is undefined,// regardless of the state of the cursor in L. The state // of L is unchanged
    if(L == NULL){
        printf("List Error: calling copyList() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    
    List new_lst = newList();
    Node n = NULL;
    for(n = L->front; n != NULL; n = n->next){
        append(new_lst, n->data);
    }
    return new_lst;
}
bool equals(List A, List B){// Returns true if A is same int sequence as B, false otherwise.
    if(A == NULL || B == NULL){
        printf("List error: calling equals with NULL A or NULL B list\n");
        exit(EXIT_FAILURE);
    }
    if(A->length != B->length){//Base case
        return false;
    }
    moveFront(A);
    moveFront(B);
    for(int i=0; i < A->length ; i++){
        if(A->cursor->data != B->cursor->data){
            return false;
        }
        moveNext(A);
        moveNext(B);
    }
    return true;
}
