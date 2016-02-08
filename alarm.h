#ifndef ALARM_H_INCLUDED
#define ALARM_H_INCLUDED
enum errCodeAlarm{

    ABS_SUCC=100,
    PER_TRIG=101,
    E_NONODE=102,
    ABS_DEL=103

};
/******************************************************************************
* Function Name 	:*/int computeTimeDifference(struct node *node); /**
*
* Description : Function that calculates the time difference in seconds
*
*
* Side effects  	:
*
* Comment       	:
*
* Parameters 		: Pointer to the current node.
*
* Returns 		    : diff - time difference
*
*
 ******************************************************************************/

/******************************************************************************
* Function Name 	:*/int alarmTrigger(struct node *node, int * p);/**
*
* Description : Function that Triggers alarms. If alarm is ABS alarm is set to be  deleted
*               while PER alarm is refreshed.
*               This function also uses some print statements for users.
*
*
* Side effects  	:
*
* Comment       	:
*
* Parameters 		: input:Pointer to the current node
*                     output: value that stores ID of the ABS alarm.
* Returns 		    : ABS_SUCC or PER_TRIG or OK. First one if ABS is successful, 2nd for PER and third if nothing happens.
*
*
 ******************************************************************************/
/******************************************************************************
* Function Name 	:*/int updatePerAlarm(struct node * node); /**
*
* Description : Function that updates PER alarm with his period.
*
*
* Side effects  	:
*
* Comment       	:
*
* Parameters 		: Pointer to the current node.
*
* Returns 		    : OK on success.
*
*
 ******************************************************************************/
 /******************************************************************************
* Function Name 	:*/int getNodeKey(struct node *node); /**
*
* Description : Function that gets the right key of the given node.
*               This key is passed so the right ABS alarm can be deleted.
*
*
* Side effects  	:
*
* Comment       	:
*
* Parameters 		: Pointer to the current node.
*
* Returns 		    : key value from the alarm structure.
*
*
 ******************************************************************************/
  /******************************************************************************
* Function Name 	:*/ char * getAlarmMsg(struct node * node);/**
*
* Description : Function that gets the message from the given node.
*
*
* Side effects  	:
*
* Comment       	:
*
* Parameters 		: Pointer to the current node.
*
* Returns 		    : char* of the message.
*
 ******************************************************************************/





#endif // ALARM_H_INCLUDED
