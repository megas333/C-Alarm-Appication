#ifndef PROCESSFILE_H_INCLUDED
#define PROCESSFILE_H_INCLUDED
/******************************************************************************/
/*              Global Variables                                                      */
/******************************************************************************/
/**Message length is 250 chars **/
#define MSG_LEN 250
/**Starting size for line allocation 100**/
#define MAX_LENGHT 100
/**Size for ABS format parsing**/
#define ABS_FORMAT_LEN 20
/**Size for PER format parsing**/
#define PER_FORMAT_LEN 38

    enum errCode{

    OK = 0,
    E_MEM_ALLO=1,
    E_EOF=2,
    E_FP=3,
    E_INVALID_ALARM_TYPE,
    E_MISSING_DATA,
    E_YEAR,
    E_MONTH,
    E_DAY,
    E_HOUR,
    E_MINUTE,
    E_SECOND,
    E_BAD,
    E_LIST_EAMPTY,
    E_PER_ZERO

};


typedef struct _alarm_t{

enum{
    ABS=0,
    PER=1
}AlarmType_t;

struct _date_t{

int y,m,d,h,mi,s;
}date_t;

struct p_date_t{

int y,m,d,h,mi,s;
}pdate_t;

char cMsg[MSG_LEN];
}Alarm_t;

/******************************************************************************/
/*              Functions Definitions                                         */
/******************************************************************************/

/******************************************************************************
* Function Name 	: */int getLine(char ** _cLine, FILE * _pFile); /**
*
* Description : This function reads the line from the input stream.
*
*
*
* Side effects  	: None
*
* Comment       	:
*
* Parameters 		: output: char ** _cLine -stores the input line into a string reference.
*                      input: FILE * _pFile - file handler
*
* Returns 		    : OK on success, E_MEM_ALLO if memory allocation fails, E_EOF if end of file is reached,
*                     E_FP if pointer to file is NULL.
*
 ******************************************************************************/


/******************************************************************************
* Function Name 	: */ int parseAlarm(struct _alarm_t * _sData,char *source); /**
* Description : This function takes the input string, parses it and fills up the alarm structure
*               Functions used for this purpose are: -int Get_Type(char * source,alarm_t ** alarm);
*                                                    -int Get_Date(char * source, alarm_t ** alarm);
*                                                    -int Get_Period_Date(char * source, alarm_t ** alarm);
*
*
*
*
*
* Side effects  	: None
*
* Comment       	:
*
* Parameters 		: input: char *source- takes the line.
*                     output: alarm_t * _sData - pointer to data structure.
* Returns 		    : OK on success, E_BAD if alarm is bad,
*
*
 ******************************************************************************/


/******************************************************************************
* Function Names 	: */ int remove_Tokens_ABS(char * source);
                         int remove_Tokens_PER(char * source); /**
*
* Description : This functions remove tokens for respective alarms.
*               Tokens removed: '-' and ':'.
*               20 chars parsed for ABS.
*               38 chars parsed for PER.
*
*
* Side effects  	: None
*
* Comment       	: None
*
* Parameters 		: input: char *source - takes the line.
*
* Returns 		    : OK on success.
*
*
 ******************************************************************************/


/******************************************************************************
* Function Name 	: */ int get_Type(char * source,Alarm_t ** alarm); /**
*
* Description : This function takes the string and checks for alarm type.
*               On success it writes the given type into structure.
*
*
* Side effects  	: None
*
* Comment       	:
*
* Parameters 		: input: char *source- takes the line.
*                     output: alarm_t ** alarm) - double pointer to data structure.
* Returns 		    : OK on success, E_INVALID_ALARM_TYPE if alarm is not ABS or PER.
*
*
 ******************************************************************************/


/******************************************************************************
* Function Name 	: */ int get_Date(char * source, Alarm_t ** alarm); /**
*
* Description : This function takes the input string and checks for date.
*               If date is in correct format function writes data into alarm structure.
*
*
* Side effects  	: None
*
* Comment       	:
*
* Parameters 		: input: char *source- takes the line.
*                     output: alarm_t ** alarm) - double pointer to data structure.
* Returns 		    : OK on success, E_MISSING_DATA - if some data is missing.
*                                    E_YEAR - if year is incorrect.
*                                    E_MONTH - if month is incorrect.
*                                    E_DAY - if day is incorrect.
*                                    E_HOUR - if hour is incorrect.
*                                    E_MINUTE - if minute is incorrect.
*                                    E_SECOND - if second is incorrect.
*
*
 ******************************************************************************/


/******************************************************************************
* Function Name 	: */ int get_Period_Date(char * source, Alarm_t ** alarm); /**
*
* Description : This function takes the input string and checks for period date.
*               If date is in correct format function writes data into alarm structure.
*
*
* Side effects  	: None
*
* Comment       	:
*
* Parameters 		: input: char *source- takes the line.
*                     output: alarm_t ** alarm) - double pointer to data structure.
* Returns 		    : OK on success, E_MISSING_DATA - if some data is missing.
*
*
 ******************************************************************************/


/******************************************************************************
* Function Name 	: */ int get_Message(char * source, Alarm_t ** alarm); /**
*
* Description : This function takes the input string and checks for message.
*               Message is than copied for 250 chars into the alarm structure.
*
* Side effects  	: None
*
* Comment       	:
*
* Parameters 		: input: char *source- takes the line.
*                     output: alarm_t ** alarm) - double pointer to data structure.
* Returns 		    : OK on success,
*
*
 ******************************************************************************/

/******************************************************************************
* Function Name 	: */ void chopN(char *str, size_t n); /**
*
* Description : Simple function that cuts first n chars from a string thus making a new
*               string without first n characters.
*
* Side effects  	: None
*
* Comment       	: len variable stores the length of a string without the terminating character.
*
* Parameters 		: input: char *source- takes the line.
*                     size_t n - number of first chars cut
* Returns 		    : void.
*
*
 ******************************************************************************/


/******************************************************************************
* Function Name 	: */ void printAlarmStructure(Alarm_t * alarm); /**
*
* Description : Simple function that prints the content of an alarm structure.
*
* Side effects  	: None
*
* Comment       	:
*
* Parameters 		: input: alarm_t * alarm
*
* Returns 		    : void
*
*
 ******************************************************************************/

/******************************************************************************
* Function Name 	: */ int diffTime(Alarm_t * alarm); /**
*
* Description : Simple function calculates time difference between current time and alarm time.
*
* Side effects  	: None
*
* Comment       	:
*
* Parameters 		: input: alarm_t * alarm
*
* Returns 		    : int diff, value of difference
*
*
 ******************************************************************************/


#endif // PROCESSFILE_H_INCLUDED
