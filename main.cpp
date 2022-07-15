/* main.cpp */
/******************************************************************
**  Kendra Wainscott           CS202                spring 2022  **
**                             Prog#2                            **
******************************************************************/
#include <iostream>
#include <fstream>
#include <array>
#include <time.h>
#include "reservations.h"
#include "lists.h"
#include "lists.tpp"
#include "helpers.h"
#include "other.h"

using namespace std;
//file input MAX variables
#define MAX_IN 1000
#define MAX_P 13
#define NUM_EVENTS 3
#define NUM_THEMES 3

//exception variables 
FILE_ERROR file_error;
BAD_INPUT input_error;
DISPLAY_ERROR display_error;

int main(int argc, char** argv)
{
    // input to fstream & error check 
    if(argc != 2) throw file_error;
    char* datafile = argv[1];
    ifstream inDatafile(datafile);
    if(!inDatafile) throw file_error;
    srand(time(0)); //seed rand num

    //3 DLL to hold all reservations 
    DLL<Clown> clown_list;
    DLL<Margarita> margarita_list;
    DLL<Theater> theater_list;

    //temp data structures for input 
    array<string,NUM_THEMES> c_themes; 
    multimap<float,string> tequila_list;
    map <string,string> cast_list;
    
    //input variables
    char* event = new char[MAX_IN];
    char* name = new char[MAX_IN];
    string str1{"none"}, str2{"none"};
    int party{0}, cycle{NUM_EVENTS}, index{0};
    float price{0};

    //build reservation input base for testing
    while(inDatafile && (inDatafile.peek() != '%'))
    {    //read in clown themes 
        getline(inDatafile,str1);
        if(index < THEME)
        c_themes.at(index) = str1;
        ++index;
    }
    inDatafile.ignore(100, '\n');
    index = 0;
    while(inDatafile && (inDatafile.peek() != '$'))
    {    //read in tequila list
        getline(inDatafile,str1);
        getline(inDatafile,str2);
        price = stof(str2);
        tequila_list.insert(pair<float,string>(price,str1));
    }
    inDatafile.ignore(100, '\n');
    while(inDatafile && (inDatafile.peek() != '@'))
    {    //read in cast list 
        getline(inDatafile,str1);
        getline(inDatafile,str2);
        cast_list.insert({str1, str2,}); //{search key,item}
    }
    inDatafile.ignore(100, '\n');
    //UNIQUE POINTER to a play object for theatre reservations 
    unique_ptr<Play> 
    play(new Play("Street Car","Tennessee Williams",cast_list));

    // read in names & make random reservations
    while(inDatafile && (inDatafile.peek() != '#'))
    {
        inDatafile.getline(name,MAX_IN);
        party = (rand() % MAX_P)+1;    
        //create new reservation obj to init events
        Reserve* reserve = new Reserve(name,party);
        price = (rand() % MAX_P)+1;
        if(cycle % NUM_EVENTS == 0)
        {
        strcpy(event,"Clown Booking");    
        Clown* clown = new Clown(*reserve, event, c_themes, price);
        clown_list.add(*clown);
        if(clown) delete clown;
    }    
    else if(cycle % NUM_EVENTS == 1)
    {
        strcpy(event,"Margarita Festival");    
        Margarita* marg = new Margarita(*reserve, event, 
                                        tequila_list, price);
        margarita_list.add(*marg);
        if(marg) delete marg;
    }else
    {
        strcpy(event,"Theater Performance");    
        Theater* theater = new Theater(*reserve, event, price,*play);
        theater_list.add(*theater);
        if(theater) delete theater;
    }
    ++ cycle;
    if(reserve) delete reserve;
    }//end file loop

    //close file stream & release input variables 
    inDatafile.close();     
    if(event) delete [] event;
    if(name) delete [] name;

    Helper h; //handles user input
    int menu {-1};
    bool done {false};

    if(!print_banner()) throw display_error;
    
    while (!done)
    {
    main_menu();
    menu = h.answer(0,2);

    if(menu == 0) done = true; 
    
    else if(menu == 1)//make a reservation 
    {//get user input for name & party num
        name = new char[MAX_IN]; 
        if(!h.name(name)) throw input_error; 
        Reserve* res = new Reserve(name, h.num_ppl(0,MAX_P));

        int choice {-1}, confirmed{0};
        price = (rand() % MAX_P)+1;
        event = new char[MAX_IN];

        while(choice != 0)//make mult res under this name 
        {
        reserve_menu(); //pick a type of reservaton 
        choice = h.answer(0,4);
        if(choice == 1)//CLOWN
        {
        cout << "\nCLOWN BOOKING!\n";
        strcpy(event,"Clown Booking");    
        Clown* clown = new Clown(*res, event, c_themes, price);
        clown->choose_theme();
        confirmed = clown_list.add(*clown);
        if(clown) delete clown;
        }
        else if(choice == 2) // MARGARITA
        {
        cout << "\nMARGARITA FESTIVAL!\n";
        strcpy(event,"Margarita Festival");    
        Margarita* marg = new Margarita(*res, event,
                                        tequila_list, price);
        confirmed = margarita_list.add(*marg);
        if(marg) delete marg;
        }
        else if(choice == 3) // MARGARITA
        {
        cout << "\nTHEATRE TICKETS!\n";
        strcpy(event,"Theater Performance");
        cout <<"(0 Confirm\t(1 View cast list\t(2 Search the cast list?\n";
        int answer = h.answer(0,2);
        if(answer == 1) 
            play->view_cast();
        else if(answer == 2) {
            string role {"none"};
            cout <<"Role to search by:" <<endl;
            cin  >> role;
            cout << play->search_cast_list(role);
        }
        Theater* theater = new Theater(*res, event, price,*play);
        confirmed = theater_list.add(*theater);
        if(theater) delete theater; 
        }
        else if(choice == 0) // Exit program
        { done = true; }
        else
        { 
        choice = 0;//default back to main menu
        }
        if(confirmed && choice > 0) {
            cout <<"\nReservation Made.\nMake another "
                 <<"reservation for "<< name <<"?\n";
        }
        }// end choice != 0 loop 

        delete res;//allow for new reservation name 
        if(name) delete [] name;
        if(event) delete [] event;
    }//end menu == 1

    else if(menu == 2) //display all exisiting reservations 
    {
        clown_list.display_list();
        margarita_list.display_list();
        //theater_list.display_list();
    }
    }//end while !done

    return 0;
}

