/* helpers.h */
/******************************************************************
**  Kendra Wainscott           CS202                spring 2022  **
**                             Prog#2                            **
******************************************************************/
#ifndef HELPERS_H
#define HELPERS_H 

#include <iostream>
#include <string>
#include <cstring>
#include <map>
using namespace std;

#define NUM_THEMES 3
/******************************************************************
*******************  EXCEPTION HANDELING  *************************
******************************************************************/
struct FILE_ERROR {}; //invalid File usage or fstream error
struct BAD_INPUT {}; //invaid user input
struct OPERATOR_ERROR {}; //overloaded operator errors 
struct DISPLAY_ERROR {}; //general display or menu error

/*****************************************************************
*******************  HELPER FUNCTIONS *****************************
******************************************************************/
class Helper
{
    public:
        /* Job: get user input as integer, error check, and return 
        ** Arg: min and max value for valid input 
        ** Ret: bad input will return 0*/ 
        int answer(int min, int max) const;

        /* Job: get user input to hold reservations */
        bool name(char* & in_name) const;
        int num_ppl(int min, int max) const;

        /* Job: set time array to current time & date
        ** Arg: time and data array format -- year|month|day|24hr|60min
        ** Ret: true */
        bool current_dt(array<int,5> & date_time);

        /* Job: print full date and time of dt array */
        bool print_dt(const array<int,5> & date_time) const;

};
/*****************************************************************
***********************  GENERAL  ********************************
******************************************************************/
bool print_banner(); //prints welcome banner, returns true
bool main_menu();     //prints main menu, returns true
bool reserve_menu();  //prints reservation menu, returns true 


#endif
