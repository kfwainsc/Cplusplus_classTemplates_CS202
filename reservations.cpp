/* reservations.cpp */
/******************************************************************
**  Kendra Wainscott           CS202                spring 2022  **
**                             Prog#2                            **
******************************************************************/
#include "reservations.h"
#include "other.h"
using namespace std;
/******** Base class to all derived reservation classes **********/
Reserve::Reserve():guest_name(nullptr), num_guests(0), unit_cost(0), 
                   date_time({0,0,0,0,0}) {}

Reserve::Reserve(const char* name, const int guest)
        :num_guests(guest), unit_cost(0) {
          guest_name = new char[strlen(name)+1];
         strcpy(guest_name, name);
         h.current_dt(date_time); //defaults to currrent date/time
}

Reserve::Reserve(const Reserve & src) 
        :num_guests(src.num_guests), unit_cost(src.unit_cost), 
         date_time(src.date_time) {
         guest_name = new char[strlen(src.guest_name)+1];
         strcpy(guest_name, src.guest_name);
}

Reserve::~Reserve()
{ if(guest_name) delete [] guest_name; }

int Reserve::remove_guest()
{ 
    cout <<"\nHow many people should be removed from your party?";
    int answer = h.answer(0,num_guests);
    if(answer == 0) return 0;
    num_guests -=  answer;
    return answer;
}

bool Reserve::display() const
{
    if(!guest_name) return 0;
    cout << guest_name <<"\nParty of "<< num_guests 
        <<"  $"<< unit_cost <<" per ticket" <<endl;
    return h.print_dt(date_time);
    return 0;
}

bool Reserve::change_dt()
{
    cout <<"Set a reservation time?  0) No  1) Yes  ";
    int choice = h.answer(0,1);
    if(choice)
    {
        cout <<"Month/Day/Year  24hr : 60min format\n"
             <<"Month (1-12) ";
        date_time.at(1) = h.answer(1,12);
        cout <<"Day(1-31)  ";
        date_time.at(2) = h.answer(1,31);
        cout <<"Hour (0-24)  ";
        date_time.at(3) = h.answer(0,24);
        cout <<"Minute (0-59) ";
        date_time.at(4) = h.answer(0,60);
    }
    return choice;
}

int Reserve::compare_date_time(const Reserve & op2) const
{
    for(int i=0; i<5; ++i)
    {
        if(date_time.at(i) > op2.date_time.at(i))
            return 1;
        if(date_time.at(i) < op2.date_time.at(i))
            return -1;
    }
    return 0; //obj.date_time == op2.date_time
}

int Reserve::compare_date_time(const array<int,5> & dt) const
{
    for(int i=0; i<5; ++i)
    {
        if(date_time.at(i) > dt.at(i))
            return 1;
        if(date_time.at(i) < dt.at(i))
            return -1;
    }
    return 0; //obj.date_time == date_time array 
}

void Reserve::operator =(const Reserve & src)
{
    if(!src.guest_name)
    {   
        OPERATOR_ERROR e;
        throw e;
    }
    if(guest_name) delete [] guest_name;    
    guest_name = new char[strlen(src.guest_name)+1];
    strcpy(guest_name, src.guest_name);

    num_guests = src.num_guests;
    unit_cost = src.unit_cost;
    date_time = src.date_time;
}

bool Reserve::operator ==(const Reserve & op2) const
{
    if(!guest_name || !op2.guest_name) {
        OPERATOR_ERROR e;
        throw e;
    }return (date_time == op2.date_time);
}

bool Reserve::operator != (const Reserve & op2) const
{
    if(!guest_name || !op2.guest_name) {
        OPERATOR_ERROR e;
        throw e;
    }return (date_time != op2.date_time);
}

ostream& operator << (ostream & out, const Reserve & op)
{
    if(!op.guest_name) {
        OPERATOR_ERROR e;
        throw e;
    }
    op.display();
    return out;    
}

bool Reserve::operator > (const Reserve & op2) const {
    if(compare_date_time(op2) > 0) return true;
    return false; }

bool Reserve::operator < (const Reserve & op2) const {
    if(compare_date_time(op2) < 0) return true;
    return false; }

bool Reserve::operator >= (const Reserve & op2) const {
    if(compare_date_time(op2) >= 0) return true;
    return false; }

bool Reserve::operator <= (const Reserve & op2) const {
    if(compare_date_time(op2) <= 0) return true;
    return false; }
/******************************************************************
***************************  CLOWN  *******************************
******************************************************************/
Clown::Clown() :Reserve(), event_name(nullptr), scare_level(10), 
                balloons(true), themes({"null","null","null"}),
                theme_choice("none"), special_request("none") {}

//basic reservation info already exists, pass reservation obj  
Clown::Clown(const Reserve & reserve, const char* event, const
             array<string,THEME> & in_theme, const float price)
      :Reserve(reserve), scare_level(10), balloons(1),
       themes(in_theme), special_request("none") 
{
        unit_cost = price; //already init to 0 in res
        theme_choice = int(price) % THEME; //rand assign 
        event_name = new char[strlen(event)+1];
        strcpy(event_name, event);
}

Clown::Clown(const Clown & src)
      :Reserve(src), scare_level(src.scare_level), 
       balloons(src.balloons), themes(src.themes), 
       theme_choice(src.theme_choice), 
       special_request(src.special_request)
{
       event_name = new char[strlen(src.event_name)+1];
       strcpy(event_name, src.event_name);
}

