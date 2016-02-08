#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "processFile.h"
#include "linkedList.h"
#include "alarm.h"



int appendNode(struct node ** head_ref, Alarm_t noviAlarm)
{
    static unsigned long int _ulUniqueID = 0;



    /* 1. alociraj node */
    struct node * new_node = (struct node*) malloc(sizeof(struct node));
    if(new_node == NULL)
        {
            return E_MEM_ALLO;
        }
    struct node *last = *head_ref;

    /* 2. postavi strukturu */
    new_node->alarm = noviAlarm;
    new_node->diff = computeTimeDifference(new_node);
    new_node->ID = _ulUniqueID;
    /* 3. set last node to point NULL*/
    new_node->next = NULL;
     _ulUniqueID++;
    /* 4. Ako je lista prazna postavi novi node za head*/
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return OK;
    }
    /* 5. U suprotonom prodji do zadnjeg node-a */
    while (last->next != NULL)
        last = last->next;

    /* 6. Promjeni next node zadnji node*/
    last->next = new_node;
    return OK;

}

void deleteNodeValue(struct node **head_ref, int key)
{
    // Store head node
    struct node* temp = *head_ref, *prev;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->ID == key)
    {
        *head_ref = temp->next;   // Changed head
        free(temp);               // free old head
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->ID != key)
    {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL) return;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp);  // Free memory
}
int printListAlarm(struct node *node)
{


    while (node != NULL)
    {
        printf("Alarm ID : %lu\n",node->ID);
        printf("-------------------------------------------------------\n");
        printf("Type of the alarm :%d \n",(*node).alarm.AlarmType_t);
        printf("Year of the alarm :%d \n",node->alarm.date_t.y);
        printf("Month of the alarm :%d \n",node->alarm.date_t.m);
        printf("Day of the alarm :%d \n",node->alarm.date_t.d);
        printf("Hour of the alarm :%d \n",node->alarm.date_t.h);
        printf("Minute of the alarm :%d \n",node->alarm.date_t.mi);
        printf("Second of the alarm :%d \n",node->alarm.date_t.s);
        printf("-------------------------------------------------------\n");
        printf("Period Year of the alarm :%d \n",node->alarm.pdate_t.y);
        printf("Period Month of the alarm :%d \n",node->alarm.pdate_t.m);
        printf("Period Day of the alarm :%d \n",node->alarm.pdate_t.d);
        printf("Period Hour of the alarm :%d \n",node->alarm.pdate_t.h);
        printf("Period Minute of the alarm :%d \n",node->alarm.pdate_t.mi);
        printf("Period Second of the alarm :%d \n",node->alarm.pdate_t.s);
        printf("Period Message: %s", (*node).alarm.cMsg);
        printf("-------------------------------------------------------\n");
        printf("Remaining seconds: %d\n", node->diff);
        printf("-------------------------------------------------------\n");
        printf("\n");
        node = node->next;
    }
    printf("Za svaki slucaj\n");
    return OK;
}
int traverseList(struct node *node, int * t){
    /**Reference for index**/
    int key;

    /**Alarm position**/
    int n =0;
    /**If list is eampty**/
    if(node == NULL){
            printf("List is empty.\n");
            return E_LIST_EAMPTY;
    }
    /**while node is not null**/
    while (node != NULL){

    if(ABS_SUCC==alarmTrigger(node,&key))
    {

        node = node->next;
        *t=key;
        return ABS_DEL;
    }
    else if(PER_TRIG==alarmTrigger(node,&key))
    {
        node = node->next;
        return OK;

    }
        node = node->next;

        n++;
    }

    return OK;

}
