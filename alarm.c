#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "processFile.h"
#include "linkedList.h"
#include "alarm.h"

int computeTimeDifference(struct node *node)
{   /*creating time structures*/
    if(node==NULL){
        return E_LIST_EAMPTY;
    }
    struct tm tm;
    time_t t1;
    time(&t1);
    double diff;
    /*update from alarm*/
    tm.tm_year=node->alarm.date_t.y-1900;
    //printf("Godina: %d\n",tm.tm_year);
    tm.tm_mon=node->alarm.date_t.m-1;
    //printf("Mjesec: %d\n",tm.tm_mon);
    tm.tm_mday=node->alarm.date_t.d;
    //printf("Dan: %d\n",tm.tm_mday);
    tm.tm_hour=node->alarm.date_t.h;
    //printf("Sat: %d\n",tm.tm_hour);
    tm.tm_min=node->alarm.date_t.mi;
    //printf("Minut: %d\n",tm.tm_min);
    tm.tm_sec=node->alarm.date_t.s-1;
    //printf("Sekund: %d\n",tm.tm_sec);
    tm.tm_isdst=-1;
    /*comparing*/
    diff=difftime(t1,mktime(&tm));
   // printf("Difference is: %lf\n",diff);
    return diff;
}
int alarmTrigger(struct node *node, int *p){

    if((computeTimeDifference(node)>0) && (node->alarm.AlarmType_t==ABS)){
                struct tm * timeinfo;
                time_t now;
                time (&now);
                timeinfo = localtime ( &now );
                printf("ABS Alarm triggered!\n");
                printf ( "Alarm went off at: %s", asctime (timeinfo));
                printf("ABS alarm message: %s",node->alarm.cMsg);
                printf("\n");
                *p=getNodeKey(node);
                return ABS_SUCC;

    }
        else if(computeTimeDifference(node)>0 && node->alarm.AlarmType_t==PER){
                if(computeTimeDifference(node)<2){
                    struct tm * timeinfo;
                    time_t now;
                    time (&now);
                    timeinfo = localtime ( &now );
                    printf("PER Alarm triggered!\n");
                    printf ("Alarm went off at: %s", asctime (timeinfo));
                    printf("PER alarm message: %s",getAlarmMsg(node));
                    updatePerAlarm(node);
                    return PER_TRIG;
                    }

    }
    return OK;

}
int updatePerAlarm(struct node * node){

    node->alarm.date_t.y = node->alarm.date_t.y + node->alarm.pdate_t.y;
    node->alarm.date_t.m = node->alarm.date_t.m + node->alarm.pdate_t.m;
    node->alarm.date_t.d = node->alarm.date_t.d + node->alarm.pdate_t.d;
    node->alarm.date_t.h = node->alarm.date_t.h + node->alarm.pdate_t.h;
    node->alarm.date_t.mi = node->alarm.date_t.mi + node->alarm.pdate_t.mi;
    node->alarm.date_t.s = node->alarm.date_t.s + node->alarm.pdate_t.s;

    return OK;

}
 int getNodeKey(struct node *node){

    if(node == NULL)
        return E_NONODE;
    int key;
    key = node->ID;
    return key;

 }
 char * getAlarmMsg(struct node * node) {
    return node->alarm.cMsg;
}
