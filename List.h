#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
//#include <stdbool.h>

//Exported types
typedef int ListElement;
typedef struct ListObj *List;

//Constructors-Deconstructors78u
List newList(void); // Created and returns a new empty list
void freeList(List *pL);  //Frees all heap memory associated with *PL and sets *Pl to NULL

//Access functions
int length(List L); //Returns the number of elements in L
int index(List L); //Returns the index of cursor element if defined, -1 otherwise
int front(List L);  //Return front elemnt of L. Pre: Length() > 0
int back(List L);  // Returns back element of L. Pre: Length() > 0
int get(List L); // Returns cursor element of L. Pre: Length() > 0, index()>=0

//Manipulation Procedures
void clear(List L); //Resets L to its original empty state
void set(List L, int x); // Overwrites the cursor element's data with x. Pre: length() > 0, index()>=0

void moveFront(List L); // If L is non-empty, sets cursor under the front element, otherwise does nothing

void moveBack(List L); //If L is non-empty, sets the cursor under the back element, otherwise does nothing

void movePrev(List L);  //If cursor is definde and not at front, move cursor one step toward the front of L. If cursor is defined at front, cursor becomes undefined. If cursor is undefined do nothing

void moveNext(List L);  //If cursor is defined and not at back, move cursor one step toward the back of L. If cursor is defiend and at back, cursor becomes undefined. if cursor is undefiend do nothing

void prepend(List L, int x); //Insert new element int L. If L is non-empty, insertion takes place before front element

void append(List L, int x); //Inset new element in L. If L is non-emptu, insertaion takes place after back element

void insertBefore(List L, int x); // Insert new element before cursor. Pre: length()>0, index()>=-

void insertAfter(List L, int x);  //Insert new element after cursor. Pre: length > 0, index()>=0

void deleteFront(List L);// Delete the front element. Pre: Length()>0

void deleteBack(List L);  //Delete the back element. Pre: length()>0

void delete(List L); //Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0

//Other operations
void printList(FILE *out, List L);// Prints to the file pointed to by out, a // string representation of L consisting // of a space separated sequence of integers,// with front on left.

List copyList(List L);// Returns a new List representing the same integer // sequence as L. The cursor in the new list is undefined,// regardless of the state of the cursor in L. The state // of L is unchanged



#endif
