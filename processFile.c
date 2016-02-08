/******************************************************************************
*           Copyright © 2016 RT-RK Institute for Computer Based Systems.      *
*******************************************************************************
*
* MODULE NAME: File handling
*
* FILE NAME: 	processFile.c
* DESCRIPTION
*
*******************************************************************************/
/******************************************************************************/
/*              Includes                                                      */
/******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include"processFile.h"


int getLine(char ** _cLine, FILE * _pFile){

    if(_pFile == NULL){
    	return E_FP;
    	}

    int cnt=1;

    /**Memory allocation for the line**/
    *_cLine = (char*)malloc(MAX_LENGHT*sizeof(char));

     if(_cLine==NULL){
        printf("Memory not allocated.\n");
        return E_MEM_ALLO;
        }

    fgets(*_cLine,MAX_LENGHT,_pFile);

    char * test_string = *_cLine;
    char last_char = test_string[strlen(*_cLine)-1];

    while(last_char!='\n'){
        /**reallocation of a line**/
        *_cLine = realloc(*_cLine,(MAX_LENGHT+cnt*MAX_LENGHT)*sizeof(char));
        if(_cLine==NULL){
        printf("Memory not allocated.\n");
        free(*_cLine);
        return E_MEM_ALLO;
        }

        if (fgets(*_cLine+cnt*MAX_LENGHT-1,MAX_LENGHT+1,_pFile)==NULL){
            printf("\n");
            return E_EOF;
            }
        /**updates for last character**/
            test_string = *_cLine;
            last_char = test_string[strlen(*_cLine)-1];
        /**increment counter for reallocation**/
            cnt++;
        }
        /**length for a new reallocation**/
    int new_length=strlen(*_cLine);
    *_cLine = realloc(*_cLine,new_length*sizeof(char)+1);
    if(_cLine==NULL)
        {
        printf("Memory not allocated.\n");
        free(*_cLine);
        return E_MEM_ALLO;
        }

    return OK;
};

