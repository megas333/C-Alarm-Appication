/******************************************************************************
*           Copyright © 2016 RT-RK Institute for Computer Based Systems.      *
*******************************************************************************
*
* MODULE NAME: Alarm application
*
* FILE NAME: 	main.c
* DESCRIPTION
*
* This file contains definitions of the following functions:
* -main()
*
*Author: Nikola Stankovic, Mentor: Aleksandar Zivkovic.
*
*******************************************************************************/
/******************************************************************************/
/*              Includes                                                      */
/******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "processFile.h"
#include "linkedList.h"
#include "alarm.h"

int main(){

	FILE *fp=NULL;
	char * buff;
    Alarm_t alarm;
    struct node* head = NULL;
    /*Counter of all alarms*/
    int cnt = 0;
    /*Counter of working alarms*/
    int cnt_w = 0;
    /*Traverse result: takes return value from traverse function*/
    int trav_result;

    fp=fopen("podaci.txt","r");

    if(fp == NULL)
    {
        printf("Error: File can not be open.\n");
        return 0;
    }

    printf("***Copyright : 2016 RT-RK Institute for Computer Based Systems.***\n");
    printf("Student: Nikola Stankovic\n");
    printf("Mentor: Aleksandar Zivkovic\n");
    printf("Task: Alarm Clock application\n");
    printf("\n");
    printf("*********************  ALARM   APPLICATION  *********************\n");

    printf("\n");
    while (getLine(&buff,fp)!=E_EOF)
    {
        /**Parsing step**/
        if(E_BAD!=parseAlarm(&alarm,buff))
        {
            /**Appending step**/
            if(E_MEM_ALLO==appendNode(&head,alarm))
            {
                printf("Failed memory allocation for alarm: %d.\n",cnt);

            }
            cnt_w++;
        }
        else
        {
            printf("Please Fix Alarm number %d.\n",cnt);
        }
        cnt++;
    }
    printf("Successful alarms read: %d\n",cnt_w);
    printf("\n");

    int takeKey;
    while(1){

         trav_result = traverseList(head,&takeKey);
         if(trav_result==E_LIST_EAMPTY)
         {
             printf("There is no more alarms.\n");
             break;
         }
         else if (trav_result == ABS_DEL)
         {
             deleteNodeValue(&head,takeKey);
         }

         Sleep(1000);

    }
    printf("\n");
    printf("No more alarms, application will close in 3 seconds.\n");
    Sleep(3000);
    fclose(fp);

	return 0;
}
