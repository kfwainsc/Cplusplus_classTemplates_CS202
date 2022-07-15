/* reservations.h */
/******************************************************************
**  Kendra Wainscott           CS202                spring 2022  **
**                             Prog#2                            **
******************************************************************/
#ifndef RESERVATIONS_H 
#define RESERVATIONS_H 

#include <iostream>
#include <cstring>
#include <array>
#include <map> ///can move if theater moves
#include "helpers.h"
#include "other.h"
#define THEME 3
using namespace std;
/**********  Base class to all derived reservation classes  ******/
/* DATA MEMBERS: char* guest_name -reservation holder’s name 
                 int num_guests   -num ppl in reservation
                 bool confirmed   -reservation is set
                 array date_time  -year|month|day|24hr|60min 
                 float unit_cost  -$ per ticket or per hr  */
class Reserve 
{
    public:
        Reserve(); //default
        Reserve(const char* name, const int guests);
        Reserve(const Reserve & source); //cc
        ~Reserve();    

        /* Job: add guest(s) to res
        ** Ret: returns num guests added */
        int add_guest();

        /* Job: remove guest(s) from res
        ** Ret: num guests removed */
        int remove_guest();

        /* Job: print info */
        bool display() const;

        /* Job: change date and/or time 
        ** Ret: true if changes, else false */
        bool change_dt();

        /* Job: for use in overloaded comparison ops
        ** for comparing the dates and times of reservations
        ** Ret: 1 if obj > op2, 0 if == , -1 if obj < op2 */
        int compare_date_time(const Reserve & op2) const;
        int compare_date_time(const array<int,5> & op2) const;

        /* overloaded operators to support template use */    
        void operator = (const Reserve & source);
        /* For comparing date& time of two Reservation objects */ 
        bool operator == (const Reserve & op2) const;
        bool operator != (const Reserve & op2) const;
        bool operator >  (const Reserve & op2) const;
        bool operator <  (const Reserve & op2) const;
        bool operator >= (const Reserve & op2) const;
        bool operator <= (const Reserve & op2) const;

        /* For comparing a Reservation & a TIME_DATE array */
        bool operator == (const array<int,5> & op2) const;
        bool operator >  (const array<int,5> & op2) const;
        bool operator <  (const array<int,5> & op2) const;
        bool operator >= (const array<int,5> & op2) const;
        bool operator <= (const array<int,5> & op2) const;

        /* allow for obj output through cout and other output streams,
        ** must pass & reutrn stream by REFERENCE to allow chaining */ 
        friend ostream& operator << (ostream & out, const Reserve & op);

        /** Reserve op not const because is being read into */
        friend istream& operator >> (istream & in, Reserve & op);

    protected:
        char* guest_name;    //reservation holder’s name 
        int num_guests;        //num ppl in reservation
        float unit_cost;    //($ per ticket or per hr) 
        array<int,5> date_time;// year|month|day|24hr|60min
        Helper h;            //to call helper functions
};

/******************************************************************
***************************  CLOWN  *******************************
******************************************************************/
/* DATA MEMBERS: char* event_name  
                 int scare_level        -defaults to max
                 bool balloons            -defaults to true
                 array<string> themes    -list of possible themes
                 string special request -user added  */
class Clown: public Reserve
{
    public:
        Clown(); //default 
        //basic res info taken before derived event is chosen, 
        //so passing in reservation object
        Clown(const Reserve & reserve, const char* event, const
              array<string,THEME> & in_themes, const float price);

        Clown(const Clown & source);//cc

        ~Clown(); //destructor 

        bool choose_theme();

        /* Job: alter scare level, default is max
        ** Args: 
        ** Ret: */
        int alter_scare();

        /* Job: ballons are default true at creation
        ** Ret: true if cancel balloons, else false */
        bool cancel_baloons();

        /* Job: review all info for reservation
        ** Args:
        ** Ret: true if correct, else false */
        bool review_booking();

        /* Job: print info */
        bool display() const;

        /* overloaded operators to support template use 
        ** these should call PARENTS overloaded ops as well */
        void operator = (const Clown & source);

        /* allow for obj output/input through iostreams,
        ** must pass & reutrn stream by REFERENCE to allow chaining */ 
        friend ostream& operator << (ostream & out, const Clown & op);
        friend istream& operator >> (istream & in, Clown & op);

        /* Job: auto choose user fields for testing
        ** Ret: name of theme chosen */
        string& test_set(int rnad);    

    protected: 
        char* event_name;
        int scare_level;
        bool balloons; 
        array<string,3> themes;
        string theme_choice;
        string special_request;                     
};
/******************************************************************
************************  MARGARITA  ******************************
******************************************************************/
class Margarita :public Reserve
{
    public:
        Margarita();
        Margarita(const Reserve & reserve, const char* event,
                  const multimap<float,string> & in_tequilas,
                  const float price);
        Margarita(const Margarita & src);
        ~Margarita();

        /* Job: displays availible types of tequila
        ** Ret: total num of items, else false */
        int display_tequilas() const;

        /* Job:  
        ** Ret: true if selection, else false */
        int choose_tequila(); 

        /* Job: display all fields
        ** Ret: true if not empty, else false */
        bool display() const;

        /* Job: disp. options for alter res 
        ** can call change_dt() as well 
        ** Ret: true if changes, else false */
        bool change_res();
        
        /* copy one marg object into another */
        void operator = (const Margarita & source);

        /* allow for obj output/input through iostreams,
        ** must pass & reutrn stream by REFERENCE to allow chaining */ 
        friend ostream& operator << (ostream& out,const Margarita& op);
        friend istream& operator >> (istream & in, Margarita & op);

        /* Job: auto choose user fields for testing

        ** Ret:  */
//        int test_set();    

    protected:
        char* event_name; //char* requirement 
        //variety of tequilas with prices, multimap to 
        //allow for sort by $ with duplicate prices
        multimap<float,string> tequilas;
        Helper h;
};

/******************************************************************
*************************  THEATRE  *******************************
******************************************************************/
/*DATA MEMBERS:    char* event_name   
                Play play           -includes playwight, title, etc
                int programs       -num of programs purchased  */
class Theater :public Reserve
{
    public:
        Theater();
        Theater(const Reserve & reserve, const char* event,
                const float price, const Play & play);
        Theater(const Theater & src);
        ~Theater();

        /* probably ALL THE SAME OVERLAODED OPS as Clown*/

        bool choose_seats(); //holding seats data type tbd

        int add_programs();//will need additional cost variable 

        /* Will be wrappers, unless I can find a way to derive
        ** the Play class from the Theater */
        bool view_cast() const;

        /* Job: finds actor playing given role
        ** Args: role to lookup
        ** Ret: actor playing given role*/
        int search_cast_list(const string role) const;

        /* Job: disp. options for alter res 
        ** can call change_dt() as well 
        ** Ret: true if changes, else false */
        bool change_res();

        /* Job: print info */
        bool display() const;

        /* copy one theater object into another */
        void operator = (const Theater & op2);

        /* allow for obj output/input through iostreams,
        ** must pass & reutrn stream by REFERENCE to allow chaining */ 
        friend ostream& operator << (ostream& out,const Theater & op);
        friend istream& operator >> (istream & in, Theater & op);

    protected:
        char* event_name;
        Play play;
        int programs;
};

#endif
        /* Job: 
        ** Args: 
        ** Ret: */

