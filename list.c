/*
Name: Blazej Byczkowski
Matric number: 170019249
Module code: AC21008
 */
#include "list.h"
#include <stdlib.h>

// initialise a new List
// Parameters:
// listPtr - will receive a pointer to the newly allocated List
int listInit(List **listPtr)
{
	// we expect to be provided with the memory address
	// of a List pointer variable. Make sure this memory
	// address is valid, e.g. isn't NULL
if (listPtr == NULL)
		return  NULL_PARAM;

	// make sure that a List hasn't been initialised already,
	// e.g. is there already something (non-NULL) present at
	// the memory address we will be writing to?
	if (*listPtr != NULL)
		return BAD_INIT_PARAM;

	// allocate memory for a new List and store in the pointer provided
	(*listPtr) = (List*)myMalloc(sizeof(List));

	// check for memory failure
	if ((*listPtr) == NULL)
	{
			return OUT_OF_MEMORY;
	}

	// initialise fields in the List
	(*listPtr)->head = NULL;
	(*listPtr)->tail = NULL;
	(*listPtr)->curr = NULL;

	return SUCCESS;
}

// push a value beforre current int the List
// Parameters:
// listPtr - a pointer to the List
// value - the value to be pushed
int insertBeforeCurr(List *listPtr, int value)
{
	// check that we have a pointer to a valid List
	if (listPtr == NULL)
		return NULL_PARAM;

	// create a new ListNode to go onto the List
	ListNode *newListNode = (ListNode*)myMalloc(sizeof(ListNode));

	// if failed to allocate memory for new ListNode
	if (newListNode == NULL)
		return OUT_OF_MEMORY;

	// initialise fields in new ListNode
	newListNode->data = value;
	newListNode->next = NULL;
	newListNode->prev = NULL;

	//check if List is empty
	//if it is, make the newListNode the new tail also
	if(listPtr->head == NULL && listPtr->tail == NULL){
		listPtr->tail = newListNode;
		listPtr->head = newListNode;
		listPtr->curr = newListNode;
	}
	else if (listPtr->curr == listPtr->head){
		newListNode->next = listPtr->head;
		listPtr->curr->prev = newListNode;
		listPtr->head = newListNode;

	}
	else{
		newListNode->next = listPtr->curr;
		newListNode->prev =listPtr->curr->prev;
		listPtr->curr->prev->next = newListNode;
		listPtr->curr->prev = newListNode;
	}



	return SUCCESS;
}

// push a value after the current of the List
// Parameters:
// listPtr - a pointer to the List
// value - the value to be pushed
int insertAfterCurr(List *listPtr, int value)
{
	// check that we have a pointer to a valid List
	if (listPtr == NULL)
		return NULL_PARAM;

	// create a new ListNode to go onto the List
	ListNode *newListNode = (ListNode*)myMalloc(sizeof(ListNode));

	// if failed to allocate memory for new ListNode
	if (newListNode == NULL)
		return OUT_OF_MEMORY;

	// initialise fields in new ListNode
	newListNode->data = value;
	newListNode->next = NULL;
	newListNode->prev = NULL;


	//check if List is empty
	//if it is, make the newListNode the new tail, head and current
	if(listPtr->head == NULL && listPtr->tail == NULL){
		listPtr->tail = newListNode;
		listPtr->head = newListNode;
		listPtr->curr = newListNode;
	}
	else if (listPtr->curr == listPtr->tail){
		newListNode->prev = listPtr->tail;
		listPtr->curr->next = newListNode;
		listPtr->tail = newListNode;

	}
	else{
		newListNode->next = listPtr->curr->next;
		newListNode->prev =listPtr->curr;
		listPtr->curr->next->prev = newListNode;
		listPtr->curr->next = newListNode;
	}

	return SUCCESS;
}

// move current to previous node
// Parameters:
// listPtr - pointer to List
int currToPrev(List* listPtr)
{
	// check that we have a pointer to a valid List
	if (listPtr == NULL)
		return NULL_PARAM;

	// check if List is empty
	if (!listPtr->head)
		return MOVE_IN_EMPTY_LIST;

	// if it is not head, move current to previous
	if(listPtr->curr != listPtr->head){
		listPtr->curr = listPtr->curr->prev;
		return SUCCESS;
	}
	else{
		return MOVE_PREV_AT_HEAD;
	}
}

