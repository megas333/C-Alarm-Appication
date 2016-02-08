#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

struct node {
    Alarm_t alarm;
    int diff;
    unsigned long ID;

    struct node * next;
};

/******************************************************************************
* Function Name 	: */ int appendNode(struct node ** head_ref, Alarm_t noviAlarm); /**
*
* Description : Function that appends the node from behind of the list.
*
*
* Side effects  	:
*
* Comment       	:
*
* Parameters 		: input: reference to the head node and Alarm_t structure.
*
* Returns 		    : OK on success, E_MEM_ALO if memory cant be allocated.
*
*
 ******************************************************************************/


/******************************************************************************
* Function Name 	: */void deleteNodeValue(struct node **head_ref, int key);/**
*
* Description : This function deletes the node at the given n position.
*               If 3 is passed than 3rd node will be deleted.
*
*
* Side effects  	:
*
* Comment       	: If there are no elements to be deleted, head pointer is set to NULL
*
* Parameters 		: input: reference to the head node and Alarm_t structure.
*
* Returns 		    : void
*
*
 ******************************************************************************/

/******************************************************************************
* Function Name 	: */int printListAlarm(struct node *node);/**
*
* Description : This function is used for debugging purpose.
*               It prints out every memeber of the
*
*
*
* Side effects  	:
*
* Comment       	: If there are no elements to be deleted, head pointer is set to NULL.
*
* Parameters 		: input: reference to the head node and Alarm_t structure.
*
* Returns 		    : OK on success
*
*
 ******************************************************************************/


/******************************************************************************
* Function Name 	: */int traverseList(struct node *node, int * t);/**
*
* Description : This function goes through linked list and checks every member for triggering.
*
*
*
*
* Side effects  	:
*
* Comment       	: If there are no elements to be deleted, head pointer is set to NULL.
*
*
* Parameters 		: input: pointer to node
*                     output: value that stores ID of ABS alarm to be deleted.
*
* Returns 		    : OK on success, E_LIST_EAMPTY if list is eampty
*
*
 ******************************************************************************/




#endif // LINKEDLIST_H_INCLUDED