int parseAlarm(Alarm_t * alarm,char *source)
{
    if(source==NULL){
        printf("Error: line empty\n");
        return E_BAD;

    }

    if(E_INVALID_ALARM_TYPE==get_Type(source,&alarm)){
        printf("Error: Invalid alarm type\n");
        return E_BAD;
        }

    if(alarm->AlarmType_t==ABS){
       remove_Tokens_ABS(source);
        if(get_Date(source,&alarm) != OK || diffTime(alarm)>0){
              return E_BAD;
          }
       get_Message(source,&alarm);
       }
    else{
       remove_Tokens_PER(source);
       if(get_Date(source,&alarm) != OK){
              return E_BAD;
          }
       if(get_Period_Date(source,&alarm) != OK){
            printf("Correct your period.\n");
        return E_BAD;
       }
       while(diffTime(alarm)>0){
        alarm->date_t.y = alarm->date_t.y + alarm->pdate_t.y;
        alarm->date_t.m = alarm->date_t.m + alarm->pdate_t.m;
        alarm->date_t.d = alarm->date_t.d + alarm->pdate_t.d;
        alarm->date_t.h = alarm->date_t.h + alarm->pdate_t.h;
        alarm->date_t.mi = alarm->date_t.mi + alarm->pdate_t.mi;
        alarm->date_t.s = alarm->date_t.s + alarm->pdate_t.s;

       }
       get_Message(source,&alarm);
    }

  return OK;
}
int remove_Tokens_ABS(char * source)
{
    char* i = source;
    char* j = source;
    int cnt=0;  //counter for chars
    while(*j != 0){
    *i = *j++;
    if((*i == '-') || (*i ==':')){
            *i=' ';
        }
    i++;
    cnt++;
    if(cnt==ABS_FORMAT_LEN){
            while(*j != 0){
                *i = *j++;
                i++;
            }
            break;
        }
    }
  *i = '\0';

    return OK;
}
int remove_Tokens_PER(char * source)
{

    char* i = source;
    char* j = source;
    int cnt=0;  //counter for chars
    while(*j != 0){
    *i = *j++;
    if((*i == '-') || (*i ==':')){
            *i=' ';
        }
    i++;
    cnt++;
    if(cnt==PER_FORMAT_LEN){
        while(*j != 0){
            *i = *j++;
            i++;
            }
            break;
      }
    }
  *i = '\0';
    return OK;
}
void chopN(char *str, size_t n)
{

    size_t len = strlen(str);
    if (n > len)
        return;
    memmove(str, str+n, len - n + 1);
}
int get_Type(char * source,Alarm_t ** alarm)
{
    /** ABS+'\0'= 4 **/
    short typeLen=4;
    char type[typeLen];

    strncpy(type,source,typeLen-1);
    type[typeLen-1]='\0';
    if(strcmp(type,"ABS")==0){
        (*alarm)->AlarmType_t=ABS;
        chopN(source,typeLen);
    }
    else if(strcmp(type,"PER")==0){
       (*alarm)->AlarmType_t=PER;
       chopN(source,typeLen);
    }
    else{
        /**Error: Wrong type**/
        return E_INVALID_ALARM_TYPE;
        }
return OK;

}
int get_Date(char * source, Alarm_t ** alarm)
{
    /**format is const of length 20**/
    short dateLen=20;
    if(6!=sscanf(source,"%d %d %d %d %d %d",&(*alarm)->date_t.y,&(*alarm)->date_t.m,&(*alarm)->date_t.d,&(*alarm)->date_t.h,&(*alarm)->date_t.mi,&(*alarm)->date_t.s))
    {
        printf("Data missing from date.\n");
        return E_MISSING_DATA;
    }
    if((*alarm)->date_t.y<2016)
    {
        printf("Error: Year must be greater than 2016.\n");
        return E_YEAR;
    }
    if((*alarm)->date_t.m<0 || (*alarm)->date_t.m>12 )
    {
        printf("Error: Month must be from 1 to 12.\n");
        return E_MONTH;
    }
    if((*alarm)->date_t.d<0 || (*alarm)->date_t.d>31)
    {
        printf("Error: Days must be from 0 - 31.\n");
        return E_DAY;
    }
    if((*alarm)->date_t.h<0 || (*alarm)->date_t.h>24)
    {
        printf("Error: Hours must be from 0 - 24.\n");
        return E_HOUR;
    }
    if((*alarm)->date_t.mi<0 || (*alarm)->date_t.mi>59)
    {
        printf("Error: Minutes must be from 0 - 59.\n");
        return E_MINUTE;
    }
    if((*alarm)->date_t.s<0 || (*alarm)->date_t.s>59)
    {
        printf("Error: Seconds must be from 0 - 59\n");
        return E_SECOND;
    }

    chopN(source,dateLen);

    return OK;
}
int get_Period_Date(char * source, Alarm_t ** alarm)
{
    short dateLen=18;
    if(6!=sscanf(source,"%d %d %d %d %d %d",&(*alarm)->pdate_t.y,&(*alarm)->pdate_t.m,&(*alarm)->pdate_t.d,&(*alarm)->pdate_t.h,&(*alarm)->pdate_t.mi,&(*alarm)->pdate_t.s))
    {
        printf("Data missing from date.\n");
        return E_MISSING_DATA;
    }
    int sum_per;
    /**checking if period is zero**/
    sum_per = (*alarm)->pdate_t.y+(*alarm)->pdate_t.m+(*alarm)->pdate_t.d+(*alarm)->pdate_t.h+(*alarm)->pdate_t.mi+(*alarm)->pdate_t.s;
    if(sum_per==0)
    {
        return E_PER_ZERO;
    }
    chopN(source,dateLen);
    return OK;
}
void printAlarmStructure(Alarm_t * alarm)
{

    printf("Type of alarm :%d \n",(*alarm).AlarmType_t);
    printf("Year of alarm :%d \n",(*alarm).date_t.y);
    printf("Month of alarm :%d \n",(*alarm).date_t.m);
    printf("Day of alarm :%d \n",(*alarm).date_t.d);
    printf("Hour of alarm :%d \n",(*alarm).date_t.h);
    printf("Minute of alarm :%d \n",(*alarm).date_t.mi);
    printf("Second of alarm :%d \n",(*alarm).date_t.s);

    printf("Type  alarm :%d \n",(*alarm).AlarmType_t);
    printf("Year of alarm :%d \n",(*alarm).pdate_t.y);
    printf("Month of alarm :%d \n",(*alarm).pdate_t.m);
    printf("Day of alarm :%d \n",(*alarm).pdate_t.d);
    printf("Hour of alarm :%d \n",(*alarm).pdate_t.h);
    printf("Minute of alarm :%d \n",(*alarm).pdate_t.mi);
    printf("Second of alarm :%d \n",(*alarm).pdate_t.s);
    printf("Message: %s", (*alarm).cMsg);

}
int get_Message(char * source, Alarm_t ** alarm)
{
    strncpy((*alarm)->cMsg,source,MSG_LEN-1);
    return OK;
}
int diffTime(Alarm_t * alarm)
{   /*creating time structures*/

    struct tm tm;
    time_t t1;
    time(&t1);
    double diff;
    /*update from alarm*/
    tm.tm_year=alarm->date_t.y-1900;

    //printf("Y: %d\n",tm.tm_year);
    tm.tm_mon=alarm->date_t.m-1;
    //printf("M: %d\n",tm.tm_mon);
    tm.tm_mday=alarm->date_t.d;
    //printf("D: %d\n",tm.tm_mday);
    tm.tm_hour=alarm->date_t.h;
    //printf("H: %d\n",tm.tm_hour);
    tm.tm_min=alarm->date_t.mi;
    //printf("Mi: %d\n",tm.tm_min);
    tm.tm_sec=alarm->date_t.s-1;
    //printf("S: %d\n",tm.tm_sec);
    tm.tm_isdst=-1;
    /*comparing*/
    diff=difftime(t1,mktime(&tm));
   // printf("Difference is: %lf\n",diff);
    return diff;
}