Clown::~Clown()
{ if(event_name) delete [] event_name; }

bool Clown::choose_theme()
{
    int max = themes.size()-1; 
    if(max <= 0) return "none";
    cout <<"Choose a theme for your Clown Booking\n"
         <<"=====================================\n";
    for(int i=0; i <= max; ++i)
        cout << i <<") "<< themes.at(i) <<"\n";

    theme_choice = themes.at(h.answer(0,max));    
    return true;
}

bool Clown::display() const
{
    if(Reserve::display()) {
        cout <<"\n"<< event_name <<" for "<< theme_choice
             <<"\nScare Level: "<< scare_level;
        if(balloons)
        cout <<"   with balloons!";
        if(special_request != "none")
        cout <<"\nSpecial Requests: "<< special_request;    
        cout <<"\n------------------------------------------------"
             <<"\n------------------------------------------------";
        return 1;
    }return 0;
}

void Clown::operator=(const Clown & op2)
{
    if(!op2.event_name)
    {
        OPERATOR_ERROR e;
        throw e;
    }
    Reserve::operator=(op2);
    scare_level = op2.scare_level;
    balloons = op2.balloons; 
    themes = op2.themes; 
    theme_choice = op2.theme_choice;
    special_request = op2.special_request;
    if(event_name)
        delete [] event_name;
    event_name = new char[strlen(op2.event_name)+1];
    strcpy(event_name,op2.event_name);
}

ostream& operator << (ostream & out, const Clown & op)
{
    if(!op.guest_name) {
        OPERATOR_ERROR e;
        throw e;
    }
    op.display();
    return out;
}
/************************ PROTECTED *******************************/
/* auto set user fields for testing */
string& Clown::test_set(int rand)
{
    theme_choice = themes.at((rand+1)%3);    
    return theme_choice;
} 

/******************************************************************
************************  MARGARITA  ******************************
******************************************************************/
/* DATA MEMBERS: char* event_name  
                 multimap of tequilas by price 
*/
Margarita::Margarita() :Reserve(), event_name(nullptr) {}

Margarita::Margarita(const Reserve & reserve, const char* event,
                     const multimap<float,string> & in_tequilas,
                     const float price) 
          :Reserve(reserve), tequilas(in_tequilas) {
           unit_cost = price; //already init to 0 in res
           event_name = new char[strlen(event)+1];
           strcpy(event_name, event);
}

Margarita::Margarita(const Margarita & src) 
          :Reserve(src), tequilas(src.tequilas) {
    unit_cost = src.unit_cost; //already init to 0 in res
    event_name = new char[strlen(src.event_name)+1];
    strcpy(event_name, src.event_name);
}

Margarita::~Margarita()
{ if(event_name) delete [] event_name; }

int Margarita::display_tequilas() const
{    
    int n{1};
    if(!tequilas.empty())
    {
        cout <<"\n============ ¡Featured Tequilas! ============="
         <<"\n==============================================\n";
    for(auto elem: tequilas)
    {
        cout <<n<<")\t$"<< elem.first <<"\t"<< elem.second <<endl;
        ++n; 
    }cout <<"\n==============================================\n";
    }return n-1;
}

int Margarita::choose_tequila()
{
    cout <<"Would you like to reserve a tequila?"
         <<"\tEnter 1 for yes 0 for no";
    int answer = h.answer(0,1);
    if(answer == 1 && display_tequilas())
    {
        cout << "Enter your chosen tequila by number";
        //answer = h.answer(1,
    }
    return 0;
}

bool Margarita::display() const
{
    if(Reserve::display())
        return display_tequilas();
    return 0;
}

void Margarita::operator =(const Margarita & op2)
{
    //(if !op2.event_name) //EXCPETION////////////////
    Reserve::operator=(op2);

    if(event_name) delete [] event_name;
    event_name = new char[strlen(op2.event_name)+1];
    strcpy(event_name, op2.event_name);
    tequilas = op2.tequilas;
}

ostream& operator << (ostream& out, const Margarita& op)
{
    op.display();
    return out;
}
/******************************************************************
*************************  THEATRE  *******************************
******************************************************************/
Theater::Theater() :Reserve(), event_name(nullptr) {}

Theater::Theater(const Reserve & reserve, const char* event,
                 const float price, const Play & in_play)
        :Reserve(reserve), play(in_play) {
        unit_cost = price; //already init to 0 in res
        event_name = new char[strlen(event)+1];
        strcpy(event_name, event);
}

Theater::Theater(const Theater & src) :Reserve(src), play(src.play)
{
    unit_cost = src.unit_cost; //already init to 0 in res
    event_name = new char[strlen(src.event_name)+1];
    strcpy(event_name, src.event_name);
}

Theater::~Theater()
{ if(event_name) delete [] event_name; }


bool Theater::display() const
{
    if(Reserve::display()) {
        cout <<"Programs: "<< programs;
        return play.view_cast();
    }return 0;
}

void Theater::operator = (const Theater & op2)
{
    Reserve::operator=(op2);
    if(event_name)
        delete [] event_name;
    event_name = new char[strlen(op2.event_name)+1];
    strcpy(event_name,op2.event_name);
    play = op2.play;
    programs = op2.programs;
}

ostream& operator << (ostream& out,const Theater & op)
{
    op.display();
    return out;
}
