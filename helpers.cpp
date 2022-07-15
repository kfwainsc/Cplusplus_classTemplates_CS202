/* helpers.cpp */
/******************************************************************
**  Kendra Wainscott           CS202                spring 2022  **
**                             Prog#2                            **
******************************************************************/
#include "helpers.h"
using namespace std;
#define MAX_STR 200

/******************************************************************
*******************  HELPER FUNCTIONS *****************************
******************************************************************/
int Helper::answer(int min, int max) const
{
    int answer {0};
    cout <<"ANSWER: ";
    cin  >> answer;
    cin.ignore(100, '\n');
    if(answer > max || answer < min) return 0;
    return answer; 
}

bool Helper::name(char* & in_name) const
{
    string input = "none";
    cout <<"Enter reservation holder's name\nANSWER: ";
    cin  >> input; 

    if(in_name) delete [] in_name;
    in_name = new char [strlen(input.c_str())+1];
    strcpy(in_name, input.c_str());
    return true;
}

int Helper::num_ppl(int min, int max) const
{
    cout <<"Enter the number of people in your party\n";
    return answer(min,max);
}

bool Helper::current_dt(array<int,5> & date_time)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    date_time.at(0) = (1900 + ltm->tm_year);
    date_time.at(1) = (1 + ltm->tm_mon);
    date_time.at(2) = (ltm->tm_mday);
    date_time.at(3) = (ltm->tm_hour);
    date_time.at(4) = (ltm->tm_min);
    return 1; 
}

bool Helper::print_dt(const array<int,5> & date_time) const
{    //Format:  Month/Day/Year 
    cout <<"Date: "<< date_time.at(1) <<"/" << date_time.at(2)
         <<"/"<< date_time.at(0) <<"\tTime: "
         << date_time.at(3) <<":" << date_time.at(4);
    if(date_time.at(4) < 10) cout << "0"; //:00 format
    return 1; 
}
/*****************************************************************
***********************  GENERAL  ********************************
******************************************************************/
bool print_banner()
{
    for(int i=0; i<2; ++i){
    cout<<"***************************************************"
        <<"*******************************"<<endl;}
    cout<<"**************************  RESERVATION DATABASE "
        <<" ********************************"<<endl;
    for(int i=0; i<2; ++i){
    cout<<"***************************************************"
        <<"*******************************"<<endl;}
    cout<<"Please choose from the following options:"<<endl;
    return true;
}

bool main_menu()
{
    cout <<"\n1)Make a Reservation\t2)View All Reservations"
         <<"\t\t0)Quit\n";
    return 1;
}

bool reserve_menu()
{
    cout <<"\n========== Availible Reservation Types ============" 
         <<"\n1)Booking a Clown\n2)Margatrita Festival Tickets"
         <<"\n3)Theatre Performance\n4)Main Menu\n0)Quit\n";
    return 1;
}