// move current to next node
// Parameters:
// listPtr - pointer to List
int currToNext(List* listPtr)
{
	// check that we have a pointer to a valid List
	if (listPtr == NULL)
		return NULL_PARAM;

	// check if the List is empty
	if (!listPtr->tail)
		return MOVE_IN_EMPTY_LIST;

	// if it is not tail, move current to next
	if(listPtr->curr != listPtr->tail){
		listPtr->curr = listPtr->curr->next;
		return SUCCESS;
	}
	else{
		return MOVE_NEXT_AT_TAIL;
	}
}

// pop a value off at the cu of the List
// Parameters:
// listPtr - a pointer to the List
// value - will receive the value popped
int removeAtCurr(List *listPtr, int *value, int moveForward)
{
	// check that we have a pointer to a valid List
	if (listPtr == NULL)
		return NULL_PARAM;

	// check that the pointer we have received
	// to store the popped value into isn't null
	// (it should be pointing to a valid memory address)
	if (value == NULL)
		return NULL_PARAM;

	// proceed with popping a ListNode from the current of the List

	// first, check: is the List currently empty?
	if (listPtr->head == NULL)
		return REMOVE_FROM_EMPTY_LIST;

	// otherwise, store the value that's in the ListNode
	// at the current of the List
	*value = listPtr->curr->data;

	// create a temporary pointer to the ListNode currently
	// at the curr of the List (we are going to remove it)
	ListNode *ListNodeToRemove = listPtr->curr;


	//check where current is in the ListNode
	//different cases for amount of nodes and position of current
	if(listPtr->curr == listPtr->head){
		if(listPtr->curr == listPtr->tail){
			listPtr->curr = NULL;
			listPtr->head = NULL;
			listPtr->tail = NULL;
		}
		else{
			listPtr->curr = listPtr->curr->next;
			listPtr->head = listPtr->curr;
		}
	}
	else if(listPtr->curr == listPtr->tail){
		listPtr->curr = listPtr->curr->prev;
		listPtr->tail = listPtr->curr;
	}
	else if(moveForward!=0){
		listPtr->curr->next->prev=listPtr->curr->prev;
		listPtr->curr->prev->next=listPtr->curr->next;
		listPtr->curr = listPtr->curr->next;
	}
	else{
		listPtr->curr->next->prev=listPtr->curr->prev;
		listPtr->curr->prev->next=listPtr->curr->next;
		listPtr->curr = listPtr->curr->prev;
	}


	//if head is empty, queue is emptying
	//make tail null
	if(listPtr->head == NULL)
		listPtr->tail = NULL;

	// remove / free the existing current (which has now been popped)
	ListNodeToRemove->next = NULL;
	ListNodeToRemove->prev = NULL;
	ListNodeToRemove->data = 0;
	free(ListNodeToRemove);

	return SUCCESS;
}

// get the value at the current of the List
// without removing / popping it
// Parameters:
// listPtr - a pointer to the List
// value - will receive the peeked value
int getDataAtCurr(List* listPtr, int *data)
{
	// check that we have a pointer to a valid List
	if (listPtr == NULL)
		return NULL_PARAM;


	// check that the pointer we have received
	// to store the popped value into isn't null
	// (it should be pointing to a valid memory address)
	if (data == NULL)
		return NULL_PARAM;

	// proceed with peeking at the current in the ListNode

	// first, check: is the List currently empty?
	if (listPtr->head == NULL)
		return GET_FROM_EMPTY_LIST;

	// otherwise, store the value that's in the ListNode
	*data = listPtr->curr->data;

	return SUCCESS;
}

// free all memory used in the List
// Parameters:
// listPtr - a pointer to the List to free
int listFree(List *listPtr)
{
	// check that we have a pointer to a valid List
	if (listPtr == NULL)
		return NULL_PARAM;

	// while there is still an item at the top of
	// the List to free
	while (listPtr->head != NULL)
	{
		// get pointer to current top of the List
		ListNode *currentTop = listPtr->head;

		// shift top to the next ListNode down
		listPtr->head = listPtr->head->next;

		// free the current top
		free(currentTop);
	}

	// all ListNodes in the List have been freed.
	// now free the List itself
	free(listPtr);

	return SUCCESS;
}
